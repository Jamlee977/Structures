#pragma once

// ! Omar Estietie
#include <iostream>
#include <initializer_list>

#ifndef TUPLE_HPP
#define TUPLE_HPP

#include "List.cpp"

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

    void reAllocate(size_t newCapacity) {
        T* newBlock = new T[newCapacity];

        if (newCapacity < Size) Size = newCapacity;

        for (size_t i = 0; i < Size; i++) newBlock[i] = std::move(tuple[i]);

        ::operator delete(tuple, newCapacity * sizeof(T));
        tuple = newBlock;
        Capacity = newCapacity;
    }

    void push(const T& VALUE) {

        if (Size >= Capacity) reAllocate(Capacity + Capacity / 2);
        

        tuple[Size] = VALUE;
        Size++;
    }

    void push(T&& VALUE) {

        if (Size >= Capacity) reAllocate(Capacity + Capacity / 2);
        

        tuple[Size] = std::move(VALUE);
        Size++;
    }

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

    size_t size() const { return Size; }

    Iterator begin() { return Iterator(tuple); }

    Iterator end() { return Iterator(tuple + Size); }

    T get(size_t index) { 
        index = index - 1;
        return this->tuple[index]; 
    }

    struct list {

        T get(size_t index, Tuple<T>& TUPLE) { 
            index = index - 1;
            return TUPLE.tuple[index]; 
        }

        void push(const T& value, Tuple<T>& TUPLE) {
            size_t SIZE = TUPLE.size();
            T* temp = new T[SIZE + 1];
            for(size_t i = 0; i < SIZE; i++) {
                temp[i] = TUPLE.tuple[i];
            }
            temp[SIZE] = value;
            TUPLE.empty();
            for(size_t i = 0; i < SIZE + 1; i++) {
                TUPLE.tuple[i] = temp[i];
                TUPLE.Size++;
                TUPLE.Capacity++;
            }
            delete[] temp;
        }

        void push(T&& value, Tuple<T>& TUPLE) {
            size_t SIZE = TUPLE.size();
            T* temp = new T[SIZE + 1];
            for(size_t i = 0; i < SIZE; i++) {
                temp[i] = TUPLE.tuple[i];
            }
            temp[SIZE] = value;
            TUPLE.empty();
            for(size_t i = 0; i < SIZE + 1; i++) {
                TUPLE.tuple[i] = std::move(temp[i]);
                TUPLE.Size++;
                TUPLE.Capacity++;
            }
            delete[] temp;
        }

        void pop(Tuple<T>& TUPLE) {
            size_t SIZE = TUPLE.size() - 1;
            T* temp = new T[SIZE];
            for(size_t i = 0; i < SIZE; i++) {
                temp[i] = TUPLE.tuple[i];
            }
            TUPLE.empty();
            for(size_t i = 0; i < SIZE; i++) {
                TUPLE.tuple[i] = std::move(temp[i]);
                TUPLE.Size++;
                TUPLE.Capacity++;
            }
            delete[] temp;
        }

        bool change(size_t index, T newValue, Tuple<T>& TUPLE) {
            index = index - 1;
            TUPLE.tuple[index] = newValue;
            return true;
        }

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

        bool remove(size_t index, Tuple<T>& TUPLE) {
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

        bool remove_e(T any, Tuple<T>& TUPLE) {
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

        bool empty(Tuple<T>& TUPLE) {
            for (size_t i = 0; i < TUPLE.size(); i++) TUPLE.tuple[i].~T();

            TUPLE.Size = 0;
            return true;
        }

        void reverse(Tuple<T>& TUPLE) {
            T temp;

            for(size_t i = 0; i < (TUPLE.size() / 2); i++){
                temp = TUPLE.tuple[i];
                TUPLE.tuple[i] = TUPLE.tuple[TUPLE.Size - i - 1];
                TUPLE.tuple[TUPLE.Size - i - 1] = temp;
            }
        }

        void replace(T new_value, T old_value, Tuple<T>& TUPLE) {
            for (size_t i = 0; i < TUPLE.size(); i++)
            {
                if (TUPLE.tuple[i] == old_value) TUPLE.tuple[i] = new_value;
            }
        }

        void quick_replace(T new_value, T old_value, Tuple<T>& TUPLE) {
            for (size_t i = 0; i < TUPLE.size(); i++)
            {
                if (TUPLE.tuple[i] == old_value) {
                    TUPLE.tuple[i] = new_value;
                    break;
                }
            }
        }

        void sort(Tuple<T>& TUPLE) {
            for (int i = TUPLE.Size / 2 - 1; i >= 0; i--) heapify(TUPLE.tuple, TUPLE.Size, i);

            for (int i = TUPLE.Size - 1; i > 0; i--) {
                std::swap(TUPLE.tuple[0], TUPLE.tuple[i]);

                heapify(TUPLE.tuple, i, 0);
            }
        }

        private:
        void heapify(T tup[], size_t Size, size_t index)
        {
            size_t largest = index; 
            size_t member = 2 * index + 1; 
            size_t other_member = 2 * index + 2; 
            
            if (member < Size && tup[member] > tup[largest])
                largest = member;
        
            if (other_member < Size && tup[other_member] > tup[largest])
                largest = other_member;
        
            if (largest != index) {
                std::swap(tup[index], tup[largest]);
        
                heapify(tup, Size, largest);
            }
        }
    };

    list List;

    T front() { return tuple[0]; }

    T back() { return tuple[Size - 1]; }

    bool find(T any) {
        for(size_t i = 0; i < Size; i++) {
            if (tuple[i] == any) return true;
        }
        return false;
    }

    bool is_sorted() {
        if(this->size() == 0) return false;
        if(this->size() == 1) return true;

        for(size_t i = 1; i < this->size(); i++) if(this->tuple[i - 1] > this->tuple[i]) return false;

        return true;
    }

    friend std::ostream& operator<<(std::ostream& out, const Tuple<T> Object) {
        out << "(";
        for(size_t i = 0; i < Object.size(); i++) {
            if(i == 0) out << ' ' << Object.tuple[0] << ", ";
            else if(i != Object.size() - 1) out << Object.tuple[i] << ", ";
            if(i == Object.size() - 1) out << Object.tuple[i] << ' ';
        }

        out << ")" << "\n";
        
       return out;
    }
};


#endif
