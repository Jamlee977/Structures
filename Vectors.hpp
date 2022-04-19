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

    /**
     * @brief A method to reallocate the memory
     * 
     * @param newCapacity 
     */
    void reAllocate(size_t newCapacity) {
        T* newBlock = new T[newCapacity];

        if (newCapacity < SIZE) SIZE = newCapacity;

        for (size_t i = 0; i < SIZE; i++) newBlock[i] = std::move(VEC[i]);

        ::operator delete(VEC, newCapacity * sizeof(T));
        VEC = newBlock;
        CAPACITY = newCapacity;
    }

    /**
     * @brief A heapify method
     * 
     * @param vec 
     * @param Size 
     * @param index 
     */
    void heapify(T vec[], size_t Size, size_t index)
    {
        size_t largest = index; 
        size_t member = 2 * index + 1; 
        size_t other_member = 2 * index + 2; 
        
        if (member < Size && vec[member] > vec[largest])
            largest = member;
    
        if (other_member < Size && vec[other_member] > vec[largest])
            largest = other_member;
    
        if (largest != index) {
            std::swap(vec[index], vec[largest]);
    
            heapify(vec, Size, largest);
        }
    }
    
public:

    Vector() {
        reAllocate(2);
    }

    ~Vector() {
        ::operator delete(VEC, CAPACITY * sizeof(T));
    }

    /**
     * @brief A push method to enter elements into the vector to the end of it
     * 
     * @param VALUE The value
     */
    void push(const T& VALUE) {

        if (SIZE >= CAPACITY) reAllocate(CAPACITY + CAPACITY / 2);
        

        VEC[SIZE] = VALUE;
        SIZE++;
    }

    /**
     * @brief A push method to enter elements into the vector to the end of it
     * 
     * @param VALUE The value
     */
    void push(T&& VALUE) {

        if (SIZE >= CAPACITY) reAllocate(CAPACITY + CAPACITY / 2);
        

        VEC[SIZE] = std::move(VALUE);
        SIZE++;
    }

    /**
     * @brief A pop method to remove the last element of a vector
     */
    void pop() {
        if(SIZE > 0) {
            SIZE--;
            VEC[SIZE].~T();
        }
    }

    /**
     * @brief An empty method to make a vector empty
     * 
     * @return true 
     * @return false 
     */
    bool empty() {
        for (size_t i = 0; i < SIZE; i++) VEC[i].~T();

        SIZE = 0;
        return true;
    }

    /**
     * @brief A method that determines if a vector is empty and returns true or false
     * 
     * @return true 
     * @return false 
     */
    bool is_empty() {
        if(SIZE != 0) return 0;
        return 1;
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
        if (SIZE >= CAPACITY) reAllocate(CAPACITY + CAPACITY / 2);

        new(&VEC[SIZE]) T(std::forward<Arguments>(ARGS)...);
        return VEC[SIZE++];
    }

    T& operator[] (size_t INDEX) { return VEC[INDEX]; } 
    const T& operator[] (size_t INDEX) const { return VEC[INDEX]; } 

    /**
     * @brief A method to return the size of the vector
     * 
     * @return size_t 
     */
    size_t size() { return SIZE; }

    /**
     * @brief A method to return the capacity of the vector
     * 
     * @return size_t 
     */
    size_t capacity() { return CAPACITY; }

    /**
     * @brief A method that prints a vector
     */
    void print() {
        for(size_t i = 0; i < size(); i++) std::cout << VEC[i] << '\n';        
    }

    /**
     * @brief A method that returns the value of the given index
     * 
     * @param IN The index
     * @return T 
     */
    T at(size_t IN) { return VEC[IN]; }

    /**
     * @brief A method that fills a vector with a given value
     * 
     * @param VALUE The value that you want to fill
     * @param start The start
     * @param end The end
     * @return bool
     */
    bool fill(T VALUE, size_t start, size_t end) {
        if (start > end) return 0;
        for (size_t i = start; i < end; i++) VEC[i] = VALUE;
        return 1;
    }

    /**
     * @brief A method used to find a given value in a vector
     * 
     * @param any The value
     * @return bool 
     */
    bool find(T any) {
        for(size_t i = 0; i < SIZE; i++) {
            if (VEC[i] == any) return true;
        }
        return false;
    }

    /**
     * @brief A method that reverses a vector
     */
    void reverse() {
        T temp;

        for(size_t i = 0; i < SIZE / 2; i++){
            temp = VEC[i];
            VEC[i] = VEC[SIZE-i-1];
            VEC[SIZE-i-1] = temp;
        }
    }

    /**
     * @brief A method to return the first index (0)
     * 
     * @return T 
     */
    T begin() { return 0; }
    
    /**
     * @brief A method to return the first index (the size)
     * 
     * @return T 
     */
    T end() { return SIZE; }
    
    /**
     * @brief A method that returns the first value of the vector
     * 
     * @return T 
     */
    T front() { return VEC[0]; }

    /**
     * @brief A method that returns the last value of the vector
     * 
     * @return T 
     */
    T back() { return VEC[SIZE - 1]; }

    /**
     * @brief A method that assigns a vector with a given value to a given index
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
     * @brief A method that inserts a value to an index and moves the other indecies by 1
     * 
     * @param indecies The index you want the value to be in
     * @param any The value that you want to be entered
     * @return bool 
     */
    bool insert(size_t indecies, T any) {
        if (SIZE - indecies == -1) {
            push(any);
            return 1;
        }
        if (SIZE - indecies < 0 && SIZE - indecies != -1) return 0;
        SIZE = CAPACITY++;

        size_t i, j;

        T* temp = new T[SIZE - indecies];
        for (i = indecies, j = 0; i < SIZE; i++, j++) temp[j] = VEC[i];

        reAllocate(SIZE + SIZE / 2);
        if (!(sizeof(T) == sizeof(int) 
            || sizeof(T) == sizeof(float) 
            || sizeof(T) == sizeof(double)
            || sizeof(T) == sizeof(long long)
            || sizeof(T) == sizeof(long double)
            || sizeof(T) == sizeof(long)
            || sizeof(T) == sizeof(unsigned int)
            || sizeof(T) == sizeof(short int)
            )) SIZE++;
            
        VEC[indecies] = any;
        for (i = indecies + 1, j = 0; i < SIZE; i++, j++) VEC[i] = temp[j];

        delete[] temp;
        return 1;
    }

    /**
     * @brief A method that exchanges all the values assigned in "old_value" with the "new_value"
     * 
     * @param new_value The new value
     * @param old_value The old value
     */
    void exchange(T new_value, T old_value) {
        for (size_t i = 0; i < size(); i++)
        {
            if (VEC[i] == old_value) VEC[i] = new_value;
        }
    }

    /**
     * @brief A method that exchanges the first value in "old_value" with the "new_value"
     * 
     * @param new_value The new value
     * @param old_value The old value
     */
    void quick_exchange(T new_value, T old_value) {
        for (size_t i = 0; i < size(); i++)
        {
            if (VEC[i] == old_value) {
                VEC[i] = new_value;
                break;
            }
        }
    }
        
    /**
     * @brief A method that sorts a vector
     */
    void sort() {
        for (int i = SIZE / 2 - 1; i >= 0; i--) heapify(VEC, SIZE, i);

        for (int i = SIZE - 1; i > 0; i--) {
            std::swap(VEC[0], VEC[i]);

            heapify(VEC, i, 0);
        }
    }

    
};

#endif