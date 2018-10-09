/* Реализовать граф с помощью матрицы смежности, матрицы инцидентности, списка смежности.

НЕМНОГО ТЕОРИИ: //Для себя

МАТРИЦА СМЕЖНОСТИ ГРАФА — это квадратная матрица, в которой каждый элемент принимает одно из двух значений: 0 или 1.
МАТРИЦА ИНЦИДЕНТНОСТИ ГРАФА — одна из форм представления графа, в которой указываются связи между инцидентными элементами графа
(ребро и вершина).
Столбцы матрицы соответствуют ребрам, строки — вершинам. Ненулевое значение в ячейке матрицы указывает
связь между вершиной и ребром (их инцидентность).
СПИСОК СМЕЖНОСТИ ГРАФА - один из способов представления графа в виде коллекции списков вершин. 
Каждой вершине графа соответствует список, состоящий из "соседей" этой вершины.
*/

#include<iostream>
#include<vector>
#include <utility>
#include<list>

using namespace std;

//Вывести список рёбер
 void PrintListEd(vector<pair<int,int> > g){
      cout << "The list of edges: " << endl;
      for( int i = 0; i < g.size(); i++){
         cout << i + 1 << ") " << g[i].first << ", " << g[i].second << endl;
      }
  }
//Перевести в матрицу смежности
  void MakeMatrixAdj(vector<pair<int,int> > g, bool** matrix){
        for(int i = 0; i < g.size(); i++){
            matrix[g[i].first-1][g[i].second-1] = 1;
            matrix[g[i].second-1][g[i].first-1] = 1;
        }
  }
//Вывести матрицу смежности
  void PrintMatrixAdj(bool** m, int v){
      cout << "The adjacency matrix: " << endl;
      for( int i = 0; i < v; i++){
            for( int j = 0; j < v; j++){
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
}
//Перевести матрицу инцидентности
void MakeMatrixIn(vector<pair<int,int> > p, bool** q){  // p - ребро, q - вершина
    for(int i = 0; i < p.size(); i++){
        q[i][p[i].first-1] = 1;
        q[i][p[i].second-1] = 1;
    }
}
//Вывести матрицу инцидентности
void PrintMatrixIn(bool** m, int r, int v){
     cout<< "incidence matrix: " << endl;
      for( int i = 0; i < r; i++){
            for( int j = 0; j < v; j++){
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
}
//Перевести в список смежности
void MakeListCon(vector<pair<int,int> > a, vector<vector<int> > &b, int k){
    vector<int> temp;
    for (int j = 0; j < k; j++){
        b.push_back(temp);
    }
    for(int i = 0; i < a.size(); i++){
        b[a[i].first-1].push_back(a[i].second);
        b[a[i].second-1].push_back(a[i].first);
    }
}
//Вывести список смежности
void PrintListCon(vector<vector<int> > c, int l){
    cout << "The list of connectivity: " << endl;
    for( int i = 0; i < l; i++){
        cout << i + 1 << ") ";
        for( int j = 0; j < c[i].size(); j++){
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
}


int main(int argc, char** argv){
    int V, E, v1, v2;
    cout << "Enter the number of vertexes: " << endl;
    cin >> V;
    cout << "Enter the number of edges: " << endl;
    cin >> E;
    vector<pair<int,int> > g; //Список рёбер графа
    for(int i = 0; i < E; i++){
        cout << "Enter the information for the " << i + 1 << " edge: ";
        cin >> v1 >> v2;
        g.push_back(make_pair(v1, v2));
            }

    //***СОЗДАНИЕ МАТРИЦ СМЕЖНОСТИ И ИНЦИДЕНТНОСТИ, СПИСКА СМЕЖНОСТИ***
    bool** MatrixIn = new bool*[E];
        for(int i = 0; i < E; i++){               //Матрица инцидентности
            MatrixIn[i] = new bool[V];
        }
        for(int i = 0; i < E; i++){
            for(int j = 0; j < V; j++){
                MatrixIn[i][j]=0;
            }
        }
    bool** MatrixAdj = new bool*[V];
        for(int i = 0; i < V; i++){
            MatrixAdj[i] = new bool[V];               //Матрица смежности
        }
    for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                MatrixAdj[i][j] = 0;
            }
        }
    vector<vector<int> > c;    //Список смежности

    //***РЕАЛИЗАЦИЯ***
    MakeMatrixAdj(g, MatrixAdj);
    MakeMatrixIn(g, MatrixIn);
    MakeListCon(g, c, V);
    PrintListEd(g);
    cout << endl;
    PrintMatrixAdj(MatrixAdj, V);
    cout << endl;
    PrintMatrixIn(MatrixIn, E, V);
    cout << endl;
    PrintListCon(c, V);
    return 0;
}
