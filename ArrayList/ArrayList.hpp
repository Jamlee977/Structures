#pragma once

/**
 * @file ArrayList.hpp
 * @author Omar Estietie (jamlee977@outlook.com), (@OmarEstietie on Twitter)
 * @brief It is a data structure that is used to store a collection of data. 
 * It is a dynamic data structure that can be resized as needed. 
 * It is a linear data structure. It is a collection of data that is indexed by a number. 
 * It works like a vector but it has much more methods and features taken from other languages like Javascript, Python and Java.
 * @version 2.0
 * @date 2022-05-09 
 */

// ! Omar Estietie
#include <iostream>
#include <initializer_list>
#include <ctime>
#include <functional>

#ifndef ArrayList_HPP
#define ArrayList_HPP

template<typename ArrayList>
class ArrayListIterator {
public:
    using ValueType = typename ArrayList::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
    PointerType arrayList_ptr;
public:
    ArrayListIterator(PointerType pointer) : arrayList_ptr(pointer) {}

    ArrayListIterator& operator++() {
        this->arrayList_ptr++;
        return *this;
    }

    ArrayListIterator operator++(int) {
        ArrayListIterator iterator = *this;
        ++(*this);
        return iterator;
    }


    ArrayListIterator& operator--() {
        this->arrayList_ptr--;
        return *this;
    }

    ArrayListIterator operator--(int) {
        ArrayListIterator iterator = *this;
        --(*this);
        return iterator;
    }


    ReferenceType operator[](int index) {
        return *(this->arrayList_ptr + index);
    }


    PointerType operator->() {
        return this->arrayList_ptr;
    }


    ReferenceType operator*() {
        return *this->arrayList_ptr;
    }


    bool operator==(const ArrayListIterator& other) const {
        return this->arrayList_ptr == other.arrayList_ptr;
    }

    bool operator!=(const ArrayListIterator& other) const {
        return !(*this == other);
    }
};

template <typename T>
class ArrayList {
private:
    T* arrayList = nullptr;

    size_t SIZE = 0;
    size_t CAPACITY = 0;

    /**
     * @brief A method to reallocate the memory
     * 
     * @param newCapacity 
     */
    void reAllocate(size_t newCapacity) {
        T* newBlock = new T[newCapacity];

        if (newCapacity < this->SIZE) this->SIZE = newCapacity;

        for (size_t i = 0; i < SIZE; i++) newBlock[i] = std::move(this->arrayList[i]);

        ::operator delete(this->arrayList, newCapacity * sizeof(T));
        this->arrayList = newBlock;
        this->CAPACITY = newCapacity;
    }

    /**
     * @brief A heapify method
     * 
     * @param arrayList 
     * @param Size 
     * @param index 
     */
    void heapify(T arrayList[], size_t Size, size_t index) {
        size_t largest = index; 
        size_t member = 2 * index + 1; 
        size_t other_member = 2 * index + 2; 
        
        if (member < Size && arrayList[member] > arrayList[largest])
            largest = member;
    
        if (other_member < Size && arrayList[other_member] > arrayList[largest])
            largest = other_member;
    
        if (largest != index) {
            std::swap(arrayList[index], arrayList[largest]);
    
            heapify(arrayList, Size, largest);
        }
    }

public:
    using ValueType = T;
    using U         = T;
    using Iterator  = ArrayListIterator<ArrayList<T>>;
public:

    ArrayList() { this->reAllocate(2); }

    ArrayList(std::initializer_list<T> arrayList) {
        this->reAllocate(2);
        for(const auto& element : arrayList) {
            this->push(element);
        }
    }

    ~ArrayList() { ::operator delete(this->arrayList, this->CAPACITY * sizeof(T)); }

    /**
     * @brief A push method to enter elements into the ArrayList to the end of it
     * 
     * @param VALUE The value
     */
    size_t push(const T& VALUE) {

        if (this->SIZE >= this->CAPACITY) this->reAllocate(this->CAPACITY + this->CAPACITY / 2);
        

        this->arrayList[this->SIZE] = VALUE;
        this->SIZE++;

        return this->size();
    }

