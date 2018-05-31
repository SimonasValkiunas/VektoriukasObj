#ifndef VEKTORIUS_MVECTOR_H
#define VEKTORIUS_MVECTOR_H

#include <iterator>
#include <cstring>
#include <stdexcept>

template <class T> class mVector
    {
    private:
        int m_Size = 0;
        int m_Capacity = 10;
        T *arr;
        inline void reallocate();
    public:
        typedef unsigned int   size_type;
        typedef T   value_type;
        typedef T &    reference;
        typedef const T &   const_reference;
        typedef T *  pointer;
        typedef const T * const_pointer;
        typedef T * iterator;
        typedef const T *  const_iterator;
        typedef std::reverse_iterator<iterator> reverse_iterator;
        typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
        //mVector Operator
        bool operator == (const mVector<T> &) const;
        bool operator != (const mVector<T> &) const;
        bool operator < (const mVector<T> &) const;
        bool operator <= (const mVector<T> &) const;
        bool operator > (const mVector<T> &) const;
        bool operator >= (const mVector<T> &) const;

        //Iterators
        iterator begin() noexcept;
        const_iterator cbegin() const noexcept;
        iterator end() noexcept;
        const_iterator cend() const noexcept;
        reverse_iterator rbegin() noexcept;
        const_reverse_iterator crbegin() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator crend() const noexcept;


        // Constructor
        mVector() noexcept;
        explicit mVector(unsigned int n);
        mVector(unsigned int, const T &);
        mVector(typename mVector<T>::iterator first, typename mVector<T>::iterator last);
        mVector(std::initializer_list<T>);
        mVector(const mVector<T> &);
        mVector(mVector<T> &&) noexcept;
        ~mVector();
        mVector<T> & operator = (const mVector<T> &);
        mVector<T> & operator = (mVector<T> &&);
        mVector<T> & operator = (std::initializer_list<T>);
        void assign(unsigned int, const T &value);


        //Access to elements
        reference operator [](size_type);
        reference at(size_type);
        reference front();
        reference back();


        //Capacity
        bool empty() const noexcept;
        int size() const noexcept;
        int capacity() const noexcept;
        void resize(int);
        void reserve(int);
        void shrink_to_fit();

        //Modifiers
        template <class ... Args> iterator emplace(const_iterator, Args && ... args);
        void push_back(const T &);
        void pop_back();
        iterator insert(const_iterator, const T &);
        iterator erase(const_iterator);
        iterator erase(const_iterator, const_iterator);
        void clear() noexcept;


    };

    // Operators
    template <typename T>
    bool mVector<T>::operator == (const mVector<T> &a) const {
        if ( m_Size!= a.m_Size) return false;
        unsigned int i;
        for (i = 0; i < m_Size; ++i)
            if (arr[i] != a.arr[i])
                return false;
        return true;
    }

    template <typename T>
    bool mVector<T>::operator != (const mVector<T> &a) const {
    if (m_Size != a.m_Size) return true;
    unsigned int i;
    for (i = 0; i < m_Size; ++i)
        if (arr[i] != a.arr[i])
            return true;
    return false;
}

    template <typename T>
    bool mVector<T>::operator < (const mVector<T> &a) const {
    unsigned int i, j, ub = m_Size < a.m_Size ? m_Size : a.m_Size;
    for (i = 0; i < ub; ++i)
        if (arr[i] != a.arr[i])
            return arr[i] < a.arr[i];
    return m_Size < a.m_Size;
}

    template <typename T>
    bool mVector<T>::operator <= (const mVector<T> &a) const {
    unsigned int i, j, ub = m_Size < a.m_Size ? m_Size : a.m_Size;
    for (i = 0; i < ub; ++i)
        if (arr[i] != a.arr[i])
            return arr[i] < a.arr[i];
    return m_Size <= a.m_Size;
}

    template <typename T>
    bool mVector<T>::operator > (const mVector<T> &a) const {
        int i, j, ub = m_Size < a.m_Size ? m_Size : a.m_Size;
        for (i = 0; i < ub; ++i)
            if (arr[i] != a.arr[i])
                return arr[i] > a.arr[i];
        return m_Size > a.m_Size;
    }

    template <typename T>
    bool mVector<T>::operator >= (const mVector<T> &a) const {
        int i, j, ub = m_Size < a.m_Size ? m_Size : a.m_Size;
        for (i = 0; i < ub; ++i)
            if (arr[i] != a.arr[i])
                return arr[i] > a.arr[i];
        return m_Size >= a.m_Size;
    }

    template <typename T>
    typename mVector<T>::iterator mVector<T>::begin() noexcept {
        return arr;
    }

    template <typename T>
    typename mVector<T>::const_iterator mVector<T>::cbegin() const noexcept {
        return arr;
    }

    template <typename T>
    typename mVector<T>::iterator mVector<T>::end() noexcept {
        return arr + m_Size;
    }

    template <typename T>
    typename mVector<T>::const_iterator mVector<T>::cend() const noexcept {
        return arr + m_Size;
    }

    template <typename T>
    typename mVector<T>::reverse_iterator mVector<T>::rbegin() noexcept {
        return reverse_iterator(arr + m_Size);
    }

    template <typename T>
    typename mVector<T>::const_reverse_iterator mVector<T>::crbegin() const noexcept {
        return reverse_iterator(arr + m_Size);
    }

    template <typename T>
    typename mVector<T>::reverse_iterator mVector<T>::rend() noexcept {
        return reverse_iterator(arr);
    }

    template <class T>
    typename mVector<T>::const_reverse_iterator mVector<T>::crend() const noexcept {
    return reverse_iterator(arr);
}
//Constructors
    template <class T>
    mVector<T>::mVector() noexcept {
            arr = new T[m_Capacity];
    }

    template <class T>
    mVector<T>::mVector(typename mVector<T>::size_type n) {
        size_type i;
        m_Capacity = n << 2;
        arr = new T[m_Capacity];
        for (i = 0; i < n; ++i)
            arr[i] = T();
        m_Size = n;
    }

    template <class T>
    mVector<T>::mVector(unsigned int n, const T &value) {
        size_type i;
        m_Capacity = n << 2;
        arr = new T[m_Capacity];
        for (i = 0; i < n; ++i)
            arr[i] = value;
        m_Size = n;
    }

    template <class T>
    mVector<T>::mVector(typename mVector<T>::iterator first, typename mVector<T>::iterator last) {
        size_type i, count = last - first;
        m_Capacity = count << 2;
        arr = new T[m_Capacity];
        for (i = 0; i < count; ++i, ++first)
            arr[i] = *first;
        m_Size = count;
    }

    template <class T>
    mVector<T>::mVector(std::initializer_list<T> lst) {
        m_Capacity = lst.size() << 2;
        arr = new T[m_Capacity];
        for (auto &item: lst)
            arr[m_Size++] = item;
    }

    template <class T>
    mVector<T>::mVector(const mVector<T> &other) {
        size_type i;
        m_Capacity = other.m_Capacity;
        arr = new T[m_Capacity];
        for (i = 0; i < other.m_Size; ++i)
            arr[i] = other.arr[i];
        m_Size = other.m_Size;
    }

    template <class T>
    mVector<T>::mVector(mVector<T> &&other) noexcept {
        size_type i;
        m_Capacity = other.m_Capacity;
        arr = new T[m_Capacity];
        for (i = 0; i < other.m_Size; ++i)
            arr[i] = std::move(other.arr[i]);
        m_Size = other.m_Size;
    }

    template <class T>
    mVector<T>::~mVector() {
        delete [] arr;
    }

    //Access Operators
    template <class T>
    mVector<T> & mVector<T>::operator = (const mVector<T> &other) {
        size_type i;
        if (m_Capacity < other.m_Size) {
            m_Capacity = other.m_Size << 2;
            reallocate();
        }
        for (i = 0; i < other.m_Size; ++i)
            arr[i] = other.arr[i];
        m_Size = other.m_Size;
    }

    template <class T>
    mVector<T> & mVector<T>::operator = (mVector<T> &&other) {
        size_type i;
        if (m_Capacity < other.m_Size) {
            m_Capacity = other.m_Size << 2;
            reallocate();
        }
        for (i = 0; i < other.m_Size; ++i)
            arr[i] = std::move(other.arr[i]);
        m_Size = other.m_Size;
    }

    template <class T>
    mVector<T> & mVector<T>::operator = (std::initializer_list<T> lst) {
        if (m_Capacity < lst.size()) {
            m_Capacity = lst.size() << 2;
            reallocate();
        }
        m_Size = 0;
        for (auto &item: lst)
            arr[m_Size++] = item;
    }

    template <class T>
    typename mVector<T>::reference mVector<T>::operator [](typename mVector<T>::size_type idx) {
        return arr[idx];
    }

    template <class T>
    typename mVector<T>::reference mVector<T>::at(typename mVector<T>::size_type pos) {
        if (pos < m_Size)
            return arr[pos-1];
        else
            throw std::out_of_range("out of range");
    }

    template <class T>
    typename mVector<T>::reference mVector<T>::front() {
        return arr[0];
    }


    template <class T>
    typename mVector<T>::reference mVector<T>::back() {
        return arr[m_Size - 1];
    }


    template <class T>
    inline void mVector<T>::reallocate() {
        T *tarr = new T[m_Capacity];
        memcpy(tarr, arr, m_Size * sizeof(T));
        delete [] arr;
        arr = tarr;
    }

    //Size and Capacity
    template <class T>
    bool mVector<T>::empty() const noexcept {return m_Size == 0;}

    template <class T>
    int mVector<T>::size() const noexcept {return m_Size;}

    template <class T>
    int mVector<T>::capacity() const noexcept {return m_Capacity;}

    template <class T>
    void mVector<T>::resize(int n) {
        if (n > m_Size) {
            if (n > m_Capacity) {
                m_Capacity = n;
                reallocate();
            }
        } else {
            for (int i = m_Size; i < n; ++i)
                arr[i].~T();
        }
        m_Size = n;
    }

    template <class T>
    void mVector<T>::reserve(int n) {
        if(n > m_Capacity){
            m_Capacity = n;
            reallocate();
        }
    }

    template <class T>
    void mVector<T>::shrink_to_fit() {
        if(m_Capacity > m_Size){
            m_Capacity = m_Size;
            reallocate();
        }
    }

    // Modifiers
    template <class T>
    void mVector<T>::push_back(const T &n) {
        if(m_Size == m_Capacity){
            m_Capacity <<=2;
            reallocate();

        }
        arr[m_Size-1] = n;
        m_Size++;
    }
    template <class T>
    void mVector<T>::pop_back() {
        m_Size--;
        arr[m_Size].~T();

    }
    template <class T>
    typename mVector<T>::iterator mVector<T>::insert( mVector<T>::const_iterator it, const T &n) {

        mVector<T>::iterator iit = &arr[it - arr];
        if (m_Size == m_Capacity) {
            m_Capacity <<= 2;
            reallocate();
        }
        memmove(iit + 1, iit, (m_Size - (it - arr)) * sizeof(T));
        ++m_Size;
        *(iit) = n;
        return iit;
    }
    template <class T>
    void mVector<T>::assign(typename mVector<T>::size_type count, const T &value) {
        size_type i;
        if (count > m_Capacity) {
            m_Capacity = count << 2;
            reallocate();
        }
        for (i = 0; i < count; ++i)
            arr[i] = value;
        m_Size = count;
    }

    template <class T>
    typename  mVector<T>::iterator mVector<T>::erase(mVector<T>::const_iterator it) {
        iterator iit = &arr[it - arr];
        (*iit).~T();
        memmove(iit, iit + 1, (m_Size - (it - arr)-1) * sizeof(T));
        --m_Size;
        return iit;
    }
    template <class T>
    typename  mVector<T>::iterator mVector<T>::erase(const_iterator itFirst , const_iterator itLast){
        iterator f = &arr[itFirst - arr];
        if (itFirst == itLast) return f;
        auto a = *itFirst;
        auto b = *itLast;
        while (itFirst != itLast) {

            (*itFirst).~T();
            ++itFirst;
        }

        memmove(f, itLast, (m_Size - (itLast - arr)) * sizeof(T));
        m_Size -= b - a;

        return f;
    }


    template <class T>
    void mVector<T>::clear() noexcept {
        size_type i;
        for (i = 0; i<m_Size; i++){
            arr[i].~T();
        }
        m_Size = 0;
    }
    template <typename T>
    template <class ... Args>
    typename mVector<T>::iterator mVector<T>::emplace(const_iterator it, Args && ... args) {
        mVector<T>::iterator iit = &arr[it - arr];
        if (m_Size == m_Capacity) {
            m_Capacity <<= 2;
            reallocate();
        }
        arr[m_Size - *iit] = std::move( T( std::forward<Args>(args) ... ) );
        *iit =  T( std::forward<Args>(args) ... );
        ++m_Size;
    }




#endif //VEKTORIUS_MVECTOR_H
