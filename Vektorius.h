#ifndef UNTITLED_VEKTORIUS_H
#define UNTITLED_VEKTORIUS_H

#include <iostream>
#include <cstring>


template <class T>
class vector{
private:
    int m_size = 0; //Vektoriaus dydis
    int m_capacity = 10; //Vieta naujiems elementams
    T *arr; //Elementu array'us

public:
    typedef unsigned int size_type;
    typedef T* iterator;
    typedef T& reference;
    typedef const T * const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    vector() noexcept ; //konstruktorius
    vector( const vector<T> &) noexcept; //Copy konstruktorius
    vector<T> & operator = (const vector<T> &); //Copy assignment'as
    vector (vector<T> &&) noexcept ; // Move konstruktorius
    vector<T> &operator = (vector<T> &&) noexcept ; //Move assignment'as
    ~vector(); //dekonstruktorius
    vector(std::initializer_list<T>); //List konstruktorius
    vector<T> & operator = (std::initializer_list<T>); //List assignment'as


    //Iteratoriai:

    iterator begin() noexcept ;
    iterator end() noexcept ;
    const_iterator cbegin() const noexcept ;
    const_iterator cend() const noexcept ;
    reverse_iterator rbegin() noexcept ;
    reverse_iterator rend() noexcept ;
    const_reverse_iterator crbegin() const noexcept ;
    const_reverse_iterator crend() const noexcept ;

    //loginiai operatoriai

    bool operator == (const vector<T> &) const;
    bool operator != (const vector<T> &) const;
    bool operator < (const vector<T> &) const;
    bool operator <= (const vector<T> &) const;
    bool operator > (const vector<T> &) const;
    bool operator >= (const vector<T> &) const;

    //nariu accessinimo budai

    reference operator [](size_type);
    reference at(size_type);
    reference front();
    reference back();