    /**
     * @brief A push method to enter elements into the ArrayList to the end of it
     * 
     * @param VALUE The value
     */
    size_t push(T&& VALUE) {

        if (this->SIZE >= this->CAPACITY) this->reAllocate(this->CAPACITY + this->CAPACITY / 2);
        

        this->arrayList[this->SIZE] = std::move(VALUE);
        this->SIZE++;

        return this->size();
    }

    /**
     * @brief A pop method to remove the last element of an ArrayList
     */
    T pop() {
        T value = this->arrayList[this->size() - 1];
        if(this->SIZE > 0) {
            this->SIZE--;
            this->arrayList[this->SIZE].~T();
        }
        return value;
    }

    /**
     * @brief A function that removes a specific index from an ArrayList
     * 
     * @param indecies 
     * @return bool
     */
    T pop(size_t index) {
        if(index == 0) return this->arrayList[this->size()];
        index = index - 1;
        if(index > this->size() || (index + 1) > this->size()) return this->arrayList[this->size()];
        if(index == this->size()) {
            this->pop();
            return this->arrayList[this->size() - 1];
        }

        auto value = this->arrayList[index];
        size_t newSize = this->size() - 1;
        T* temp = new T[newSize];

        for(size_t i = 0, j = 0; i < this->size() - 1; i++, j++) {
            if(j == index) {
                i--;
                continue;
            }
            temp[i] = this->arrayList[j];
        }

        this->empty();
        for(size_t i = 0; i < newSize; i++) {
            this->push(temp[i]);
        }

        delete[] temp;
        return value;
    }

    /**
     * @brief An empty method to make an ArrayList empty
     * 
     * @return bool
     */
    bool empty() {
        for (size_t i = 0; i < this->SIZE; i++) this->arrayList[i].~T();

        this->SIZE = 0;
        return true;
    }

    /**
     * @brief A method that determines if an ArrayList is empty and returns true or false
     * 
     * @return bool
     */
    bool is_empty() {
        if(this->SIZE != 0) return 0;
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
        if (this->SIZE >= this->CAPACITY) this->reAllocate(this->CAPACITY + this->CAPACITY / 2);

        new(&this->arrayList[this->SIZE]) T(std::forward<Arguments>(ARGS)...);
        return this->arrayList[this->SIZE++];
    }

    T& operator[](int INDEX) {
        if(INDEX >= 0) return this->arrayList[INDEX];
        INDEX = INDEX + 1;
        int temp = (this->size() + INDEX);
        return this->arrayList[temp - 1];
    }
    
    const T& operator[](int INDEX) const { 
        if(INDEX >= 0) return this->arrayList[INDEX];
        INDEX = INDEX + 1;
        int temp = (this->size() + INDEX);
        return this->arrayList[temp - 1];     
    }

    /**
     * @brief A method to return the size of the list
     * 
     * @return size_t 
     */
    size_t size() const { return this->SIZE; }

    /**
     * @brief A method to return the capacity of the list
     * 
     * @return size_t 
     */
    size_t capacity() const { return this->CAPACITY; }

    /**
     * @brief A method that returns the value of the given index
     * 
     * @param IN The index
     * @return T 
     */
    T at(size_t IN) const {
        IN = IN - 1;
        return this->arrayList[IN];
    }

    /**
     * @brief A method that fills an ArrayList with a given value
     * 
     * @param VALUE The value that you want to fill
     * @param start The start
     * @param end The end
     * @return bool
     */
    bool fill(T VALUE, size_t start, size_t end) {
        if (start > end) return 0;
        for (size_t i = start; i < end; i++) this->arrayList[i] = VALUE;
        return 1;
    }

    /**
     * @brief A method used to find a given value in an ArrayList
     * 
     * @param any The value
     * @return bool 
     */
    bool find(T any) {
        for(size_t i = 0; i < this->SIZE; i++) if(this->arrayList[i] == any) return true;
        return false;
    }

    /**
     * @brief A method that reverses a list
     * 
     * @return ArrayList&
     */
    ArrayList& reverse() {
        T temp;

        for(size_t i = 0; i < this->SIZE / 2; i++){
            temp = this->arrayList[i];
            this->arrayList[i] = this->arrayList[this->SIZE - i - 1];
            this->arrayList[this->SIZE - i - 1] = temp;
        }
        return *this;
    }

