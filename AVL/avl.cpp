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

int avl_leaf(Node *node)
{
  if (node == nullptr)
    return 0;
  if (node->left == nullptr && node->right == nullptr)
    return 1;
  else
    return avl_leaf(node->left) + avl_leaf(node->right);
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

int avl_height(Node *node)
{
  if (node == nullptr)
    return 0;
  else
    return node->height;
}

Node *avl_minimum(Node *node)
{
  if (node != nullptr && node->left != nullptr)
    return avl_minimum(node->left);
  else
    return node;
}

Node *avl_maximum(Node *node)
{
  if (node != nullptr && node->right != nullptr)
    return avl_maximum(node->right);
  else
    return node;
}

int balance(Node *node)
{
  if (node == nullptr)
    return 0;
  return avl_height(node->right) - avl_height(node->left);
}

int avl_size(Node *node)
{
  if (node == nullptr)
    return 0;
  else
    return 1 + avl_size(node->left) + avl_size(node->right);
}

bool avl_empty(Node *node)
{
  return (node == nullptr);
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

Node *fixup_node_deletion(Node *node)
{
  int bal = balance(node); // obtém balanço de p
  if (bal > 1)
  {
    //caso 4 (a) & caso 4 (b)
    if (balance(node->right) == 0 || balance(node->right) == 1)
      return leftRotation(node);
    //caso 4 (c)
    else if (balance(node->right) == -1)
    {
      node->right = rightRotation(node->right);
      return leftRotation(node);
    }
  }
  else if (bal < 1)
  {
    //simetrico do caso 4 (a) && 4 (b)
    if (balance(node->left) == 0 || balance(node->left) == 1)
      return rightRotation(node);
    else if (balance(node->left) == -1)
    {
      node->left = leftRotation(node->left);
      return rightRotation(node);
    }
  }
}

Node *delete_predecessor(Node *root, Node *node)
{
  if (node->right != nullptr)
    node->right = delete_predecessor(root, node->right);
  else
  {
    root->key = node->key;
    Node *aux = node->left;
    delete node;
    return aux;
  }
  // Atualiza o campo 'height ' e regula o nó
  node = fixup_node_deletion(node);
  return node;
}

Node *avl_delete(Node *node, Tkey key)
{
  if (node == nullptr) // nó não encontrado
    return nullptr;
  if (key < node->key) // vai para a esquerda
    node->left = avl_delete(node->left, key);
  else if (key > node->key) // vai para a direita
    node->right = avl_delete(node->right, key);
  /* encontramos o nó */
  else if (node->left == nullptr && node->right == nullptr)
  {
    delete node;
    return nullptr;
  }
  else if (node->left == nullptr || node->right == nullptr)
  {
    Node *child = node->left ? node->left : node->right;
    delete node;
    return child;
  }
  /* nó tem dois filhos: copia a chave do antecessor ,
  remove antecessor , atualiza altura dos nós e os regula */
  else
    node->left = delete_predecessor(node, node->left);
  node = fixup_node_deletion(node); // regula node
  return node;
}