#pragma once

#include <iostream>

#ifndef VECTOR_HPP
#define VECTOR_HPP

template <typename T>
class Vector {
private:
    T* VEC = nullptr;

    size_t SIZE = 0;
    size_t CAPACITY = 0;

    reAllocate(size_t newCapacity) {
        T* newBlock = (T*)::operator new(newCapacity * sizeof(T));

        if (newCapacity < SIZE) SIZE = newCapacity;

        for (size_t i = 0; i < SIZE; i++) newBlock[i] = std::move(VEC[i]);

        ::operator delete(VEC, newCapacity * sizeof(T));
        VEC = newBlock;
        CAPACITY = newCapacity;
    }
public:
    Vector() {
        reAllocate(2);
    }

    ~Vector() {
        ::operator delete(VEC, CAPACITY * sizeof(T));
    }

    void push(const T& VALUE) {

        if (SIZE >= CAPACITY) reAllocate(CAPACITY + CAPACITY / 2);
        

        VEC[SIZE] = VALUE;
        SIZE++;
    }

    void push(T&& VALUE) {

        if (SIZE >= CAPACITY) reAllocate(CAPACITY + CAPACITY / 2);
        

        VEC[SIZE] = std::move(VALUE);
        SIZE++;
    }

    void pop() {
        if(SIZE > 0) {
            SIZE--;
            VEC[SIZE].~T();
        }
    }

    void empty() {
        for (size_t i = 0; i < SIZE; i++) VEC[i].~T();

        SIZE = 0;
    }

    template <typename... Arguments>
    T& emplace(Arguments&&... ARGS) {
        if (SIZE >= CAPACITY) reAllocate(CAPACITY + CAPACITY / 2);

        new(&VEC[SIZE]) T(std::forward<Arguments>(ARGS)...);
        return VEC[SIZE++];
    }

    T& operator[] (size_t INDEX) { return VEC[INDEX]; } 
    const T& operator[] (size_t INDEX) const { return VEC[INDEX]; } 

    size_t size() { return SIZE; }
    size_t capacity() { return CAPACITY; }

    void print() {
        for(size_t i = 0; i < size(); i++) std::cout << VEC[i] << '\n';
        
        std::cout << std::endl;
    }
};

#endif
