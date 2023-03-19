#pragma once
#include <trie.hpp>
#include <spdlog/spdlog.h>

namespace f7t {
    class App {
        bool m_shouldClose = false;
        std::shared_ptr<spdlog::logger> m_logger;
        Trie m_trie;
    public:
        App(const std::vector<std::string>& wordlist, std::shared_ptr<spdlog::logger> logger);
        App(std::vector<std::string>&& wordlist, std::shared_ptr<spdlog::logger> logger);
        [[nodiscard]] bool shouldClose() const;
        void poll();
        ~App();
    };
}