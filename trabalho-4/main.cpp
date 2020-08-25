#include <iostream>
#include "rbtree.h"

int main()
{
  RBTree<int, char> tree = RBTree<int, char>();

  int op = 0;

  do
  {
    cout << "---------------------------" << endl;
    cout << "IMPLEMENTAÇÃO DA ARVORE AVL" << endl;
    cout << "---------------------------" << endl;
    cout << "1 - Inserir" << endl;
    cout << "2 - Apagar no específico" << endl;
    cout << "3 - Imprimir" << endl;
    cout << "4 - Pesquisar valor por chave" << endl;
    cout << "5 - Altura da árvore" << endl;
    cout << "6 - Apagar um no" << endl;
    cout << "7 - Sair" << endl;
    cin >> op;
    if (op == 1)
    {
      int chave;
      char valor;
      cin >> chave;
      cin >> valor;
      tree.insert(chave, valor);
    }
    else if (op == 2)
    {
      tree.clear(tree.getRoot());
    }
    else if (op == 3)
    {
      tree.preorder();
    }
    else if (op == 4)
    {
      int chave;
      cin >> chave;
      Node<int, char> *no = tree.search(chave);
      if (no == nullptr)
      {
        cout << "tem nao";
      }
      else
      {
        cout << tree.getValue(no);
      }
    }
    else if (op == 5)
    {
      cout << tree.height(tree.getRoot());
    }
    else if (op == 6)
    {
      int chave;
      cin >> chave;
      tree.remove(chave);
    }

  } while (op != 7);

  tree.~RBTree();

  return 0;
}