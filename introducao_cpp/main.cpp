#include <iostream>
using namespace std;

struct meuTipo{ // objeto com apenas atributos
    short int ano;
    double tempMedia;
};

int somaV1(int a, int b) {
    // Retorna a soma dos inteiros a e b
    return a + b;
}

int somaV2(int *a, int *b) {
    // Retorna a soma dos valores apontados pelos ponteiros a e b
    // duplicação de memória
    return *a + *b;
}

int somaV3(int &a, int &b) {
    // Retorna a soma dos valores referenciados por a e 
    // sem duplicação de memória
    // apelido, nao endereço
    return a + b;
}

int main() {
    int x = 1, y = 2;
    
    cout << somaV1(x,y) << endl;
    cout << somaV2(&a, &y) << endl;
    cout << somaV3(a,y) << endl;

    char a;
    int b;
    unsigned int c;
    long d;
    float e;
    double f;
    meuTipo g;
    float temps[12] = { // vetor, aloca os enderecos (ponteiro)
        10, 11, 12, 13, 14, 15, 1, 2, 3, 4, 5, 6};   // se a gente nao definisse ele ia botar valores aleatorios
       
    float *p; // ponteiro para p
    p = temps; // p = &temps[0];
    
    g.ano = 2024;
    g.tempMedia = 23.2;
    
    string nome = "UFSC"; // tipo string, definido no namespace
    cout << nome << endl;
    
    cout << "tamanho do char " << sizeof(a)  << endl;
    cout << "tamanho do int " << sizeof(b)  << endl;
    cout << "tamanho do long " << sizeof(d)  << endl;
    cout << "tamanho do float " << sizeof(e)  << endl;
    cout << "tamanho do double " << sizeof(f)  << endl;
    cout << "tamanho do meuTipo " << sizeof(g)  << endl;
    
    cout << g.ano << " " << g.tempMedia << endl;
    
    for (int i=0; i < 12; i++) {
        // cout << temps[i] << " ";
        cout << *(p+i) << " "; // * para ler o conteudo
    } cout << endl;
    
    return 0;
}
