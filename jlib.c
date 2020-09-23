#ifndef JLIB
#define JLIB

/*
AUTHOR: Jerry Li unless otherwise specified
NOTES:
- to use these functions on a std::string, pass the string using &str[0] so that you pass a char* instead of a const char* when using str.c_str()
- queue is made up of elements called item, uses a singly linked list
- stack is made up of elements called item, uses a singly linked list
- set union data structure is not general, made specially for kruskal algorithm
- graphs use adjacent lists
*/
#ifdef __cplusplus
extern "C" {
#endif
	
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

//temp
	//
	//
	//
	//

#define JLIB_GRAPH
	//
	//
	//
	//
	//


#ifdef JLIB_PRINT
/*
this is a general purpose print function that allows you to specify what
string separator and end character you want
- you must pass in what you want to print as c style strings
*/
void print(int num_args, char separator, char endline, ...){
	va_list ap;
	va_start(ap, endline);
	for(int i = 0; i < num_args; ++i){
		char *output = va_arg(ap, char*);
		printf(output);
		printf("%c", separator);
	}
	printf("%c", endline);
	va_end(ap);
}
/*
assumes that you are printing one line separated by spaces and ending with endline
- you must pass in what you want to print as c style strings
*/
void println(int num_args, ...){
	va_list ap;
	va_start(ap, num_args);
	for(int i = 0; i < num_args; ++i){
		char *output = va_arg(ap, char*);
		printf("%s%c", output, ' ');
	}
	printf("%c", '\n');
	va_end(ap);
}
#endif
#ifdef JLIB_TIMER
clock_t fJdmiB6HJmrxl8Vb2ApzV1bRTTec;
/*
starts the timer
*/
void timerStart(){
	fJdmiB6HJmrxl8Vb2ApzV1bRTTec = clock();
}
/*
stops the timer
*/
void timerEnd(){
	fJdmiB6HJmrxl8Vb2ApzV1bRTTec = clock() - fJdmiB6HJmrxl8Vb2ApzV1bRTTec;
}
/*
print the time elapsed from when you called timerStart() and timerEnd()
*/
void timerPrint(){
	double time = ((double)fJdmiB6HJmrxl8Vb2ApzV1bRTTec)/CLOCKS_PER_SEC;
	printf("took %f seconds\n", time);
}
#endif
#ifdef JLIB_STRING
/*
turns all characters in a string to lowercase
*/
char* lower(char *s){
	int length = strlen(s);
	for(int i = 0; i < length; ++i){
		if(s[i] >= 'A' && s[i] <= 'Z'){
			s[i] += 32;
		}
	}
	return s;
}
/*
turns all characters in a string to uppercase
*/
char* upper(char *s){
	int length = strlen(s);
	for(int i = 0; i < length; ++i){
		if(s[i] >= 'a' && s[i] <= 'z'){
			s[i] -= 32;
		}
	}
	return s;
}

/*
AUTHOR OF TRIM FUNCTIONS IS MARTIN BROADHURST
FOUND AT martinbroadhurst.com
I MAKE NO CLAIM TO THESE THREE FUNCTIONS:
char *ltrim(char *str, const char *seps)
char *rtrim(char *str, const char *seps)
char *trim(char *str, const char *seps)

MINOR CHANGES DONE TO MAKE IT WORK WITH C++
*/
/*
removes seps chars from the left side of a string
*/
char *ltrim(char *str, const char *seps)
{
    size_t totrim;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        }
        else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}
