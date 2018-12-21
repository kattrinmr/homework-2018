/* Реализовать топологическую сортировку */

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
/*int n; // число вершин
vector<int> g[MAXN]; // граф
bool used[MAXN];
vector<int> ans;
 
void dfs (int v) {
	used[v] = true;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (!used[to])
			dfs (to);
	}
	ans.push_back (v);
}
 
void topological_sort() {
	for (int i=0; i<n; ++i)
		used[i] = false;
	ans.clear();
	for (int i=0; i<n; ++i)
		if (!used[i])
			dfs (i);
	reverse (ans.begin(), ans.end());
	*/
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

#include<iostream>
#include<vector>
#include<utility>

using namespace std;

int v; //Количество вершин
bool* used = new bool[v];     //Для DFS
vector<int> ans;             // и топологической сортировки
int** g = new int*[v]; //Граф

//РЕАЛИЗАЦИЯ ГРАФА (МАТРИЦА СМЕЖНОСТИ)
  void MakeMatrixAdj(vector<pair<int,int> > q){
        for(int i = 0; i < q.size(); i++){
            g[q[i].first-1][q[i].second-1] = 1;
        }
  }
  void PrintMatrixAdj(int** m, int v){
      cout << "The adjacency matrix: " << endl;
      for( int i = 0; i < v; i++){
            for( int j = 0; j < v; j++){
                cout << m[i][j] << " ";
            }
            cout << endl;
        }
}

//ПОИСК В ГЛУБИНУ
void DFS(int s){
     used[s] = true; //Отметили стартовую вершину
     for (int i = 0; i < v; ++i){
        if ((g[s][i] == 1) && (used[i] == false))
            DFS(i);
    }
    ans.push_back(s+1);
}
//ТОПОЛОГИЧЕСКАЯ СОРТИРОВКА
void TopologicalSort(){
    for( int i = 0; i < v; i++){
		if( used[i] == false)
            DFS(i);
    }
    vector <int> temp;
	for (int i = 0; i < v; i++){
        temp.push_back(ans[i]);
	}
	for (int i = 0; i < v; i++){
        ans[v - 1 - i] = temp[i];
	}
}

int main(int argc, char** argv){
    cout << "Enter the number of vertexes: ";
    cin >> v;
    cout << "Enter the number of edges: ";
    int e;
    cin >> e;
    //Создание матрицы смежности
    for( int i = 0; i < v; i++){
        g[i] = new int[v];
    }
    for( int i = 0; i < v; i++){
        for( int j = 0; j < v; j++){
            g[i][j] = 0;
        }
    }
    vector<pair<int,int> > E; //Список рёбер
    int f,s;
    for( int i = 0; i < e; i++){
        cout << "Enter the information of " << i + 1 << "'th edge: " << endl;
        cin >> f;
        cin >> s;
        E.push_back(make_pair(f,s));
        cout << endl;
    }
    MakeMatrixAdj(E);
    TopologicalSort();
    for(int i = 0; i < v; i++){
        cout << ans[i] << " ";
    }

    return 0;
}
