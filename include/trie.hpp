/**
 * @file trie.hpp
 * @author Shriram R
 * @brief header file for trie
 * @date 2023-03-19
 *
 */
#pragma once
#include <vector>
#include <memory>
#include <string>

 /**
  * @brief namespace for foresight,
  * contains a struct for trie node and a class for trie data structure
  *
  */
namespace f7t
{
    /**
     * @brief struct for trie node
     *
     */
    struct TrieNode
    {
        char c;
        bool isWord;
        std::vector<std::shared_ptr<TrieNode>> children;

        /**
         * @brief Construct a new Trie Node object
         *
         * @param c character to be stored in the node
         */
        TrieNode(char c): c(c), isWord(false) {}
    };

    /**
     * @brief class for trie data structure
     *
     */
    class Trie
    {
        std::shared_ptr<TrieNode> root;

        /**
         * @brief insert word into trie node
         *
         * @param node trie node
         * @param word word to be inserted
         * @param i index of word
         */
        void insert(std::shared_ptr<TrieNode> node, const std::string& word, size_t i);

        /**
         * @brief suggest words that start with word
         *
         * @param node trie node
         * @param word partial word on which suggestions are to be made
         * @param suggestions vector of suggestions
         */
        void suggest(std::shared_ptr<TrieNode> node, const std::string& word, std::vector<std::string>& suggestions);

    public:
        /**
         * @brief Construct a new Trie object
         *
         */
        Trie(): root(std::make_shared<TrieNode>(' ')) {}

        /**
         * @brief insert word into trie
         *
         * @param word word to be inserted
         */
        void insert(const std::string& word);

        /**
         * @brief suggest words that start with word
         *
         * @param word partial word on which suggestions are to be made
         * @return vector of words that are suggestions for given word
         */
        std::vector<std::string> suggest(const std::string& word);
    };
}