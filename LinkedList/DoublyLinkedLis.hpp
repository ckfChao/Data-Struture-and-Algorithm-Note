// file: DoublyLinkedList.hpp
// author: Tony Chao
// Date: June 29, 2020

#pragma once

#include <iostream>
#include <stdexcept>

template<class T> class DoublyLinkedList;

template<class T>
class Node {
    private:
        T val;
        Node<T>* next;
        Node<T>* prev;
    public:
        Node() : val(), next() {};
        Node(const T& _val) : val(_val), prev(nullptr), next(nullptr) {};
        Node(const T&& _val) : val(_val), prev(nullptr), next(nullptr) {};
        Node(const T& _val, Node<T>* p, Node<T>* n) : val(_val), prev(p), next(n) {};
        Node(const T&& _val, Node<T>* p, Node<T>* n) : val(_val), prev(p), next(n) {};
        friend class DoublyLinkedList<T>;
};

template<class T>
class DoublyLinkedList {
    private:
        Node<T>* head_;
        Node<T>* tail_;
        size_t size_;
    
    public:
        static const size_t npos = -1;

        DoublyLinkedList();                               // constructor
        ~DoublyLinkedList();                              // destructor
        
        T& front();                                       // return head element
        T& back();                                        // return tail element
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

        void reverse();                                   // reverse the Linkde list

        size_t size() const;                              // return size of Linked list;
        bool empty() const;                               // check the Linked list is empty
        void print() const;                               // print the elements of Linked list from front to end
        void print_reverse() const;                       // print the elements of Linked list from end to front 
};

template<class T>
DoublyLinkedList<T>::DoublyLinkedList() {
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    Node<T>* del_node;
    while (head_ != nullptr) {
        del_node = head_;
        head_ = head_->next;
        delete del_node;
    }
    tail_ = nullptr;
    size_ = 0;
}

template<class T>
T& DoublyLinkedList<T>::front() {
    return head_->val;
}

template<class T>
T& DoublyLinkedList<T>::back() {
    return tail_->val;
}

template<class T>
void DoublyLinkedList<T>::clear() {
    this->~DoublyLinkedList();
}

template<class T>
void DoublyLinkedList<T>::push_front(const T& val) {
    if (head_ == nullptr) {
        head_ = new Node<T>(val);
        tail_ = head_;
    } else {
        if (head_ == tail_) {
            head_ = new Node<T>(val, nullptr, head_);
            tail_->prev = head_;
        } else {
            head_ = new Node<T>(val, nullptr, head_);
            head_->next->prev = head_;
        }
    }
    size_++;
}

template<class T>
void DoublyLinkedList<T>::push_front(const T&& val) {
    if (head_ == nullptr) {
        head_ = new Node<T>(val);
        tail_ = head_;
    } else {
        if (head_ == tail_) {
            head_ = new Node<T>(val, nullptr, head_);
            tail_->prev = head_;
        } else {
            head_ = new Node<T>(val, nullptr, head_);
            head_->next->prev = head_;
        }
    }
    size_++;
}

template<class T>
void DoublyLinkedList<T>::push_back(const T& val) {
    if (tail_ == nullptr) {
        tail_ = new Node<T>(val);
        tail_ = head_;
    } else {
        if (tail_ == head_) {
            tail_ = new Node<T>(val, head_, nullptr);
            head_->next = tail_;
        } else {
            tail_ = new Node<T>(val, tail_, nullptr);
            tail_->prev->next = tail_;
        }
    }
    size_++;
}

template<class T>
void DoublyLinkedList<T>::push_back(const T&& val) {
    if (tail_ == nullptr) {
        tail_ = new Node<T>(val);
        tail_ = head_;
    } else {
        if (tail_ == head_) {
            tail_ = new Node<T>(val, head_, nullptr);
            head_->next = tail_;
        } else {
            tail_ = new Node<T>(val, tail_, nullptr);
            tail_->prev->next = tail_;
        }
    }
    size_++;
}

template<class T>
void DoublyLinkedList<T>::pop_front() {
    if (head_ != nullptr) {
        Node<T>* new_head_ = head_->next;
        delete head_;
        head_ = new_head_;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        size_--;
    }
}

template<class T>
void DoublyLinkedList<T>::pop_back() {
    if (tail_ != nullptr) {
        Node<T>* new_tail_ = tail_->prev;
        delete tail_;
        tail_ = new_tail_;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr; 
        }
        size_--;
    }
}

template<class T>
size_t DoublyLinkedList<T>::find(const T& val) const {
    size_t index = 0;
    const Node<T>* curr = head_;
    while (curr != nullptr && curr->val != val) {
        curr = curr->next;
        index++;
    }
    return (curr == nullptr) ? npos : index;
}

