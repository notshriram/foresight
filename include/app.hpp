#pragma once
#include <trie.hpp>
#include <spdlog/spdlog.h>

namespace f7t
{
    /**
     * @brief class for application
     *
     */
    class App
    {
        bool m_shouldClose = false;
        std::shared_ptr<spdlog::logger> m_logger;
        Trie m_trie;

    public:
        /**
         * @brief Construct a new App object
         *
         * @param wordlist vector of words (vocab) - to be converted to a trie
         * @param logger logger instance
         */
        App(const std::vector<std::string> &wordlist, std::shared_ptr<spdlog::logger> logger);

        /**
         * @brief Construct a new App object
         *
         * @param wordlist vector of words (vocab) - to be converted to a trie
         * @param logger logger instance
         */
        App(std::vector<std::string> &&wordlist, std::shared_ptr<spdlog::logger> logger);

        /**
         * @brief says if the app should be closed or not
         * flagged as [nodiscard] so the returned value must be used
         *
         * @return a boolean value indicating whether the app should close or not
         */
        [[nodiscard]] bool shouldClose() const;

        /**
         * @brief starts the application
         *
         */
        void poll();

        /// @brief Destroy the app instance
        ~App();
    };
}