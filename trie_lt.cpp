#include <string>
using namespace std;

struct trieNode {
    bool isWord = false;
    trieNode* children[128] = {nullptr};
};

struct trie {
    int count;
    trieNode* root;

    trie()
        : count(0)
        , root(nullptr)
    { }

    void insert(string& s)
    {
        trieNode* t = root;
        for (int i = 0; i < s.size(); ++i) {
            if (!t->children[s[i]]) {
                t->children[s[i]] = new trieNode();
            }
            t = t->children[s[i]];
        }

        if (!t->isWord) {
            t->isWord = true;
            ++count;
        }
    }

    bool contains(string& s)
    {
        trieNode* t = root;
        for (int i = 0; i < s.size(); ++i) {
            if (!t->children[s[i]]) {
                return false;
            }
        }
        return true;
    }

    void remove(string& s)
    {
        trieNode* t = root;
        for (int i = 0; i < s.size(); ++i) {
            if (!t->children[s[i]]) {
                return;
            }
        }
        t->isWord = false;
    }
};