    /**
     * @brief The beginning of the iterator
     * 
     * @return Iterator 
     */
    Iterator begin() { return Iterator(this->arrayList); }

    /**
     * @brief The ending of the iterator
     * 
     * @return Iterator 
     */
    Iterator end() { return Iterator(this->arrayList + this->SIZE); }
    
    /**
     * @brief A method that returns the first value of the ArrayList
     * 
     * @return T 
     */
    T front() { return this->arrayList[0]; }

    /**
     * @brief A method that returns the last value of the ArrayList
     * 
     * @return T 
     */
    T back() { return this->arrayList[SIZE - 1]; }

    /**
     * @brief A method that returns the first value of the ArrayList
     * 
     * @return size_t
     */ 
    size_t first() { return 0; }

    /**
     * @brief A method that returns the last value of the ArrayList
     * 
     * @return size_t 
     */
    size_t last() { return this->size() - 1; }


    /**
     * @brief A method that assigns an ArrayList with a given value to a given index
     * 
     * @param indecies The index
     * @param any The value
     */
    void assign(size_t indecies, T any) {
        for(size_t i = 0; i < indecies; i++)
            this->push(any);
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
        if(index == this->size()) {
            push(any);
            return true;
        }
        if(index > this->size()) return false;
        if(index < 0) return false;
        size_t newSize = this->size() + 1;
        T* temp = new T[newSize];

        for(size_t i = 0, j = 0; i < newSize; i++, j++) {
            if(i == index) {
                j--;
                temp[i] = any;
                continue;
            }
            temp[i] = this->arrayList[j];
        }
        
        empty();
        for(size_t i = 0; i < newSize; i++) {
            this->push(temp[i]);
        }

        delete[] temp;
        return true;
    }

    /**
     * @brief A function that removes a specific value from an ArrayList
     * 
     * @param any 
     * @return bool
     */
    bool remove(T any) {
        size_t newSize = this->size() - 1;
        T* temp = new T[newSize];

        size_t SIZE = 0;
        size_t count = 0;
        for(size_t i = 0, j = 0; i < this->size() - 1; i++, j++) {
            if(count == 0 && this->arrayList[j] == any) {
                i--;
                count++;
                continue;
            }
            
            temp[i] = this->arrayList[j];
            SIZE++;
        }

        this->empty();
        for(size_t i = 0; i <= SIZE - 1; i++) {
            this->push(temp[i]);
        }

        delete[] temp;
        return true;
    }

