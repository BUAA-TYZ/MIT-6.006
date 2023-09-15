#ifndef AVL_H
#define AVL_H

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <initializer_list>

class AVLTree;
class AVLNode {
	friend class AVLTree;
public:
  explicit AVLNode(int data): data_(data) {}

	void update_height() {
		height_ = 1 + std::max((right_ ? right_->height_ : -1), (left_ ? left_->height_ : -1));
	}

	int32_t skew() {
		return (right_ ? right_->height_ : -1) - (left_ ? left_->height_ : -1); 
	}

	AVLNode* subtree_first(); 
	AVLNode* subtree_last();

	/** Return the predecessor of this node. */
	AVLNode* predecessor();
	AVLNode* successor();

	AVLNode* find(int data);

	/** rotate towawrds left, which means scew of node is 2.
	 *    A              C
	 *  B   C			=>   A   E
	 *     D E			  B D
	 * {B,A,D,C,E}=>{B,A,D,C,E}
	 */
	void left_rotation();
	void right_rotation();

	void rebalance();
	void maintain();

	void insert_before(AVLNode *insert_node);
	void insert_after(AVLNode *insert_node);
	/** Not support replicated key. */
	void subtree_insert(AVLNode *insert_node);

	/******************************
	 * Test Functions
	 *****************************/
	int32_t height() {
		return height_;
	}

	bool checkchild(AVLNode *left, AVLNode *right) {
		return left_ == left && right_ == right;
	}

private:
  /** TODO: change it to general*/
  int data_{0};

  int32_t height_{0};
  AVLNode *parent_{nullptr};
  AVLNode *left_{nullptr};
  AVLNode *right_{nullptr};
};
class AVLTree {
public:
	AVLTree() = default;
	void build(std::initializer_list<int> data_set) {
		for(const auto &data: data_set) {
			insert(data);
			update_root();
		}
	}

	AVLNode* find(int x) {
		if (!root)
			return nullptr;
		return root->find(x);
	}

	void insert(int x) {
		AVLNode *new_node = new AVLNode(x);
		if (root == nullptr) {
			root = new_node;
			return;
		}
		root->subtree_insert(new_node);
		update_root();
	}

	/******************************
	 * Test Functions
	 *****************************/
	int32_t height() {
		return root->height_;
	}

	~AVLTree() {
		DeleteAllNode(root);
	}
private:
	AVLNode *root{nullptr};

	/** When in a rotation, the root maybe go down. */
	void update_root() {
		while (root->parent_) {
			root = root->parent_;
		}
	}

	void DeleteAllNode(AVLNode *cur) {
		if (!cur) return;
		if (cur->left_) DeleteAllNode(cur->left_);
		if (cur->right_) DeleteAllNode(cur->right_);
		delete cur;
	}
};

#endif