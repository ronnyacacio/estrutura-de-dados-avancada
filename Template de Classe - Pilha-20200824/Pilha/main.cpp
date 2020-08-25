#include <iostream>
#include "Stack.h"

int main() {
    Stack<int> ipilha(15); // instancia pilha de int
    Stack<double> dpilha(14); // instancia pilha de double

    for(int i = 1; i <= 13; i++) {
        ipilha.push(i);
        dpilha.push(i / 33.0);
    }
    
    while( !ipilha.empty() ) {
        std::cout << ipilha.top() << " ";
        ipilha.pop();
    }
    std::cout << std::endl;
    while( !dpilha.empty() ) {
        std::cout << dpilha.top() << " ";
        dpilha.pop();
    }
    return 0;
}
