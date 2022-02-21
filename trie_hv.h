#pragma once /* _TRIE_H_ */

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

class Trie {
private:
	struct TrieNode {
		std::unordered_map<char, std::shared_ptr<TrieNode>> children_;
		bool isWord_ = false;
	};
	size_t wordCount_;
	size_t prefixCount_;
    std::shared_ptr<TrieNode> root_;

public:
    Trie();
	Trie(const std::string& s);
	Trie(const std::string&& s);

    void insert(const std::string& s);
	void insert(const std::string&& s);
	void insert(const std::vector<std::string>& list);

    bool contains(const std::string& s) const;
	bool contains(const std::string&& s) const;
    bool hasPrefix(const std::string& s) const;
	bool hasPrefix(const std::string&& s) const;

	bool deleteWord(const std::string& s);
	bool deleteWord(const std::string&& s);

	std::string generateGraphvizOutput(const std::string& s) const;
	std::string generateGraphvizOutput(const std::string&& s) const;
	std::string generateGraphvizOutput(const std::vector<std::string>& s) const;

    ~Trie() = default;
};

/* trie.h */