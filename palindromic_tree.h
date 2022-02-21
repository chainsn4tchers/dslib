#pragma once /* _EERTREE_H_ */

#include <string>
#include <vector>
#include <iostream>

class eertree {
private:
	struct Node {
		size_t strBeg_;
		size_t strEnd_;
		size_t strLen_;
		std::string s_;
		Node* suffixLink_ptr_;
		std::vector<Node*> labeledEdges_;
	};
	size_t palinCount_;
	Node* nullRoot_ptr_;
	Node* zeroRoot_ptr_;
	Node* suffixCursor_ptr_;

	void print(const std::string& s, Node* r)
	{
		if (r != zeroRoot_ptr_ || r != nullRoot_ptr_)
		{
			for (size_t i = r->strBeg_; i <= r->strEnd_; ++i)
				std::cout << s[i];
			std::cout << '\n';
		}
		else
		{
			for (size_t i = 0; i < 26; ++i)
			{
				if (r->labeledEdges_[i])
					print(s, r->labeledEdges_[i]);
			}
		}
	}

public:
	eertree()
	{
		palinCount_ = 0;

		nullRoot_ptr_ = new Node();
		nullRoot_ptr_->suffixLink_ptr_ = nullRoot_ptr_;
		nullRoot_ptr_->strLen_ = -1;

		zeroRoot_ptr_ = new Node();
		zeroRoot_ptr_->suffixLink_ptr_ = nullRoot_ptr_;
		zeroRoot_ptr_->strLen_ = 0;
		zeroRoot_ptr_->labeledEdges_.assign(26, nullptr); // lowercase latin alphabet

		suffixCursor_ptr_ = zeroRoot_ptr_;
	}

	eertree(const std::string& s)
		: eertree()
	{
		for (size_t i = 0; i < s.size(); ++i)
			insert(i, s);
	}

	void insert(const size_t& idx, const std::string& s)
	{
		Node* curr = suffixCursor_ptr_;
		size_t letterId = s[idx] - 'a';

		while (true)
		{
			if (idx - 1 - curr->strLen_ >= 0 && s[idx - 1 - curr->strLen_] == s[idx]) break;
			curr = curr->suffixLink_ptr_;
		}

		if (curr->labeledEdges_[letterId]) return;

		//       X         label / directed edge          X'
		Node* newTmp = new Node();
		newTmp->strLen_ = curr->strLen_ + 2;
		newTmp->strBeg_ = idx - newTmp->strLen_ + 1;
		newTmp->strEnd_ = idx;
		curr->labeledEdges_[letterId] = newTmp;

		if (curr->strLen_ == -1)
		{
			newTmp->suffixLink_ptr_ = nullRoot_ptr_;
			suffixCursor_ptr_ = newTmp;
			return;
		}

		// find longest palindrome suffix for the newly inserted node X'
		curr = curr->suffixLink_ptr_;
		while (true)
		{
			if (idx - 1 - curr->strLen_ >= 0 && s[idx - 1 - curr->strLen_] == s[idx]) break;
			curr = curr->suffixLink_ptr_;
		}
		newTmp->suffixLink_ptr_ = curr->labeledEdges_[letterId];
		suffixCursor_ptr_ = newTmp;
		// if the longest palindrome suffix for the newly inserted node X' is the null root
		// instead of choosing this null root as the suffix link for X'
		// choose the zero root, as longest suffix for a non empty palindrome has at least length 0
	}

	void display(const std::string& s)
	{
		print(s, zeroRoot_ptr_);
		print(s, nullRoot_ptr_);
	}
};
