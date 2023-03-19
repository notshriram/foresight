#pragma once
#include <vector>
#include <memory>
#include <string>

namespace f7t {
    // trie node
    struct TrieNode {
        char c;
        bool isWord;
        std::vector<std::shared_ptr<TrieNode>> children;
        TrieNode(char c): c(c), isWord(false) {}
    };

    // trie
    class Trie {
        std::shared_ptr<TrieNode> root;
        void insert(std::shared_ptr<TrieNode> node, const std::string& word, size_t i);
        void suggest(std::shared_ptr<TrieNode> node, const std::string& word, std::vector<std::string>& suggestions);
    public:
        Trie(): root(std::make_shared<TrieNode>(' ')) {}
        void insert(const std::string& word);
        std::vector<std::string> suggest(const std::string& word);
    };
}