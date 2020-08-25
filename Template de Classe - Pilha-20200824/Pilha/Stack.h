#ifndef MYSTACK_H
#define MYSTACK_H

template <typename T>
class Stack {
public:
    class StackException {}; // Classe de Excecao
    Stack(int n); // construtor
    ~Stack(); // destrutor
    void push(const T& item);
    void pop();
    const T& top() const;
    int size() const;
    bool empty() const;
    bool full() const;
private:
    int itop; // indice do elemento no topo
    int _size; // numero de elementos na pilha
    T *array; // ponteiro para o array de elementos
};

template <typename T>
Stack<T>::Stack(int n) 
    : itop(0), _size(n > 0 ? n : 10)
{
    array = new T[n];
}

template <typename T>
void Stack<T>::push(const T& item) {
    if(full()) throw StackException{};
    array[itop] = item;
    ++itop;
}

template <typename T>
void Stack<T>::pop() {
    if(empty()) throw StackException{};
    --itop;
}

template <typename T>
const T& Stack<T>::top() const {
    if(empty()) throw StackException{};
    return array[itop - 1];
}

template <typename T>
bool Stack<T>::empty() const {
    return (itop == 0);
}

template <typename T>
bool Stack<T>::full() const {
    return (itop == _size);
}

template <typename T>
int Stack<T>::size() const {
    return _size;
}

template <typename T>
Stack<T>::~Stack() {
    delete[] array;
}

#endif
