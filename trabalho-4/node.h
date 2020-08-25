#ifndef NODE_H
#define NODE_H

enum Color
{
  RED,
  BLACK
};

template <typename Tkey, typename Tvalue>
class Node
{
public:
  Tkey key;
  Tvalue value;
  Color color;
  Node *left;
  Node *right;
  Node *parent;
};
#endif