/*
removes seps chars from the right side of a string
*/
char *rtrim(char *str, const char *seps)
{
    int i;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    i = strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }
    return str;
}
/*
removes seps chars from the left and right side of a string
*/
char *trim(char *str, const char *seps)
{
    return ltrim(rtrim(str, seps), seps);
}
/*
replaces all toReplace chars in a string with replacer
*/
char *replace(char *str, char toReplace, char replacer){
	int length = strlen(str);
	for(int i = 0; i < length; ++i){
		if(str[i] == toReplace){
			str[i] = replacer;
		}
	}
	return str;
}
#endif
#if defined JLIB_GRAPH || defined JLIB_STACK || defined JLIB_QUEUE
/*
int item used for the queues and stacks
*/
typedef struct item{
	int i;
	struct item *next;
}item;
#endif
#if defined JLIB_GRAPH || defined JLIB_QUEUE
/*



INT QUEUE DATA STRUCTURE



*/
typedef struct queue{
	int size;
	item *first;
}queue;
/*
allocates data for a queue and sets values to 0/NULL
*/
queue* createQueue(){
	queue *Q = (queue*)(calloc(1, sizeof(queue)));
	Q->size = 0;
	Q->first = NULL;
	return Q;
}
/*
adds an item to the queue
*/
void enqueue(queue* Q, int i){
	item *add = (item*)(calloc(1, sizeof(item)));
	add->i = i;
	add->next = NULL;
	item *head = Q->first;
	if(!head){
		Q->first = add;
	}else{
		while(head->next){
			head = head->next;
		}
		head->next = add;
	}
	Q->size++;
}
/*
returns and removes an item out of the queue
*/
int dequeue(queue* Q){
	if(Q->size == 0){
		return -1;
	}
	if(Q->size == 1){
		Q->size--;
		int output = Q->first->i;
		free(Q->first);
		Q->first = NULL;
		return output;
	}
	item *temp = Q->first;
	Q->first = Q->first->next;
	int output = temp->i;
	free(temp);
	Q->size--;
	return output;
}
/*
returns if the queue is empty
*/
bool isEmpty(queue* Q){
	return Q->size == 0;
}
/*
frees the queue
*/
void freeQueue(queue *Q){
	while(Q->size > 0){
		dequeue(Q);
	}
	free(Q);
}
#endif
#if defined JLIB_STACK || defined JLIB_GRAPH
/*



INT STACK DATA STRUCTURE




*/
typedef struct stack{
	int size;
	item *first;
}stack;
/*
allocates memory for the stack
*/
stack *createStack(){
	stack *S = (stack*)(calloc(1, sizeof(stack)));
	S->size = 0;
	S->first = NULL;
	return S;
}
/*
adds an item to the stack
*/
void pushStack(stack *s, int v){
	item *temp = (item*)(calloc(1, sizeof(item)));
	temp->i = v;
	temp->next = s->first;
	s->first = temp;
	s->size++;
}
/*
removes and returns an item from the stack
*/
int popStack(stack *s){
	if(s->size == 0){
		return -1;
	}
	int output = s->first->i;
	item *toFree = s->first;
	s->first = s->first->next;
	free(toFree);
	s->size--;
	return output;
}
/*
prints the stack top to bottom
*/
void printStack(stack *s){
	item *temp = s->first;
	printf("\n");
	while(s->first){
		printf("%d ", s->first->i);
		s->first = s->first->next;
	}
	printf("\n");
	s->first = temp;
}
/*
frees the stack
*/
void freeStack(stack *s){
	while(s->size > 0){
		popStack(s);
	}
	free(s);
}
#endif
#if defined JLIB_GRAPH || defined JLIB_SETUNION
/*



INT SET UNION DATA STRUCTURE



*/
typedef struct{
	int *p;
	int *size;
	int n;
}setUnion;
/*
allocates memory for set union
*/
void createSetUnion(setUnion *s, int size){
	s = (setUnion *)(calloc(1, sizeof(setUnion)));
	s->p = (int *)(calloc(size, sizeof(int)));
	s->size = (int *)(calloc(size, sizeof(int)));

	for(int i = 1; i <= size; ++i){
		s->p[i] = i;
		s->size[i] = 1;
	}
	s->n = size;
}
/*
find parent of the integer x
*/
int find(setUnion *s, int x){
	if(s->p[x] == x) return x;
	else return (find(s, s->p[x]));
}
/*
combines two union sets
*/
void unionSets(setUnion *s, int s1, int s2){
	int r1, r2;
	r1 = find(s, s1);
	r2 = find(s, s2);
	if(r1 == r2) return;
	if(s->size[r1] >= s->size[r2]){
		s->size[r1] = s->size[r1] + s->size[r2];
		s->p[r2] = r1;
	}else{
		s->size[r2] = s->size[r1] + s->size[r2];
		s->p[r1] = r2;
	}
}
/*
returns whether two ints are part of the same tree
*/
bool same_component(setUnion *s, int s1, int s2){
	return (find(s, s1) == find(s, s2));
}
#endif
#ifdef JLIB_GRAPH
/*



GRAPH DATA STRUCTURE

MOST OF THESE METHODS ARE FROM THE BOOK:
SKIENA THE ALGORITHM DESIGN MANUAL
I MAKE NO CLAIM TO THESE ALGORITHMS


*/
typedef struct edgenode{
	int y;
	int weight;
	struct edgenode *next;
}edgenode;

