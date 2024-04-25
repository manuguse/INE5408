#include <iostream>
#include <string>
#include <fstream>
#include "arrayStack.h"

using namespace std;
using namespace structures;

struct Scenario {
    string name;
    string content;
    bool wrong = false;
};

string getDirectory() {
    return R"(C:\Users\emanu\Documents\ufsc\estruturas-de-dados\trabalhos\trabalho1\)";
}

int verifyNestedTags(string *scenario) {

    ArrayStack <char> tagsStack = ArrayStack<char>(100);
    for (int i = 0; i < scenario->size(); i++) {
        if (scenario->at(i) == '<') {
            if (scenario->at(i + 1) == '/') {
                i++;
                char tag = scenario->at(i + 1);
                if (tagsStack.empty()) {
                    cout << "Erro" << endl;
                    return 2;
                }
                char top = tagsStack.top();
                if (top != tag) {
                    cout << "Erro" << endl;
                    return 1;
                }
                tagsStack.pop();
            } else {
                char tag = scenario->at(i + 1);
                tagsStack.push(tag);
            }
        }
    }
    return 0;
}

void loadFile(Scenario *currentScenario) {

    string directory = getDirectory();
    string filename = directory + currentScenario->name; // assumimos que o nome do arquivo é o nome do
                                                         // cenário e que ele está na raiz do projeto
    ifstream file(filename);              // abrimos o arquivo

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
        currentScenario->wrong = true;
    } else {
        string line;
        while (getline(file, line)) {
            currentScenario->content += line + "\n";
        }
        if (verifyNestedTags(&currentScenario->content)) {
            currentScenario->wrong = true;
        }
        file.close();
    }
}

void defineArea(Scenario *currentScenario) {
    printf("");
}

void findMeasures(Scenario *currentScenario) {
}

int main() {
    Scenario currentScenario = Scenario();
    // cin >> currentScenario.name;
    currentScenario.name = "cenarios1.xml";
    loadFile(&currentScenario);
    if (!currentScenario.wrong)
        defineArea(&currentScenario);
}