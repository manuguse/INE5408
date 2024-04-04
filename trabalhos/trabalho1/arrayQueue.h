//
// Created by emanu on 03/04/2024.
//

#ifndef TRABALHO1_ARRAYQUEUE_H
#define TRABALHO1_ARRAYQUEUE_H

#include <cstring>
#include <stdexcept>

namespace structures {

    template<typename T>
    class ArrayQueue {
    public:
        //! construtor padrao
        ArrayQueue();

        //! construtor com parametro
        explicit ArrayQueue(std::size_t max);

        //! destrutor padrao
        ~ArrayQueue();

        //! metodo enfileirar
        void enqueue(const T &data);

        //! metodo desenfileirar
        T dequeue();

        //! metodo retorna o ultimo
        T &back();

        //! metodo limpa a fila
        void clear();

        //! metodo retorna tamanho atual
        std::size_t size();

        //! metodo retorna tamanho maximo
        std::size_t max_size();

        //! metodo verifica se vazio
        bool empty();

        //! metodo verifica se esta cheio
        bool full();

    private:
        T *contents;
        std::size_t size_;
        std::size_t max_size_;
        int begin_;  // indice do inicio (para fila circular)
        int end_;  // indice do fim (para fila circular)
        static const auto DEFAULT_SIZE = 10u;
    };
}  // namespace structures

template<typename T>
structures::ArrayQueue<T>::ArrayQueue() {
    max_size_ = DEFAULT_SIZE;
    contents = new T[max_size_];
    size_ = 0;
    begin_ = 0;
    end_ = -1;
}

template<typename T>
structures::ArrayQueue<T>::ArrayQueue(std::size_t max) {
    max_size_ = max;
    contents = new T[max_size_];
    size_ = 0;
    begin_ = 0;
    end_ = -1;
}

template<typename T>
structures::ArrayQueue<T>::~ArrayQueue() {
    delete[] contents;
}

template<typename T>
void structures::ArrayQueue<T>::enqueue(const T &data) {
    if (full()) {
        throw std::out_of_range("fila cheia");
    } else {
        end_ = (end_ + 1) % max_size_;
        contents[end_] = data;
        size_++;
    }
}

template<typename T>
T structures::ArrayQueue<T>::dequeue() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        T data = contents[begin_];
        begin_ = (begin_ + 1) % max_size_;
        size_--;
        return data;
    }
}

template<typename T>
T &structures::ArrayQueue<T>::back() {
    if (empty()) {
        throw std::out_of_range("fila vazia");
    } else {
        return contents[end_];
    }
}

template<typename T>
void structures::ArrayQueue<T>::clear() {
    size_ = 0;
    begin_ = 0;
    end_ = -1;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::size() {
    return size_;
}

template<typename T>
std::size_t structures::ArrayQueue<T>::max_size() {
    return max_size_;
}

template<typename T>
bool structures::ArrayQueue<T>::empty() {
    return size_ == 0;
}

template<typename T>
bool structures::ArrayQueue<T>::full() {
    return size_ == max_size_;
}

#endif TRABALHO1_ARRAYQUEUE_H