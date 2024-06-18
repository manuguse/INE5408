#include <iostream>
#include "constants.h"

using namespace std;

class TrieNode {

    public:
        TrieNode* children[ALPHABET_LENGTH];
        int length, position, prefixes;

        TrieNode() {
            for (int i = 0; i < ALPHABET_LENGTH; i++) {
                children[i] = nullptr;
            }
            length = 0;
            position = 0;
            prefixes = 0;
        }

        ~TrieNode() {};

};