    /**
     * @brief A function that removes all specific value from an ArrayList
     * 
     * @param any 
     * @return bool
     */
    bool remove_all(T any) {
        size_t newSize = this->size() - 1;
        T* temp = new T[newSize];

        size_t SIZE = 0;
        size_t subOfSize = 0;
        for(size_t i = 0, j = 0; i < this->size() - 1; i++, j++) {
            if(this->arrayList[j] == any) {
                i--;
                subOfSize++;
                continue;
            }
            temp[i] = this->arrayList[j];
            SIZE++;
        }

        this->empty();
        for(size_t i = 0; i <= SIZE - subOfSize; i++) {
            this->push(temp[i]);
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
        for (size_t i = 0; i < this->size(); i++)
            if (this->arrayList[i] == old_value) this->arrayList[i] = new_value;
    }

    /**
     * @brief A method that exchanges the first value in "old_value" with the "new_value"
     * 
     * @param new_value The new value
     * @param old_value The old value
     */
    void quick_replace(T new_value, T old_value) {
        for (size_t i = 0; i < this->size(); i++)
        {
            if (this->arrayList[i] == old_value) {
                this->arrayList[i] = new_value;
                break;
            }
        }
    }
        
    /**
     * @brief A method that sorts an ArrayList
     */
    void sort() {
        for (int i = this->SIZE / 2 - 1; i >= 0; i--) heapify(this->arrayList, this->SIZE, i);

        for (int i = this->SIZE - 1; i > 0; i--) {
            std::swap(this->arrayList[0], this->arrayList[i]);

            heapify(this->arrayList, i, 0);
        }
    }

    /**
     * @brief A method that checks if an ArrayList is sorted
     * 
     * @return bool
     */
    bool is_sorted() {
        if(this->size() == 0) return false;
        if(this->size() == 1) return true;

        for(size_t i = 1; i < this->size(); i++) if(this->arrayList[i - 1] > this->arrayList[i]) return false;

        return true;
    }

    /**
     * @brief A range class that can be used to assign an ArrayList of numbers.
     * 
     * @param number The starting of the range. 
     */ 
    bool range(size_t number) {
        size_t i;
        if(0 > number) return false;
        for (i = 0; i < number; i++) this->push(i);
        return true;
    }

    /**
     * @brief A range class that can be used to assign an ArrayList of numbers.
     * 
     * @param firstNumber The starting of the range.
     * @param lastNumber The ending of the range.
     * 
     */ 
    bool range(int firstNumber, int lastNumber) {
        int i;
        if(firstNumber > lastNumber) return false;
        for (i = firstNumber; i < lastNumber; i++) this->push(i);
        return true;
    }

    /**
     * @brief A range class that can be used to assign an ArrayList.
     * range(0, 21, 2) will assign the even numbers between 0 and 21 including 0
     * 
     * @param firstNumber The starting of the range.
     * @param lastNumber The ending of the range.
     * @param step The step for moving (start from 1).
     * 
     */
    bool range(int firstNumber, int lastNumber, size_t step) {
        step = step - 1;
        int i;
        if(firstNumber > lastNumber) return false;
        for (i = firstNumber; i < lastNumber; i++) {
            this->push(i);
            i = i + step;
        }
        return true;
    }

    /**
     * @brief This method can be used to filter out values using lambda function such as:
     * list.filter([](T any) { return any > 10; }); will output the values that are greater than 10 inside that list. 
     * list.filter([](const std::string& any) { return any.size() > 4; }); will output the values that are greater than 4 inside that list. 
     * 
     * @param condition 
     * @return ArrayList& 
     */
    ArrayList& filter(const std::function<bool(const T& value)>& condition) {
        for(int i = 0; i < this->size(); i++) {
            if(!condition(this->arrayList[i])) {
                this->remove(this->arrayList[i]);
                i--;
            }
        }
        return *this;
    }
    
    /**
     * @brief Calls an anonymous function on each element of an arraylist, and returns an arraylist that contains the results.
     * 
     * @param condition 
     * @return ArrayList& 
     */
    ArrayList& forEach(const std::function<void(T& value)>& condition) {
        for(size_t i = 0; i < this->size(); i++) {
            condition(this->arrayList[i]);
        }
        return *this;
    }

    /**
     * @brief Calls an anonymous function on each element of an arraylist, and returns an arraylist that contains the results.
     * 
     * @param condition 
     * @return ArrayList& 
     */
    ArrayList& map(const std::function<T(const T& value)>& condition) {
        for(size_t i = 0; i < this->size(); i++) {
            this->arrayList[i] = condition(this->arrayList[i]);
        }
        return *this;
    }

    /**
     * @brief Calls an anonymous function on each element of an arraylist, and removes the elements that return true.
     * 
     * @param condition 
     * @return ArrayList& 
     */
    ArrayList& remove(const std::function<bool(const T& value)>& condition) {
        for(size_t i = 0; i < this->size(); i++) {
            if(condition(this->arrayList[i])) {
                this->remove(this->arrayList[i]);
                i--;
            }
        }
        return *this;
    }

    /**
     * @brief Removes the first element from an array and returns it.
     * If the array is empty, undefined is returned and the arraylist is not modified.
     * 
     * @return T 
     */
    T shift() {
        if(this->size() == 0) return 0;
        T temp = this->arrayList[0];
        this->remove(this->arrayList[0]);
        return temp;
    }
    
    /**
     * @brief Returns a copy of a section of an arraylist.
     * For both start and end.
     * 
     * @return ArrayList& 
     */
    ArrayList& slice() {
        return *this;
    }

    /**
     * @brief Returns a copy of a section of an arraylist.
     * For both start and end.
     * @return ArrayList& 
     */
    ArrayList& slice(size_t start) {
        if(start > this->size()) return *this;
        ArrayList<T> temp;
        for(size_t i = start; i < this->size(); i++) {
            temp.push(this->arrayList[i]);
        }
        *this = temp;
        return *this;
    }

    /**
     * @brief Returns a copy of a section of an arraylist.
     * For both start and end.
     * 
     * @return ArrayList& 
     */
    ArrayList& slice(size_t start, size_t end) {
        if(start > end) return *this;
        if(start > this->size()) return *this;
        if(end > this->size()) end = this->size();

        ArrayList<T> temp;
        for(size_t i = start; i < end; i++) {
            temp.push(this->arrayList[i]);
        }
        *this = temp;
        return *this;
    }

    /**
     * @brief Combines two or more arraylists.
     * 
     * @param other 
     * @return ArrayList 
     */
    ArrayList operator+(const ArrayList& other) {
        ArrayList<T> temp;
        for(size_t i = 0; i < this->size(); i++) temp.push(this->arrayList[i]);
        for(size_t i = 0; i < other.size(); i++) temp.push(other.arrayList[i]);
        return temp;
    }

    /**
     * @brief Combines two or more arraylists.
     * 
     * @param other 
     * @return ArrayList 
     */
    ArrayList operator+=(const ArrayList& other) {
        for(size_t i = 0; i < other.size(); i++) this->push(other.arrayList[i]);
        return *this;
    }

    /**
     * @brief Removes an arraylist's elements from another arraylist.
     * 
     * @param other 
     * @return ArrayList 
     */
    ArrayList operator-(const ArrayList& other) {
        ArrayList<T> temp;
        for(size_t i = 0; i < this->size(); i++) temp.push(this->arrayList[i]);
        for(size_t i = 0; i < other.size(); i++) temp.remove(other.arrayList[i]);
        return temp;
    }

    /**
     * @brief Removes an arraylist's elements from another arraylist.
     * 
     * @param other 
     * @return ArrayList 
     */
    ArrayList operator-=(const ArrayList& other) {
        for(size_t i = 0; i < other.size(); i++) this->remove(other.arrayList[i]);
        return *this;
    }

    /**
     * @brief Combines two arraylists.
     * 
     * @param other 
     * @return ArrayList 
     */
    ArrayList concat(const ArrayList<T>& other) {
        ArrayList<T> newList;
        for(size_t i = 0; i < this->size(); i++) {
            newList.push(this->arrayList[i]);
        }
        for(size_t i = 0; i < other.size(); i++) {
            newList.push(other.arrayList[i]);
        }
        return newList;
    }

    /**
     * @brief Removes a sub list from the list.
     * 
     * @param sublist 
     */
    void remove_sublist(const ArrayList<T>& sublist) {
        for(size_t i = 0; i < sublist.size(); i++) {
            this->remove(sublist.arrayList[i]);
        }
    }

    /**
     * @brief Determines whether all the members of an array satisfy the specified test.
     * 
     * @param condition 
     * @return bool
     */
    bool every(const std::function<bool(const T& value)>& condition) {
        for(int i = 0; i < this->size(); i++) {
            if(!condition(this->arrayList[i])) return false;
        }
        return true;
    }

    /**
     * @brief Determines whether the specified callback function returns true for any element of an array.
     * 
     * @param condition 
     * @return bool
     */
    bool some(const std::function<bool(const T& value)>& condition) {
        for(int i = 0; i < this->size(); i++) {
            if(condition(this->arrayList[i])) return true;
        }
        return false;
    }
    
    /**
     * @brief Returns the value of the first element in the array where predicate is true.
     * 
     * @param condition 
     * @return T 
     */
    T find(const std::function<bool(const T& value)>& condition) {
        for(int i = 0; i < this->size(); i++) {
            if(condition(this->arrayList[i])) return this->arrayList[i];
        }
        return T();
    }

    /**
     * @brief This method returns the index of an element specified in the third parameter.
     * 
     * @param start start of range
     * @param end end of range
     * @param value 
     * @return int 
     */
    int findIndex(size_t start, size_t end, const T& value) {
        for(int i = start; i < end; i++) {
            if(this->arrayList[i] == value) return i;
        }
        return -1;
    }

    /**
     * @brief Returns the index of the first element in the array where predicate is true, and -1 otherwise.
     * 
     * @param condition 
     * @return int 
     */
    int findIndex(const std::function<T(const T& value)>& condition) {
        for(int i = 0; i < this->size(); i++) {
            if(condition(this->arrayList[i])) return i;
        }
        return -1;
    }

    /**
     * @brief This method returns the first element that satisfies the condition.
     * 
     * @param start start of range
     * @param end end of range
     * @param condition 
     * @return T 
     */
    T find_if(size_t start, size_t end, const std::function<bool(const T& value)>& condition) {
        for(int i = start; i < end; i++) {
            if(condition(this->arrayList[i])) return this->arrayList[i];
        }
        return T();
    }
    
    /**
     * @brief This method returns the first element that does not satisfy the condition.
     * 
     * @param start start of range
     * @param end end of range
     * @param condition 
     * @return T 
     */
    T find_if_not(size_t start, size_t end, const std::function<bool(const T& value)>& condition) {
        for(int i = start; i < end; i++) {
            if(!condition(this->arrayList[i])) return this->arrayList[i];
        }
        return T();
    }

    /**
     * @brief A method used to swap 2 elements in an ArrayList with indecies starting from 1 for the first index
     * 
     * @param firstIndex 
     * @param secondIndex 
     */
    void swap(size_t firstIndex, size_t secondIndex) {
        firstIndex = firstIndex - 1;
        secondIndex = secondIndex - 1;
        T temp = arrayList[firstIndex];
        arrayList[firstIndex] = arrayList[secondIndex];
        arrayList[secondIndex] = temp;
    }

    /**
     * @brief A method to swap all elements between 2 ArrayLists
     * 
     * @param other Another Arraylist to swap elements with
     * @return bool 
     */
    bool swap(ArrayList<T>& other) {
        size_t sizeOfThis  = this->size();
        size_t sizeOfOther = other.size();

        T* temp = new T[sizeOfThis];
        for(size_t i = 0; i < sizeOfThis; i++) temp[i] = this->arrayList[i];
        this->empty();

        for(size_t i = 0; i < sizeOfOther; i++) this->push(other.arrayList[i]);
        other.empty();
        for(size_t i = 0; i < sizeOfThis; i++) other.push(temp[i]);

        delete[] temp;
        return true;
    }

    /**
     * @brief A methods that can be used to insert an ArrayList into an array that has a different size compared to the arraylist
     * 
     * @param Array 
     * @param size 
     */
    void toArray(T Array[], size_t Size) {
        for(size_t i = 0; i < Size; i++) { Array[i] = this->arrayList[i]; }
    }

    /**
     * @brief A methods that can be used to insert an ArrayList into an array which has the same size as the arraylist
     * 
     * @param Array 
     */
    void toArray(T Array[]) {
        for(size_t i = 0; i < size(); i++) { Array[i] = this->arrayList[i]; }
    }

    /**
     * @brief A method that can be used to check if 2 ArrayLists are equal for all elements
     * 
     * @param other 
     * @return bool
     */
    bool is_equal(ArrayList<T> other) {
        if(this->size() != other.size()) return false;
        for(size_t i = 0; i < this->size(); i++) if(this->arrayList[i] != other.arrayList[i]) return false; 
        return true;
    }

    /**
     * @brief A method that shuffles an ArrayList
     * 
     */
    void shuffle() {
        srand(time(NULL));

        for(size_t i = this->size() - 1; i > 0; i--) {
            size_t j = rand() % (i + 1);
            std::swap(this->arrayList[i], this->arrayList[j]);
        }
        return;
    }

    /**
     * @brief A method to copy an ArrayList into another ArrayList
     * 
     * @param other 
     * @return bool
     */
    bool clone(const ArrayList<T>& other) {
        if(!this->is_empty()) this->empty();

        for(size_t i = 0; i < other.size(); i++) {
            this->push(other.arrayList[i]);
        }
        return true;
    }
    
    ArrayList& operator=(const ArrayList<T>& list) {
        this->clone(list);
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& out, const ArrayList<T>& Object) {
        if(Object.size() == 1) {
            out << "[ " << Object.arrayList[0] << " ]\n";
            return out;
        }
        out << "[";
        for(size_t i = 0; i < Object.size(); i++) {
            if(i == 0) out << ' ' << Object.arrayList[0] << ", ";
            else if(i != Object.size() - 1) out << Object.arrayList[i] << ", ";
            if(i == Object.size() - 1) out << Object.arrayList[i] << ' ';
        }
        out << "]\n";
        
       return out;
    }
};

#endif
