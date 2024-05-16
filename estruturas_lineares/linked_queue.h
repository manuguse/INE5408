//! Copyright [2024] <Emanuelle Guse>

#include <cstdint>   // std::size_t
#include <stdexcept>   // C++ exceptions

namespace structures {

    template<typename T>
    class LinkedQueue {
    public:
        LinkedQueue();

        ~LinkedQueue();

        void clear();  // limpar

        void enqueue(const T &data);  // enfileirar

        T dequeue();  // desenfileirar

        T &front() const;  // primeiro dado

        T &back() const;  // último dado

        bool empty() const;  // fila vazia

        std::size_t size() const;  // tamanho

    private:
        class Node {
        public:
            explicit Node(const T &data);

            explicit Node(const T &data, Node *next);

            T &data();  // getter: info
            const T &data() const;  // getter-constante: info

            Node *next();  // getter: próximo
            const Node *next() const;  // getter-constante: próximo

            void next(Node *next);  // setter: próximo
        private:
            T data_;
            Node *next_;
        };

        Node *top_;  // nodo-topo
        std::size_t size_;  // tamanho
    };

    template<typename T>
    LinkedQueue<T>::LinkedQueue() {
        top_ = nullptr;
        size_ = 0;
    }

    template<typename T>
    LinkedQueue<T>::~LinkedQueue() {
        clear();
    }

    template<typename T>
    void LinkedQueue<T>::clear() {
        while (!empty()) {
            dequeue();
        }
    }

    template<typename T>
    void LinkedQueue<T>::enqueue(const T &data) {
        if (empty()) {
            top_ = new Node(data);
        } else {
            Node *last = top_;
            while (last->next() != nullptr) {
                last = last->next();
            }
            last->next(new Node(data));
        } size_++;
    }

    template<typename T>
    T LinkedQueue<T>::dequeue() {
        if (empty()) {
            throw std::out_of_range("Fila vazia");
        } else {
            Node *out = top_;
            T data = out->data();
            top_ = top_->next();
            delete out;
            size_--;
            return data;
        }
    }

    template<typename T>
    T &LinkedQueue<T>::front() const {
        if (empty()) {
            throw std::out_of_range("Fila vazia");
        }
        return top_->data();
    }

    template<typename T>
    T &LinkedQueue<T>::back() const {
        if (empty()) {
            throw std::out_of_range("Fila vazia");
        }
        Node *last = top_;
        while (last->next() != nullptr) {
            last = last->next();
        }
        return last->data();
    }

    template<typename T>
    bool LinkedQueue<T>::empty() const {
        return size_ == 0;
    }

    template<typename T>
    std::size_t LinkedQueue<T>::size() const {
        return size_;
    }

    template<typename T>
    LinkedQueue<T>::Node::Node(const T &data) {
        data_ = data;
        next_ = nullptr;
    }

    template<typename T>
    LinkedQueue<T>::Node::Node(const T &data, Node *next) {
        data_ = data;
        next_ = next;
    }

    template<typename T>
    T &LinkedQueue<T>::Node::data() {
        return data_;
    }

    template<typename T>
    const T &LinkedQueue<T>::Node::data() const {
        return data_;
    }

    template<typename T>
    typename LinkedQueue<T>::Node *LinkedQueue<T>::Node::next() {
        return next_;
    }

    template<typename T>
    const typename LinkedQueue<T>::Node *LinkedQueue<T>::Node::next() const {
        return next_;
    }

    template<typename T>
    void LinkedQueue<T>::Node::next(Node *next) {
        next_ = next;
    }
}  // namespace structures
