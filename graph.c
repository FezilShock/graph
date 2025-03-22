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

edge *create_edge(char val1, char val2)
{
    edge *new_edge = (edge *)malloc(sizeof(edge));
    new_edge->first_top = val1;
    new_edge->second_top = val2;
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
    if(new_var != '\n' && new_var != ' ' && new_var != EOF){
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



void edgesetPush(edgeset *set, char new_var1, char new_var2)
{
    if((new_var1 != '\n' && new_var1 != ' ' && new_var1 != EOF) && (new_var2 != '\n' && new_var2 != ' ' && new_var2 != EOF)){
        if (set->first_edge == NULL)
        {
            edge *tmp = create_edge(new_var1, new_var2);
            set->first_edge = tmp;
            set->now = tmp;
            ++set->size;
        }else{
            edge *tmp = create_edge(new_var1, new_var2);
            set->now->next = tmp;
            set->now = tmp;
            ++set->size;
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
            fputc(' ', fp);
            fputc(curNode->val, fp);
            fputs("; ", fp);
            curNode = curNode->next;
        }
    }
    else
    {
        printf("Пустое множество");
    }
    putchar('\n');
}

void edgesetOutput(edgeset *set, FILE* fp)
{
    if (set->size)
    {
        edge *curNode = set->first_edge;
        while (curNode != NULL)
        {
            fputc(curNode->first_top, fp);
            fputs("--", fp);
            fputc(curNode->second_top, fp);
            fputs("; ", fp);
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

void freeedgeset(edgeset *set)
{
    if (set->size)
    {
        edge *curNode = set->first_edge;
        while (curNode != NULL)
        {
            edge *delNode = curNode;
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
    edgeset *edges = createEdgeSet();
    FILE* fp = fopen("list_of_edges199.txt", "r");
    if(fp == NULL)
        return 1;
    do{
        char ch1 = fgetc(fp);
        fgetc(fp);
        char ch2 = fgetc(fp);
        setPush(tops, ch1);
        setPush(tops, ch2);
        edgesetPush(edges, ch1, ch2);
    }
    while((byte = fgetc(fp)) != EOF);
        
    fclose(fp);
    FILE* fp2 = fopen("list_of_tops0.txt", "w");
    if(fp2 == NULL)
        return 1;
    setOutput(tops, fp2);
    fclose(fp2);
    FILE* fp3 = fopen("list_of_edges01.txt", "w");
    if(fp3 == NULL)
        return 1;
    edgesetOutput(edges, fp3);


    FILE* fp4 = fopen("graph199.dot", "w");
    if(fp4 == NULL)
        return 1;
    fputs("graph graphname {", fp4);
    fclose(fp4);

    FILE* fp5 = fopen("graph199.dot", "a");
    if(fp5 == NULL)
        return 1;
    setOutput(tops, fp5);
    edgesetOutput(edges, fp5);
    fputc('}', fp5);
    fclose(fp5);


    freeset(tops);
    freeedgeset(edges);

    system("dot -Tpng graph199.dot -ograph199.png");
    system("open graph199.png");
    //system("find . -name \"*.dot\"");
    return 0;
}