typedef struct graph{
	int nvertices;
	int nedges;
	bool directed;
	edgenode **edges;
	int *degree;

	int *parent;
	bool *discovered;
	bool *processed;
	int *entry_time;
	int *exit_time;
	int time;
	bool bfs;
	bool dfs;
	bool finished;

	int *reachable_ancestor;
	int *tree_out_degree;

	queue *q;
	stack *s;
}graph;
/*
helper function for sorting the edges to make adding them easier
*/
static int cmprow(const void *a, const void *b){
    const int * const ia = (const int*)a, * const ib = (const int*)b;
    return ia[0] < ib[0] ? -1 : ia[0] > ib[0];
}

//graph creation
/*
adds an edge to a certain vertex in the adjacency list
*/
void prependEdge(graph *G, int x, int y){
	edgenode *root = (edgenode*)(calloc(1, sizeof(edgenode)));
	root->y = y;
	root->weight = 1;
	root->next = G->edges[x];
	G->edges[x] = root;
}
/*
adds a weighted edge to a certain vertex in the adjacency list
*/
void prependWeightedEdge(graph *G, int currentVertex, int y, int weight){
	edgenode *root = (edgenode*)(calloc(1, sizeof(edgenode)));
	root->y = y;
	root->weight = weight;
	root->next = G->edges[currentVertex];
	G->edges[currentVertex] = root;
}
/*
allocates memory and sets values for nonweighted graph
*/
graph* createGraph(int numVertices, int numEdges, int sides[][2], bool directed){
	if(numVertices == 0){
		return NULL;
	}
	graph *G = (graph*)(calloc(1, sizeof(graph)));
	G->degree = (int*)(calloc(numVertices + 1, sizeof(int)));
	G->edges = (edgenode**)(calloc(numVertices + 1, sizeof(edgenode*)));
	G->directed = directed;
	G->nvertices = numVertices;
	G->nedges = numEdges;
	G->parent = (int*)(calloc(numVertices + 1, sizeof(int)));
	G->bfs = false;
	G->dfs = false;
	G->time = 0;
	G->finished = false;
	if(!directed){
		for(int i = 0; i < numEdges; ++i){
			G->degree[sides[i][0]] += 1;
			G->degree[sides[i][1]] += 1;
		}
	}else{
		for(int i = 0; i < numEdges; ++i){
			G->degree[sides[i][0]] += 1;
		}
	}
	qsort(sides, numEdges, sizeof *sides, cmprow);
	int currentVertex = 1;
	int index = 0;
	while(currentVertex <= numVertices && index < numEdges){
		if(G->degree[currentVertex] == 0){
			currentVertex++;
			continue;
		}
		if(sides[index][0] == currentVertex){
			if(directed){
				prependEdge(G, currentVertex, sides[index][1]);
				index++;
				while(index < numEdges && sides[index][0] == currentVertex){
					prependEdge(G, currentVertex, sides[index][1]);
					index++;
				}
			}else{
				prependEdge(G, currentVertex, sides[index][1]);
				prependEdge(G, sides[index][1], currentVertex);
				index++;
				while(index < numEdges && sides[index][0] == currentVertex){
					prependEdge(G, currentVertex, sides[index][1]);
					prependEdge(G, sides[index][1], currentVertex);
					index++;
				}
			}
		}
		currentVertex++;
	}
	return G;
}
/*
allocates memory and sets data for weighted graph
*/
graph* createWeightedGraph(int numVertices, int numEdges, int sides[][3], bool directed){
	if(numVertices == 0){
		return NULL;
	}
	graph *G = (graph*)(calloc(1, sizeof(graph)));
	G->degree = (int*)(calloc(numVertices + 1, sizeof(int)));
	G->edges = (edgenode**)(calloc(numVertices + 1, sizeof(edgenode*)));
	G->directed = directed;
	G->nvertices = numVertices;
	G->nedges = numEdges;
	G->parent = (int*)(calloc(numVertices + 1, sizeof(int)));
	G->bfs = false;
	G->dfs = false;
	G->finished = false;
	G->time = 0;
	if(!directed){
		for(int i = 0; i < numEdges; ++i){
			G->degree[sides[i][0]] += 1;
			G->degree[sides[i][1]] += 1;
		}
	}else{
		for(int i = 0; i < numEdges; ++i){
			G->degree[sides[i][0]] += 1;
		}
	}
	qsort(sides, numEdges, sizeof *sides, cmprow);
	int currentVertex = 1;
	int index = 0;
	while(currentVertex <= numVertices && index < numEdges){
		if(G->degree[currentVertex] == 0){
			currentVertex++;
			continue;
		}
		if(sides[index][0] == currentVertex){
			if(directed){
				prependWeightedEdge(G, currentVertex, sides[index][1], sides[index][2]);
				index++;
				while(index < numEdges && sides[index][0] == currentVertex){
					prependWeightedEdge(G, currentVertex, sides[index][1], sides[index][2]);
					index++;
				}
			}else{
				prependWeightedEdge(G, currentVertex, sides[index][1], sides[index][2]);
				prependWeightedEdge(G, sides[index][1], currentVertex, sides[index][2]);
				index++;
				while(index < numEdges && sides[index][0] == currentVertex){
					prependWeightedEdge(G, currentVertex, sides[index][1], sides[index][2]);
					prependWeightedEdge(G, sides[index][1], currentVertex, sides[index][2]);
					index++;
				}
			}
		}
		currentVertex++;
	}
	return G;
}

