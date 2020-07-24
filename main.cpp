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
    cout << "2. Percurso em pré-ordem\n";
    cout << "3. Percurso em in-ordem\n";
    cout << "4. Percurso em pós-ordem\n";
    cout << "5. Altura da árvore\n";
    cout << "6. Número de folhas da árvore\n";
    cout << "7. Valor máximo e mínimo da árvore\n";
    cout << "8. Sair\n";
    cout << "Entre com sua escolha ";
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
      avl_preorder(root);
    else if (op == 3)
      avl_inorder(root);
    else if (op == 4)
      avl_postorder(root);
    else if (op == 5)
      cout << "A altura da árvore é: " << avl_height(root) << endl;
    else if (op == 6)
      cout << "O número de folhas da árvore é: " << avl_leaf(root) << endl;
    else if (op == 7)
    {
      Node *max = avl_maximum(root);
      Tkey maxKey = avl_getKey(max);
      Tvalue maxValue = avl_getValue(max);

      Node *min = avl_minimum(root);
      Tkey minKey = avl_getKey(min);
      Tvalue minValue = avl_getValue(min);

      cout << "O valor máximo da árvore é: (" << maxKey << ", " << maxValue << ")" << endl;
      cout << "O valor mínimo da árvore é: (" << minKey << ", " << minValue << ")" << endl;
    }
  }

  cout << "\nDestruindo a arvore...\n";
  root = avl_clear(root);

  return 0;
}
