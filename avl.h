#ifndef AVL_H
#define AVL_H
#include "item.h"

struct Node;

Node* avl_insert(Node *node, Tkey key, Tvalue value);
Node* avl_delete(Node *node, Tkey key);

Tkey avl_getKey(Node *node);
Tvalue avl_getValue(Node *node);
Node *avl_search(Node *node, Tkey key);
void avl_preorder(Node *node);
void avl_inorder(Node *node);
void avl_level_traversal(Node *node);
int avl_height(Node *node);
int avl_size(Node *node);
bool avl_empty(Node *node);
Node *avl_clear(Node *node);

#endif 
