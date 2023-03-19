#include <trie.hpp>

namespace f7t {
    // insert word into trie
    void Trie::insert(const std::string& word) {
        insert(root, word, 0);
    }

    // insert word into trie
    void Trie::insert(std::shared_ptr<TrieNode> node, const std::string& word, size_t i) {
        if (i == word.size()) {
            node->isWord = true;
            return;
        }
        for (auto& child : node->children) {
            if (child->c == word[i]) {
                insert(child, word, i + 1);
                return;
            }
        }
        auto child = std::make_shared<TrieNode>(word[i]);
        node->children.push_back(child);
        insert(child, word, i + 1);
    }

    // suggest words that start with word
    std::vector<std::string> Trie::suggest(const std::string& word) {
        std::vector<std::string> suggestions;
        auto node = root;
        for (size_t i = 0; i < word.size(); i++) {
            for (auto& child : node->children) {
                if (child->c == word[i]) {
                    node = child;
                    break;
                }
            }
        }
        suggest(node, word, suggestions);
        return suggestions;
    }

    // suggest words that start with word
    void Trie::suggest(std::shared_ptr<TrieNode> node, const std::string& word, std::vector<std::string>& suggestions) {
        if (node->isWord) {
            suggestions.push_back(word);
        }
        for (auto& child : node->children) {
            suggest(child, word + child->c, suggestions);
        }
    }
}