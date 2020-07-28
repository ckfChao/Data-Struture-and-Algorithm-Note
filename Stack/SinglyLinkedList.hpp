// file: SinglyLinkedList.hpp
// author: Tony Chao
// Date: June 28, 2020

#pragma once

#include <iostream>
#include <stdexcept>

template<class T> class SinglyLinkedList;

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
        friend class SinglyLinkedList<T>;
};

template<class T>
class SinglyLinkedList {
    private:
        Node<T>* head_;
        size_t size_;
    
    public:
        static const size_t npos = -1;

        SinglyLinkedList();                               // constructor
        ~SinglyLinkedList();                              // destructor
        
        T& front();                                       // return head element
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
        
        size_t size() const;                              // return size of Linked list;
        bool empty() const;                               // check the Linked list is empty
        void print() const;                               // print the elements of Linked list from front to end
};

template<class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    head_ = nullptr;
    size_ = 0;
}

template<class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    Node<T>* del_node;
    while (head_ != nullptr) {
        del_node = head_;
        head_ = head_->next;
        delete del_node;
    }
    size_ = 0;
}

template<class T>
T& SinglyLinkedList<T>::front() {
    return head_->val;
}

template<class T>
void SinglyLinkedList<T>::clear() {
    this->~SinglyLinkedList();
}

template<class T>
void SinglyLinkedList<T>::push_front(const T& val) {
    if (head_ == nullptr) {
        head_ = new Node<T>(val);
    } else {
        Node<T>* new_head_ = new Node<T>(val, head_);
        head_ = new_head_;
    }
    size_++;
}

template<class T>
void SinglyLinkedList<T>::push_front(const T&& val) {
    if (head_ == nullptr) {
        head_ = new Node<T>(val);
    } else {
        Node<T>* new_head_ = new Node<T>(val, head_);
        head_ = new_head_;
    }
    size_++;
}

template<class T>
void SinglyLinkedList<T>::push_back(const T& val) {
    Node<T>* curr = head_;
    while (curr != nullptr && curr->next != nullptr) {
        curr = curr->next;
    }
    curr->next = new Node<T>(val);
    size_++;
}

template<class T>
void SinglyLinkedList<T>::push_back(const T&& val) {
    if (head_ == nullptr) {
        head_ = new Node<T>(val);
    } else {
        Node<T>* curr = head_;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = new Node<T>(val);
    }
    size_++;
}

template<class T>
void SinglyLinkedList<T>::pop_front() {
    if (head_ != nullptr) {
        Node<T>* new_head_ = head_->next;
        delete head_;
        head_ = new_head_;
        size_--;
    }
}

template<class T>
void SinglyLinkedList<T>::pop_back() {
    if (head_ != nullptr) {
        if (size_ == 1) {
            pop_front();
        } else {
            Node<T>* curr = head_;
            Node<T>* prev = head_;
            while (curr->next != nullptr) {
                prev = curr;
                curr = curr->next;
            }
            delete curr;
            prev->next = nullptr;
            size_--; 
        }
   }
}

template<class T>
size_t SinglyLinkedList<T>::find(const T& val) const {
    size_t index = 0;
    const Node<T>* curr = head_;
    while (curr != nullptr && curr->val != val) {
        curr = curr->next;
        index++;
    }
    return (curr == nullptr) ? npos : index;
}

template<class T>
size_t SinglyLinkedList<T>::find(const T&& val) const {
    size_t index = 0;
    const Node<T>* curr = head_;
    while (curr != nullptr && curr->val != val) {
        curr = curr->next;
        index++;
    }
    return (curr == nullptr) ? npos : index;
}

template<class T>
void SinglyLinkedList<T>::insert(const T& val, const size_t& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }
    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* prev = nullptr;
        Node<T>* curr = head_;
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
void SinglyLinkedList<T>::insert(const T&& val, const size_t& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }
    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* prev = nullptr;
        Node<T>* curr = head_;
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
void SinglyLinkedList<T>::insert(const T&& val, const size_t&& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }
    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* prev = nullptr;
        Node<T>* curr = head_;
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
void SinglyLinkedList<T>::insert(const T& val, const size_t&& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }
    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* prev = nullptr;
        Node<T>* curr = head_;
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
void SinglyLinkedList<T>::remove(const size_t& index) {
    if (index > size_ - 1) {
        throw std::overflow_error("The index is overflow");
    } 
    
    if (index == 0) {
        pop_front();
    } else if (index == size_ - 1) {
        pop_back();
    } else {
        Node<T>* curr = head_;
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
void SinglyLinkedList<T>::remove(const size_t&& index) {
    if (index > size_ - 1) {
        throw std::overflow_error("The index is overflow");
    } 
    if (index == 0) {
        pop_front();
    } else if (index == size_ - 1) {
        pop_back();
    } else {
        Node<T>* curr = head_;
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
size_t SinglyLinkedList<T>::size() const {
    return size_;
}

template<class T>
bool SinglyLinkedList<T>::empty() const {
    return size_ == 0;
}

template<class T>
void SinglyLinkedList<T>::print() const {
    const Node<T>* curr = head_;
    while (curr != nullptr) {
        std::cout << curr->val << ' ';
        curr = curr->next;
    }
    std::cout << std::endl;
}

