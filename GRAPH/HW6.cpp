/* Эйлеров путь */

#include<iostream>
#include<vector>
#include<queue>
#include<utility>

using namespace std;

int V;//Количество вершин
int** g = new int*[V];

//ПЕРЕВЕСТИ В МАТРИЦУ СМЕЖНОСТИ
void MakeMatrixAdj(vector<pair<int,int> > gr, int** matrix){
        for( int i = 0; i < gr.size(); i++){
            matrix[gr[i].first - 1][gr[i].second - 1] = 1;
            matrix[gr[i].second - 1][gr[i].first - 1] = 1;
        }
  }
//ПОИСК В ГЛУБИНУ
void dfs(int n, bool* used){
    used[n] = 1;
    for( int i = 0; i < V; i++){
        if((used[i] == 0) && (g[n][i]==1)){
            dfs(i, used);
    }
 }
}
//КОЛИЧЕСТВО КОМПОНЕНТ СВЯЗНОСТИ
int NumConCom(bool* used){
    int temp = 1;
    for(int i = 0; i < V; i++){
        if(used[i] == 0){
            dfs(i, used);
            temp++;
        }
    }
    return temp;
}
//ЧЁТНОСТЬ ГРАФА
int parity(int** k, int l){
        int temp = 0;
        int p;
        for(int i = 0; i < l; i++){
                p = 0;
            for(int j = 0; j < l; j++){
                if(k[i][j] == 1) p++; }
            if( p%2 == 1) temp++; }
    return temp;
}

void EulerWay(int** k, int l, bool* c){
            if((parity(k, l) < 3) && (NumConCom(c) == 1)){
                cout << "Exists";
            }
            else{
                cout << "Doesn't exist";
            }
}

int main(int argc, char** argv){
    int E; //Количество рёбер
    cout<<"Enter the number of vertexes: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;
//СПИСОК РЁБЕР И ЕГО ЗАПОЛНЕНИЕ
    vector<pair<int,int> > h;
    bool* used = new bool[V];
    int f,s;
    for(int i = 0; i < E; i++){
        cout<<"Enter the information for the " << i+1 <<"'th edge " << endl;
        cin >> f >> s;
        h.push_back(make_pair(f,s));
    }
//СОЗДАНИЕ МАТРИЦЫ СМЕЖНОСТИ
    for(int i = 0; i < V; i++){
        g[i] = new int[V];
        used[i] = 0;
    }
    for( int i = 0; i < V; i++){
        for( int j = 0; j < V; j++){
            g[i][j] = 0;
        }
    }
    MakeMatrixAdj(h, g);
    dfs(0, used);
    EulerWay(g, V, used);
    return 0;
}
