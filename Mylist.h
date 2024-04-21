#pragma once
#include <iostream>
#include <cstring>
#include <sstream>



    template<typename T>
    class List {
    private:

        bool is_deleted = false;
        class Node {
        public:
            T data;
            Node* next;


            Node(const T& data) : data(data), next(nullptr) {};
            Node() : data(data), next(nullptr) {}
        };
        Node head;

    public:

        List() {
            head = Node();
        }


        List(List&& other) : head(other.head) {
            other.head = Node();
        }

        List& operator=(List&& other) {
            if (this != &other) {

                clear();


                head = other.head;
                other.head = Node();
            }
            return *this;
        }


        List& operator=(const List& other) {
            if (this != &other) {

                clear();


                Node* current = other.head.next;
                while (current != nullptr) {
                    AddToTail(current->data);
                    current = current->next;
                }
            }
            return *this;
        }
        bool find(const T& data) {
            Node* current = head.next;
            while (current->data != data) {
                if (current->next == nullptr) { return false; }
                current = current->next;
            }return true;

        }

        void AddToTail(const T& data) {
            Node* newNode = new Node(data);
            if (head.next == nullptr) {
                head.next = newNode;
            }
            else {
                Node* current = head.next;
                while (current->next != nullptr)
                    current = current->next;
                current->next = newNode;
            }
        }

        T GetLast() {
            Node* current = head.next;
            while (current->next != nullptr)
                current = current->next;
            return current->data;
        }

        void RemoveLast() {
            if (head.next != nullptr)
            {
                Node* current = head.next;
                while (current->next->next != nullptr)
                    current = current->next;
                Node* tmp = current->next;
                current->next = nullptr;
                delete tmp;
            }
        }


        List(const List& other) {
            clear();
            Node* current = other.head;
            while (current != nullptr) {
                AddToTail(current->data);
                current = current->next;
            }
        }


        friend std::ostream& operator<<(std::ostream& os, const List& list) {
            Node* current = list.head.next;
            while (current != nullptr) {
                os << current->data << ' ';
                current = current->next;
            }
            os << std::endl;
            return os;
        }


        friend std::istream& operator>>(std::istream& is, List& list) {
            std::string str;
            while (std::getline(is, str)) {
                T c = T(str);
                list.AddToTail(c);
            }
            return is;
        }

        void clear() {
            Node* current = head.next;
            while (current != nullptr) {
                Node* tmp = current;
                current = current->next;
                delete tmp;
            }

            head.next = nullptr;
        }

        bool empty() const {
            return head.next == nullptr;
        }

        bool remove(T data) {
            if (empty()) return false;
            Node* current = head.next;
            while (current != nullptr) {
                if (current->data == data) {
                    Node* tmp = current;
                    current = current->next;
                    delete tmp;
                }
                head.next = nullptr;
                return true;
            }
            return false;

        }




        ~List() {
            if (!is_deleted) {
                clear();
                is_deleted = true;
            }
        }
    

  //  List<T> m_data;

};