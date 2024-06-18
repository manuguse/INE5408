#include <iostream>
#include "trie_node.cpp"
#include "constants.h"

class Trie {

    private:
        TrieNode* root;

    public:

        Trie() {
            root = new TrieNode();
        }

        ~Trie() {
            deleteTrie(root);
        }

        void deleteTrie(TrieNode* root) {
            for (int i = 0; i < ALPHABET_LENGTH; i++) {
                delete root->children[i];
            }
        }

        void insert(string word, int position, int length) {
            TrieNode* current = root;
            for (int i = 0; i < word.length(); i++) {
                int index = tolower(word[i]) - 'a';
                if (current->children[index] == nullptr) {
                    current->children[index] = new TrieNode();
                }
                current = current->children[index];
                current->prefixes++;
            }
            current->position = position;
            current->length = length;
        }

        TrieNode* countPrefixes(string word) {
            TrieNode* current = root;
            for (int i = 0; i < word.length(); i++) {
                int index = tolower(word[i]) - 'a';
                if (current->children[index] == nullptr) {
                    return nullptr;
                }
                current = current->children[index];
            }
            return current;
        }

};