#ifndef RBTREE_H
#define RBTREE_H
#include <iostream>
#include <bits/stdc++.h>
#include "node.h"
using namespace std;

template <typename Tkey, typename Tvalue>
class RBTree
{
private:
  Node<Tkey, Tvalue> *root;
  Node<Tkey, Tvalue> *nil;

protected:
  void left_rotate(Node<Tkey, Tvalue> *x)
  {
    Node<Tkey, Tvalue> *y = x->right;
    x->right = y->left;
    if (y->left != nil)
    {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil)
    {
      root = y;
    }
    else if (x == x->parent->left)
    {
      x->parent->left = y;
    }
    else
    {
      x->parent->right = y;
    }

    y->left = x;
    x->parent = y;
  }

  void right_rotate(Node<Tkey, Tvalue> *x)
  {
    Node<Tkey, Tvalue> *y = x->left;
    x->left = y->right;
    if (y->right != nil)
    {
      y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nil)
    {
      root = y;
    }
    else if (x == x->parent->right)
    {
      x->parent->right = y;
    }
    else
    {
      x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
  }

  void RBinsert(Node<Tkey, Tvalue> *z)
  {
    Node<Tkey, Tvalue> *father = nil;
    Node<Tkey, Tvalue> *son = root;
    while (son != nil)
    {
      father = son;
      if (z->key == son->key)
      {

        delete z;

        return;
      }
      son = (z->key < son->key) ? son->left : son->right;
    }
    z->parent = father;
    if (father == nil)
      root = z;
    else if (z->key < father->key)
      father->left = z;
    else
      father->right = z;
    z->left = z->right = nil;
    z->color = RED;

    RBinsert_fixUp(z);
  }

  void RBinsert_fixUp(Node<Tkey, Tvalue> *z)
  {
    while (z->parent->color == RED)
    {
      if (z->parent == z->parent->parent->left)
      {
        Node<Tkey, Tvalue> *uncle = z->parent->parent->right;
        if (uncle->color == RED)
        {
          z->parent->color = BLACK;
          uncle->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        }
        else
        {
          if (z == z->parent->right)
          {
            z = z->parent;
            left_rotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          right_rotate(z->parent->parent);
        }
      }
      else
      {
        Node<Tkey, Tvalue> *uncle = z->parent->parent->left;
        if (uncle->color == RED)
        {
          z->parent->color = BLACK;
          uncle->color = BLACK;
          z->parent->parent->color = RED;
          z = z->parent->parent;
        }
        else
        {
          if (z == z->parent->left)
          {
            z = z->parent;
            right_rotate(z);
          }
          z->parent->color = BLACK;
          z->parent->parent->color = RED;
          left_rotate(z->parent->parent);
        }
      }
    }
    root->color = BLACK;
  }

  void RBdelete(Node<Tkey, Tvalue> *z)
  {
    Node<Tkey, Tvalue> *y;
    Node<Tkey, Tvalue> *x;
    if (z->left == nil || z->right == nil)
      y = z;
    else
      y = minimum(z->right);
    if (y->left != nil)
      x = y->left;
    else
      x = y->right;
    if (x != nil)
      x->parent = y->parent;
    if (y->parent == nil)
    {
      root = x;
    }
    else
    {
      if (y == y->parent->left)
        y->parent->left = x;
      else
        y->parent->right = x;
    }
    if (y != z)
      z->key = y->key;
    if (y->color == BLACK)
      RBdelete_fixUp(x);
    delete y;
  }

  Node<Tkey, Tvalue> *minimum(Node<Tkey, Tvalue> *no)
  {
    while (no->left != nil)
    {
      no = no->left;
    }
    return no;
  }

  void RBdelete_fixUp(Node<Tkey, Tvalue> *no)
  {
    while (no != root && no->color == BLACK)
    {
      if (no == no->parent->left)
      {
        Node<Tkey, Tvalue> *w = no->parent->right;
        if (w->color == RED)
        {
          w->color = BLACK;
          no->parent->color = RED;
          left_rotate(no->parent);
          w = no->parent->right;
        }
        if (w->left->color == BLACK && w->right->color == BLACK)
        {
          w->color = RED;
          no = no->parent;
        }
        else
        {
          if (w->right->color == BLACK)
          {
            w->left->color = BLACK;
            w->color = RED;
            right_rotate(w);
            w = no->parent->right;
          }
          w->color = no->parent->color;
          no->parent->color = BLACK;
          w->right->color = BLACK;
          left_rotate(no->parent);
          no = root;
        }
      }
      else
      {
        Node<Tkey, Tvalue> *w = no->parent->left;
        if (w->color == RED)
        {
          w->color = BLACK;
          no->parent->color = RED;
          left_rotate(no->parent);
          w = no->parent->left;
        }
        if (w->left->color == BLACK && w->right->color == BLACK)
        {
          w->color = RED;
          no = no->parent;
        }
        else
        {
          if (w->left->color == BLACK)
          {
            w->right->color = BLACK;
            w->color = RED;
            left_rotate(w);
            w = no->parent->right;
          }
          w->color = no->parent->color;
          no->parent->color = BLACK;
          w->right->color = BLACK;
          right_rotate(no->parent);
          no = root;
        }
      }
    }
    no->color = BLACK;
  }

  bool empty()
  {
    if (root->left == nil && root->right == nil)
    {
      return true;
    }
    return false;
  }

public:
  RBTree()
  {
    nil = new Node<Tkey, Tvalue>{};
    nil->key = 0;
    nil->left = nil->right = nil->parent = nil;
    nil->color = BLACK;
    root = nil;
  }

  Node<Tkey, Tvalue> *getRoot()
  {
    return root;
  }

  void insert(const Tkey &key, const Tvalue &v)
  {
    Node<Tkey, Tvalue> *newNode = new Node<Tkey, Tvalue>{};
    newNode->key = key;
    newNode->value = v;
    newNode->left = newNode->right = nil;
    newNode->parent = nil;

    RBinsert(newNode);
  }

  void remove(const Tkey &key)
  {
    Node<Tkey, Tvalue> *p = root;
    while (p != nil && p->key != key)
    {
      p = (key < p->key) ? p->left : p->right;
    }
    if (p != nil)
      RBdelete(p);
  }

  Node<Tkey, Tvalue> *search(const Tkey &key)
  {
    Node<Tkey, Tvalue> *p = root;
    while (p != nil && p->key != key)
    {
      p = (key < p->key) ? p->left : p->right;
    }
    if (p != nil)
      return p;
    return nullptr;
  }

  Tvalue getValue(Node<Tkey, Tvalue> *no)
  {
    return no->value;
  }

  void preorder() const
  {
    Node<Tkey, Tvalue> *tree = root;
    stack<Node<Tkey, Tvalue> *> pilha;
    if (tree != nil)
    {
      pilha.push(tree);
      while (!pilha.empty())
      {
        tree = pilha.top();
        pilha.pop();
        if (tree->color == BLACK)
        {
          cout << "(" << tree->key << "," << tree->value << ") -> Black" << endl;
        }
        else
        {
          cout << "(" << tree->key << "," << tree->value << ") -> Red" << endl;
        }
        if (tree->right != nil)
        {
          pilha.push(tree->right);
        }
        if (tree->left != nil)
        {
          pilha.push(tree->left);
        }
      }
    }
  }

  void clear(Node<Tkey, Tvalue> *root)
  {
    Node<Tkey, Tvalue> *aux = root;
    stack<Node<Tkey, Tvalue> *> nodes;

    if (aux != nil)
    {
      nodes.push(aux);
    }
    while (!nodes.empty())
    {
      Node<Tkey, Tvalue> *node = nodes.top();
      if (node->right != nil)
      {
        nodes.push(node->right);
      }
      if (node->left != nil)
      {
        nodes.push(node->left);
      }
      if (node->left == nil && node->right == nil)
      {
        RBdelete(node);
        nodes.pop();
      }
    }
  }

  int height(Node<Tkey, Tvalue> *node)
  {
    if (node != nil)
    {
      int l, r;
      l = height(node->left);
      r = height(node->right);
      if (l > r)
        return 1 + l;
      else
        return 1 + r;
    }
    else
      return 0;
  }

  ~RBTree()
  {
    delete nil;
    nil = nullptr;
    root = nullptr;
  }
};
#endif