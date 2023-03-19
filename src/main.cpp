// program to suggest autocomplete words as user types
// words are from usr/share/dict/words
// words are stored in a trie

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>
#include <trie.hpp>
#include <spdlog/sinks/basic_file_sink.h>

// read words from file
std::vector<std::string> readWords(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<std::string> words;
    std::string word;
    while (file >> word) {
        words.push_back(word);
    }
    return words;
}

std::shared_ptr<spdlog::logger> make_logger(spdlog::level::level_enum level) noexcept {
    try {
        //current time
        auto now = std::chrono::system_clock::now();
        auto logger = spdlog::basic_logger_mt("foresight", "logs/" + std::to_string(now.time_since_epoch().count()) + ".log");
        logger->set_level(level);
        return logger;
    }
    catch (const spdlog::spdlog_ex& ex) {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return nullptr;
    }
}


// main
int main() {

    static auto logger = make_logger(spdlog::level::info);

    auto words = readWords("/usr/share/dict/words");
    f7t::Trie trie;
    for (auto& word : words) {
        trie.insert(word);
    }

    // Set terminal to raw mode 
    system("stty raw");
    // disable echo
    system("stty -echo");
    char c;
    std::cout << "> ";

    while (std::cin.get(c))
    {
        static std::string word;
        static std::string last_suggestion = "";
        static int choice = 0;

        // if ctrl-c is pressed, reset terminal to cooked mode
        if (c == 3)
        {
            logger->info("ctrl-c pressed");
            system("stty cooked");
            break;
        }
        else if (c == ' ')
        {
            word = "";
            last_suggestion = "";
            std::cout << ' ';
        }
        // tab pressed 
        else if (c == 9)
        {
            if (last_suggestion.empty())
            {
                // alarm if no suggestion
                std::cout << "\a";
                logger->info("no suggestion");
                continue;
            }
            // replace the word with the suggestion
            for (size_t i = 0; i < word.size(); i++) {
                std::cout << "\b";
            }
            word = last_suggestion;
            // print the word in white
            std::cout << "\033[1;37m" << word << "\033[0m";
        }
        // backspace
        else if (c == 127)
        {
            if (word.empty())
            {
                continue;
            }
            // delete the last char
            std::cout << '\b';
            word.pop_back();
            // delete till eol
            std::cout << "\033[K";
        }
        else
        {
            // delete until the end of line (right of cursor)
            std::cout << "\033[K";
            // ctrl + p pressed
            if (c == 16)
            {
                logger->info("ctrl-p pressed");
                choice--;
            }
            // ctrl + n pressed
            else if (c == 14)
            {
                logger->info("ctrl-n pressed");
                choice++;
            }
            else {
                // clear the word and reprint it
                for (size_t i = 0; i < word.size(); i++) {
                    std::cout << "\b";
                }
                word += c;
                std::cout << "\033[1;37m" << word << "\033[0m";
            }

            auto suggestions = trie.suggest(word);
            // print the remaining chars of the longest suggestion
            if (!suggestions.empty()) {
                logger->info("for " + word + " suggestions count: " + std::to_string(suggestions.size()));
                last_suggestion = suggestions[choice % suggestions.size()];
                // print the word in white and remaining chars in grey
                std::cout << "\033[1;30m" << last_suggestion.substr(word.size()) << "\033[0m";
                for (size_t i = 0; i < last_suggestion.size() - word.size(); i++) {
                    std::cout << "\b";
                }
            }
            else {
                logger->info("no suggestions after " + word);
                last_suggestion = "";
                // clear until next word
                std::cout << "\033[K";
            }
        }
    }
    return 0;
}