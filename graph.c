#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct n
{
    char val;     // переменная для хранения содержимого ноды
    struct n *next; // указатель на следующую ноду
} node;


typedef struct n2
{
    char first_top; // указатель на первую ноду множества
    char second_top;
    struct n2 *next; // указатель на следующую ноду
} edge;

// объявляем структуру для множества
typedef struct
{
    node *first_node; // указатель на первую ноду множества
    node *now;        // указатель на
    int size;         // переменная для хранения количества элементов
} set;

typedef struct
{
    edge *first_edge; // указатель на первую ноду множества
    edge *now;        // указатель на
    int size;         // переменная для хранения количества элементов
} edgeset;

typedef struct
{
    edgeset *edges; // указатель на первую ноду множества
    set *tops;
    int size;         // переменная для хранения количества элементов
} graph;

/**
 * Функция выделяет память под новую ноду и возвращает указатель на неё.
 * Параметр `val` используется для записи значения в ноду
 */
node *create_node(char val)
{
    node *new_node = (node *)malloc(sizeof(node));
    new_node->val = val;
    new_node->next = NULL;
    return new_node;
}

edge *create_edge(char val)
{
    edge *new_edge = (edge *)malloc(sizeof(edge));
    new_edge->first_top = 0;
    new_edge->second_top = 0;
    return new_edge;
}

// Функция выделяет память под множество и возвращает указатель на множество
edgeset *createEdgeSet(void)
{
    edgeset *new_set = (edgeset *)malloc(sizeof(edgeset));
    new_set->first_edge = NULL;
    new_set->size = 0;
    return new_set;
}

// Функция выделяет память под множество и возвращает указатель на множество
set *createSet(void)
{
    set *new_set = (set *)malloc(sizeof(set));
    new_set->first_node = NULL;
    new_set->size = 0;
    return new_set;
}

graph *createGraph(void)
{
    graph *new_graph = (graph *)malloc(sizeof(graph));
    new_graph->edges = NULL;
    new_graph->tops = NULL;
    new_graph->size = 0;
    return new_graph;
}

/*
 * Функция для проверки существования элемента
 * Возвращает NULL, если элемент не найден
 */
bool setSearch(set *set, double var)
{
    if (set->size)
    {
        node *curNode = set->first_node;
        while (curNode != NULL)
        {
            if (curNode->val == var)
                return curNode;
            curNode = curNode->next;
        }
        return NULL;
    }
    else
        return NULL;
}

/*
 * Функция добавления элементов в множество
 * Возвращает 0 если был записан хотя бы один элемент
 * Иначе возвращает -1
 * Параметр `set` - указатель на множество
 */
void setPush(set *set, char new_var)
{
    if(new_var != '\n' && new_var != ' '){
        if (set->first_node == NULL)
        {
            node *tmp = create_node(new_var);
            set->first_node = tmp;
            set->now = tmp;
            ++set->size;
        }
        else
        {
            if (!setSearch(set, new_var))
            {
                node *tmp = create_node(new_var);
                set->now->next = tmp;
                set->now = tmp;
                ++set->size;
            }
        }
    }
}

void setOutput(set *set, FILE* fp)
{
    if (set->size)
    {
        node *curNode = set->first_node;
        while (curNode != NULL)
        {
            fputc(curNode->val, fp);
            curNode = curNode->next;
        }
    }
    else
    {
        printf("Пустое множество");
    }
    putchar('\n');
}

void freeset(set *set)
{
    if (set->size)
    {
        node *curNode = set->first_node;
        while (curNode != NULL)
        {
            node *delNode = curNode;
            curNode = curNode->next;
            free(delNode);
        }
        free(curNode);
    }
    free(set);
}

int main(void){
    char byte;
    set* tops = createSet();
    //set *edgeset = createEdgeSet();

    FILE* fp = fopen("list_of_edges0.txt", "r");
    if(fp == NULL)
        return 1;
    while((byte = fgetc(fp)) != '\n'){
        setPush(tops, byte);
    }
    fclose(fp);
    FILE* fp2 = fopen("list_of_tops0.txt", "w");
    if(fp2 == NULL)
        return 1;
    setOutput(tops, fp2);
    fclose(fp2);
    freeset(tops);
    //system("dot -Tpng graph.dot -ograph.png");
    //system("open graph.png");
    //system("find . -name \"*.dot\"");
    return 0;
}