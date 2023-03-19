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
        App(std::vector<std::string> &&wordlist, std::shared_ptr<spdlog::logger> logger);
        [[nodiscard]] bool shouldClose() const;
        void poll();
        ~App();
    };
}