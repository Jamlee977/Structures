#pragma once

// ! Omar Estietie
#include <iostream>
#include <initializer_list>

#ifndef TUPLE_HPP
#define TUPLE_HPP

template<typename Tuple>
class TupleIterator {
public:
    using ValueType = typename Tuple::ValueType;
    using PointerType = ValueType*;
    using ReferenceType = ValueType&;
    PointerType tuple_ptr;
public:
    TupleIterator(PointerType pointer) : tuple_ptr(pointer) {}

    TupleIterator& operator++() {
        tuple_ptr++;
        return *this;
    }

    TupleIterator operator++(int) {
        TupleIterator iterator = *this;
        ++(*this);
        return iterator;
    }


    TupleIterator& operator--() {
        tuple_ptr--;
        return *this;
    }

    TupleIterator operator--(int) {
        TupleIterator iterator = *this;
        --(*this);
        return iterator;
    }


    ReferenceType operator[](int index) {
        return *(tuple_ptr + index);
    }


    PointerType operator->() {
        return tuple_ptr;
    }


    ReferenceType operator*() {
        return *tuple_ptr;
    }


    bool operator==(const TupleIterator& other) const {
        return tuple_ptr == other.tuple_ptr;
    }

    bool operator!=(const TupleIterator& other) const {
        return !(*this == other);
    }
};

template<typename T>
class Tuple {
private:
    T* tuple = nullptr;
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

        for (size_t i = 0; i < Size; i++) newBlock[i] = std::move(tuple[i]);

        ::operator delete(tuple, newCapacity * sizeof(T));
        tuple = newBlock;
        Capacity = newCapacity;
    }

    /**
     * @brief A method that adds a value to the end of a tuple
     * 
     * @param VALUE 
     */
    void push(const T& VALUE) {

        if (Size >= Capacity) reAllocate(Capacity + Capacity / 2);
        

        tuple[Size] = VALUE;
        Size++;
    }

    /**
     * @brief A method that adds a value to the end of a tuple
     * 
     * @param VALUE 
     */
    void push(T&& VALUE) {

        if (Size >= Capacity) reAllocate(Capacity + Capacity / 2);
        

        tuple[Size] = std::move(VALUE);
        Size++;
    }

    /**
     * @brief A method that removes the last element of a tuple
     * 
     */
    void pop() {
        if(this->Size > 0) {
            this->Size--;
            this->tuple[this->Size].~T();
        }
    }

    /**
     * @brief A method that makes a tuple emoty
     * 
     * @return true 
     * @return false 
     */
    bool empty() {
        for (size_t i = 0; i < Size; i++) tuple[i].~T();

        Size = 0;
        return true;
    }

public:
    using ValueType = T;
    using U         = T;
    using Iterator  = TupleIterator<Tuple<T>>;
