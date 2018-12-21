// Поиск шарниров и мостов (Сut points )

#include <iostream>
#include <vector>
#include <algorithm> // для функции sort

using namespace std;

int n; //число вершин
vector < vector < int > > g; // список смежности
vector <bool> cutpoint;  // true если шарнир
vector <bool> bridge;  // true если мост
vector <bool> used;
vector <int> tin;   // время входа в вершину i
vector <int> fup;   // Время fup[v] равно минимуму из времени захода в саму вершину
                    //tin[v], времена захода в каждую вершину p, являющуюся концом
                    //некоторого обратного ребра (v,p), а также из всех
                    //значений fup[to] для каждой вершины to, являющейся
                    //непосредственным сыном v в дереве поиска.
int timer;

void CutPoints(int v, int p = -1) { //p - parent. p = -1 если dfs из корня
	used[v] = true;
	tin[v] = fup[v] = timer++;
	int children = 0;  //считаем детей этой вершины (надо для корня)
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue; //ребро в родителя
		if (used[to])
                   //if( tin[to] < fup[v] )
			fup[v] = min (fup[v], tin[to]);
		else {
		     CutPoints(to, v);
		     fup[v] = min (fup[v], fup[to]);
		     if (fup[to] >= tin[v] && p != -1) //если обратное ребро от потомка в V, то всеравно шарнир
		                                       // а для моста равно не надо, только >
				cutpoint[v]= true;
		     ++children;
		}
	}
	if (p == -1 && children > 1)   // если v - это стартовая вершина
                                   // и детей > 1, то корень- шарнир (для мостов это не надо)
		cutpoint[v] = true;
}

void Bridges(int v, int p = -1) { //p - parent. p = -1 если dfs из корня
	used[v] = true;
	tin[v] = fup[v] = timer++;
	for (size_t i=0; i<g[v].size(); ++i) {
		int to = g[v][i];
		if (to == p)  continue; //ребро в родителя
		if (used[to])
                        if( tin[to] < fup[v] ) fup[v] = tin[to];
			//fup[v] = min (fup[v], tin[to]);
		else {
			Bridges(to, v);
			fup[v] = min (fup[v], fup[to]);
			if (fup[to] > tin[v] ) 
				bridge[v]= true;
		}
	}
}

int main(int argc, char** argv) {
	return 0;
}