//deleting graph
/*
frees the memory allocated for an edge
*/
void freeEdge(edgenode *e){
	if(e == NULL)
		return;
	freeEdge(e->next);
	free(e);
}
/*
frees a graph
*/
void freeGraph(graph *G){
	for(int i = 0; i < G->nvertices + 1; ++i){
		freeEdge(G->edges[i]);
	}
	free(G->degree);
	if(G->parent)
		free(G->parent);
	if(G->discovered)
		free(G->discovered);
	if(G->processed)
		free(G->processed);
	if(G->entry_time)
		free(G->entry_time);
	if(G->exit_time)
		free(G->exit_time);
	free(G);
}

//initializing searches
/*
allocates memory and sets default values in preparation for searching
*/
void init_search(graph *g){
	g->discovered = (bool*)(calloc(g->nvertices + 1, sizeof(bool)));
	g->processed = (bool*)(calloc(g->nvertices + 1, sizeof(bool)));
	for(int i = 1; i <= g->nvertices; ++i){
		g->parent[i] = -1;
	}
}
/*
allocates memory and sets default values in preparation for searching by dfs
*/
void init_search_dfs(graph *g){
	init_search(g);
	g->entry_time = (int*)(calloc(g->nvertices + 1, sizeof(int)));
	g->exit_time = (int*)(calloc(g->nvertices + 1, sizeof(int)));
	g->time = 0;
}

