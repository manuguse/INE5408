// COM CERTEZA nõo é o melhor jeito de fazer

#include <string>


class Aluno {
 public:
    Aluno() {}  // construtor
    ~Aluno() {}  // destrutor
    std::string devolveNome() {
        return nome;
    }
    int devolveMatricula() {
        return matricula;
    }
    void escreveNome(std::string nome_) {
        nome = nome_;
    }
    void escreveMatricula(int matricula_) {
        matricula = matricula_;
    }
 private:
    std::string nome;
    int matricula;
};

int *turma_conta(Aluno t[], int N) {
    int *c;
    c = new int[26];
    for (int i = 0; i < 26; ++i) {
        c[i] = 0;
    }
    for (int i = 0; i < N; ++i) {
        c[t[i].devolveNome()[0] - 'A']++;
    }
    return c;
}

Aluno **grupos_por_iniciais(Aluno t[], int N) {
    Aluno **g;
    g = new Aluno*[26];  // vetor de ponteiros;
                         // cada posição aponta para um vetor de alunos;
                         // tg[i] deve ser alocado com o seguinte:
                         //   tg[0] é um ponteiro para alunos com letra 'A'
                         //   tg[1] é um ponteiro para alunos com letra 'B'
                         //   ...
                         //   tg[25] é um ponteiro para alunos com letra 'Z'

    // DICA: utilize a função 'turma_conta' (implementada no execício 5) para
    //       definir o tamanho de cada um dos 26 vetores

    int* c = turma_conta(t, N);
    for (int i = 0; i < 26; i++) {
        g[i] = new Aluno[c[i]];
    }
    
    int* indiceGrupo = new int[26];
    for (int i = 0; i < 26; i++) {
        indiceGrupo[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        int indice = t[i].devolveNome()[0] - 'A';
        int indiceAtual = indiceGrupo[indice];
        g[indice][indiceAtual] = t[i];
        indiceGrupo[indice]++;
    }
    delete [] indiceGrupo;
    return g;
}

/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
