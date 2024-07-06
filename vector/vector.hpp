#pragma once
#include <iostream>
#include <initializer_list>
#include <stdexcept>


template <typename T>

class Vector
{
    private:
        size_t size;
        size_t capacity;
        T* array;
        
    public:
        Vector();
        Vector(const Vector& copiedVector);
        Vector(size_t elements, T value = 0);
        //Vector(const std::initializer_list<T>& list);

        ~Vector();

        void pushBack(T value);
        void popBack();

        bool isEmpty() const;
        size_t Size() const;
        size_t Capacity() const;

        bool operator==(const Vector& copiedVector) const;
        bool operator!=(const Vector& copiedVector) const;

        friend std::ostream& operator <<(std::ostream& ostr, const Vector& copiedVector);

        Vector& operator =(const Vector& copiedVector);

        T& operator[](size_t index);
        T& At(size_t index);
        T& Front();
        T& Back();

        void Insert(size_t index, T value);
        void Erase(size_t index);
        void Clear();
};