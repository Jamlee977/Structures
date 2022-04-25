#pragma once

#include <iostream>

#ifndef QUEUE_HPP
#define QUEUE_HPP

template <typename T>
class Queue {
    private:
        T* queue = nullptr;
        size_t Size = 0;
        size_t capacity = 0;

        void reAllocate(size_t newCapacity) {
            T* newBlock = new T[newCapacity];

            if(newCapacity < Size) Size = newCapacity;

            for (size_t i = 0; i < Size; i++) queue[i] = std::move(queue[i]);

            ::operator delete(queue, newCapacity * sizeof(T));
            queue = newBlock;
            capacity = newCapacity;
        }

        void heapify(T QUEUE[], size_t SIZE, size_t index)
        {
            size_t largest = index; 
            size_t member = 2 * index + 1; 
            size_t other_member = 2 * index + 2; 
            
            if (member < SIZE && QUEUE[member] > QUEUE[largest])
                largest = member;
        
            if (other_member < SIZE && QUEUE[other_member] > QUEUE[largest])
                largest = other_member;
        
            if (largest != index) {
                std::swap(QUEUE[index], QUEUE[largest]);
        
                heapify(QUEUE, SIZE, largest);
            }
        }

    public:
        Queue() { reAllocate(2); }

        ~Queue() { ::operator delete(queue, capacity * sizeof(T)); }

        void push(const T& value) {
            if(Size > capacity) reAllocate(capacity + capacity / 2);

            queue[Size] = value;
            Size++;
        }

        void push(T&& value) {
            if(Size > capacity) reAllocate(capacity + capacity / 2);

            queue[Size] = std::move(value);
            Size++;       
        }

        void pop() {
            this->reverse();
            if(Size > 0) {
                Size--;
                queue[Size].~T();
            }
            this->reverse();
        }

        bool empty() {
            for (size_t i = 0; i < Size; i++) queue[i].~T();

            Size = 0;
            return true;
        }

        bool is_empty() {
            if(Size != 0) return 0;
            return 1;
        }

        T front() { return queue[0]; }
        
        T back() { return queue[Size - 1]; }

        size_t size() const { return Size; }

        void reverse() {
            T temp;

            for(size_t i = 0; i < Size / 2; i++){
                temp = queue[i];
                queue[i] = queue[Size-i-1];
                queue[Size-i-1] = temp;
            }
        }

        void print() {
            if(!(is_empty())) {
                std::cout << "[ ";
                for(size_t i = 0; i < size(); i++) {
                    if(i == size() - 1) std::cout << queue[i];
                    if(i != size() - 1) std::cout << queue[i] << ", ";
                }
                std::cout << " ]" << '\n';
            }
            else std::cout << "[]";
        }

        void sort() {
            for (int i = Size / 2 - 1; i >= 0; i--) heapify(queue, Size, i);

            for (int i = Size - 1; i > 0; i--) {
                std::swap(queue[0], queue[i]);

                heapify(queue, i, 0);
            }
        }
};

#endif