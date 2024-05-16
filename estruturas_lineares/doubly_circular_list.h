// Copyright [2024] <Emanuelle Guse>

#include <cstdint>

namespace structures {

    template<typename T>
    class DoublyCircularList {
    public:
        DoublyCircularList();

        ~DoublyCircularList();

        void clear();

        void push_back(const T &data);  // insere no fim
        void push_front(const T &data);  // insere no início
        void insert(const T &data, std::size_t index);  // insere na posição
        void insert_sorted(const T &data);  // insere em ordem

        T pop(std::size_t index);  // retira da posição
        T pop_back();  // retira do fim
        T pop_front();  // retira do início
        void remove(const T &data);  // retira específico

        bool empty() const;  // lista vazia
        bool contains(const T &data) const;  // contém

        T &at(std::size_t index);  // acesso a um elemento (checando limites)
        const T &at(std::size_t index) const;  // getter constante a um elemento

        std::size_t find(const T &data) const;  // posição de um dado
        std::size_t size() const;  // tamanho

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
    void DoublyCircularList<T>::clear() {
        while (!empty()) {
            pop_front();
        }
    }

    template<typename T>
    void DoublyCircularList<T>::push_front(const T &data) {
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
    void DoublyCircularList<T>::push_back(const T &data) {
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
    void DoublyCircularList<T>::insert(const T &data, std::size_t index) {
        if (index > size_) {
            throw std::out_of_range("Index inválido");
        }
        if (index == 0) {
            push_front(data);
        } else {
            Node *new_node = new Node(data);
            Node *current = head;
            for (std::size_t i = 0; i < index - 1; i++) {
                current = current->next();
            }
            new_node->next(current->next());
            new_node->prev(current);
            current->next(new_node);
            new_node->next()->prev(new_node);
            size_++;
        }
    }

    template<typename T>
    void DoublyCircularList<T>::insert_sorted(const T &data) {
        if (empty()) {
            push_front(data);
        } else {
            Node *current = head;
            std::size_t index = 0;
            while (index < size_ && data > current->data()) {
                current = current->next();
                index++;
            }
            insert(data, index);
        }
    }

    template<typename T>
    T DoublyCircularList<T>::pop(std::size_t index) {
        if (index >= size_) {
            throw std::out_of_range("Index inválido");
        }
        if (index == 0) {
            return pop_front();
        } else {
            Node *current = head;
            for (std::size_t i = 0; i < index; i++) {
                current = current->next();
            }
            T data = current->data();
            current->prev()->next(current->next());
            current->next()->prev(current->prev());
            delete current;
            size_--;
            return data;
        }
    }

    template<typename T>
    T DoublyCircularList<T>::pop_back() {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        T data = head->prev()->data();
        Node *last = head->prev();
        last->prev()->next(head);
        head->prev(last->prev());
        delete last;
        size_--;
        return data;
    }

    template<typename T>
    T DoublyCircularList<T>::pop_front() {
        if (empty()) {
            throw std::out_of_range("Lista vazia");
        }
        T data = head->data();
        Node *out = head;
        head = head->next();
        head->prev(out->prev());
        out->prev()->next(head);
        delete out;
        size_--;
        return data;
    }

    template<typename T>
    void DoublyCircularList<T>::remove(const T &data) {
        pop(find(data));
    }

    template<typename T>
    bool DoublyCircularList<T>::empty() const {
        return size_ == 0;
    }

    template<typename T>
    bool DoublyCircularList<T>::contains(const T &data) const {
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
    T &DoublyCircularList<T>::at(std::size_t index) {
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
    const T &DoublyCircularList<T>::at(std::size_t index) const {
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
    std::size_t DoublyCircularList<T>::find(const T &data) const {
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
    std::size_t DoublyCircularList<T>::size() const {
        return size_;
    }

    template<typename T>
    DoublyCircularList<T>::DoublyCircularList() {
        head = nullptr;
        size_ = 0;
    }

    template<typename T>
    DoublyCircularList<T>::~DoublyCircularList() {
        clear();
    }

    template<typename T>
    DoublyCircularList<T>::Node::Node(const T &data) {
        data_ = data;
        prev_ = nullptr;
        next_ = nullptr;
    }

    template<typename T>
    DoublyCircularList<T>::Node::Node(const T &data, Node *next) {
        data_ = data;
        next_ = next;
    }

    template<typename T>
    DoublyCircularList<T>::Node::Node(const T &data, Node *prev, Node *next) {
        data_ = data;
        prev_ = prev;
        next_ = next;
    }

    template<typename T>
    T &DoublyCircularList<T>::Node::data() {
        return data_;
    }

    template<typename T>
    const T &DoublyCircularList<T>::Node::data() const {
        return data_;
    }

    template<typename T>
    typename DoublyCircularList<T>::Node *DoublyCircularList<T>::Node::prev() {
        return prev_;
    }

    template<typename T>
    const typename DoublyCircularList<T>::Node
    *DoublyCircularList<T>::Node::prev() const {
        return prev_;
    }

    template<typename T>
    void DoublyCircularList<T>::Node::prev(Node *node) {
        prev_ = node;
    }

    template<typename T>
    typename DoublyCircularList<T>::Node *DoublyCircularList<T>::Node::next() {
        return next_;
    }

    template<typename T>
    const typename DoublyCircularList<T>::Node
    *DoublyCircularList<T>::Node::next() const {
        return next_;
    }

    template<typename T>
    void DoublyCircularList<T>::Node::next(Node *node) {
        next_ = node;
    }
}  // namespace structures
