#include <iostream>
#include <stack>
#include "rbTree.h"
using std ::cout;
using std ::endl;

RBTree ::RBTree()
{
  nil = new Node{};
  nil->key = 0;
  nil->left = nil->right = nil->parent = nil;
  nil->color = BLACK;
  root = nil;
}

RBTree ::~RBTree()
{
  clear(root);
  delete nil;
  nil = nullptr;
  root = nullptr;
}

Node *clear(Node *node)
{
  if (node != nullptr)
  {
    node->left = clear(node->left);
    node->right = clear(node->right);
    cout << "Removendo chave " << node->key << endl;
    delete node;
  }
  return nullptr;
}