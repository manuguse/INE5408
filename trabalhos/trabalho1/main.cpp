#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "array_stack.h"
#include "array_queue.h"

using namespace std;
using namespace structures;

struct Point {
  int x;
  int y;
} point;

struct Scenario {
  string content;
  bool wrong;
} scenario;

struct SubScenario {
  string name;
  int height;
  int width;
  Point point;
  string matrix;
} subScenario;

/**
 * verifica se há tags incorretas ou faltando tags de fechamento, utilizando uma
 * pilha de strings.
 *
 * @param content o conteúdo do arquivo xml a ser verificado.
 * @return true se houver tags incorretas ou faltando tags de fechamento, false
 * caso contrário.
 */
bool wrongTags(string& content) {
  ArrayStack<string> stack =
      ArrayStack<string>(content.length());  // pilha de strings

  size_t i = 0;  // contador
  size_t start;  // posição de início da tag (abertura ou fechamento)
  size_t end;    // posição de fim da tag (abertura ou fechamento)

  while (i < content.length()) {
    if (content[i] == '<') {
      start = i;
    }  // inicio da tag de abertura na posição i
    else if (content[i] == '>') {  // fim da tag de abertura na posição i
      end = i;
      string tag = content.substr(start + 1,
                                  end - (start + 1));  // tag = conteúdo da tag
      if (tag[0] == '/') {                             // tag de fechamento
        if (stack.empty()) {                           // pilha vazia
          return true;
        }  // está faltando tag de abertura
        if (stack.top() == tag.substr(1)) {  // tag de fechamento correta
          stack.pop();
        }  // desempilha
        else {  // tag de fechamento incorreta
          return true;
        }
      }  // erro de tag de fechamento
      else {  // tag de abertura
        stack.push(tag);
      }
    }  // empilha
    i++;
  }  // continua a percorrer string
  return !stack.empty();  // pilha não vazia (se for verdadeiro, está faltando
                          // tag de fechamento)
}

/**
 * pega o conteúdo de uma tag específica.
 *
 * @param content o conteúdo do arquivo xml.
 * @param tag a tag a ser procurada.
 * @param start a posição de início da busca, baseada em quantos já foram.
 * @return o conteúdo da tag.
 */
string getTagContent(string& content, string tag, int start) {
  int open = content.find('<' + tag + '>', start);  // procura tag de abertura
  int close =
      content.find("</" + tag + '>', open);  // procura tag de fechamento
  int end_open = open + tag.size() + 2;  // posição de início do conteúdo
  return content.substr(end_open, close - end_open);  // retorna conteúdo da tag
}

SubScenario createSubcenario(string& content, int start) {
  SubScenario subScenario;
  subScenario.name = getTagContent(content, "nome", start);
  subScenario.height = stoi(getTagContent(content, "altura", start));
  subScenario.width = stoi(getTagContent(content, "largura", start));
  subScenario.point.x = stoi(getTagContent(content, "x", start));
  subScenario.point.y = stoi(getTagContent(content, "y", start));
  subScenario.matrix = getTagContent(content, "matriz", start);
  return subScenario;
}

vector<SubScenario> createSubScenarios(Scenario& scenario) {
  vector<SubScenario> subScenarios;  // lista de subcenarios
  int start = 0;
  while (true) {
    // adiciona subcenario à lista
    try {
      subScenarios.push_back(createSubcenario(scenario.content, start));
    } catch (std::invalid_argument& e) {
      return subScenarios;
    }
    start += getTagContent(scenario.content, "cenario", start).length();
    // atualiza posição de início (tamanho do conteudo do
    // subcenario + tamanho da tag <cenario> e </cenario>)
  }
  return subScenarios;
};

Scenario createScenario(string path) {
  ifstream file(path);
  if (file.is_open()) {
    string line;
    while (getline(file, line)) {
      scenario.content += line;
    }
    file.close();
  } else {
    cout << "Erro ao abrir arquivo" << endl;
  }
  scenario.wrong = wrongTags(scenario.content);
  return scenario;
}

/**
 * calcula a área de um subcenário.
 * a área é calculada utilizando uma matriz de visitados e uma pilha de pontos.
 *
 * @param subScenario o subcenário a ser calculado.
 * @return a área do subcenário.
 * */
int calculateArea(SubScenario& subScenario) {
    vector<vector<bool>> visited(subScenario.height, vector<bool>(subScenario.width, false));
    ArrayQueue<Point> queue = ArrayQueue<Point>(subScenario.height * subScenario.width);

    queue.enqueue(subScenario.point); // adiciona o ponto inicial à fila
    int area = 0; // área total

    while (!queue.empty()) {
        Point point = queue.dequeue(); // remove o primeiro ponto da fila

        // verifica se o ponto está dentro dos limites do subcenário
        if (point.x >= 0 && point.x < subScenario.height && point.y >= 0 && point.y < subScenario.width) {
            // verifica se o ponto não foi visitado
            if (!visited[point.x][point.y]) {
                // marca o ponto como visitado
                visited[point.x][point.y] = true;

                // verifica se o ponto é uma área válida
                if (subScenario.matrix[point.x * subScenario.width + point.y] == '1') {
                    area++; // aumenta a área

                    // adiciona os pontos dos lados à fila
                    if (point.x - 1 >= 0 && !visited[point.x - 1][point.y]) // acima
                        queue.enqueue({point.x - 1, point.y});
                    if (point.x + 1 < subScenario.height && !visited[point.x + 1][point.y]) // abaixo
                        queue.enqueue({point.x + 1, point.y});
                    if (point.y - 1 >= 0 && !visited[point.x][point.y - 1]) // esquerda
                        queue.enqueue({point.x, point.y - 1});
                    if (point.y + 1 < subScenario.width && !visited[point.x][point.y + 1]) // direita
                        queue.enqueue({point.x, point.y + 1});
                }
            }
        }
    }
    return area;
}

int main() {
  string path;
  cin >> path;
  Scenario scenario = createScenario(path);
  if (scenario.wrong) {
    cout << "Erro" << endl;
  } else {
    vector<SubScenario> subScenarios = createSubScenarios(scenario);
    int size = subScenarios.size();
    for (int i = 0; i < size; i++) {
      cout << subScenarios[i].name << " " << calculateArea(subScenarios[i])
           << endl;
    }
  }
  return 0;
}