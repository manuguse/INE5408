#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

#include "trie.cpp"

using namespace std;

bool debug = true;


bool addToTrie(string filename, Trie* trie) {
    
    ifstream file;
    string word;

    file.open(filename);
    if (!file.is_open()) {
        cout << "file not found" << endl;
        return false;
    }

    string line;
    int position = 0;


    int start = 1;
    while (getline(file, line)) {
        size_t start = line.find('[') + 1;
        size_t end = line.find(']');
        word = line.substr(start, end - start);
        trie->insert(word, position, line.length());
        position += line.length() + 1;
    }

    file.close();
    return true;
}

void verify(string word, Trie *trie) {
    TrieNode* curent = trie->countPrefixes(word);
        if (curent == nullptr) {
            cout << word << " is not prefix" << endl;
        } else {
            cout << word << " is prefix of " << curent->prefixes << " words" << endl;
            if (curent->length > 0) {
                cout << word << " is at (" << curent->position << ", " << curent->length << ")" << endl;
            }
        }
}

int main() {
    
    Trie trie;

    string filename;
    string word;
    ifstream file;

    if (!debug) {
        cin >> filename;  
    } else {
        filename = "dicionario1.dic";}

    if (!addToTrie(filename, &trie)) {
        return 0;
    }

    vector<string> words = {"bear", "bell", "bid", "bu", "bull", "buy", "but", "sell", "stock", "stop", "0"};
    int ct = 0;
    while (1) {  // leitura das palavras ate' encontrar "0"

        if (!debug) {
            cin >> word;

        } else {
            word = words[ct++];
        }

        if (word.compare("0") == 0) {
            break;
        }

        transform(word.begin(), word.end(), word.begin(), ::tolower);
        verify(word, &trie);
    }
    return 0;
}