//default methods during search
/*
debug print statement when used as the processing vertex early function
*/
void printPVE(int v, graph *g){
	printf("processing vertex early: %d\n", v);
	return;
}
/*
debug print statement when used as the processing edge function
*/
void printPE(int v, int y, graph *g){
	printf("processing edge: %d, %d\n", v, y);
	return;
}
/*
debug print statement when used as the processing vertex late function
*/
void printPVL(int v, graph *g){
	printf("processing vertex late: %d\n", v);
	return;
}
/*
blank processing vertex early function
*/
void pve(int v, graph *g){return;}
/*
blank processing edge function
*/
void pe(int v, int y, graph *g){return;}
/*
blank processing vertex late function
*/
void pvl(int v, graph *g){return;}

//search helper method
enum EDGEedge_classIFICATION{TREE, BACK, FORWARD, CROSS};
/*
the recursive function for dfs
*/
void dfsHelper(graph *g, int v, void(*process_vertex_early)(int, graph*), void(*process_edge)(int, int, graph*), void(*process_vertex_late)(int, graph*)){
	edgenode *p;
	int y;
	if(g->finished){
		return;
	}

	g->discovered[v] = true;
	g->time = g->time + 1;
	g->entry_time[v] = g->time;

	(*process_vertex_early)(v, g);
	p = g->edges[v];
	while(p != NULL){
		y = p->y;
		if(g->discovered[y] == false){
			g->parent[y] = v;
			(*process_edge)(v, y, g);
			dfsHelper(g, y, process_vertex_early, process_edge, process_vertex_late);
		}else if((!g->processed[y]) || g->directed){
			(*process_edge)(v, y, g);
		}
		if(g->finished){
			return;
		}
		p = p->next;
	}
	(*process_vertex_late)(v, g);
	g->time = g->time + 1;
	g->exit_time[v] = g->time;

	g->processed[v] = true;
}
/*
classifying what kind of edge each edge is during a dfs traversal
*/
int edge_classification(int x, int y, graph *g){
	if(g->parent[y] == x) return TREE;
	if(g->discovered[y] && !g->processed[y]) return BACK;
	if(g->processed[y] && (g->entry_time[y] > g->entry_time[x])) return FORWARD;
	if(g->processed[y] && (g->entry_time[y] < g->entry_time[x])) return CROSS;
	return -1;
}

//searches
/*
does a bfs traversal and calls the 3 passed functions during the time where the names specify; if null, defaults to methods that don't do anything
*/
void bfs(graph *g, int start, void(*process_vertex_early)(int, graph*), void(*process_edge)(int, int, graph*), void(*process_vertex_late)(int, graph*)){
	g->bfs = true;
	g->dfs = false;
	if(process_vertex_early == NULL){
		process_vertex_early = &pve;
	}
	if(process_edge == NULL){
		process_edge = &pe;
	}
	if(process_vertex_late == NULL){
		process_vertex_late = &pvl;
	}
	g->q = createQueue();
	int v, y;
	edgenode *p;
	init_search(g);
	enqueue(g->q, start);
	g->discovered[start] = true;
	while(isEmpty(g->q) == false){
		v = dequeue(g->q);
		(*process_vertex_early)(v, g);
		g->processed[v] = true;
		p = g->edges[v];
		while(p != NULL){
			y = p->y;
			if((g->processed[y] == false) || g->directed){
				(*process_edge)(v, y, g);
			}
			if(g->discovered[y] == false){
				enqueue(g->q, y);
				g->discovered[y] = true;
				g->parent[y] = v;
			}
			p = p->next;
		}
		(*process_vertex_late)(v, g);
	}

	free(g->discovered);
	free(g->processed);
	freeQueue(g->q);
}
/*
does a dfs traversal and calls the 3 passed functions during the time where the names specify; if null, defaults to methods that don't do anything
*/
void dfs(graph *g, int v, void(*process_vertex_early)(int, graph*), void(*process_edge)(int, int, graph*), void(*process_vertex_late)(int, graph*)){
	g->dfs = true;
	g->bfs = false;
	init_search_dfs(g);
	if(process_vertex_early == NULL){
		process_vertex_early = &pve;
	}
	if(process_edge == NULL){
		process_edge = &pe;
	}
	if(process_vertex_late == NULL){
		process_vertex_late = &pvl;
	}
	dfsHelper(g, v, process_vertex_early, process_edge, process_vertex_late);
	if(g->finished){
		g->finished = false;
	}
	free(g->discovered);
	free(g->processed);
}

