#include <iostream>
#include <string>
#include <vector>
using namespace std;

class TrieNode {
public:
    vector<TrieNode*> children;
    bool isEndOfSuffix;
    int suffixIndex;

    TrieNode() {
        children.assign(256, nullptr);
        isEndOfSuffix = false;
        suffixIndex = -1;
    }
};

class SuffixTrie {
    TrieNode* root;
    string text;

public:
    SuffixTrie(string s) {
        text = s + "$";
        root = new TrieNode();
        buildBruteForceSuffixTrie();
    }

    void buildBruteForceSuffixTrie() {
        int n = text.length();

        for (int i = 0; i < n; i++) {
            TrieNode* current = root;

            for (int j = i; j < n; j++) {
                char ch = text[j];

                if (current->children[ch] == nullptr) {
                    current->children[ch] = new TrieNode();
                }

                current = current->children[ch];
            }

            current->isEndOfSuffix = true;
            current->suffixIndex = i;
        }
    }

    bool search(string pattern) {
        TrieNode* current = root;

        for (char ch : pattern) {
            if (current->children[ch] == nullptr)
                return false;
            current = current->children[ch];
        }

        return true;
    }

    void printSuffixes(TrieNode* node, string prefix) {
        if (node->isEndOfSuffix) {
            cout << "Suffix starting at index " << node->suffixIndex
                 << ": " << prefix << endl;
        }

        for (int i = 0; i < 256; i++) {
            if (node->children[i] != nullptr) {
                printSuffixes(node->children[i], prefix + (char)i);
            }
        }
    }

    void displayAllSuffixes() {
        cout << "All suffixes in trie:\n";
        printSuffixes(root, "");
    }
};

int main() {
    string text;
    cout << "Enter text: ";
    getline(cin, text);

    SuffixTrie trie(text);

    cout << "\nBuilding suffix trie...\n";
    trie.displayAllSuffixes();

    string pattern;
    cout << "\nEnter pattern to search: ";
    getline(cin, pattern);

    if (trie.search(pattern))
        cout << "Pattern '" << pattern << "' found in text" << endl;
    else
        cout << "Pattern '" << pattern << "' not found in text" << endl;

    return 0;
}
