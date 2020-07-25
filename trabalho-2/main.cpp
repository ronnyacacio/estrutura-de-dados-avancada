#include <iostream>
#include <cstdlib>
#include "item.h"
#include "avl.h"
using namespace std;

int main()
{
  int op = 0;
  Node *root = nullptr;

  while (op != 8)
  {
    cout << "\n----------------------------\n";
    cout << "Implementação da Árvore AVL.\n";
    cout << "----------------------------\n";
    cout << "1. Inserir elemento na árvore\n";
    cout << "2. Apagar todos os nós da árvore\n";
    cout << "3. Percurso em pré-ordem\n";
    cout << "4. Percurso em in-ordem\n";
    cout << "5. Percurso em pós-ordem\n";
    cout << "6. Pesquisar por chave\n";
    cout << "7. Altura da árvore\n";
    cout << "8. Sair\n";
    cout << "Entre com sua escolha: ";
    cin >> op;

    if (op == 1)
    {
      Tkey key;
      Tvalue value;

      cout << "Dígite a chave: ";
      cin >> key;
      cout << "Dígite o valor: ";
      cin >> value;

      root = avl_insert(root, key, value);
    }
    else if (op == 2)
      root = avl_clear(root);
    else if (op == 3)
      avl_preorder(root);
    else if (op == 4)
      avl_inorder(root);
    else if (op == 5)
      avl_postorder(root);
    else if (op == 6)
    {
      Tkey key;
      cout << "\nDígite a chave: ";
      cin >> key;

      Node *node = avl_search(root, key);

      if (node)
        cout << "\nO valor requerido é: " << avl_getValue(node) << endl;
      else
        cout << "\nO valor requerido não está presente nessa árvore\n\n";
    }
    else if (op == 7)
      cout << "A altura da árvore é: " << avl_height(root) << endl;
  }

  cout << "\nDestruindo a arvore...\n";
  root = avl_clear(root);

  return 0;
}
