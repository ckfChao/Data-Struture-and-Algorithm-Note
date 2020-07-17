// file: CircularLinkedList.hpp
// author: Tony Chao
// Date: July 15, 2020

#pragma once

#include <iostream>
#include <stdexcept>

template<class T> class CircularLinkedList;

template<class T>
class Node {
    private:
        T val;
        Node<T>* next;
    public:
        Node() : val(), next() {};
        Node(const T& _val) : val(_val), next(nullptr) {};
        Node(const T&& _val) : val(_val), next(nullptr) {};
        Node(const T& _val, Node<T>* p) : val(_val), next(p) {};
        Node(const T&& _val, Node<T>* p) : val(_val), next(p) {};
        friend class CircularLinkedList<T>;
};

template<class T>
class CircularLinkedList {
    private:
        Node<T>* cursor_;
        size_t size_;
    
    public:
        static const size_t npos = -1;
        
        CircularLinkedList();                               // constructor
        ~CircularLinkedList();                              // destructor
        
        T& front();                                       // return head element
        T& back();
        void clear();                                     // make the linked List to empty

        void push_front(const T&);                        // insert element to front of Linked list
        void push_front(const T&&);                       // overloading push_front()

        void push_back(const T&);                         // insert element to end of Linked list
        void push_back(const T&&);                        // overloading push_back()

        void pop_front();                                 // remove the front element in Linked list
        
        void pop_back();                                  // remove the end elemnt in Linked list

        size_t find(const T&) const;                      // check the value is exit in the linked list and return the index
        size_t find(const T&&) const;                     // overloading find()

        void insert(const T&, const size_t&);             // insert elements according to the index
        void insert(const T&, const size_t&&);            // overloading insert()
        void insert(const T&&, const size_t&);            // overloading insert()
        void insert(const T&&, const size_t&&);           // overloading insert()

        void remove(const size_t&);                       // remove element by index
        void remove(const size_t&&);                      // overloading remove()
        
        void advance();

        size_t size() const;                              // return size of Linked list;
        bool empty() const;                               // check the Linked list is empty
        void print() const;
};

template<class T>
CircularLinkedList<T>::CircularLinkedList() {
    cursor_ = nullptr;
    size_ = 0;
}

template<class T>
CircularLinkedList<T>::~CircularLinkedList() {
    Node<T>* curr = cursor_;
    Node<T>* del_node;
    while (curr != cursor_) {
        del_node = curr;
        curr = curr->next;
        delete del_node;
    }
    delete curr;
}

template<class T>
T& CircularLinkedList<T>::front() {
    return cursor_->next->val;
}

template<class T>
T& CircularLinkedList<T>::back() {
    return cursor_->val;
}

template<class T>
void CircularLinkedList<T>::clear() {
    this->~CircularLinkedList();
    cursor_ = nullptr;
    size_ = 0;
}

template<class T>
void CircularLinkedList<T>::push_front(const T& val) {
    if (cursor_ == nullptr) {
        cursor_ = new Node<T>(val);
        cursor_->next = cursor_;
    } else {
        cursor_->next = new Node<T>(val, cursor_->next);
    }
    size_++;
}

template<class T>
void CircularLinkedList<T>::push_front(const T&& val) {
    if (cursor_ == nullptr) {
        cursor_ = new Node<T>(val);
        cursor_->next = cursor_;
    } else {
        cursor_->next = new Node<T>(val, cursor_->next);
    }
    size_++;
}

template<class T>
void CircularLinkedList<T>::push_back(const T& val) {
    if (cursor_ == nullptr) {
        cursor_ = new Node<T>(val);
        cursor_->next = cursor_;
    } else {
        cursor_->next = new Node<T>(val, cursor_->next);
        cursor_ = cursor_->next;
    }
    size_++;
}

template<class T>
void CircularLinkedList<T>::push_back(const T&& val) {
    if (cursor_ == nullptr) {
        cursor_ = new Node<T>(val);
        cursor_->next = cursor_;
    } else {
        cursor_->next = new Node<T>(val, cursor_->next);
        cursor_ = cursor_->next;
    }
    size_++;
}

template<class T>
void CircularLinkedList<T>::pop_front() {
    if (cursor_ != nullptr) {
        if (cursor_ == cursor_->next) {
            delete cursor_;
            cursor_ = nullptr;
        } else {
            Node<T>* new_head = cursor_->next->next;
            delete cursor_->next;
            cursor_->next = new_head;
        }
        size_--;
    }
}

