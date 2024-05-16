// Copyright [2024] <Emanuelle Guse>

#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>


namespace structures {

    template<typename T>
    class CircularList {
    public:
        CircularList();

        ~CircularList();

        void clear();  // limpar lista

        void push_back(const T &data);  // inserir no fim
        void push_front(const T &data);  // inserir no início
        void insert(const T &data, std::size_t index);  // inserir na posição
        void insert_sorted(const T &data);  // inserir em ordem

        T &at(std::size_t index);  // acessar em um indice (com checagem de limites)
        const T &at(std::size_t index) const;  // versão const do acesso ao indice

        T pop(std::size_t index);  // retirar da posição
        T pop_back();  // retirar do fim
        T pop_front();  // retirar do início
        void remove(const T &data);  // remover dado específico

        bool empty() const;  // lista vazia
        bool contains(const T &data) const;  // lista contém determinado dado?
        std::size_t find(const T &data) const;  // posição de um item na lista

        std::size_t size() const;  // tamanho da lista

    private:
        class Node {
        public:
            explicit Node(const T &data);

            Node(const T &data, Node *next);

            Node(const T &data, Node *prev, Node *next);

            T &data();

            const T &data() const;

            Node *prev();

            const Node *prev() const;

            void prev(Node *node);

            Node *next();

            const Node *next() const;

            void next(Node *node);

        private:
            T data_;
            Node *prev_;
            Node *next_;
        };

        Node *head;
        std::size_t size_;
    };

    template<typename T>
    CircularList<T>::CircularList() {
        size_ = 0;
    }

    template<typename T>
    CircularList<T>::~CircularList() {
        clear();
    }

    template<typename T>
    void CircularList<T>::clear() {
        while (!empty()) {
            pop_front();
        }
    }

    template<typename T>
    void CircularList<T>::push_back(const T &data) {
        Node *new_node = new Node(data);
        if (empty()) {
            head = new_node;
            head->next(head);
            head->prev(head);
        } else {
            Node *last = head->prev();
            new_node->next(head);
            new_node->prev(last);
            head->prev(new_node);
            last->next(new_node);
        }
        size_++;
    }

    template<typename T>
    void CircularList<T>::push_front(const T &data) {
        Node *new_node = new Node(data);
        if (empty()) {
            head = new_node;
            head->next(head);
            head->prev(head);
        } else {
            Node *last = head->prev();
            new_node->next(head);
            new_node->prev(last);
            head->prev(new_node);
            last->next(new_node);
            head = new_node;
        }
        size_++;
    }

    template<typename T>
    void CircularList<T>::insert(const T &data, std::size_t index) {
        if (index == 0) {
            push_front(data);
        } else if (index == size()) {
            push_back(data);
        } else {
            Node *new_node = new Node(data);
            Node *previous = head;
            for (size_t i = 0; i < index - 1; i++) {
                previous = previous->next();
            }
            new_node->next(previous->next());
            new_node->prev(previous);
            previous->next(new_node);
            new_node->next()->prev(new_node);
            size_++;
        }
    }

    template<typename T>
    void CircularList<T>::insert_sorted(const T &data) {
        if (empty()) {
            push_front(data);
        } else {
            Node *current = head;
            std::size_t index = 0;
            while (index < size() && data > current->data()) {
                current = current->next();
                index++;
            }
            insert(data, index);
        }
    }

    template<typename T>
    T &CircularList<T>::at(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index inválido");
        }
        Node *current = head;
        for (std::size_t i = 0; i < index; i++) {
            current = current->next();
        }
        return current->data();
    }

    template<typename T>
    const T &CircularList<T>::at(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index inválido");
        }
        Node *current = head;
        for (std::size_t i = 0; i < index; i++) {
            current = current->next();
        }
        return current->data();
    }

    template<typename T>
    T CircularList<T>::pop(std::size_t index) {
        Node *new_node = head;
        if (index > size() || empty()) {
            throw std::out_of_range("Index inválido");
        }
        for (size_t i = 0; i < size(); i++) {
            if (i == index) {
                T data = new_node->data();
                pop(i);
                size_--;
                return data;
            }
        }
        return head->data();
    }

    template<typename T>
    T CircularList<T>::pop_back() {
        Node *new_node = head->prev();
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        T data = new_node->data();
        Node *last = head->prev();
        last->prev()->next(head);
        head->prev(last->prev());
        delete last;
        size_--;
        return data;
    }

    template<typename T>
    T CircularList<T>::pop_front() {
        Node *new_node = head;
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        T data = new_node->data();
        Node *out = head;
        head = head->next();
        head->prev(out->prev());
        out->prev()->next(head);
        delete out;
        size_--;
        return data;
    }

    template<typename T>
    void CircularList<T>::remove(const T &data) {
        pop(find(data));
    }

    template<typename T>
    bool CircularList<T>::empty() const {
        return size() == 0;
    }

    template<typename T>
    bool CircularList<T>::contains(const T &data) const {
        bool contains = false;
        Node *current = head;
        for (std::size_t i = 0; i < size_; i++) {
            if (current->data() == data) {
                contains = true;
                break;
            }
            current = current->next();
        }
        return contains;
    }

    template<typename T>
    std::size_t CircularList<T>::find(const T &data) const {
        Node *current = head;
        for (std::size_t i = 0; i < size_; i++) {
            if (current->data() == data) {
                return i;
            }
            current = current->next();
        }
        return size_;
    }

    template<typename T>
    std::size_t CircularList<T>::size() const {
        return size_;
    }

    template<typename T>
    CircularList<T>::Node::Node(const T &data) {
        data_ = data;
        prev_ = nullptr;
        next_ = nullptr;
    }

    template<typename T>
    CircularList<T>::Node::Node(const T &data, Node *next) {
        data_ = data;
        next_ = next;
    }

    template<typename T>
    CircularList<T>::Node::Node(const T &data, Node *prev, Node *next) {
        data_ = data;
        prev_ = prev;
        next_ = next;
    }

    template<typename T>
    T &CircularList<T>::Node::data() {
        return data_;
    }

    template<typename T>
    const T &CircularList<T>::Node::data() const {
        return data_;
    }

    template<typename T>
    typename CircularList<T>::Node *CircularList<T>::Node::prev() {
        return prev_;
    }

    template<typename T>
    const typename CircularList<T>::Node *CircularList<T>::Node::prev() const {
        return prev_;
    }

    template<typename T>
    void CircularList<T>::Node::prev(Node *node) {
        prev_ = node;
    }

    template<typename T>
    typename CircularList<T>::Node *CircularList<T>::Node::next() {
        return next_;
    }

    template<typename T>
    const typename CircularList<T>::Node *CircularList<T>::Node::next() const {
        return next_;
    }

    template<typename T>
    void CircularList<T>::Node::next(Node *node) {
        next_ = node;
    }

}   // namespace structures

#endif
