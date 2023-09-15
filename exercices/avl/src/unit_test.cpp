#include "gtest/gtest.h"

#include "avl.h"

// Demonstrate some basic assertions.
TEST(AVLTREETest, Basic)
{
  AVLTree T = AVLTree();
  auto l = {2, 1, 5, 4, 6, 3, 7, 8};
  T.build(l);
  AVLNode *a = T.find(1);
  AVLNode *b = T.find(2);
  AVLNode *c = T.find(3);
  AVLNode *d = T.find(4);
  AVLNode *e = T.find(5);
  AVLNode *f = T.find(6);
  AVLNode *g = T.find(7);

  EXPECT_EQ(a->height(), 0);
  EXPECT_EQ(b->height(), 1);
  EXPECT_EQ(c->height(), 0);
  EXPECT_EQ(d->height(), 3);
  EXPECT_EQ(e->height(), 0);
  EXPECT_EQ(f->height(), 2);
  EXPECT_EQ(g->height(), 1);
  EXPECT_TRUE(b->checkchild(a, c));
  EXPECT_TRUE(d->checkchild(b, f));
  EXPECT_EQ(T.find(10), nullptr);
  T.insert(10);
  EXPECT_NE(T.find(10), nullptr);
  EXPECT_TRUE(T.find(8)->checkchild(g, T.find(10)));
}

TEST(AVLTREETest, Find) {
  AVLTree T = AVLTree();
  for (int i = 0; i < 10000; ++i) 
    T.insert(i);
  for (int i = 0; i < 10000; ++i) 
    EXPECT_NE(T.find(i), nullptr);
  EXPECT_TRUE(T.height() >= 13);
}