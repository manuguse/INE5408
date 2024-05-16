#include <iostream>
#define TIPO int

using namespace std;
const int N1 = 1000;  // é melhor pras alocações estáticas
const int N2 = 10;    // ter os valores constantes

TIPO *alocaDinamico(int tamanho) { // dinâmica
    TIPO *p;
    p = new TIPO[tamanho];
    for (int i = 0; i < tamanho; i++) { 
        // se tiver uma única intrução não é obrigatório ter chave, mas é muito útil
        p[i] = i; // criando o vetor
    }
    return p;
}

void alocaEstatico(TIPO *p, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        p[i] = 1;
    }
}

int main()
{
    bool TESTE;
    TESTE = true;

    if (TESTE) {
        TIPO nomeVariavel;  // alocação estática
        nomeVariavel = 10;
        
        TIPO v2[N1]; // tambem alocação estatica

        TIPO *ponteiro;
        ponteiro = new TIPO;  // alocação dinâmica
        *ponteiro = 20;
        
        TIPO *p2;
        p2 = new TIPO[N1];
        p2[3] = N1; 

        cout << "escopo do if - " << nomeVariavel << endl; 
        // nome_variavel é deslocada automaticamente
        // memoria de ponteiro é mantida
        
        delete ponteiro; // só precisamos nos preocupar em fazer o delete com alocação dinâmica
        delete [] p2; // precisamos indicar que é um vetor
    }
    
    TIPO *p3;
    p3 = alocaDinamico(N2);
    
    for (int i = 0; i < N2; i++) {
        cout << p3[i] << " ";
    }
    
    delete [] p3;
    
    // pré decremento
    int a = 10;
    int b = 15 + --a;
        // a = a - 1 
        // b = 15 + a
    // -> a = 9, b = 24

    // pós decremento
    int c = 10;
    int d = 15 + (a--);
        // b = 15 + a
        // a = a - 1
    // -> b = 25, a = 9

    return 0;
}
