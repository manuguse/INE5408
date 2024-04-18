#include <iostream>
#include <string>
#include "arrayStack.h"

using namespace std;

bool validXML(string *currentScenario) {
    return rand() % 2;
}

bool validMove(int x, int y, int xMax, int yMax) {
    if (x < 0 || x > xMax) {
        return false;
    } else if (y < 0 || y > yMax) {
        return false;
    } else {
        return true;
    }
}

struct coordinates {
    int x;
    int y;
};

void verifiesArea(string *pString) {
    structures::ArrayStack stack = new structures::ArrayStack(10);
}


int main() {
    string *currentScenario;
    for (int i = 1; i < 7; ++i) {
        currentScenario = new string("scenario" + to_string(i) + ".xml");
        if (validXML(currentScenario)) {
            verifiesArea(currentScenario);
        } else {
            cout << "erro" << endl;
        }
    }
    free(currentScenario);
    return 0;
}