    //Funkcijos
    bool empty() const noexcept;
    int size() const noexcept;
    int capacity() const noexcept;
    void resize(int);
    void reserve(int);
    void shrink_to_fit();
    void push_back( const T &);
    void push_back( T &&);
    void pop_back();
    iterator insert(iterator, const T &);
    iterator erase(iterator);
    iterator erase(iterator, iterator);
    void clear() noexcept;
    template <class ... Args> iterator emplace(iterator, Args && ... args);
    template <class ... Args> iterator emplace_back( Args && ... args);

};


    //Default konstruktorius
    template <class T>
    vector<T>::vector() noexcept {
      arr = new T[m_capacity];
    }
    // Copy konstruktorius
    template <class T>
    vector<T>::vector(const vector<T> & rhs) noexcept {
        m_capacity = rhs.m_capacity;
        arr = new T[m_capacity];
        for (size_type i=0; i!= rhs.m_size; ++i){
            arr[i] = rhs.arr[i];
        }
        m_size = rhs.m_size;
    }
    // Move konstruktorius
    template <class T>
    vector<T>::vector(vector<T> && rhs) noexcept {
        m_capacity = rhs.m_capacity;
        arr = new T[m_capacity];
        for(size_type i=0; i!=rhs.m_size; ++i){
            arr[i]=std::move(rhs.arr[i]);
        }
        m_size = rhs.m_size;
    }
    // Destruktorius
    template <class T>
    vector<T>::~vector() {
        delete [] arr;
    }
    // Copy assignment'as
    template <class T>
    vector<T>& vector<T>::operator =(const vector<T> &rhs) {
        if(m_capacity > rhs.m_size){
            m_capacity = rhs.m_capacity;
            arr = new T[m_capacity];
            for(size_type i =0; i!= rhs.m_size; ++i){
                arr[i] = rhs.arr[i];
            }
            m_size = rhs.m_size;
        } else {
            m_capacity = rhs.m_size << 2;
            T *tempArr = new T[m_capacity];
            memcpy(tempArr, arr, sizeof(T));
            delete []arr;
            arr = tempArr;
        }

    }
    // Move assignment'as
    template <class T>
    vector<T>& vector<T>::operator = (vector<T> && rhs) noexcept {
        if(m_capacity > rhs.m_size){
            m_capacity = rhs.m_capacity;
            arr = new T[m_capacity];
            for(size_type i =0; i!= rhs.m_size; ++i){
                arr[i] = std::move(rhs.arr[i]);
            }
            m_size = rhs.m_size;
        } else {
            m_capacity = rhs.m_size << 2;
            T *tempArr = new T[m_capacity];
            memcpy(tempArr, arr, sizeof(T));
            delete []arr;
            arr = tempArr;
        }
    }

    //list konstruktorius
      template <class T>
      vector<T>::vector(std::initializer_list<T> rhs) {
            m_capacity = rhs.size()*2;
            arr = new T[rhs.size()];
            for(auto &item : rhs){
                arr[m_size++] = item;
            }
    }

    //List assignment'as
    template <class T>
    vector<T>& vector<T>::operator=(std::initializer_list<T> rhs) {
        if(m_capacity > rhs.size()){
            m_size =0;
            for(auto &item: rhs){
                arr[m_size++]=item;
            }
        }else{
            m_capacity = rhs.size() << 2;
            T *tempArr = new T[m_capacity];
            memcpy(tempArr, arr, sizeof(T));
            delete []arr;
            arr = tempArr;
        }
    }

    template <class T>
    typename vector<T>::iterator vector<T>::begin() noexcept {
        return arr;
    }
    template <class T>
    typename vector<T>::const_iterator vector<T>::cbegin() const noexcept {
        return arr;
    }
    template <class T>
    typename vector<T>::iterator vector<T>::end() noexcept {
        return arr+m_size;
    }
    template <class T>
    typename vector<T>::const_iterator vector<T>::cend() const noexcept {
        return arr+m_size;
    }
    template <class T>
    typename vector<T>::reverse_iterator vector<T>::rbegin() noexcept {
        return arr+m_size;
    }
    template <class T>
    typename vector<T>::reverse_iterator vector<T>::rend() noexcept {
        return arr;
    }
    template <class T>
    typename vector<T>::const_reverse_iterator vector<T>::crbegin() const noexcept {
        return arr+m_size;
    }
    template <class T>
    typename vector<T>::const_reverse_iterator vector<T>::crend() const noexcept {
        return arr;
    }

    //Loginiai operatoriai

    // "=="
    template <class T>
    bool vector<T>::operator ==(const vector<T> & rhs) const {
        if (m_size != rhs.m_size) return false;
        for (size_type i = 0; i != m_size; ++i) {
            if (arr[i] != rhs.arr[i]) return false;
            return true;
        }
    }

    // "!='
    template <class T>
    bool vector<T>::operator !=(const vector<T> & rhs) const {
        if (m_size != rhs.m_size) return true;
        for (size_type i = 0; i != m_size; ++i) {
            if (arr[i] != rhs.arr[i]) return true;
            return false;
        }
    }

    //"<"
    template <class T>
    bool vector<T>::operator<(const vector<T> &rhs) const {
        if(m_size < rhs.m_size) return true;
            else return false;
    }
    //">"
    template <class T>
    bool vector<T>::operator>(const vector<T> &rhs) const {
        if (m_size > rhs.m_size) return true;
        else return false;
    }
    //"<="
    template <class T>
    bool vector<T>::operator<=(const vector<T> &rhs) const {
        if(m_size<=rhs.m_size) return true;
        else return false;
    }
    //">="
    template <class T>
    bool vector<T>::operator>=(const vector<T> &rhs) const {
        if(m_size >= rhs.m_size)return true;
        else return false;
    }

    //Accesinimo budai

    //[] operatorius
    template <class T>
    typename vector<T>::reference vector<T>::operator[](unsigned int n) {
        return arr[n];
    }
    // at
    template <class T>
    typename vector<T>::reference vector<T>::at(unsigned int n) {
        return arr[n-1];
    }
    // front
    template <class T>
    typename vector<T>::reference vector<T>::front() {
        return arr[m_size-1];
    }
    //back
    template <class T>
    typename vector<T>::reference vector<T>::back() {
        return arr[0];
    }


    //Funkcijos

    template <class T>
    bool vector<T>::empty() const noexcept {
        if(m_size == 0)return true;
            else return false;
    }
    template <class T>
    int vector<T>::size() const noexcept {
        return m_size;
    }

    template <class T>
    int vector<T>::capacity() const noexcept {
        return m_capacity;
    }
    template <class T>
    void vector<T>::resize(int n) {
        if( n > m_size){
            if(n < m_capacity){
                m_capacity = n*2;
                T *tempArr = new T[m_capacity];
                memcpy(tempArr, arr,m_size*  sizeof(T));
                delete []arr;
                arr = tempArr;
                m_size = n;
            } else reserve(n);

        } else {
            m_capacity = n;
            for (size_type i = n; n < m_size; ++i ){
                arr[i].~T();
            }
            m_size = n;
        }
    }
    template <class T>
    void vector<T>::reserve(int n) {
        if(n > m_capacity){
            m_capacity = n;
            T *tempArr = new T[m_capacity];
            memcpy(tempArr, arr,m_size*  sizeof(T));
            delete []arr;
            arr = tempArr;
        }
    }
    template <class T>
    void vector<T>::shrink_to_fit() {
        if( m_capacity > m_size){
            m_capacity = m_size;
            T *tempArr = new T[m_capacity];
            memcpy(tempArr, arr,m_size*  sizeof(T));
            delete []arr;
            arr = tempArr;
        }
    }
    template <class T>
    void vector<T>::push_back( const T &rhs) {
        if(m_size == m_capacity){
            m_capacity *=2;
            T *tempArr = new T[m_capacity];
            memcpy(tempArr, arr,m_size* sizeof(T));
            delete []arr;
            arr = tempArr;
        }
        arr[m_size]=rhs;
        m_size++;
    }
    template <class T>
    void vector<T>::push_back( T &&rhs){
        if(m_size == m_capacity){

            m_capacity *= 2;
            T *tempArr = new T[m_capacity];
            memcpy(tempArr, arr,m_size*  sizeof(T));
            delete []arr;
            arr = tempArr;
            arr[m_size]=std::move(rhs);
            m_size++;

        }else
            arr[m_size]=std::move(rhs);
            m_size++;
    }

    template <class T>
    void vector<T>::pop_back() {
        --m_size;
        arr[m_size].~T();
    }
    template<class T>
    typename vector<T>::iterator vector<T>::insert(vector<T>::iterator it, const T &rhs) {
        if(m_size == m_capacity){
            m_capacity *=2;
            T *tempArr = new T[m_capacity];
            memcpy(tempArr, arr,m_size*  sizeof(T));
            delete []arr;
            arr = tempArr;
        }
        int i=0;
        auto itx = it;
        auto itend = end();
        auto size = itend-itx;
        T* tempArray = new T[size];
        for(itx; itx != itend; itx++){
            tempArray[i] = *itx;
            ++i;
        }
        *it = rhs;
        ++m_size;
        i = 0;
        itx = it;
        for(itx; itx!=itend; ++itx){
            *(itx+1) = tempArray[i];
            ++i;
        }return it;
    }



    template <class T>
    typename vector<T>::iterator vector<T>::erase(vector<T>::iterator it) {

        if(it == end()){
            pop_back();
            return it;
        }   else {
            auto itend = end();
            auto size = itend - it-1;
            auto itx = it+1;
            T* tempArray = new T[size];
            int i =0;
            for(itx; itx != itend; itx++){
                tempArray[i] = *itx;
                ++i;

            }
             itx = it;
            i = 0;
            for (itx; itx != itend; itx++){
                *itx = tempArray[i];
                ++i;
            }
            m_size--;
            return it;
    }
    }

    template <class T>
    typename vector<T>::iterator  vector<T>::erase(vector<T>::iterator itFirst, vector<T>::iterator itLast) {

        auto itend = end();
        auto size = itend - itLast;
        auto itx = itLast+1;
        T* tempArray = new T[size];
        int i =0;
        for(itx; itx != itend; itx++){
            tempArray[i] = *itx;
            ++i;

        }
        itx = itFirst;
        i = 0;
        for (itx; itx != itend; itx++){
            *itx = tempArray[i];
            ++i;
        }
        m_size -= (itLast-itFirst)+1;
        return itFirst;
    }
    template <class T>
    void vector<T>::clear() noexcept {
        for (size_type i = 0; i != m_size; ++i){
            arr[i].~T();
        }
        m_size = 0;
    }
    template <class T>
    template <class ... Args>
    typename vector<T>::iterator vector<T>::emplace(vector<T>::iterator it, Args &&... args) {
        if(m_size == m_capacity){
            m_capacity *=2;
            T *tempArr = new T[m_capacity];
            memcpy(tempArr, arr,m_size*  sizeof(T));
            delete []arr;
            arr = tempArr;
        }
        size_type i =0;
        auto itx = it;
        auto itend = end();
        auto size = itend-itx;
        T* tempArray = new T[size];
        for(itx; itx != itend; itx++){
            tempArray[i] = *itx;
            ++i;
        }

        *it = std::move(T(std::forward<Args>(args)...));
        ++m_size;
        i = 0;
        itx = it;
        for(itx; itx!=itend; ++itx) {
            *(itx + 1) = tempArray[i];
            ++i;
        }return it;
    }
    template <class T>
    template <class... Args>
    typename vector<T>::iterator vector<T>::emplace_back(Args &&... args) {
        if(m_size== m_capacity){
            m_capacity *=2;
            T *tempArr = new T[m_capacity];
            memcpy(tempArr, arr,m_size*  sizeof(T));
            delete []arr;
            arr = tempArr;
        }

        arr[m_size] = std::move(T(std::forward<Args>(args)...));
        ++m_size;

    }


#endif //UNTITLED_VEKTORIUS_H
