#include<stdio.h>
# include<stdlib.h>

# define EleType char
# define MAXSIZE 20

typedef struct EdgeNode
{
    int head, tail;  // 弧头和弧尾在顶点列表中的位置
    struct EdgeNode *next_in, *next_out;
}EdgeNode;

typedef struct VexNode
{
    EleType data;
    EdgeNode *next_in, *next_out;
}VexNode, *VexList;

typedef struct Graph
{
    VexList vex_list;  // 顶点列表
    int vex_num, edge_num;  // 顶点数和边数
}*Graph;

void graph_init(Graph graph){
    graph->vex_list = (VexList)malloc(sizeof(VexNode) * MAXSIZE);
    for (int i = 0; i < MAXSIZE; i++)
    {
        graph->vex_list[i].next_in = NULL;
        graph->vex_list[i].next_out = NULL;
    }
    printf("图的初始化完毕!\n");
    return;
}

void create_graph(Graph graph, int vex_num, int edge_num){
    graph->vex_num = vex_num;
    graph->edge_num = edge_num;
    for (int i = 0; i < vex_num; i++)
    {
        printf("输入顶点%d的数据: ", i);
        scanf("%c", &(graph->vex_list[i].data));
        getchar();
    }
    for (int idx = 0; idx < edge_num; idx++)
    {
        int i, j;
        EdgeNode *edge_node = (EdgeNode*)malloc(sizeof(EdgeNode));
        edge_node->next_out = NULL;
        edge_node->next_in = NULL;
        
        printf("输入弧%d <Vi, Vj>的弧尾和弧头: ", idx);
        scanf("%d %d", &i, &j);
        getchar();
        edge_node->tail = i;
        edge_node->head = j;
        
        edge_node->next_out = graph->vex_list[i].next_out;
        graph->vex_list[i].next_out = edge_node;

        edge_node->next_in = graph->vex_list[j].next_in;
        graph->vex_list[j].next_in = edge_node;
    }
    return;
}

void describe_graph(Graph graph){
    for (int i = 0; i < graph->vex_num; i++)
    {
        printf("顶点%d的数据是: %c\t", i, graph->vex_list[i].data);
        printf("以顶点%d为弧尾的弧有:\t", i);
        EdgeNode *p = graph->vex_list[i].next_out;
        while (p != NULL)
        {
            printf("<V%d, V%d>\t", p->tail, p->head);
            p = p->next_out;
        }
        printf("以顶点%d为弧头的弧有:\t", i);
        p = graph->vex_list[i].next_in;
        while (p != NULL)
        {
            printf("<V%d, V%d>\t", p->tail, p->head);
            p = p->next_in;
        }
        printf("\n");
    }
}

void main(){
    Graph graph = (Graph)malloc(sizeof(Graph));
    graph_init(graph);
    create_graph(graph, 4, 5);
    describe_graph(graph);
}