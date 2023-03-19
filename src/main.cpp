/**
 * @file main.cpp
 * @author Shriram R
 * @brief program to suggest autocomplete words as user types
 * words are from usr/share/dict/words
 * words are stored in a trie
 * @date 2023-03-19
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
#include <chrono>
#include <trie.hpp>
#include <app.hpp>
#include <spdlog/sinks/basic_file_sink.h>

/**
 * @brief read words from file
 *
 * @param filename file name that contains the words
 * @return vector of words from the file
 */
std::vector<std::string> readWords(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<std::string> words;
    std::string word;
    while (file >> word)
    {
        words.push_back(word);
    }
    return words;
}

/**
 * @brief instantiates a logger
 *
 * @param level log level
 * @return shared_ptr to logger instance
 * @exceptsafe
 */
std::shared_ptr<spdlog::logger> make_logger(spdlog::level::level_enum level) noexcept
{
    try
    {
        // current time
        auto now = std::chrono::system_clock::now();
        auto logger = spdlog::basic_logger_mt("foresight", "logs/" + std::to_string(now.time_since_epoch().count()) + ".log");
        logger->set_level(level);
        return logger;
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return nullptr;
    }
}

/// @brief main function
int main()
{

    static auto logger = make_logger(spdlog::level::info);

    std::vector<std::string> words = readWords("/usr/share/dict/words");

    std::unique_ptr<f7t::App> app = std::make_unique<f7t::App>(std::move(words), logger);

    while (!app->shouldClose())
    {
        app->poll();
    }

    return 0;
}