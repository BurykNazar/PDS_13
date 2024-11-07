#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<iomanip>
#include<Windows.h>

using namespace std;

int N, M;
vector<vector<int>> adjList;

void addEdge(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
}

bool readGraphFromFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл." << endl;
        return false;
    }

    file >> N >> M;

    if (N <= 0 || M <= 0) {
        cerr << "Кількість вершин і ребер повинно бути більше нуля." << endl;
        return false;
    }

    adjList.resize(N);

    for (int i = 0; i < M; i++) {
        int start, end;
        if (!(file >> start >> end)) {
            cerr << "Помилка при зчитуванні ребра." << endl;
            return false;
        }
        if (start < 1 || start > N || end < 1 || end > N) {
            cerr << "Помилка: невірні індекси ребра: "
                << start << " -> " << end << endl;
        }
        addEdge(start - 1, end - 1);
    }

    file.close();
    return true;
}

vector<int> colorGraph() {
    vector<int> colors(N, -1);
    colors[0] = 0;

    vector<bool> isAvbColor(N, false);
    for (int i = 1; i < N; i++) {
        for (int neighbor : adjList[i]) {
            if (colors[neighbor] != -1)
                isAvbColor[colors[neighbor]] = true;
        }

        int clr;
        for (clr = 0; clr < N; clr++)
            if (!isAvbColor[clr])
                break;

        colors[i] = clr;

        for (int neighbor : adjList[i])
            if (colors[neighbor] != -1)
                isAvbColor[colors[neighbor]] = false;
    }

    return colors;
}

void printAdjacencyMatrix() {
    vector<vector<int>> adjMatrix(N, vector<int>(N, 0));

    for (int i = 0; i < N; i++)
        for (int neighbor : adjList[i])
            adjMatrix[i][neighbor] = 1;

    cout << "Матриця суміжності графа: " << endl;
    for (const auto& row : adjMatrix) {
        for (int val : row)
            cout << setw(5) << val << " ";
        cout << endl;
    }
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	string path;
	cout << "Введіть шлях до графа для розфарбування: ";
	getline(cin, path);
    if (!readGraphFromFile(path)) {
        return 1;
    }

    printAdjacencyMatrix();

    vector<int> colors = colorGraph();
    cout << "Розфарбування графа: " << endl;
    for (int i = 0; i < N; i++) {
        cout << "Вершина " << i + 1 << " має колір " << colors[i] + 1 << endl;
    }

	return 0;
}