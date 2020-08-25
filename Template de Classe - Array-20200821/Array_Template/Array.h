#ifndef MYARRAY_H
#define MYARRAY_H
#include <cassert> // para assert()

template < typename T >
class Array
{
private:
    int m_size;
    T *m_array;
public:
    // Constructor
    Array(int n)
    {
        assert(n > 0); // aborta o programa se n <= 0
        m_size = n;
        m_array = new T[m_size];
    }

    // Destructor
    ~Array()
    {
        delete[] m_array;
    }

    int size() const
    {
        return m_size;
    }

    T& operator[](int index) const
    {
        // aborta o programa se a condicao for falsa
        assert(index >= 0 && index <= m_size);
        return m_array[index];
    }
};

#endif
