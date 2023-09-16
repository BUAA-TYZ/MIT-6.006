#include "gtest/gtest.h"

#include "avl.h"

// Demonstrate some basic assertions.
TEST(AVLTREETest, BasicInt)
{
  AVLTree<int> T = AVLTree<int>();
  auto l = {2, 1, 5, 4, 6, 3, 7, 8};
  T.build(l);
  AVLNode<int> *a = T.find(1);
  AVLNode<int> *b = T.find(2);
  AVLNode<int> *c = T.find(3);
  AVLNode<int> *d = T.find(4);
  AVLNode<int> *e = T.find(5);
  AVLNode<int> *f = T.find(6);
  AVLNode<int> *g = T.find(7);

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

TEST(AVLTREETest, BasicString) {
  AVLTree<std::string> T = AVLTree<std::string>();
  auto l = {std::string("a"), std::string("abcd"), std::string("tyz"), std::string("zyt")};
  T.build(l);
  AVLNode<std::string> *a = T.find(std::string("a"));
  AVLNode<std::string> *b = T.find(std::string("abcd"));
  AVLNode<std::string> *c = T.find(std::string("tyz"));
  AVLNode<std::string> *d = T.find(std::string("zyt"));

  EXPECT_EQ(a->height(), 0);
  EXPECT_EQ(b->height(), 2);
  EXPECT_EQ(c->height(), 1);
  EXPECT_EQ(d->height(), 0); 
  EXPECT_TRUE(b->checkchild(a, c));
}

class Student {
public:
  Student(int age, std::string name):
  age_(age), name_(std::move(name)) {}
  int age_{0};
  std::string name_{};
};

TEST(AVLTREETest, Comparator) {
  Student aa{21, "tyz"}, bb{21, "zr"}, cc{50, "tlq"}, dd{50, "zyh"};
  auto comp = [](const Student &a, const Student &b) {
    if (a.age_ != b.age_) {
      return a.age_ < b.age_;
    }
    return std::less<std::string>()(a.name_, b.name_);
  };
  auto T = AVLTree<Student, decltype(comp)>(comp);
  auto l = {aa, bb, cc, dd};
  T.build(l);
  auto *a = T.find(aa);
  auto *b = T.find(bb);
  auto *c = T.find(cc);
  auto *d = T.find(dd);

  EXPECT_EQ(a->height(), 0);
  EXPECT_EQ(b->height(), 2);
  EXPECT_EQ(c->height(), 1);
  EXPECT_EQ(d->height(), 0); 
  EXPECT_TRUE(b->checkchild(a, c));  
}

TEST(AVLTREETest, Find) {
  AVLTree<int> T = AVLTree<int>();
  for (int i = 0; i < 10000; ++i) 
    T.insert(i);
  for (int i = 0; i < 10000; ++i) 
    EXPECT_NE(T.find(i), nullptr);
  EXPECT_TRUE(T.height() >= 13);
}