//! Copyright [2024] <Emanuelle Guse>

#include <cstdint>   // std::size_t
#include <stdexcept>   // C++ exceptions

namespace structures {

    template<typename T>
    class LinkedStack {
    public:
        LinkedStack();

        ~LinkedStack();

        void clear();  // limpa pilha

        void push(const T& data);  // empilha

        T pop();  // desempilha

        T& top() const;  // dado no topo

        bool empty() const;  // pilha vazia

        std::size_t size() const;  // tamanho da pilha

    private:
        class Node {
        public:
            explicit Node(const T& data);
            explicit Node(const T& data, Node* next);

            T& data();  // getter: info
            const T& data() const;  // getter-constante: info

            Node* next();  // getter: próximo
            const Node* next() const;  // getter-constante: próximo

            void next(Node* next);  // setter: próximo
        private:
            T data_;
            Node* next_;
        };

        Node* top_;  // nodo-topo
        std::size_t size_;  // tamanho
    };

    template<typename T>
    LinkedStack<T>::LinkedStack() {
        top_ = nullptr;
        size_ = 0;
    }

    template<typename T>
    LinkedStack<T>::~LinkedStack() {
        clear();
    }

    template<typename T>
    void LinkedStack<T>::clear() {
        while (!empty()) {
            pop();
        }
    }

    template<typename T>
    void LinkedStack<T>::push(const T& data) {
        Node* new_node = new Node(data, top_);
        if (new_node == nullptr) {
            throw std::out_of_range("Pilha cheia");
        }
        top_ = new_node;
        size_++;
    }

    template<typename T>
    T LinkedStack<T>::pop() {
        if (empty()) {
            throw std::out_of_range("Pilha vazia");
        }
        Node* out = top_;
        top_ = top_->next();
        size_--;
        T data = out->data();
        delete out;
        return data;
    }

    template<typename T>
    T& LinkedStack<T>::top() const {
        if (empty()) {
            throw std::out_of_range("Pilha vazia");
        }
        return top_->data();
    }

    template<typename T>
    bool LinkedStack<T>::empty() const {
        return size_ == 0;
    }

    template<typename T>
    std::size_t LinkedStack<T>::size() const {
        return size_;
    }

    template<typename T>
    LinkedStack<T>::Node::Node(const T& data) {
        data_ = data;
        next_ = nullptr;
    }

    template<typename T>
    LinkedStack<T>::Node::Node(const T& data, Node* next) {
        data_ = data;
        next_ = next;
    }

    template<typename T>
    T& LinkedStack<T>::Node::data() {
        return data_;
    }

    template<typename T>
    const T& LinkedStack<T>::Node::data() const {
        return data_;
    }

    template<typename T>
    typename LinkedStack<T>::Node* LinkedStack<T>::Node::next() {
        return next_;
    }

    template<typename T>
    const typename LinkedStack<T>::Node* LinkedStack<T>::Node::next() const {
        return next_;
    }

    template<typename T>
    void LinkedStack<T>::Node::next(Node* next) {
        next_ = next;
    }
}  // namespace structures
