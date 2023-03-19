#include <app.hpp>
#include <iostream>
#include <cstdlib>

namespace termcolor {
    const std::string red = "\033[1;31m";
    const std::string green = "\033[1;32m";
    const std::string yellow = "\033[1;33m";
    const std::string blue = "\033[1;34m";
    const std::string magenta = "\033[1;35m";
    const std::string cyan = "\033[1;36m";
    const std::string white = "\033[1;37m";
    const std::string reset = "\033[0m";
    const std::string bold = "\033[1m";
    const std::string dim = "\033[2m";
    const std::string underline = "\033[4m";
    const std::string blink = "\033[5m";
    const std::string reverse = "\033[7m";
    const std::string concealed = "\033[8m";
}

namespace f7t {

    void erase_till_eol() {
        std::cout << "\033[K";
    }

    void erase_word(size_t word_size) {
        for (size_t i = 0; i < word_size; i++) {
            std::cout << '\b';
        }
    }

    void init_terminal() {
        /* static cast to discard these return values and fix warnings */
        // Set terminal to raw mode 
        static_cast<void>(std::system("stty raw"));
        // disable echo
        static_cast<void>(std::system("stty -echo"));
        // print prompt
        std::cout << "> ";
    }

    App::App(const std::vector<std::string>& wordlist, std::shared_ptr<spdlog::logger> logger): m_logger(logger) {
        for (auto& word : wordlist) {
            m_trie.insert(word);
        }
        init_terminal();
    }

    App::App(std::vector<std::string>&& wordlist, std::shared_ptr<spdlog::logger> logger): m_logger(logger) {
        for (auto& word : wordlist) {
            m_trie.insert(word);
        }
        init_terminal();
    }

    [[nodiscard]]
    bool App::shouldClose() const {
        return m_shouldClose;
    }

    void App::poll() {
        char c;
        std::cin.get(c);
        static std::string word;
        static std::string last_suggestion = "";
        static int choice = 0;

        // if ctrl-c or ctrl-d is pressed, reset terminal to cooked mode
        if (c == 3 || c == 4)
        {
            m_logger->info("ctrl-c or ctrl-d pressed");
            m_shouldClose = true;
            return;
        }
        else if (c == ' ')
        {
            word = "";
            last_suggestion = "";
            std::cout << ' ';
            erase_till_eol();
        }
        // tab pressed 
        else if (c == 9)
        {
            if (last_suggestion.empty())
            {
                // alarm if no suggestion
                std::cout << "\a";
                m_logger->info("no suggestion");
                return;
            }

            word = last_suggestion;
            std::cout << word;
        }
        // backspace
        else if (c == 127)
        {
            if (word.empty())
            {
                return;
            }
            // delete the last char
            std::cout << '\b';
            word.pop_back();
            erase_till_eol();
        }
        else
        {
            erase_till_eol();
            // ctrl + p pressed
            if (c == 16)
            {
                m_logger->info("ctrl-p pressed");
                choice--;
            }
            // ctrl + n pressed
            else if (c == 14)
            {
                m_logger->info("ctrl-n pressed");
                choice++;
            }
            else {
                // clear the word and reprint it
                erase_word(word.size());
                word += c;
                std::cout << word;
            }

            auto suggestions = m_trie.suggest(word);
            // print the remaining chars of the longest suggestion
            if (!suggestions.empty()) {
                m_logger->info("for " + word + " suggestions count: " + std::to_string(suggestions.size()));
                last_suggestion = suggestions[choice % suggestions.size()];
                // print the remaining chars (dimmed)
                std::cout << termcolor::dim << last_suggestion.substr(word.size()) << termcolor::reset;
                for (size_t i = 0; i < last_suggestion.size() - word.size(); i++) {
                    std::cout << "\b";
                }
            }
            else {
                m_logger->info("no suggestions after " + word);
                last_suggestion = "";
                erase_till_eol();
            }
        }
    }

    App::~App() {
        // reset terminal to cooked mode
        static_cast<void>(std::system("stty cooked"));
        // enable echo
        static_cast<void>(std::system("stty echo"));
        /* static cast to discard these return values and fix warnings */
    }
}
