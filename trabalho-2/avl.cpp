#include <iostream>
#include <queue>
#include <algorithm>
#include "avl.h"
#include "item.h"
using namespace std;

struct Node
{
  Tkey key;
  Tvalue value;
  int height;
  Node *left;
  Node *right;
};

Tkey avl_getKey(Node *node)
{
  return node->key;
}

Tvalue avl_getValue(Node *node)
{
  return node->value;
}

Node *avl_search(Node *node, Tkey key)
{
  if (node == nullptr)
    return nullptr;
  if (key < node->key)
    return avl_search(node->left, key);
  else if (key > node->key)
    return avl_search(node->right, key);
  else
    return node;
}

void avl_preorder(Node *node)
{
  if (node != nullptr)
  {
    cout << "(" << node->key << ", " << node->value << ")" << endl;
    avl_preorder(node->left);
    avl_preorder(node->right);
  }
}

void avl_inorder(Node *node)
{
  if (node != nullptr)
  {
    avl_preorder(node->left);
    cout << "(" << node->key << ", " << node->value << ")" << endl;
    avl_preorder(node->right);
  }
}

void avl_postorder(Node *node)
{
  if (node != nullptr)
  {
    avl_postorder(node->left);
    avl_postorder(node->right);
    cout << "(" << node->key << ", " << node->value << ")" << endl;
  }
}

int balance(Node *node)
{
  if (node == nullptr)
    return 0;
  return avl_height(node->right) - avl_height(node->left);
}

int avl_height(Node *node)
{
  if (node == nullptr)
    return 0;
  else
    return node->height;
}

Node *avl_clear(Node *node)
{
  if (node != nullptr)
  {
    node->left = avl_clear(node->left);
    node->right = avl_clear(node->right);
    cout << "Removendo chave " << node->key << endl;
    delete node;
  }
  return nullptr;
}

//--------------codes rotations--------------//
Node *rightRotation(Node *node)
{
  Node *u = node->left;
  node->left = u->right;
  u->right = node;
  // atualiza alturas dos nós
  node->height = 1 + max(avl_height(node->left), avl_height(node->right));
  u->height = 1 + max(avl_height(u->left), avl_height(u->right));
  return u; // nova raiz
}

Node *leftRotation(Node *node)
{
  Node *u = node->right;
  node->right = u->left;
  u->left = node;
  // atualiza alturas dos nós
  node->height = 1 + max(avl_height(node->left), avl_height(node->right));
  u->height = 1 + max(avl_height(u->left), avl_height(u->right));
  return u; // nova raiz
}
//--------------codes rotations--------------//

Node *allocateNode(Tkey key, Tvalue value)
{
  Node *node = new Node;
  node->key = key;
  node->value = value;
  node->left = nullptr;
  node->right = nullptr;
  node->height = 1;
  return node;
}

Node *fixup_node(Node *p, Tkey key)
{
  int bal = balance(p); // obtém balanço de p
  // caso 4(a)
  if (bal < -1 && key < p->left->key)
    return rightRotation(p);
  // caso 4(b)
  else if (bal < -1 && key > p->left->key)
  {
    p->left = leftRotation(p->left);
    return rightRotation(p);
  }
  // simétrico do caso 4(a)
  else if (bal > 1 && key > p->right->key)
    return leftRotation(p);
  // simétrico do caso 4(b)
  else if (bal > 1 && key < p->right->key)
  {
    p->right = rightRotation(p->right);
    return leftRotation(p);
  }
  return p;
}

Node *avl_insert(Node *p, Tkey key, Tvalue value)
{
  if (p == nullptr)
    return allocateNode(key, value);
  if (key < p->key)
    p->left = avl_insert(p->left, key, value);
  else if (key > p->key)
    p->right = avl_insert(p->right, key, value);
  else
    return p; // não permite chaves repetidas
  // atualiza altura deste ancestral p
  p->height = 1 + max(avl_height(p->left), avl_height(p->right));
  // Conserta a regulagem do nó p
  p = fixup_node(p, key);
  return p;
}