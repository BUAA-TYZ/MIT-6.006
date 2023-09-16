#include "avl.h"

/******************************
 * Search Functions
 *****************************/
TEMPLATE_ARGUMENT
AVLNODE_TYPE * AVLNODE_TYPE::subtree_first() {
	AVLNODE_TYPE *cur = this;
	while (cur->left_) {
		cur = cur->left_;
	}
	return cur;
}

TEMPLATE_ARGUMENT
AVLNODE_TYPE * AVLNODE_TYPE::subtree_last() {
	AVLNODE_TYPE *cur = this;
	while (cur->right_) {
		cur = cur->right_;
	}
	return cur;
}

TEMPLATE_ARGUMENT
AVLNODE_TYPE * AVLNODE_TYPE::predecessor() {
		AVLNODE_TYPE *cur = this;
		if (cur->left_) { return cur->left_->subtree_last(); }
		while (cur->parent_ && cur->parent_->left_ == cur) {
			cur = cur->parent_;
		}
		return cur->parent_;
	}

TEMPLATE_ARGUMENT
AVLNODE_TYPE * AVLNODE_TYPE::successor() {
	AVLNODE_TYPE *cur = this;
	if (cur->right_) { return cur->right_->subtree_first(); }
	while (cur->parent_ && cur->parent_->right_ == cur) {
		cur = cur->parent_;
	}
	return cur->parent_;
}

TEMPLATE_ARGUMENT
AVLNODE_TYPE * AVLNODE_TYPE::find(T data) {
	if (comparator_(data, data_)) {
		if (left_) {
			return left_->find(data);
		}
	} else if (comparator_(data_, data)) {
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
TEMPLATE_ARGUMENT
void AVLNODE_TYPE::left_rotation() {
	assert(right_);
	AVLNODE_TYPE *A = this, *B = left_, *C = right_,
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

TEMPLATE_ARGUMENT
void AVLNODE_TYPE::right_rotation() {
	assert(left_);
	AVLNODE_TYPE *A = this, *B = left_, *C = left_->left_,
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

TEMPLATE_ARGUMENT
void AVLNODE_TYPE::rebalance() {
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

TEMPLATE_ARGUMENT
void AVLNODE_TYPE::maintain() {
	rebalance();
	update_height();
	if (parent_)	parent_->maintain();
}

/******************************
 * Insert Functions
 *****************************/
TEMPLATE_ARGUMENT
void AVLNODE_TYPE::insert_before(AVLNODE_TYPE *insert_node) {
	assert(insert_node != nullptr);
	if (left_) {
		AVLNODE_TYPE *cur = nullptr;
		cur = left_->subtree_last();
		cur->right_ = insert_node;
		insert_node->parent_ = cur;
	} else {
		left_ = insert_node;
		insert_node->parent_ = this;
	}
	maintain();
}

TEMPLATE_ARGUMENT
void AVLNODE_TYPE::insert_after(AVLNODE_TYPE *insert_node) {
	assert(insert_node != nullptr);
	if (right_) {
		AVLNODE_TYPE *cur = nullptr;
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
TEMPLATE_ARGUMENT
void AVLNODE_TYPE::subtree_insert(AVLNODE_TYPE *insert_node) {
	if (comparator_(insert_node->data_, data_)) {
		if (left_)
			left_->subtree_insert(insert_node);
		else
			insert_before(insert_node);
	} else if (comparator_(data_, insert_node->data_)) {
		if (right_)
			right_->subtree_insert(insert_node);
		else
			insert_after(insert_node);
	}
}
