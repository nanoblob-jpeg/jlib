#include "jlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(){
	int edges[][2] = {
		{1, 2},
		{1, 3},
		{2, 4},
		{4, 7},
		{4, 8},
		{8, 11},
		{3, 5},
		{3, 6},
		{6, 9},
		{6, 10}
	};
	graph *G = createGraph(11, 10, edges, true);
	dfs(G, 1, NULL, NULL, NULL);
	printGraph(G);
	free(G);
}