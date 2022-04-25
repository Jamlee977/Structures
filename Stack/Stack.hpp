#pragma once

#include <iostream>

#ifndef STACK_HPP
#define STACK_HPP

template<typename Stack>
class StackIterator {
public:
    using ValueType = typename Stack::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
    PointerType stack_ptr;
public:
    StackIterator(PointerType pointer) : stack_ptr(pointer) {}

    StackIterator& operator++() {
        stack_ptr++;
        return *this;
    }

    StackIterator operator++(int) {
        StackIterator iterator = *this;
        ++(*this);
        return iterator;
    }


    StackIterator& operator--() {
        stack_ptr--;
        return *this;
    }

    StackIterator operator--(int) {
        StackIterator iterator = *this;
        --(*this);
        return iterator;
    }


    ReferenceType operator[](int index) {
        return *(stack_ptr + index);
    }


    PointerType operator->() {
        return stack_ptr;
    }


    ReferenceType operator*() {
        return *stack_ptr;
    }


    bool operator==(const StackIterator& other) const {
        return stack_ptr == other.stack_ptr;
    }

    bool operator!=(const StackIterator& other) const {
        return !(*this == other);
    }


};

template<typename T>
class Stack {
public:
    using ValueType = T;
    using U         = T;
    using Iterator  = StackIterator<Stack<T>>;
private:
    T* stack = nullptr;
    size_t Size = 0;
    size_t Capacity = 0;

    /**
     * @brief A method to reallocate the memory
     * 
     * @param newCapacity 
     */
    void reAllocate(size_t newCapacity) {
        T* newBlock = new T[newCapacity];

        if (newCapacity < Size) Size = newCapacity;

        for (size_t i = 0; i < Size; i++) newBlock[i] = std::move(stack[i]);

        ::operator delete(stack, newCapacity * sizeof(T));
        stack = newBlock;
        Capacity = newCapacity;
    }

public:
    Stack() {
        reAllocate(2);
    }

    ~Stack() { ::operator delete(stack, Capacity * sizeof(T)); }

    /**
     * @brief A push method to enter elements into the list to the end of it
     * 
     * @param VALUE The value
     */
    void push(const T& value) {
        if (Size > Capacity) reAllocate(Capacity + Capacity / 2);

        stack[Size] = value;
        Size++;
    }

    /**
     * @brief A push method to enter elements into the list to the end of it
     * 
     * @param VALUE The value
     */
    void push(T&& value) {

        if (Size >= Capacity) reAllocate(Capacity + Capacity / 2);
        

        stack[Size] = std::move(value);
        Size++;
    }

    /**
     * @brief A pop method to remove the last element of a list
     */
    void pop() {
        if (Size > 0) {
            Size--;
            stack[Size].~T();
        }
    }

    /**
     * @brief Returns the last value of the stack
     * 
     * @return T 
     */
    T top() {
        return stack[Size - 1];
    }

    /**
     * @brief An empty method to make a list empty
     * 
     * @return bool
     */
    bool empty() {
        for (size_t i = 0; i < Size; i++) stack[i].~T();

        Size = 0;
        return true;
    }

    /**
     * @brief A method that determines if a list is empty and returns true or false
     * 
     * @return bool
     */
    bool is_empty() {
        if(Size != 0) return 0;
        return 1;
    }

    /**
     * @brief A method to return the size of the list
     * 
     * @return size_t 
     */
    size_t size() { return Size; }

    /**
     * @brief A method that reverses a list
     */
    void reverse() {
        T temp;

        for(size_t i = 0; i < Size / 2; i++){
            temp = stack[i];
            stack[i] = stack[Size-i-1];
            stack[Size-i-1] = temp;
        }
    }

    /**
     * @brief A method that prints a list
     */
    void print() {
        if(!(is_empty())) {
            std::cout << "[ ";
            for(size_t i = 0; i < size(); i++) {
                if(i == size() - 1) std::cout << stack[i];
                if(i != size() - 1) std::cout << stack[i] << ", ";
            }
            std::cout << " ]" << '\n';
        }
        else std::cout << "[]";
    }

    /**
     * @brief The beginning of the iterator
     * 
     * @return Iterator 
     */
    Iterator begin() { return Iterator(stack); }

    /**
     * @brief The ending of the iterator
     * 
     * @return Iterator 
     */
    Iterator end() { return Iterator(stack + Size); }

    /**
     * @brief A method that assigns a stack with a given value to a given index
     * 
     * @param indecies The index
     * @param any The value
     */
    void assign(size_t indecies, T any) {
        for(size_t i = 0; i < indecies; i++) {
            push(any);
        }
    }

    /**
     * @brief An emplace method
     * 
     * @tparam Arguments 
     * @param ARGS 
     * @return T& 
     */
    template <typename... Arguments>
    T& emplace(Arguments&&... ARGS) {
        if (Size >= Capacity) reAllocate(Capacity + Capacity / 2);

        new(&stack[Size]) T(std::forward<Arguments>(ARGS)...);
        return stack[Size++];
    }

};

#endif