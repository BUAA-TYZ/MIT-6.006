#include "avl.h"

/******************************
 * Search Functions
 *****************************/
AVLNode * AVLNode::subtree_first() {
	AVLNode *cur = this;
	while (cur->left_) {
		cur = cur->left_;
	}
	return cur;
}

AVLNode * AVLNode::subtree_last() {
	AVLNode *cur = this;
	while (cur->right_) {
		cur = cur->right_;
	}
	return cur;
}

AVLNode* AVLNode::predecessor() {
		AVLNode *cur = this;
		if (cur->left_) { return cur->left_->subtree_last(); }
		while (cur->parent_ && cur->parent_->left_ == cur) {
			cur = cur->parent_;
		}
		return cur->parent_;
	}

AVLNode* AVLNode::successor() {
	AVLNode *cur = this;
	if (cur->right_) { return cur->right_->subtree_first(); }
	while (cur->parent_ && cur->parent_->right_ == cur) {
		cur = cur->parent_;
	}
	return cur->parent_;
}

AVLNode* AVLNode::find(int data) {
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
void AVLNode::left_rotation() {
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

void AVLNode::right_rotation() {
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

void AVLNode::rebalance() {
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

void AVLNode::maintain() {
	rebalance();
	update_height();
	if (parent_)	parent_->maintain();
}

/******************************
 * Insert Functions
 *****************************/
void AVLNode::insert_before(AVLNode *insert_node) {
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

void AVLNode::insert_after(AVLNode *insert_node) {
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
void AVLNode::subtree_insert(AVLNode *insert_node) {
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