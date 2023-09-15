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

	/******************************
	 * Search Functions
	 *****************************/
	AVLNode* subtree_first() {
		AVLNode *cur = this;
		while (cur->left_) {
			cur = cur->left_;
		}
		return cur;
	}

	AVLNode* subtree_last() {
		AVLNode *cur = this;
		while (cur->right_) {
			cur = cur->right_;
		}
		return cur;
	}

	/** Return the predecessor of this node. */
	AVLNode* predecessor() {
		AVLNode *cur = this;
		if (cur->left_) { return cur->left_->subtree_last(); }
		while (cur->parent_ && cur->parent_->left_ == cur) {
			cur = cur->parent_;
		}
		return cur->parent_;
	}

	AVLNode* successor() {
		AVLNode *cur = this;
		if (cur->right_) { return cur->right_->subtree_first(); }
		while (cur->parent_ && cur->parent_->right_ == cur) {
			cur = cur->parent_;
		}
		return cur->parent_;
	}

	AVLNode* find(int data) {
		if (data < data_) {
			if (left_) {
				return left_->find(data);
			}
		} else if (data > data_) {
			if (right_) {
				return right_->find(data);
			}
		} else {
			return this;
		}
		return nullptr;
	}

	/******************************
	 * Balance Functions
	 *****************************/

	/** rotate towawrds left, which means scew of node is 2.
	 *    A              C
	 *  B   C			=>   A   E
	 *     D E			  B D
	 * {B,A,D,C,E}=>{B,A,D,C,E}
	 */
	void left_rotation() {
		assert(right_);
		AVLNode *A = this, *B = left_, *C = right_,
						*D = right_->left_, *E = right_->right_;
		// A, C is not nullptr.
		if (A->parent_) {
			if (A->parent_->left_ == A) 
				A->parent_->left_ = C;
			else
				A->parent_->right_ = C;
		}
		C->parent_ = A->parent_;
		A->parent_ = C;
		C->left_ = A;
		A->right_ = D;
		if (D) D->parent_ = A;
		A->update_height();
		C->update_height();
	}

	void right_rotation() {
		assert(left_);
		AVLNode *A = this, *B = left_, *C = left_->left_,
						*D = left_->right_, *E = right_;
		// A, B is not nullptr.
		if (A->parent_) {
			if (A->parent_->left_ == A) 
				A->parent_->left_ = B;
			else
				A->parent_->right_ = B;
		}
		B->parent_ = A->parent_;
		A->parent_ = B;
		B->right_ = A;
		A->left_ = D;
		if (D) D->parent_ = A;
		A->update_height();
		B->update_height(); 
	}

	void rebalance() {
		if (skew() == 2) {
			if (right_->skew() < 0) 
				right_->right_rotation();
			left_rotation();
		} else if (skew() == -2) {
			if (left_->skew() > 0)
				left_->left_rotation();
			right_rotation();
		}
	}

	void maintain() {
		rebalance();
		update_height();
		if (parent_)	parent_->maintain();
	}

	/******************************
	 * Insert Functions
	 *****************************/
	void insert_before(AVLNode *insert_node) {
		assert(insert_node != nullptr);
		if (left_) {
			AVLNode *cur = nullptr;
			cur = left_->subtree_last();
			cur->right_ = insert_node;
			insert_node->parent_ = cur;
		} else {
			left_ = insert_node;
			insert_node->parent_ = this;
		}
		maintain();
	}

	void insert_after(AVLNode *insert_node) {
		assert(insert_node != nullptr);
		if (right_) {
			AVLNode *cur = nullptr;
			cur = right_->subtree_first();
			cur->left_ = insert_node;
			insert_node->parent_ = cur;
		} else {
			right_ = insert_node;
			insert_node->parent_ = this;
		}
		maintain();
	}

	/** Not support replicated key. */
	void subtree_insert(AVLNode *insert_node) {
		if (insert_node->data_ < data_) {
			if (left_)
				left_->subtree_insert(insert_node);
			else
				insert_before(insert_node);
		} else if (insert_node->data_ > data_) {
			if (right_)
				right_->subtree_insert(insert_node);
			else
				insert_after(insert_node);
		}
	}

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
			while (root->parent_) {
				root = root->parent_;
			}
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
	}

	~AVLTree() {
		DeleteAllNode(root);
	}
private:
	AVLNode *root{nullptr};

	void DeleteAllNode(AVLNode *cur) {
		if (!cur) return;
		if (cur->left_) DeleteAllNode(cur->left_);
		if (cur->right_) DeleteAllNode(cur->right_);
		delete cur;
	}
};

#endif