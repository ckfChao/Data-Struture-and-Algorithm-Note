// file: stack.hpp
// author: Tony Chao
// Date: July 26, 2020

#pragma once

#include <iostream>
#include "SinglyLinkedList.hpp"

template<class T>
class Stack {
    private:
        SinglyLinkedList<T> stack_;

    public:

        Stack();
        ~Stack();
        
        T& top();

        void push(const T&&);
        void push(const T&);

        void pop();

        void clear();

        size_t size(); 
        bool empty();
};

template<class T>
Stack<T>::Stack() {};

template<class T>
Stack<T>::~Stack() {
    stack_.~SinglyLinkedList();
}

template<class T>
T& Stack<T>::top() {
    return stack_.front();
}

template<class T>
void Stack<T>::push(const T&& val) {
    stack_.push_front(val);
}

template<class T>
void Stack<T>::push(const T& val) {
    stack_.push_front(val);
}

template<class T>
void Stack<T>::pop() {
    stack_.pop_front();
}

template<class T>
void Stack<T>::clear() {
    stack_.clear();
}

template<class T>
size_t Stack<T>::size() {
    return stack_.size();
}

template<class T>
bool Stack<T>::empty() {
    return stack_.empty();
}