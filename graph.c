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

int readfile(FILE* fp, set* tops, edgeset* edges){
    char byte;
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
    return 0;
}

int writefile1(FILE* fp, set* tops, edgeset* edges){
    if(fp == NULL)
        return 1;
    fputs("graph graphname {", fp);
    fclose(fp);
    return 0;
}

int writefile2(FILE* fp, set* tops, edgeset* edges){
    if(fp == NULL)
        return 1;
    setOutput(tops, fp);
    edgesetOutput(edges, fp);
    fputc('}', fp);
    fclose(fp);
    return 0;
}

int createGraph(void){
    set* tops = createSet();
    edgeset *edges = createEdgeSet();
    FILE* fp = fopen("input/list_of_edges1.txt", "r");
    readfile(fp, tops, edges);

    FILE* fp2 = fopen("output/graph1.dot", "w");
    writefile1(fp2, tops, edges);

    FILE* fp3 = fopen("output/graph1.dot", "a");
    writefile2(fp3, tops, edges);

    freeset(tops);
    freeedgeset(edges);
    
    return 0;
}

void outputGraph(){
    system("dot -Tpng output/graph1.dot -opngs/graph1.png");
    system("open pngs/graph1.png");
}

void help(void){
    printf("Commands for work with programm:\n1 - Create graph from file.\n2 - Output graph.\n0 - exit from program.\n");

}

int main(void){
    int menu = 0;
    int input;

    help();
    do
    {
        menu = -1;
        puts("Введите команду: ");
        input = scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            createGraph();
            break;
        case 2:
            outputGraph();
            break;
        case 0:
            
            return 0;
        case -1:
            puts("Ошибка ввода!!");
            return 0;
        default:
            menu = 0;
            help();
        }
    }while(input);
    return 0;
    //system("find . -name \"*.dot\"");
}