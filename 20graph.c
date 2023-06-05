#include <stdio.h>
#include <stdlib.h>
struct QNode {
    int key;
    struct QNode* link;
};
struct Queue {
    struct QNode *front, *rear;
};
 
struct QNode *newNode(int k){
    struct QNode *temp = malloc(sizeof(struct QNode));
    temp->key = k; temp->link = NULL;
    return temp;
}
struct Queue *createQueue(){
    struct Queue *q = malloc(sizeof(struct Queue));
    q->front = q->rear = NULL;
    return q;
}

int isEmpty(struct Queue* q){
    if (q->front == NULL) return 1;
    return 0;
}
void enQueue(struct Queue* q, int k){
    struct QNode* temp = newNode(k);
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->link = temp;
    q->rear = temp;
}
int deQueue(struct Queue* q){
    if (isEmpty(q)) return -1;
    struct QNode* temp = q->front;
    int val = temp->key;
    q->front = q->front->link;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return val;
}

typedef struct AdjNode {
	int dest;
	struct AdjNode *next;
}Node;
typedef struct Graph {
	int V, *visited;
    Node **array;
}G;

Node *createNode(int dest) {
    Node* newNode = malloc(sizeof(Node));
	newNode->dest = dest;
	newNode->next = NULL;
	return newNode;
}
G *createGraph(int V) {
	G *graph = malloc(sizeof(G));
	graph->V = V;
    graph->array = malloc(V * sizeof(Node *));
    graph->visited = calloc(V, sizeof(int));
    for (int i = 0; i < V; i++)
		graph->array[i] = NULL;
	return graph;
}

void addEdge(G *graph, int src, int dest) {
    Node *check = NULL;
    Node *newNode = createNode(dest);

	if (graph->array[src] == NULL) {
		newNode->next = graph->array[src];
		graph->array[src] = newNode;
	}
	else {
        check = graph->array[src];
		while (check->next)
			check = check->next;
		//graph->array[src] = newNode;
		check->next = newNode;
	}

	newNode = createNode(src);
	if (graph->array[dest] == NULL) {
		newNode->next = graph->array[dest];
		graph->array[dest] = newNode;
	}
	else {
		check = graph->array[dest];
		while (check->next)
			check = check->next;
		check->next = newNode;
	}

	// newNode = createNode(src);
	// newNode->next = graph->array[dest];
	// graph->array[dest] = newNode;
}

void print(G *graph) {
    for (int v = 0; v < graph->V; v++) {
		Node *pCrawl = graph->array[v];
		printf("\nAdjacency list of vertex %d\n head ", v);
		while (pCrawl) {
			printf("-> %d", pCrawl->dest);
			pCrawl = pCrawl->next;
		}
		printf("\n");
	}
}


void BFS(G *graph, int s) {
    printf("BFS starting from %d : ", s);
    struct Queue* q = createQueue();
    graph->visited[s] = 1;
    enQueue(q, s);
 
    while(!isEmpty(q)) {
        s = deQueue(q);
        printf("%d ",s);
		Node *pCrawl = graph->array[s];
        while (pCrawl) {
            int i = pCrawl->dest;
            if (!graph->visited[i]) {
                graph->visited[i] = 1;
                enQueue(q, i);
            }
            pCrawl = pCrawl->next;
        }
    }
}

void DFS(G *graph, int s) {
    Node* adjList = graph->array[s];
    Node* temp = adjList;

    graph->visited[s] = 1;
    printf(" %d ", s);

    while (temp != NULL) {
        int next = temp->dest;
        if (graph->visited[next] == 0)
            DFS(graph, next);
        temp = temp->next;
    }
}

int main() {
    int V, src, dest, v;
    printf("Enter No. of vertices : ");
    scanf("%d",&V);
	G* graph = createGraph(V);
    printf("Enter -1 as src to stop\n");
    for (int i = 0; ; i++) {
        printf("Enter src & dest : ");
        scanf("%d",&src);
        if (src == -1) break;
        scanf("%d",&dest);
        addEdge(graph, src, dest);
    }
    print(graph);

    printf("\nEnter Vertex to start BFS : ");
    scanf("%d",&v); BFS(graph, v);

    printf("\n\nEnter Vertex to start DFS : ");
    scanf("%d",&v);
    printf("DFS starting from %d : ", v);
    DFS(graph, v);

	return 0;
}