//graph methods
//find_path 
//
//
//needs bfs/dfs first
void find_path(int start, int end, int parents[], graph *g){
	if(!g->bfs && !g->dfs){
		return;
	}
	if((start == end) || (end == -1)){
		printf("\n%d", start);
	}else{
		find_path(start, parents[end], parents, g);
		printf(" %d", end);
	}
}
//bipartite
//
//
//uses a global randomly named array
int *HGMxSsfaWurBQTspMLYLmVriBzDQ;
bool eRCBtOhuQvkeUYpsLHDoptqJWwjr;
void init_bipartite(graph *g){
	HGMxSsfaWurBQTspMLYLmVriBzDQ = (int*)(calloc(g->nvertices + 1, sizeof(int)));
	eRCBtOhuQvkeUYpsLHDoptqJWwjr = true;
}
void process_edge_bipartite(int v, int y, graph* g){
	if(HGMxSsfaWurBQTspMLYLmVriBzDQ[v] == HGMxSsfaWurBQTspMLYLmVriBzDQ[y]){
		eRCBtOhuQvkeUYpsLHDoptqJWwjr = false;
	}
	HGMxSsfaWurBQTspMLYLmVriBzDQ[y] = 1;
}
bool isBipartite(graph *g, int start){
	init_bipartite(g);
	HGMxSsfaWurBQTspMLYLmVriBzDQ[start] = 1;
	bfs(g, start, NULL, process_edge_bipartite, NULL);
	free(HGMxSsfaWurBQTspMLYLmVriBzDQ);
	return eRCBtOhuQvkeUYpsLHDoptqJWwjr;
}
//finding cycles
//
//
//prints out to console the cycle
void process_edge_cycle(int v, int y, graph* g){
	if(g->parent[y] != v){
		printf("Cycle from %d to %d:", y, v);
		find_path(y, v, g->parent, g);
		g->finished = true;
	}
}
void findCycle(graph*g, int start){
	dfs(g, start, NULL, process_edge_cycle, NULL);
}
//find articulation points
//
//
//
void findAP_pve(int v, graph *g){
	g->reachable_ancestor[v] = v;
}
void findAP_pe(int v, int y, graph *g){
	int edge_class = edge_classification(v, y, g);
	if(edge_class == TREE)
		g->tree_out_degree[v] += 1;
	if((edge_class == BACK) && (g->parent[v] != y)){
		if(g->entry_time[y] < g->entry_time[g->reachable_ancestor[v]])
			g->reachable_ancestor[v] = y;
	}
}
void findAP_pvl(int v, graph *g){
	bool root;
	int time_v, time_parent;
	if(g->parent[v] < 1){
		if(g->tree_out_degree[v] > 1){ 
			printf("root\n");
			return;
		}else{
			return;
		}
	}
	root = g->parent[g->parent[v]] < 1;
	if((g->reachable_ancestor[v] == g->parent[v]) && (!root))
		printf("parent articulation vertex at %d\n", g->parent[v]);
	if(g->reachable_ancestor[v] == v){
		printf("bridge articulation for parent %d\n", g->parent[v]);
		if(g->tree_out_degree[v] > 0)
			printf("bridge articulation for child %d\n", v);
	}
	time_v = g->entry_time[g->reachable_ancestor[v]];
	time_parent = g->entry_time[g->reachable_ancestor[g->parent[v]]];
	if(time_v < time_parent){
		g->reachable_ancestor[g->parent[v]] = g->reachable_ancestor[v];
	}
}
void findArtifulcationPoints(graph *g, int start){
	g->reachable_ancestor = (int*)(calloc(g->nvertices + 1, sizeof(int)));
	g->tree_out_degree = (int*)(calloc(g->nvertices + 1, sizeof(int)));
	dfs(g, start, findAP_pve, findAP_pe, findAP_pvl);
	free(g->reachable_ancestor);
	free(g->tree_out_degree);
}
//topological sorting
//
//
//
void topsort_pvl(int v, graph *g){
	pushStack(g->s, v);
}
void topsort_pe(int v, int y, graph *g){
	int edge_class = edge_classification(v, y, g);
	if(edge_class == BACK){
		printf("Warning: directed cycle found, not a DAG\n");
	}
}
void topsort(graph *g){
	int i;
	g->s = createStack();
	init_search_dfs(g);
	for(i = 1; i <= g->nvertices; ++i){
		if(g->discovered[i] == false){
			dfsHelper(g, i, pve, topsort_pe, topsort_pvl);
		}
	}
	printStack(g->s);
}

