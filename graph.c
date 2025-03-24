#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char *dynstring(char c)
{
    int l = 0;
    int size = 10;
    char *string = (char *)malloc(size * sizeof(char));
    char ch = getchar();
    ch = getchar();
    while (ch != c)
    {
        string[(l)++] = ch;
        if (l >= size)
        {
            size *= 2;
            string = (char *)realloc(string, size * sizeof(char));
        }
        ch = getchar();
    }
    string[l] = '\0';
    return string;
}

typedef struct n
{
    char val;
    struct n *next;
} node;

typedef struct n2
{
    char first_top; 
    char second_top;
    struct n2 *next; 
} edge;

typedef struct
{
    node *first_node;
    node *now;        
    int size;        
} set;

typedef struct
{
    edge *first_edge;
    edge *now;       
    int size;        
} edgeset;

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

edgeset *createEdgeSet(void)
{
    edgeset *new_set = (edgeset *)malloc(sizeof(edgeset));
    new_set->first_edge = NULL;
    new_set->size = 0;
    return new_set;
}

set *createSet(void)
{
    set *new_set = (set *)malloc(sizeof(set));
    new_set->first_node = NULL;
    new_set->size = 0;
    return new_set;
}

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

void setPush(set *set, char new_var)
{
    if (new_var != '\n' && new_var != ' ' && new_var != EOF)
    {
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
    if ((new_var1 != '\n' && new_var1 != ' ' && new_var1 != EOF) && (new_var2 != '\n' && new_var2 != ' ' && new_var2 != EOF))
    {
        if (set->first_edge == NULL)
        {
            edge *tmp = create_edge(new_var1, new_var2);
            set->first_edge = tmp;
            set->now = tmp;
            ++set->size;
        }
        else
        {
            edge *tmp = create_edge(new_var1, new_var2);
            set->now->next = tmp;
            set->now = tmp;
            ++set->size;
        }
    }
}

void setOutput(set *set, FILE *fp)
{
    if (set->size)
    {
        node *curNode = set->first_node;
        while (curNode != NULL)
        {
            fputc(curNode->val, fp);
            fputs(";", fp);
            curNode = curNode->next;
        }
    }
}

void edgesetOutput(edgeset *set, FILE *fp)
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

int readfile(FILE *fp, set *tops, edgeset *edges)
{
    char byte;
    if (fp == NULL)
    {
        return 1;
    }

    do
    {
        char ch1 = fgetc(fp);
        fgetc(fp);
        char ch2 = fgetc(fp);
        setPush(tops, ch1);
        setPush(tops, ch2);
        edgesetPush(edges, ch1, ch2);
    } while ((byte = fgetc(fp)) != EOF);
    fclose(fp);
    return 0;
}

int writefile1(FILE *fp, set *tops, edgeset *edges)
{
    if (fp == NULL)
        return 1;
    fputs("graph graphname {", fp);
    fclose(fp);
    return 0;
}

int writefile2(FILE *fp, set *tops, edgeset *edges)
{
    if (fp == NULL)
        return 1;
    setOutput(tops, fp);
    edgesetOutput(edges, fp);
    fputc('}', fp);
    fclose(fp);
    return 0;
}

int createGraph(void)
{
    set *tops = createSet();
    edgeset *edges = createEdgeSet();
    char *filename = dynstring('\n');

    char *filepath = (char *)malloc(sizeof(filename) * strlen(filename) * 2);
    strcat(filepath, "input/");
    strcat(filepath, filename);
    strcat(filepath, ".txt");

    char *outfilepath = (char *)malloc(sizeof(filename) * strlen(filename) * 2);
    strcat(outfilepath, "output/");
    strcat(outfilepath, filename);
    strcat(outfilepath, ".dot");

    FILE *fp = fopen(filepath, "r");
    if(readfile(fp, tops, edges) == 0){

        FILE *fp2 = fopen(outfilepath, "w");
        writefile1(fp2, tops, edges);

        FILE *fp3 = fopen(outfilepath, "a");
        writefile2(fp3, tops, edges);
    }else{
        perror(filepath);
        return 1;
    }
    freeset(tops);
    freeedgeset(edges);
    free(filepath);
    free(outfilepath);

    return 0;
}

void outputGraph(void)
{
    char *filename = dynstring('\n');
    char *filepath = (char *)malloc(sizeof(filename) * strlen(filename) * 2);
    strcat(filepath, "dot -Tpng output/");
    strcat(filepath, filename);
    strcat(filepath, ".dot -opngs/");
    strcat(filepath, filename);
    strcat(filepath, ".png");

    char *filepath2 = (char *)malloc(sizeof(filename) * strlen(filename) * 2);
    strcat(filepath2, "open pngs/");
    strcat(filepath2, filename);
    strcat(filepath2, ".png");

    system(filepath);
    system(filepath2);
    free(filepath);
    free(filepath2);
}

void help(void)
{
    printf("Commands for work with program:\n1 - Create graph from file.\n2 - Output graph.\n0 - Exit from program.\n");
}

int main(void)
{
    int menu = 0;
    int input;
    char *filename;

    help();
    do
    {
        menu = -1;
        puts("Input commands: ");
        input = scanf("%d", &menu);
        switch (menu)
        {
        case 1:
            system("cd input && ls");
            puts("Input filename without extention");
            createGraph();
            break;
        case 2:
            system("cd output && ls");
            puts("Input filename without extention");
            outputGraph();
            break;
        case 0:

            return 0;
        case -1:
            puts("Input error!!");
            return 0;
        default:
            menu = 0;
            help();
        }
    } while (input);
    return 0;
}