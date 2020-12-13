# jlib

This is a library that contains algorithms written by me and algorithms I've compiled from other sources which are listed in the document and in this readme.

## Prerequisites
This library is just a c header file that you can #include in your c/c++ programs. To reduce the overhead to just want you need, the header is separated by preprocessor #ifdef and #endif. More detailed descriptions of functions are in the .c file so I'm just going to put function prototype here.
Define the following things to include certain algs
```
#define JLIB_PRINT
```
- void print(int num_args, char separator, char enlin, ...)
- void println(int num_args, ...)

```
#define JLIB_TIMER
```
- void timerStart()
- void timerEnd()
- void timerPrint()

```
#define JLIB_STRING
```
- char* lower(char *s)
- char* upper(char *s)
- char* replace(char *str, char toReplace, char replacer)
(author of following three trim functions is Martin Broadhurst, martinbroadhurst.com)
- char* ltrim(char *str, const char *seps)
- char* rtrim(char *str, const char *seps)
- char* trim(char *str, const char *seps)

```
#define JLIB_QUEUE
```
- struct item
- struct queue
- queue* createQueue()
- void enqueue(queue *Q, int i)
- int dequeue(queue *Q)
- bool isEmpty(queue *Q)
- void freeQueue(queue *Q)

```
#define JLIB_STACK
```
- struct stack
- stack* createStack()
- void pushStack(stack *s, int v)
- int popStack(stack *s)
- void printStack(stack *s)
- void freeStack(stack *s)

```
#define JLIB_SETUNION
```
(this "class" comes from The Algorithm Design Manual by Skiena)
- struct setUnion
- void createSetUnion(setUnion *s, int size)
- int find(setUnion *s, int x)
- void unionsets(setUnion *s, int s1, int s2)
- bool same_component(setUnion *s, int s1, int s2)

```
#define JLIB_GRAPH
```
* (this also defines JLIB_STACK, JLIB_QUEUE, and JLIB_SETUNION by itself as it needs all of these)
* (most of these are from The Algorithm Design Manual by Skiena with slight changes)
* (functions that should be called are listed first)
* (disabled processing functions are in the middle)
* (helper functions are listed at the bottom)
- struct edgenode
- struct graph
- graph* createGraph(int numVertices, int numEdges, int sides[][2], bool directed)
- graph* createWeightedGraph(int numVertices, int numEdges, int sides[][3], bool directed)
- void freeGraph(graph *G)
- bfs(graph *g, int start, void(*process_vertex_early)(int, graph*), void(*process_edge)(int, int, graph*), void(*process_vertex_late)(int, graph*))
- def(graph *g, int start, void(*process_vertex_early)(int, graph*), void(*process_edge)(int, int, graph*), void(*process_vertex_late)(int, graph*))
- void find_path(int start, int end, int parents[], graph *g)
- bool isBipartite(graph *g, int start)
- void findCycle(graph *g, int start)
- void findArticulationPoints(graph *g, int start)
- void topsort(graph *g)
- void printGraph(graph *g)
- void prim(graph *g, int start)
```
```
- void printPVE(int v, graph *g)
- void printPE(int v, int y, graph *g)
- void printPVL(int v, graph *g)
- void pve(int v, graph *g)
- void pe(int v, int y, graph *g)
- void pvl(int v, graph *g)
```
```
(following compare function for qsort provided by user unwind on stackoverflow: https://stackoverflow.com/users/28169/unwind)
- static int cmprow(const void *a, const void *b)
- void prependEdge(graph *G, int x, int y)
- void prependWeightedEdge(graph *G, int currentVertex, int y, int weight)
- void freeEdge(edgenode *e)
- void init_search(graph *g)
- void init_search_dfs(graph *g)
- void dfsHelper(graph *g, int v, void(*process_vertex_early)(int, graph*), void(*process_edge)(int, int, graph*), void(*process_vertex_late)(int, graph*))
- int edge_classification(int x, int y, graph *g)
- void init_bipartite(graph *g)
- void process_edge_bipartite(int v, int y, graph *g)
- void process_edge_cycle(int v, int y, graph *g)
- void findAP_pve(int v, graph *g)
- void findAP_pe(int v, int y, graph *g)
- void findAP_pvl(int v, graph *g)
- void topsort_pvl(int v, graph *g)
- void topsort_pe(int v, int y, graph *g)



Will add more soon
