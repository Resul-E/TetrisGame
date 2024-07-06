#include "headers/vector.hpp"


template <typename T>
Vector<T>::Vector()
    :   size(0),
        capacity(5),
        array(new T[capacity])
{
    
}

template <typename T>
Vector<T>::Vector(const Vector<T>& copiedVector )
    :   size(copiedVector.size),
        capacity(copiedVector.capacity),
        array(new T[capacity])
{
    for(int i = 0; i < copiedVector.Size(); i++)
    {
        array[i] = copiedVector.array[i];
    }
}

template <typename T>
Vector<T>::Vector(size_t elements, T value)
    :   size(elements),
        capacity(elements + 5),
        array(new T[capacity])
{
    for (int i = 0; i < size; i++)
    {
        array[i] = value;
    }
}

// template <typename T>
// Vector<T>::Vector(const std::initializer_list<T>& list)
//     :   size(0),
//         capacity(list.size() + 5),
//         array(new T[capacity])
// {
//     for(T i : list)
//     {
//         pushBack(i);
//     }
// }

template <typename T>
Vector<T>::~Vector()
{
    delete[] array;
}

template <typename T>
void Vector<T>::pushBack(T value)
{
    if(size < capacity)
    {    
        array[size] = value;
        ++size;
    }
    else
    {
        capacity *= 2;
        T* newarray = new T[capacity];
        
        for(int i = 0; i < size; i++)
        {
            newarray[i] = array[i];
        }

        array[size] = value;
        size++;

        delete[] array;
        array = newarray;
    }
}

template <typename T>
void Vector<T>::popBack()
{
    if(size == 0)
    {
        ;
    }
    else
    {
        size--;
    }
}

template <typename T>
bool Vector<T>::isEmpty() const
{
    return size == 0;
}

template <typename T>
size_t Vector<T>::Size() const
{
    return size;
}

template <typename T>
size_t Vector<T>::Capacity() const
{
    return capacity;
}

template <typename T>
bool Vector<T>::operator==(const Vector<T>& copiedVector) const
{
    if(Size() != copiedVector.Size()) return false;

    for(int i = 0; i < Size(); i++)
    {
        if(array[i] !=  copiedVector.array[i]) return false;
    } 

    return true;
}

template <typename T>
bool Vector<T>::operator!=(const Vector<T>& copiedVector) const
{
    return !(*this == copiedVector);
}

template <typename T>
std::ostream& operator <<(std::ostream& ostr, const Vector<T>& copiedVector)
{
    for(int i = 0; i < copiedVector.size; i++)
    {
        std::cout << copiedVector.array[i] << " ";
    }
    ostr << " || ";

    for(int i = copiedVector.size; i < copiedVector.capacity; i++)
    {
        ostr << copiedVector.array[i] << " ";
    }
    ostr << std::endl;

    return ostr;
}


template <typename T>
Vector<T>& Vector<T>::operator =(const Vector<T>& copiedVector)
{
    if(copiedVector.size > size)
    {
        delete[] array;
        capacity = copiedVector.size + 5;
        array = new T[capacity];
    }
    
    for(int i = 0; i < copiedVector.Size(); i++)
    {
        array[i] = copiedVector.array[i];
    }

    size = copiedVector.size;
    return *this;
}

template <typename T>
T& Vector<T>::operator[](size_t index)
{
    return array[index];
}

template <typename T>
T& Vector<T>::At(size_t index)
{
    if((index < 0) && (index >= size))
    {
        throw std::out_of_range("Dont do it anakin.");
    }
    else
    {
    return array[index];
    }
}

template <typename T>
T& Vector<T>::Front()
{
    return array[0];
}

template <typename T>
T& Vector<T>::Back()
{
    return array[size-1];
}

template <typename T>
void Vector<T>::Insert(size_t index, T value)
{
    if((index < 0) || (index >= size))
    {
        ;
    }
    else if(size != capacity)
    {
        for(int i = size - 1; i >= index; i--)
        {
            array[i + 1] = array[i];
        }
     
        array[index] = value;
        size++;
    }
    else
    {
        capacity *= 2;
        T* newArray = new T[capacity];
     
        for(int i = 0; i < size; i++)
        {
            newArray[i] = array[i];
        }
     
        delete[] array;
        array = newArray;
        Insert(index, value);
    }
}

template <typename T>
void Vector<T>::Erase(size_t index)
{
    if((index < 0) || (index >= size))
    {
        ;
    }
    
    for(int i = index; i < size - 1; i++)
    {
        array[i] = array[i + 1];
    }
    
    size--;
}

template <typename T>
void Vector<T>::Clear()
{
    size = 0;
}