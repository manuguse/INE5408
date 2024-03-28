// Copyright [2024] <Emanuelle Guse>
//#include "./array_stack.h"
#include "structures.h"

bool verificaChaves(std::string trecho_programa) {
    bool resposta = true;
    int  tamanho  = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);

    for (int i = 0; i < tamanho; i++) {
        if (trecho_programa[i] == '{') {
            pilha.push(trecho_programa[i]);
        } else if (trecho_programa[i] == '}') {
            if (pilha.empty()) {
                resposta = false;
                break;
            } else {
                pilha.pop();
            }
        }
    }
    return resposta;
}
