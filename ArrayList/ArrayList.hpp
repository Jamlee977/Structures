#pragma once

// ! Omar Estietie
#include <iostream>
#include <initializer_list>
#include <ctime>
// #include <cstdlib>

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
        arrayList_ptr++;
        return *this;
    }

    ArrayListIterator operator++(int) {
        ArrayListIterator iterator = *this;
        ++(*this);
        return iterator;
    }


    ArrayListIterator& operator--() {
        arrayList_ptr--;
        return *this;
    }

    ArrayListIterator operator--(int) {
        ArrayListIterator iterator = *this;
        --(*this);
        return iterator;
    }


    ReferenceType operator[](int index) {
        return *(arrayList_ptr + index);
    }


    PointerType operator->() {
        return arrayList_ptr;
    }


    ReferenceType operator*() {
        return *arrayList_ptr;
    }


    bool operator==(const ArrayListIterator& other) const {
        return arrayList_ptr == other.arrayList_ptr;
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

        if (newCapacity < SIZE) SIZE = newCapacity;

        for (size_t i = 0; i < SIZE; i++) newBlock[i] = std::move(arrayList[i]);

        ::operator delete(arrayList, newCapacity * sizeof(T));
        arrayList = newBlock;
        CAPACITY = newCapacity;
    }

    /**
     * @brief A heapify method
     * 
     * @param arrayList 
     * @param Size 
     * @param index 
     */
    void heapify(T arrayList[], size_t Size, size_t index)
    {
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

    size_t len(std::string lenOfString) {
        int i, countOfStringChars = 0;
        for (int i = 0; lenOfString[i]; i++)
        {
            countOfStringChars++;
        }
        return countOfStringChars;
    }

    
public:
    using ValueType = T;
    using U         = T;
    using Iterator  = ArrayListIterator<ArrayList<T>>;
public:

    ArrayList() { reAllocate(2); }

    ArrayList(std::initializer_list<T> arrayList) {
        reAllocate(2);
        for(auto&& element : arrayList) {
            push(element);
        }
    }

    ~ArrayList() { ::operator delete(arrayList, CAPACITY * sizeof(T)); }

    /**
     * @brief A push method to enter elements into the ArrayList to the end of it
     * 
     * @param VALUE The value
     */
    void push(const T& VALUE) {

        if (SIZE >= CAPACITY) reAllocate(CAPACITY + CAPACITY / 2);
        

        arrayList[SIZE] = VALUE;
        SIZE++;
    }

    /**
     * @brief A push method to enter elements into the ArrayList to the end of it
     * 
     * @param VALUE The value
     */
    void push(T&& VALUE) {

        if (SIZE >= CAPACITY) reAllocate(CAPACITY + CAPACITY / 2);
        

        arrayList[SIZE] = std::move(VALUE);
        SIZE++;
    }

    /**
     * @brief A pop method to remove the last element of an ArrayList
     */
    void pop() {
        if(SIZE > 0) {
            SIZE--;
            arrayList[SIZE].~T();
        }
    }

    /**
     * @brief An empty method to make an ArrayList empty
     * 
     * @return bool
     */
    bool empty() {
        for (size_t i = 0; i < SIZE; i++) arrayList[i].~T();

        SIZE = 0;
        return true;
    }

    /**
     * @brief A method that determines if an ArrayList is empty and returns true or false
     * 
     * @return bool
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

        new(&arrayList[SIZE]) T(std::forward<Arguments>(ARGS)...);
        return arrayList[SIZE++];
    }

    T& operator[] (size_t INDEX) { return arrayList[INDEX]; } 
    const T& operator[] (size_t INDEX) const { return arrayList[INDEX]; } 

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
     * @brief A method that returns the value of the given index
     * 
     * @param IN The index
     * @return T 
     */
    T at(size_t IN) { return arrayList[IN]; }

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
        for (size_t i = start; i < end; i++) arrayList[i] = VALUE;
        return 1;
    }

    /**
     * @brief A method used to find a given value in an ArrayList
     * 
     * @param any The value
     * @return bool 
     */
    bool find(T any) {
        for(size_t i = 0; i < SIZE; i++) {
            if (arrayList[i] == any) return true;
        }
        return false;
    }

    /**
     * @brief A method that reverses a list
     */
    void reverse() {
        T temp;

        for(size_t i = 0; i < SIZE / 2; i++){
            temp = arrayList[i];
            arrayList[i] = arrayList[SIZE-i-1];
            arrayList[SIZE-i-1] = temp;
        }
    }

    /**
     * @brief The beginning of the iterator
     * 
     * @return Iterator 
     */
    Iterator begin() { return Iterator(arrayList); }

    /**
     * @brief The ending of the iterator
     * 
     * @return Iterator 
     */
    Iterator end() { return Iterator(arrayList + SIZE); }
    
    /**
     * @brief A method that returns the first value of the ArrayList
     * 
     * @return T 
     */
    T front() { return arrayList[0]; }

    /**
     * @brief A method that returns the last value of the ArrayList
     * 
     * @return T 
     */
    T back() { return arrayList[SIZE - 1]; }

    /**
     * @brief A method that assigns an ArrayList with a given value to a given index
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
            temp[i] = arrayList[j];
        }
        
        empty();
        for(size_t i = 0; i < newSize; i++) {
            push(temp[i]);
        }

        delete[] temp;
        return true;
    }

    /**
     * @brief A function that removes a specific index from an ArrayList
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
            temp[i] = arrayList[j];
        }

        empty();
        for(size_t i = 0; i < newSize; i++) {
            push(temp[i]);
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
        size_t newSize = size() - 1;
        T* temp = new T[newSize];

        size_t SIZE = 0;
        size_t subOfSize = 0;
        for(size_t i = 0, j = 0; i < size() - 1; i++, j++) {
            if(this->arrayList[j] == any) {
                i--;
                subOfSize++;
                continue;
            }
            temp[i] = arrayList[j];
            SIZE++;
        }

        this->empty();
        for(size_t i = 0; i <= SIZE - subOfSize; i++) {
            push(temp[i]);
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
    bool remove_e(T any) {
        size_t newSize = size() - 1;
        T* temp = new T[newSize];

        size_t SIZE = 0;
        size_t count = 0;
        for(size_t i = 0, j = 0; i < size() - 1; i++, j++) {
            if(count == 0 && this->arrayList[j] == any) {
                i--;
                count++;
                continue;
            }
            
            temp[i] = arrayList[j];
            SIZE++;
        }

        this->empty();
        for(size_t i = 0; i <= SIZE - 1; i++) {
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
            if (arrayList[i] == old_value) arrayList[i] = new_value;
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
            if (arrayList[i] == old_value) {
                arrayList[i] = new_value;
                break;
            }
        }
    }
        
    /**
     * @brief A method that sorts an ArrayList
     */
    void sort() {
        for (int i = SIZE / 2 - 1; i >= 0; i--) heapify(arrayList, SIZE, i);

        for (int i = SIZE - 1; i > 0; i--) {
            std::swap(arrayList[0], arrayList[i]);

            heapify(arrayList, i, 0);
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
     * @brief A range class that can be used to assign an ArrayList of integers.
     * 
     * @param number The starting of the range. 
     */ 
    bool range(size_t number) {
        size_t i;
        if(0 > number) return false;
        for (i = 0; i < number; i++) {
            push(i);
        }
        return true;
    }

    /**
     * @brief A range class that can be used to assign an ArrayList of integers.
     * 
     * @param firstNumber The starting of the range.
     * @param lastNumber The ending of the range.
     * 
     */ 
    bool range(int firstNumber, int lastNumber) {
        int i;
        if(firstNumber > lastNumber) return false;
        for (i = firstNumber; i < lastNumber; i++) {
            push(i);
        }
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
            push(i);
            i = i + step;
        }
        return true;
    }

    /**
     * @brief A method that will filter a specific condition and change the ArrayList into that condition (currently it's only "even" and "odd")
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
                if((int)arrayList[i] % 2 == 0) {
                    temp[j] = arrayList[i];
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
                if((int)arrayList[i] % 2 != 0) {
                    temp[j] = arrayList[i];
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

    /**
     * @brief A method used to swap 2 elements in an ArrayList with indecies starting from 1 for the first index
     * 
     * @param firstIndex 
     * @param secondIndex 
     */
    void swap(int firstIndex, int secondIndex) {
        firstIndex = firstIndex - 1;
        secondIndex = secondIndex - 1;
        T temp = arrayList[firstIndex];
        arrayList[firstIndex] = arrayList[secondIndex];
        arrayList[secondIndex] = temp;
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
        if(this->size() != other.size()) return 0;
        for(size_t i = 0; i < this->size(); i++) if(this->arrayList[i] != other.arrayList[i]) return 0; 
        return 1;
    }

    void shuffle() {

        srand(time(NULL));

        for(size_t i = this->size() - 1; i > 0; i--) {
            size_t j = rand() % (i + 1);
            std::swap(this->arrayList[i], this->arrayList[j]);
        }
        return;
    }


   friend std::ostream& operator<<(std::ostream& out, const ArrayList<T>& Object) {
        out << "[";
        for(size_t i = 0; i < Object.size(); i++) {
            if(i == 0) out << ' ' << Object.arrayList[0] << ", ";
            else if(i != Object.size() - 1) out << Object.arrayList[i] << ", ";
            if(i == Object.size() - 1) out << Object.arrayList[i] << ' ';
        }
        out << "]" << "\n";
        
       return out;
    }

};

#endif
