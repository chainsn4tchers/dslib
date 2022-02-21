#ifndef _BINTREE_H_
#define _BINTREE_H_

#include <stack>
#include <queue>
#include <vector>
#include <memory>
#include <algorithm>

template <typename T>
class BSTree {
private:
	struct TreeNode {
		T data_;
		std::shared_ptr<TreeNode> lchild_;
		std::shared_ptr<TreeNode> rchild_;
		TreeNode(T d)
			: data_(d)
			, lchild_(nullptr)
			, rchild_(nullptr)
		{ }
	};
	size_t nodes_;
	std::shared_ptr<TreeNode> root_;
	std::shared_ptr<TreeNode> getRoot() const { return root_; }

protected:
	size_t height(std::shared_ptr<TreeNode> r) const;

public:
	BSTree();
	BSTree(const T& data);
	BSTree(const T&& data);
	BSTree(const std::vector<T>& nodes);

	void insert(const T& value);
	void insert(const T&& value);

	inline size_t getHeight() const;
	inline size_t totalNodes() const;

	std::vector<T> getInOrder() const;
	std::vector<T> getPreOrder() const;
	std::vector<T> getPostOrder() const;
	std::vector<T> getLevelOrder() const;

	void insert(const std::vector<T>& nodes);
};

/* impl */
/* protected */
template <typename T>
size_t BSTree<T>::height(std::shared_ptr<TreeNode> r) const
{
	if (!r) return 0;
	return 1 + std::max(height(r->lchild_), height(r->rchild_));
}

/* constructors */
template <typename T>
BSTree<T>::BSTree()
	: root_(nullptr)
	, nodes_(0)
{ }

template <typename T>
BSTree<T>::BSTree(const T& data)
	: root_(std::make_shared<TreeNode>(data))
	, nodes_(1)
{ }

template <typename T>
BSTree<T>::BSTree(const T&& data)
	: root_(std::make_shared<TreeNode>(data))
	, nodes_(1)
{ }

template <typename T>
BSTree<T>::BSTree(const std::vector<T>& nodes)
{
	for (int i = 0; i < nodes.size(); ++i)
		insert(nodes[i]);
}

/* public */
template <typename T>
void BSTree<T>::insert(const T& value)
{
	if (!root_)
	{
		root_ = std::make_shared<TreeNode>(value);
		nodes_ = 1;
		return;
	}
	std::shared_ptr<TreeNode> tmp = root_, prev = tmp;

	while (tmp)
	{
		prev = tmp;
		if (tmp->data_ < value)
			tmp = tmp->rchild_;
		else
			tmp = tmp->lchild_;
	}

	if (prev->data_ < value)
		prev->rchild_ = std::make_shared<TreeNode>(value);
	else
		prev->lchild_ = std::make_shared<TreeNode>(value);

	++nodes_;
}

template <typename T>
void BSTree<T>::insert(const T&& value)
{
	if (!root_)
	{
		root_ = std::make_shared<TreeNode>(value);
		return;
	}
	std::shared_ptr<TreeNode> tmp = root_, prev = tmp;

	while (tmp)
	{
		prev = tmp;
		if (tmp->data_ < value)
			tmp = tmp->rchild_;
		else
			tmp = tmp->lchild_;
	}

	if (prev->data_ < value)
		prev->rchild_ = std::make_shared<TreeNode>(value);
	else
		prev->lchild_ = std::make_shared<TreeNode>(value);

	++nodes_;
}

template <typename T>
inline size_t BSTree<T>::getHeight() const
{
	return height(root_);
}

template <typename T>
inline size_t BSTree<T>::totalNodes() const
{
	return nodes_;
}

template <typename T>
std::vector<T> BSTree<T>::getInOrder() const
{
	auto tmp = root_;
	std::vector<T> res;
	std::stack<std::shared_ptr<TreeNode>> st;

	while (!st.empty() || tmp)
	{
		if (tmp)
		{
			st.push(tmp);
			tmp = tmp->lchild_;
			continue;
		}
		if (!st.empty())
		{
			res.push_back(st.top()->data_);
			tmp = st.top()->rchild_;
			st.pop();
		}
	}

	return res;
}

template <typename T>
std::vector<T> BSTree<T>::getPreOrder() const
{
	auto tmp = root_;
	std::vector<T> res;
	std::stack<std::shared_ptr<TreeNode>> st;

	while (!st.empty() || tmp)
	{
		if (tmp)
		{
			res.push_back(tmp->data_);
			st.push(tmp);
			tmp = tmp->lchild_;
			continue;
		}
		if (!st.empty())
		{
			tmp = st.top()->rchild_;
			st.pop();
		}
	}

	return res;
}

template <typename T>
std::vector<T> BSTree<T>::getPostOrder() const
{
	auto tmp = root_;
	std::stack<std::shared_ptr<TreeNode>> st;
	std::vector<T> res;

	while (!st.empty() || tmp)
	{
		if (tmp)
		{
			res.push_back(tmp->data_);
			st.push(tmp);
			tmp = tmp->rchild_;
			continue;
		}
		if (!st.empty())
		{
			tmp = st.top()->lchild_;
			st.pop();
		}
	}

	std::reverse(res.begin(), res.end());
	return res;
}

template <typename T>
std::vector<T> BSTree<T>::getLevelOrder() const
{
	if (!root_) return {};

	std::vector<T> res;
	std::shared_ptr<TreeNode> tmp = nullptr;
	std::queue<std::shared_ptr<TreeNode>> q;
	q.push(root_);

	while (!q.empty())
	{
		tmp = q.front();
		q.pop();
		res.push_back(tmp->data_);
		if (tmp->lchild_) q.push(tmp->lchild_);
		if (tmp->rchild_) q.push(tmp->rchild_);
	}

	return res;
}

#endif /* _BINTREE_H_ */
