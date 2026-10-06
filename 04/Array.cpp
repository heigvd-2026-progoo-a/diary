#include <cstddef>      // std::size_t, std::ptrdiff_t
#include <stdexcept>    // std::out_of_range

template<class T, std::size_t N>
struct Array
{
    // Le stockage réel
    T elements[N];

    // Types pratiques
    using value_type      = T;
    using size_type       = std::size_t;
    using difference_type = std::ptrdiff_t;

    using reference       = T&; // typedef T& reference;
    using const_reference = const T&;

    using pointer         = T*;
    using const_pointer   = const T*;

    using iterator        = T*;
    using const_iterator  = const T*;


    // -------------------------
    // Accès aux éléments
    // -------------------------

    reference operator[](size_type index)
    {
        return elements[index];
    }

    const_reference operator[](size_type index) const
    {
        return elements[index];
    }


    reference at(size_type index)
    {
        if (index >= N)
            throw std::out_of_range("Array::at");

        return elements[index];
    }

    const_reference at(size_type index) const
    {
        if (index >= N)
            throw std::out_of_range("Array::at");

        return elements[index];
    }


    reference front()
    {
        return elements[0];
    }

    const_reference front() const
    {
        return elements[0];
    }


    reference back()
    {
        return elements[N - 1];
    }

    const_reference back() const
    {
        return elements[N - 1];
    }


    // -------------------------
    // Pointeur vers les données
    // -------------------------

    pointer data()
    {
        return elements;
    }

    const_pointer data() const
    {
        return elements;
    }


    // -------------------------
    // Taille
    // -------------------------

    constexpr size_type size() const
    {
        return N;
    }

    constexpr bool empty() const
    {
        return N == 0;
    }


    // -------------------------
    // Itérateurs
    // -------------------------

    iterator begin()
    {
        return elements;
    }

    const_iterator begin() const
    {
        return elements;
    }


    iterator end()
    {
        return elements + N;
    }

    const_iterator end() const
    {
        return elements + N;
    }


    // -------------------------
    // Remplissage
    // -------------------------

    void fill(const T& value)
    {
        for (size_type i = 0; i < N; ++i)
            elements[i] = value;
    }


    // -------------------------
    // Échange
    // -------------------------

    void swap(Array& other)
    {
        for (size_type i = 0; i < N; ++i)
        {
            T temp = elements[i];
            elements[i] = other.elements[i];
            other.elements[i] = temp;
        }
    }
};