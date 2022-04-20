#pragma once

#include <iostream>
#include <initializer_list>

#ifndef list_HPP
#define list_HPP

template<typename list>
class listIterator {
public:
    using ValueType = typename list::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
    PointerType vec_ptr;
public:
    listIterator(PointerType pointer) : vec_ptr(pointer) {}

    listIterator& operator++() {
        vec_ptr++;
        return *this;
    }

    listIterator operator++(int) {
        listIterator iterator = *this;
        ++(*this);
        return iterator;
    }


    listIterator& operator--() {
        vec_ptr--;
        return *this;
    }

    listIterator operator--(int) {
        listIterator iterator = *this;
        --(*this);
        return iterator;
    }


    ReferenceType operator[](int index) {
        return *(vec_ptr + index);
    }


    PointerType operator->() {
        return vec_ptr;
    }


    ReferenceType operator*() {
        return *vec_ptr;
    }


    bool operator==(const listIterator& other) const {
        return vec_ptr == other.vec_ptr;
    }

    bool operator!=(const listIterator& other) const {
        return !(*this == other);
    }


};

template <typename T>
class list {
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
    using ValueType = T;
    using U         = T;
    using Iterator  = listIterator<list<T>>;
public:

    list() { reAllocate(2); }

    list(std::initializer_list<T> VEC) {
        reAllocate(2);
        for (auto element : VEC) {
            push(element);
        }
    }

    ~list() { ::operator delete(VEC, CAPACITY * sizeof(T)); }

    /**
     * @brief A push method to enter elements into the list to the end of it
     * 
     * @param VALUE The value
     */
    void push(const T& VALUE) {

        if (SIZE >= CAPACITY) reAllocate(CAPACITY + CAPACITY / 2);
        

        VEC[SIZE] = VALUE;
        SIZE++;
    }

    /**
     * @brief A push method to enter elements into the list to the end of it
     * 
     * @param VALUE The value
     */
    void push(T&& VALUE) {

        if (SIZE >= CAPACITY) reAllocate(CAPACITY + CAPACITY / 2);
        

        VEC[SIZE] = std::move(VALUE);
        SIZE++;
    }

    /**
     * @brief A pop method to remove the last element of a list
     */
    void pop() {
        if(SIZE > 0) {
            SIZE--;
            VEC[SIZE].~T();
        }
    }

    /**
     * @brief An empty method to make a list empty
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
     * @brief A method that determines if a list is empty and returns true or false
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
     * @brief A method to return the size of the list
     * 
     * @return size_t 
     */
    size_t size() const { return SIZE; }

    /**
     * @brief A method to return the capacity of the list
     * 
     * @return size_t 
     */
    size_t capacity() const { return CAPACITY; }

    /**
     * @brief A method that prints a list
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
     * @brief A method that fills a list with a given value
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
     * @brief A method used to find a given value in a list
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
     * @brief A method that reverses a list
     */
    void reverse() {
        T temp;

        for(size_t i = 0; i < SIZE / 2; i++){
            temp = VEC[i];
            VEC[i] = VEC[SIZE-i-1];
            VEC[SIZE-i-1] = temp;
        }
    }

    Iterator begin() { return Iterator(VEC); }
    Iterator end() { return Iterator(VEC + SIZE); }
    
    /**
     * @brief A method that returns the first value of the list
     * 
     * @return T 
     */
    T front() { return VEC[0]; }

    /**
     * @brief A method that returns the last value of the list
     * 
     * @return T 
     */
    T back() { return VEC[SIZE - 1]; }

    /**
     * @brief A method that assigns a list with a given value to a given index
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
    bool insert(size_t index, T any) {
        if(index == 0) return false;
        index = index - 1;
        if(index == size()) {
            push(any);
            return true;
        }
        if(index > size()) return false;
        if(index < 0) return false;
        size_t newSize = size() + 1;
        T* temp = new T[newSize];

        for(size_t i = 0, j = 0; i < newSize; i++, j++) {
            if(i == index) {
                j--;
                temp[i] = any;
                continue;
            }
            temp[i] = VEC[j];
        }
        
        empty();
        for(size_t i = 0; i < newSize; i++) {
            push(temp[i]);
        }

        delete[] temp;
        return true;
    }

    /**
     * @brief A function that removes a specific index from a list of strings
     * 
     * @param indecies 
     * @return bool
     */
    bool remove(size_t index) {
        if(index == 0) return false;
        index = index - 1;
        if(index > size()) return false;
        if(index == size()) {
            pop();
            return true;
        }
        if(index < 0) return false;
        size_t newSize = size() - 1;
        T* temp = new T[newSize];

        for(size_t i = 0, j = 0; i < size() - 1; i++, j++) {
            if(j == index) {
                i--;
                continue;
            }
            temp[i] = VEC[j];
        }

        empty();
        for(size_t i = 0; i < newSize; i++) {
            push(temp[i]);
        }

        delete[] temp;
        return true;
    }

    /**
     * @brief A method that exchanges all the values assigned in "old_value" with the "new_value"
     * 
     * @param new_value The new value
     * @param old_value The old value
     */
    void replace(T new_value, T old_value) {
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
    void quick_replace(T new_value, T old_value) {
        for (size_t i = 0; i < size(); i++)
        {
            if (VEC[i] == old_value) {
                VEC[i] = new_value;
                break;
            }
        }
    }
        
    /**
     * @brief A method that sorts a list
     */
    void sort() {
        for (int i = SIZE / 2 - 1; i >= 0; i--) heapify(VEC, SIZE, i);

        for (int i = SIZE - 1; i > 0; i--) {
            std::swap(VEC[0], VEC[i]);

            heapify(VEC, i, 0);
        }
    }

    /**
     * @brief A range class that can be used to assign a list of integers.
     * 
     * @param firstNumber The starting of the range.
     * @param lastNumber The ending of the range.
     * 
     */ 
    void range(int firstNumber, int lastNumber) {
        int i;
        for (i = firstNumber; i < lastNumber; i++) {
            push(i);
        }
    }

    /**
     * @brief A range class that can be used to assign a list.
     * 
     * @param firstNumber The starting of the range.
     * @param lastNumber The ending of the range.
     * @param step The step for moving (start from 1).
     * 
     */
    void range(int firstNumber, int lastNumber, size_t step) {
        step = step - 1;
        int i;
        for (i = firstNumber; i < lastNumber; i++) {
            push(i);
            i = i + step;
        }
    }

    /**
     * @brief A method that will filter a specific condition and change the list into that condition (currently it's only "even" and "odd")
     * 
     * @param condition even or odd
     * @return bool
     */
    bool filter(std::string condition) {
        size_t Size = size();
        size_t count = 0;
        T* temp = new T[Size];
        if(condition == "even") {
            for(size_t i = 0, j = 0; i < size(); i++) {
                if((int)VEC[i] % 2 == 0) {
                    temp[j] = VEC[i];
                    j++;
                    count++;
                }
            }
            empty();
            for(size_t i = 0; i < count; i++) {
                push(temp[i]);
            }
            if(is_empty()) return false;
            return true;

        }

        if(condition == "odd") {
            for(size_t i = 0, j = 0; i < size(); i++) {
                if((int)VEC[i] % 2 != 0) {
                    temp[j] = VEC[i];
                    j++;
                    count++;
                }
            }
            empty();
            for(size_t i = 0; i < count; i++) {
                push(temp[i]);
            }
            if(is_empty()) return false;
            return true;

        }

        delete[] temp;
    }
    
};

#endif