void printGraph(graph *g){
	printf("numvert: %d\n", g->nvertices);
	printf("numEdges: %d\n", g->nedges);
	for(int i = 1; i <= g->nvertices; ++i){
		edgenode *temp = g->edges[i];
		printf("%d: ", i);
		while(temp){
			printf("%d(%d) ", temp->y, temp->weight);
			temp = temp->next;
		}
		printf("\n");
	}
	for(int i = g->nvertices; i != 0; --i){
		find_path(1, i, g->parent, g);
	}
	printf("\n");
}
/*


WEIGHTED GRAPH ALG


*/
//create min spanning tree
void prim(graph *g, int start){
	g->bfs = true;
	int i, v, w, weight, dist;
	edgenode *p;
	bool *intree = (bool*)(calloc(g->nvertices + 1, sizeof(bool)));
	int *distance = (int *)(calloc(g->nvertices + 1, sizeof(int)));
	for(i = 1; i <= g->nvertices; ++i){
		distance[i] = INT_MAX;
		g->parent[i] = -1;
	}
	distance[start] = 0;
	v = start;
	while(intree[v] == false){
		intree[v] = true;
		p = g->edges[v];
		while(p != NULL){
			w = p->y;
			weight = p->weight;
			if((distance[w] > weight) && (intree[w] == false)){
				distance[w] = weight;
				g->parent[w] = v;
			}
			p = p->next;
		}
		v = 1;
		dist = INT_MAX;
		for(i = 1; i <= g->nvertices; ++i){
			if((intree[i] == false) && (dist > distance[i])){
				dist = distance[i];
				v = i;
			}
		}
	}
	free(intree);
	free(distance);
}
void kruskal(graph *g){

}
#endif

int main(void){
	int edges[][3] = {
		{1, 2, 6},
		{2, 3, 2},
		{1, 3, 18},
		{2, 4, 2},
		{4, 7, 4},
		{4, 8, 10},
		{8, 11, 2},
		{3, 5, 34},
		{3, 6, 7},
		{6, 9, 4},
		{6, 10, 5}
	};
	graph *G = createWeightedGraph(11, 11, edges, false);
	prim(G, 1);
	printGraph(G);
	free(G);
}

#ifdef __cplusplus
}
#endif

#endif