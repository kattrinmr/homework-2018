/* Реализовать поиск кратчайшего пути */

#include<iostream>
#include<utility>
#include<queue>
#include<vector>

using namespace std;

int V; // Количество вершин
int** g = new int*[V];
bool* used = new bool[V];
queue<int> q;
vector<int> parent, dest;// для хранения предыдущей вершины и длины пути по заданным точкам

//ПОИСК В ШИРИНУ (КРАТЧАЙШИЙ ПУТЬ)
void bfs(int v1, int v2){
    int t1;
    for(int x = 0; x < V; x++){
        parent.push_back(t1);
        dest.push_back(t1);
    }
    int t2 = v1 - 1;
    used[t2] = 1;
    parent[t2] = 0;
    dest[t2] = 0;
    q.push(t2);
    while(!q.empty()){
         int k = q.front();
         q.pop();
         for(int i = 0; i < V; i++){
             if(!used[i] && g[k][i] == 1){
                used[i] = 1;
                q.push(i);
                dest[i] = dest[k] + 1;
                parent[i] = k;
             }
         }
     }
    if(!used[v2-1]){
        cout << "There is no path";
    }
    else{
        vector<int> path;
        for(int i = v2 - 1; i != 0; i = parent[i]){
            path.push_back(i + 1);
        }
        cout << "The path is "<< v1 <<" ";
        for(int i = path.size() - 1; i > -1; i--){
            cout << path[i] << " ";
        }
        cout << "The path's length = " << dest[v2-1];
    }
}
//ПЕРЕВЕСТИ В МАТРИЦУ СМЕЖНОСТИ
void MakeMatrixAdj(vector<pair<int, int> > gr){
        for(int i = 0; i < gr.size(); i++){
            g[gr[i].first - 1][gr[i].second - 1] = 1;
        }
    }

int main(int argc, char** argv){
    int E; // Количество рёбер
    cout << "Enter the number of vertexes: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;
//СПИСОК РЁБЕР И ЕГО ЗАПОЛНЕНИЕ
    vector<pair<int,int> > h;
    int f, s;
    for(int i = 0; i < E; i++){
        cout << "Enter the information for the " << i + 1 << "'th edge " << endl;
        cin >> f >> s;
        h.push_back(make_pair(f,s));
    }
//СОЗДАНИЕ МАТРИЦЫ СМЕЖНОСТИ
    for(int i = 0; i < V; i++){
        g[i] = new int[V];
    }
    for(int i = 0; i < V; i++){
        for(int j = 0; j < V; j++){
            g[i][j] = 0;
        }
    }

    MakeMatrixAdj(h);
    bfs(1, 2);
    return 0;
}
