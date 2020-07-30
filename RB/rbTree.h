#ifndef RBTREE_H
#define RBTREE_H
#include "node.h"

class RBTree
{
private:
  Node *root;
  Node *nil;

protected:
  void left_rotate(Node *node);
  void right_rotate(Node *node);
  void RBinsert(Node *node);
  void RBinsert_fixUp(Node *node);
  void RBdelete(Node *z);
  void RBdelete_fixUp(Node *z);
  Node *minimum(Node *node);
  void clear(Node *node);

public:
  RBTree();
  void insert(const Tkey &key, const Tvalue &v);
  void remove(const Tkey &key);
  bool search(const Tkey &key, Tvalue *v) const;
  void preorder() const;
  bool empty() const;
  ~RBTree();
};
#endif