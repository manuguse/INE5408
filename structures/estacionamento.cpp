// Copyright [2024] Emanuelle Guse>

#include "ArrayQueue.h"

void retira_veiculo(structures::ArrayQueue<int> *f, int k) {
    for (int i = 0; i < k; ++i) {
        f->enqueue(f->dequeue());
    }
}

void mantenha_veiculo(structures::ArrayQueue<int> *f, int k) {
    int count = 0;
    while (static_cast<int>(f->size()) != 1) {
        if (count == k) {
            f->dequeue();
        } else {
            f->enqueue(f->dequeue());
            count++;
        }
    }
}

// a main está implementada no vpl