template<class T>
void CircularLinkedList<T>::pop_back() {
    if (cursor_ != nullptr) {
        if (cursor_ == cursor_->next) {
            delete cursor_;
            cursor_ = nullptr;
        } else {
            Node<T>* new_cursor = cursor_->next;       
            while (new_cursor->next != cursor_) {
                new_cursor = new_cursor->next;
            }
            new_cursor->next = cursor_->next;
            delete cursor_;
            cursor_ = new_cursor;
        }
        size_--;
    }
}

template<class T>
size_t CircularLinkedList<T>::find(const T& val) const {
    if (size_ != 0) {
        Node<T>* curr = cursor_->next;
        size_t index = 0;
        do {
           if (curr->val == val) {
               return index;
           } 
           index += 1;
           curr = curr->next;
        } while (curr != cursor_->next);
        
    }
    return npos;
}

template<class T>
size_t CircularLinkedList<T>::find(const T&& val) const {
    if (size_ != 0) {
        Node<T>* curr = cursor_->next;
        size_t index = 0;
        do {
           if (curr->val == val) {
               return index;
           } 
           index += 1;
           curr = curr->next;
        } while (curr != cursor_->next);
        
    }
    return npos;
}

template<class T>
void CircularLinkedList<T>::insert(const T& val, const size_t& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }

    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* prev = nullptr;
        Node<T>* curr = cursor_->next;
        for (int i = 0; i < index; i++) {
            prev = curr;
            curr = curr->next;
        }

        Node<T>* insert_node = new Node<T>(val, curr);
        prev->next = insert_node;
        size_++;
    }
}

template<class T>
void CircularLinkedList<T>::insert(const T&& val, const size_t& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }
    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* prev = nullptr;
        Node<T>* curr = cursor_->next;
        for (int i = 0; i < index; i++) {
            prev = curr;
            curr = curr->next;
        }

        Node<T>* insert_node = new Node<T>(val, curr);
        prev->next = insert_node;
        size_++;
    }
}

template<class T>
void CircularLinkedList<T>::insert(const T&& val, const size_t&& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }
    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* prev = nullptr;
        Node<T>* curr = cursor_->next;
        for (int i = 0; i < index; i++) {
            prev = curr;
            curr = curr->next;
        }

        Node<T>* insert_node = new Node<T>(val, curr);
        prev->next = insert_node;
        size_++;
    }
}

template<class T>
void CircularLinkedList<T>::insert(const T& val, const size_t&& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }
    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* prev = nullptr;
        Node<T>* curr = cursor_->next;
        for (int i = 0; i < index; i++) {
            prev = curr;
            curr = curr->next;
        }

        Node<T>* insert_node = new Node<T>(val, curr);
        prev->next = insert_node;
        size_++;
    }
}

template<class T>
void CircularLinkedList<T>::remove(const size_t& index) {
    if (index > size_ - 1) {
        throw std::overflow_error("The index is overflow");
    } 
    
    if (index == 0) {
        pop_front();
    } else if (index == size_ - 1) {
        pop_back();
    } else {
        Node<T>* curr = cursor_->next;
        Node<T>* prev = nullptr;
        for (int i = 0; i < index; i++) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        delete curr;
        size_--;
    }
}

template<class T>
void CircularLinkedList<T>::remove(const size_t&& index) {
    if (index > size_ - 1) {
        throw std::overflow_error("The index is overflow");
    } 
    if (index == 0) {
        pop_front();
    } else if (index == size_ - 1) {
        pop_back();
    } else {
        Node<T>* curr = cursor_->next;
        Node<T>* prev = nullptr;
        for (int i = 0; i < index; i++) {
            prev = curr;
            curr = curr->next;
        }
        prev->next = curr->next;
        delete curr;
        size_--;
    }
}

template<class T>
void CircularLinkedList<T>::advance() {
    cursor_ = cursor_->next;
}

template<class T>
size_t CircularLinkedList<T>::size() const {
    return size_;
}

template<class T>
bool CircularLinkedList<T>::empty() const {
    return size_ == 0;
}

template<class T>
void CircularLinkedList<T>::print() const {
    Node<T>* head = cursor_->next;
    while (head != cursor_) {
        std::cout << head->val << " ";
        head = head->next;
    }
    std::cout << cursor_->val << std::endl;
}