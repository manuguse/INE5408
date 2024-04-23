#include <iostream>
#include <string>
#include <fstream>
#include "arrayStack.h"
#include "arrayQueue.h"

using namespace std;
using namespace structures;

struct Scenario {
    string name;
    string content;
    bool wrong = false;
};

const char *getScenariosDir() {
    // TODO fazer ficar generico
    const char *scenariosDirEnv = getenv("CENARIOS_DIR");
    if (scenariosDirEnv != nullptr) {
        return scenariosDirEnv;
    } else {
        return R"(C:/Users/emanu/Documents/ufsc/estruturas-de-dados/trabalhos/trabalho1/cenarios)";
    }
}

int verifyNestedTags(string *scenario) {

    ArrayStack tagsStack = ArrayStack<char>(100);
    for (int i = 0; i < scenario->size(); i++) {
        if (scenario->at(i) == '<') {
            if (scenario->at(i + 1) == '/') {
                i++;
                char tag = scenario->at(i + 1);
                if (tagsStack.empty()) {
                    cout << "Erro" << endl;
                    return 1;
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
    cout << "Tudo certo" << endl;
    return 0;
}

int loadFile(Scenario *currentScenario) {
    string scenarioDir = getScenariosDir();
    string filename = scenarioDir + "/" + currentScenario->name;
    ifstream file(filename);

    if (!file.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << filename << endl;
    } else {
        string line;
        while (getline(file, line)) {
            currentScenario->content += line + "\n"; // Add newline for clarity
        }
        if (verifyNestedTags(&currentScenario->content)) {
            currentScenario->wrong = true;
            return 1;
        };
        file.close();
    }
    return 0;
}

void defineArea(Scenario *currentScenario) {
    if (currentScenario->wrong) {
        cout << "Erro" << endl;
    } else {
        cout << "Tudo certo" << endl;
    }
}


int main() {
    Scenario currentScenario = Scenario();
    cin >> currentScenario.name;
    loadFile(&currentScenario);
    if (!currentScenario.wrong)
        defineArea(&currentScenario);
}