template<class T>
size_t DoublyLinkedList<T>::find(const T&& val) const {
    size_t index = 0;
    const Node<T>* curr = head_;
    while (curr != nullptr && curr->val != val) {
        curr = curr->next;
        index++;
    }
    return (curr == nullptr) ? npos : index;
}

template<class T>
void DoublyLinkedList<T>::insert(const T& val, const size_t& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }
    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* curr;
        Node<T>* insert_node = new Node<T>(val);

        if (index > size_ / 2) {
            curr = tail_;            
            for (int i = 0; i < size_ - index - 1; i++) {
                curr = curr->prev;
            }
        } else {
            curr = head_;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
        }
        insert_node->next = curr;
        insert_node->prev = curr->prev;
        insert_node->next->prev = insert_node;
        insert_node->prev->next = insert_node;

        size_++;
    }
}

template<class T>
void DoublyLinkedList<T>::insert(const T&& val, const size_t& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }
    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* curr;
        Node<T>* insert_node = new Node<T>(val);

        if (index > size_ / 2) {
            curr = tail_;            
            for (int i = 0; i < size_ - index - 1; i++) {
                curr = curr->prev;
            }
        } else {
            curr = head_;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
        }
        insert_node->next = curr;
        insert_node->prev = curr->prev;
        insert_node->next->prev = insert_node;
        insert_node->prev->next = insert_node;
        
        size_++;
    }
}

template<class T>
void DoublyLinkedList<T>::insert(const T&& val, const size_t&& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }
    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* curr;
        Node<T>* insert_node = new Node<T>(val);

        if (index > size_ / 2) {
            curr = tail_;            
            for (int i = 0; i < size_ - index - 1; i++) {
                curr = curr->prev;
            }
        } else {
            curr = head_;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
        }
        insert_node->next = curr;
        insert_node->prev = curr->prev;
        insert_node->next->prev = insert_node;
        insert_node->prev->next = insert_node;
        
        size_++;
    }
}

template<class T>
void DoublyLinkedList<T>::insert(const T& val, const size_t&& index) {
    if (index > size_) {
        throw std::overflow_error("the index overflow error");
    }
    if (index == 0) {
        push_front(val);
    } else if (index == size_) {
        push_back(val);
    } else {
        Node<T>* curr;
        Node<T>* insert_node = new Node<T>(val);

        if (index > size_ / 2) {
            curr = tail_;            
            for (int i = 0; i < size_ - index - 1; i++) {
                curr = curr->prev;
            }
        } else {
            curr = head_;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
        }
        insert_node->next = curr;
        insert_node->prev = curr->prev;
        insert_node->next->prev = insert_node;
        insert_node->prev->next = insert_node;
        
        size_++;
    }
}

template<class T>
void DoublyLinkedList<T>::remove(const size_t& index) {
    if (index > size_ - 1) {
        throw std::overflow_error("The index is overflow");
    } 
    
    if (index == 0) {
        pop_front();
    } else if (index == size_ - 1) {
        pop_back();
    } else {
        Node<T>* curr;

        if (index > size_ / 2) {
            curr = tail_;            
            for (int i = 0; i < size_ - index - 1; i++) {
                curr = curr->prev;
            }
        } else {
            curr = head_;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
        }
        
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        
        delete curr;

        size_--;
    }
}

template<class T>
void DoublyLinkedList<T>::remove(const size_t&& index) {
    if (index > size_ - 1) {
        throw std::overflow_error("The index is overflow");
    } 
    
    if (index == 0) {
        pop_front();
    } else if (index == size_ - 1) {
        pop_back();
    } else {
        Node<T>* curr;

        if (index > size_ / 2) {
            curr = tail_;            
            for (int i = 0; i < size_ - index - 1; i++) {
                curr = curr->prev;
            }
        } else {
            curr = head_;
            for (int i = 0; i < index; i++) {
                curr = curr->next;
            }
        }
        
        curr->prev->next = curr->next;
        curr->next->prev = curr->prev;
        
        delete curr;
        
        size_--;
    }
}

template<class T>
void DoublyLinkedList<T>::reverse() {
    Node<T>* curr = head_;
    while (curr != nullptr) {
        std::swap(curr->prev, curr->next);
        curr = curr->prev;
    }
    std::swap(head_, tail_);
}

template<class T>
size_t DoublyLinkedList<T>::size() const {
    return size_;
}

template<class T>
bool DoublyLinkedList<T>::empty() const {
    return size_ == 0;
}

template<class T>
void DoublyLinkedList<T>::print() const {
    const Node<T>* curr = head_;
    while (curr != nullptr) {
        std::cout << curr->val << ' ';
        curr = curr->next;
    }
    std::cout << std::endl;
}

template<class T>
void DoublyLinkedList<T>::print_reverse() const {
    const Node<T>* curr = tail_;
    while (curr != nullptr) {
        std::cout << curr->val << ' ';
        curr = curr->prev;
    }
    std::cout << std::endl;
}