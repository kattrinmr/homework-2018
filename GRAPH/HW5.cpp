/* Реализовать программу, которая показывает, находятся ли две вершины в одной компоненте связности */
#include<iostream>
#include<vector>

using namespace std;

int V; //Количество вершин
int** g = new int*[V];

//ПОИСК В ГЛУБИНУ
void dfs(int n, int* used){
    used[n] = 1;
    for(int i = 0; i < V; i++){
        if((used[i] == 0) && (g[n][i] == 1)){
            dfs(i, used);
    }
 }
}
//ПЕРЕВЕСТИ В МАТРИЦУ СМЕЖНОСТИ
void MakeMatrixAdj(vector<pair<int,int> > gr, int** matrix){
        for(int i = 0; i < gr.size(); i++){
            matrix[gr[i].first - 1][gr[i].second - 1] = 1;
            matrix[gr[i].second - 1][gr[i].first - 1] = 1;
        }
  }

int main(int argc, char** argv){
    int E; //Количество рёбер
    cout << "Enter the number of vertexes: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;
    int* used = new int[V];
    for(int i = 0; i < V; i++){
        used[i]=0;
    }
//СПИСОК РЁБЕР И ЕГО ЗАПОЛНЕНИЕ
    vector<pair<int,int> > h;
    int f, s;
    for(int i = 0; i < E; i++){
        cout<<"Enter the information for the "<< i + 1 << "'th edge: " << endl;
        cin >> f >> s;
        h.push_back(make_pair(f,s));
    }
//СОЗДАНИЕ МАТРИЦЫ СМЕЖНОСТИ
    for(int i = 0; i < V; i++){
        g[i] = new int[V];
    }
    for(int i = 0; i < V; i++){
            for(int j = 0; j < V; j++){
                g[i][j]=0;
            }
        }

    MakeMatrixAdj(h, g);
    int v1, v2;
    cout << "Enter the index of the first vertex: ";
    cin >> v1;
    cout << "Enter the index of the second vertex: ";
    cin >> v2;
    dfs(g[v1 - 1][0], used);
    if( used[v2 - 1] == 1){
        cout<< "The vertexes is in the same connected component";
    }
    else{
        cout << "The vertexes isn't in the same connected component";
    }
//УДАЛЕНИЕ ПАМЯТИ
    delete[] used;
    for(int i = V - 1; i >= 0; i--){
        delete[] g[i];
    }
    return 0;
}