public:

    Tuple() { reAllocate(2); }

    Tuple(std::initializer_list<T> TUPLE) {
        reAllocate(2);
        for(auto&& element : TUPLE) {
            this->push(element);
        }
    }

    /**
     * @brief A method to get the size of the tuple
     * 
     * @return size_t 
     */
    size_t size() const { return Size; }

    /**
     * @brief The beginning of the iterator
     * 
     * @return Iterator 
     */
    Iterator begin() { return Iterator(tuple); }

    /**
     * @brief The ending of the iterator
     * 
     * @return Iterator 
     */
    Iterator end() { return Iterator(tuple + Size); }

    /**
     * @brief A class that allows tuples to use lists methods
     * 
     */
    class list {
    public:
        /**
         * @brief A method to get the value of a specific index (start from 1)
         * 
         * @param index 
         * @param TUPLE 
         * @return T 
         */
        T get(size_t index, Tuple<T>& TUPLE) { 
            index = index - 1;
            return TUPLE.tuple[index]; 
        }

        /**
         * @brief A push method to enter elements into the tuple to the end of it
         * 
         * @param value 
         * @param TUPLE 
         */
        void push(const T& value, Tuple<T>& TUPLE) {
            TUPLE.push(value);
        }

        /**
         * @brief A push method to enter elements into the tuple to the end of it
         * 
         * @param value 
         * @param TUPLE 
         */
        void push(T&& value, Tuple<T>& TUPLE) {
            TUPLE.push(value);
        }

        /**
         * @brief A method that removes the last element of a tuple
         * 
         * @param TUPLE 
         */
        void pop(Tuple<T>& TUPLE) {
            TUPLE.pop();
        }

        /**
         * @brief A function that removes a specific index from a tuple
         * 
         * @param index 
         * @param TUPLE 
         * @return true 
         * @return false 
         */
        bool pop(size_t index, Tuple<T>& TUPLE) {
            if(index == 0) return false;
            index = index - 1;
            if(index > TUPLE.size()) return false;
            if(index == TUPLE.size()) {
                this->pop(TUPLE);
                return true;
            }
            if(index < 0) return false;
            size_t newSize = TUPLE.size() - 1;
            T* temp = new T[newSize];

            for(size_t i = 0, j = 0; i < TUPLE.size() - 1; i++, j++) {
                if(j == index) {
                    i--;
                    continue;
                }
                temp[i] = TUPLE.tuple[j];
            }

            TUPLE.empty();
            for(size_t i = 0; i < newSize; i++) {
                this->push(temp[i], TUPLE);
            }            

            delete[] temp;
            return true;
        }

        /**
         * @brief A method to change a value of an index
         * 
         * @param index 
         * @param newValue 
         * @param TUPLE 
         * @return bool 
         */
        bool change(size_t index, T newValue, Tuple<T>& TUPLE) {
            index = index - 1;
            TUPLE.tuple[index] = newValue;
            return true;
        }

        /**
         * @brief A method that inserts a value to an index and moves the other indecies by 1
         * 
         * @param index 
         * @param any 
         * @param TUPLE 
         * @return bool 
         */
        bool insert(size_t index, T any, Tuple<T>& TUPLE) {
            if(index == 0) return false;
            index = index - 1;
            if(index == TUPLE.size()) {
                this->push(any, TUPLE);
                return true;
            }
            if(index > TUPLE.size()) return false;
            if(index < 0) return false;
            size_t newSize = TUPLE.size() + 1;
            T* temp = new T[newSize];

            for(size_t i = 0, j = 0; i < newSize; i++, j++) {
                if(i == index) {
                    j--;
                    temp[i] = any;
                    continue;
                }
                temp[i] = TUPLE.tuple[j];
            }
            TUPLE.empty();
            for(size_t i = 0; i < newSize; i++) {
                this->push(temp[i], TUPLE);
            }

            delete[] temp;
            return true;
        }

        /**
         * @brief A function that removes a specific value from a tuple
         * 
         * @param any 
         * @param TUPLE 
         * @return bool
         */
        bool remove(T any, Tuple<T>& TUPLE) {
            size_t newSize = TUPLE.size() - 1;
            T* temp = new T[newSize];

            size_t SIZE = 0;
            size_t count = 0;
            for(size_t i = 0, j = 0; i < TUPLE.size() - 1; i++, j++) {
                if(count == 0 && TUPLE.tuple[j] == any) {
                    i--;
                    count++;
                    continue;
                }
                
                temp[i] = TUPLE.tuple[j];
                SIZE++;
            }

            TUPLE.empty();
            for(size_t i = 0; i <= SIZE - 1; i++) {
                this->push(temp[i], TUPLE);
            }

            delete[] temp;
            return true;
        }

        /**
         * @brief A function that removes all specific value from a tuple
         * 
         * @param any 
         * @param TUPLE 
         * @return bool
         */
        bool remove_all(T any, Tuple<T>& TUPLE) {
            size_t newSize = TUPLE.size() - 1;
            T* temp = new T[newSize];

            size_t SIZE = 0;
            size_t subOfSize = 0;
            for(size_t i = 0, j = 0; i < TUPLE.size() - 1; i++, j++) {
                if(TUPLE.tuple[j] == any) {
                    i--;
                    subOfSize++;
                    continue;
                }
                temp[i] = TUPLE.tuple[j];
                SIZE++;
            }

            TUPLE.empty();
            for(size_t i = 0; i <= SIZE - subOfSize; i++) {
                this->push(temp[i], TUPLE);
            }

            delete[] temp;
            return true;
        }

        /**
         * @brief A method to make a tuple empty
         * 
         * @param TUPLE 
         * @return bool
         */
        bool empty(Tuple<T>& TUPLE) {
            for (size_t i = 0; i < TUPLE.size(); i++) TUPLE.tuple[i].~T();

            TUPLE.Size = 0;
            return true;
        }

        /**
         * @brief A method that reverses a tuple
         * 
         * @param TUPLE 
         */
        void reverse(Tuple<T>& TUPLE) {
            T temp;

            for(size_t i = 0; i < (TUPLE.size() / 2); i++){
                temp = TUPLE.tuple[i];
                TUPLE.tuple[i] = TUPLE.tuple[TUPLE.Size - i - 1];
                TUPLE.tuple[TUPLE.Size - i - 1] = temp;
            }
        }

        /**
         * @brief A method that exchanges all the values assigned in "old_value" with the "new_value"
         * 
         * @param new_value The new value
         * @param old_value The old value
         * @param TUPLE 
         */
        void replace(T new_value, T old_value, Tuple<T>& TUPLE) {
            for (size_t i = 0; i < TUPLE.size(); i++)
            {
                if (TUPLE.tuple[i] == old_value) TUPLE.tuple[i] = new_value;
            }
        }

        /**
         * @brief A method that exchanges the first value in "old_value" with the "new_value"
         * 
         * @param new_value The new value
         * @param old_value The old value 
         * @param TUPLE 
         */
        void quick_replace(T new_value, T old_value, Tuple<T>& TUPLE) {
            for (size_t i = 0; i < TUPLE.size(); i++)
            {
                if (TUPLE.tuple[i] == old_value) {
                    TUPLE.tuple[i] = new_value;
                    break;
                }
            }
        }

        /**
         * @brief A method that sorts a tuple
         * 
         * @param TUPLE 
         */
        void sort(Tuple<T>& TUPLE) {
            for (int i = TUPLE.Size / 2 - 1; i >= 0; i--) heapify(TUPLE.tuple, TUPLE.Size, i);

            for (int i = TUPLE.Size - 1; i > 0; i--) {
                std::swap(TUPLE.tuple[0], TUPLE.tuple[i]);

                heapify(TUPLE.tuple, i, 0);
            }
        }

        /**
         *@brief A range class that can be used to assign an ArrayList of numbers. 
         * @param number 
         * @param TUPLE 
         * @return true 
         * @return false 
         */
        bool range(size_t number, Tuple<T>& TUPLE) {
            size_t i;
            if(0 > number) return false;
            for (i = 0; i < number; i++) {
                this->push(i, TUPLE);
            }
            return true;
        }

        /**
         * @brief A range class that can be used to assign an tuple of numbers.
         * 
         * @param firstNumber The starting of the range.
         * @param lastNumber The ending of the range.
         * @param TUPLE 
         * @return true 
         * @return false 
         */
        bool range(int firstNumber, int lastNumber, Tuple<T>& TUPLE) {
            int i;
            if(firstNumber > lastNumber) return false;
            for (i = firstNumber; i < lastNumber; i++) {
                this->push(i, TUPLE);
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
         * @param TUPLE 
         * @return bool 
         */
        bool range(int firstNumber, int lastNumber, size_t step, Tuple<T>& TUPLE) {
            step = step - 1;
            int i;
            if(firstNumber > lastNumber) return false;
            for (i = firstNumber; i < lastNumber; i++) {
                this->push(i, TUPLE);
                i = i + step;
            }
            return true;
        }

        /**
         * @brief A method that shuffles a tuple
         * 
         * @param TUPLE 
         */
        void shuffle(Tuple<T>& TUPLE) {

            srand(time(NULL));

            for(size_t i = TUPLE.size() - 1; i > 0; i--) {
                size_t j = rand() % (i + 1);
                std::swap(TUPLE.tuple[i], TUPLE.tuple[j]);
            }
            return;
        }

        /**
         * @brief A method that fills a tuple with a given value
         * 
         * @param VALUE 
         * @param start 
         * @param end 
         * @param TUPLE 
         * @return bool
         */
        bool fill(T VALUE, size_t start, size_t end, Tuple<T>& TUPLE) {
            if (start > end) return 0;
            for (size_t i = start; i < end; i++) TUPLE.tuple[i] = VALUE;
            return 1;
        }

        /**
         * @brief A method that prints a tuple
         * 
         * @param TUPLE 
         */
        void print(Tuple<T>& TUPLE) {
            if(!(TUPLE.is_empty())) {
                std::cout << "[ ";
                for(size_t i = 0; i < TUPLE.size(); i++) {
                    if(i == TUPLE.size() - 1) std::cout << TUPLE.tuple[i];
                    if(i != TUPLE.size() - 1) std::cout << TUPLE.tuple[i] << ", ";
                }
                std::cout << " ]" << '\n';
            }
            else std::cout << "[]";
        }

        /**
         * @brief A method to check is a tuple is sorted
         * 
         * @return bool
         */
        bool is_sorted(const Tuple<T>& TUPLE) {
            if(TUPLE.size() == 0) return false;
            if(TUPLE.size() == 1) return true;

            for(size_t i = 1; i < TUPLE.size(); i++) if(TUPLE.tuple[i - 1] > TUPLE.tuple[i]) return false;

            return true;
        }

        size_t size(Tuple<T> TUPLE) const { return TUPLE.Size; }

        /**
         * @brief A method to check if a tuple is empty
         * 
         * @param TUPLE 
         * @return bool 
         */
        bool is_empty(const Tuple<T>& TUPLE) {
            if(TUPLE.Size != 0) return 0;
            return 1;
        }

    private:
        /**
         * @brief A heapify method
         * 
         * @param TUPLE 
         * @param Size 
         * @param index 
         */
        void heapify(T TUPLE[], size_t Size, size_t index) {
            size_t largest = index; 
            size_t member = 2 * index + 1; 
            size_t other_member = 2 * index + 2; 
            
            if (member < Size && TUPLE[member] > TUPLE[largest]) largest = member;
        
            if (other_member < Size && TUPLE[other_member] > TUPLE[largest]) largest = other_member;
        
            if (largest != index) {
                std::swap(TUPLE[index], TUPLE[largest]);

                heapify(TUPLE, Size, largest);
            }
        }
    } List;

    /**
     * @brief A method to check if a tuple is empty
     * 
     * @return bool
     */
    bool is_empty() {
        if(Size != 0) return 0;
        return 1;
    }
    
    /**
     * @brief A method to return the first value of a tuple
     * 
     * @return T 
     */
    T front() { return tuple[0]; }

    /**
     * @brief A method to return the last value of a tuple
     * 
     * @return T 
     */
    T back() { return tuple[Size - 1]; }

    /**
     * @brief A method that checks if a value exists in a tuple
     * 
     * @param any 
     * @return bool
     */
    bool find(T any) {
        for(size_t i = 0; i < Size; i++) {
            if (tuple[i] == any) return true;
        }
        return false;
    }

    /**
     * @brief A method to check is a tuple is sorted
     * 
     * @return bool
     */
    bool is_sorted() {
        if(this->size() == 0) return false;
        if(this->size() == 1) return true;

        for(size_t i = 1; i < this->size(); i++) if(this->tuple[i - 1] > this->tuple[i]) return false;

        return true;
    }

    const T* operator[] (size_t Index) const { 
        Index = Index - 1;
        return this->tuple[Index];
    } 


    friend std::ostream& operator<<(std::ostream& out, const Tuple<T> Object) {
        out << "(";
        for(size_t i = 0; i < Object.size(); i++) {
            if(i == 0) out << ' ' << Object.tuple[0] << ", ";
            else if(i != Object.size() - 1) out << Object.tuple[i] << ", ";
            if(i == Object.size() - 1) out << Object.tuple[i] << ' ';
        }

        out << ")\n";
        
       return out;
    }
};


#endif
