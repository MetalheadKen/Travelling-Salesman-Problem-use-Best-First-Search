#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Priority_Queue_Min.h"

#define CITY   8
#define LENGTH CITY * 10
#define INF    999

#define TURN_STRING(X, Y) sprintf(X, ",%d", Y)

int Travelling_Salesman(char *);
int Bound(Node);
int Length(Node);

int String_to_Integer(int *, char *);

_Node_Algo *node_algo      = &Node_Algo;
_Priority_Queue_Algo *algo = &Priority_Queue_Algo;

int adjacency_matrix[CITY][CITY]
                       = {{  0,   5,   8, INF, INF, INF, INF, INF},
                          {INF,   0,   4, INF,   4, INF, INF, INF},
                          {INF, INF,   0,   2, INF, INF,   5, INF},
                          {INF, INF, INF,   0, INF, INF, INF,   7},
                          {  1, INF, INF, INF,   0, INF, INF, INF},
                          {INF,   6, INF, INF,   2,   0, INF, INF},
                          {INF, INF, INF,   3, INF,   8,   0, INF},
                          {INF, INF, INF, INF, INF,   5,   4,   0}};

int main(void)
{
    int  min_length;
    char opt_tour[LENGTH] = {0};

    min_length = Travelling_Salesman(opt_tour);

    printf("The shortest path is [");
    for (int i = 0; opt_tour[i]; i++) {
        if (opt_tour[i] == ',')
            printf(", ");
        else
            printf("%c", opt_tour[i] + 1);
    }
    printf("].\nThe minimum length of tour is %d.\n", min_length);
    
    return 0;
}

int Travelling_Salesman(char *opt_tour)
{
    char temp[LENGTH];

    Queue queue;
    Node  u, v;

    algo->Create(&queue, LENGTH);
    node_algo->Create(&u, LENGTH);
    node_algo->Create(&v, LENGTH);
    
    /* Set the first vertex as the starting point */
    v.level     = 0;
    v.path[0]   = '0';
    v.bound     = Bound(v);
    v.is_use[0] = true;

    int min_length = INT_MAX;
    algo->Insert(&queue, v);

    while (!algo->Is_Empty(queue)) {
        algo->Remove(&queue, &v);

        /* Check is promising or not */
        if (v.bound < min_length) {
            u.level = v.level + 1;

            for (int i = 1; i < CITY; i++) {
                if (v.is_use[i]) continue;

                strcpy(u.path, v.path);
                TURN_STRING(temp, i);
                strcat(u.path, temp);
                memcpy(u.is_use, v.is_use, sizeof(u.is_use[0]) * LENGTH);
                u.is_use[i] = true;

                /* Check if just one more node to complete a tour */
                if (u.level == CITY - 2) {
                    int j;
                    for (j = 0; u.is_use[j]; j++) ;

                    TURN_STRING(temp, j);
                    strcat(u.path, temp);
                    strcat(u.path, ",0");

                    if (Length(u) < min_length) {
                        min_length = Length(u);
                        strcpy(opt_tour, u.path);
                    }
                } else {
                    u.bound = Bound(u);

                    if (u.bound < min_length) {
                        algo->Insert(&queue, u);
                    }
                }
            }
        }
    }

    algo->Delete(queue);
    node_algo->Delete(u);
    node_algo->Delete(v);

    return min_length;
}

int Bound(Node u)
{
    int result = 0;
    int path[LENGTH];

    int path_length = String_to_Integer(path, u.path);

    for (int i = 0; i < path_length - 1; i++) {
        result += adjacency_matrix[ path[i] ][ path[i + 1] ];
    }

    for (int i = 0; i < CITY; i++) {
        /* Cannot choose the node that has been selected and itself */
        if (u.is_use[i] && i != path[path_length - 1])
            continue;
        
        int min = INT_MAX;

        for (int j = 0; j < CITY; j++) {
            if (path_length > 1 && path[path_length - 1] == i && path[0] == j)
                continue;
            
            if (u.is_use[j] && j != path[0])
                continue;

            if (i != j && min > adjacency_matrix[i][j]) {
                min = adjacency_matrix[i][j];
            }
        }
        result += min;
    }

    return result;
}

int Length(Node u)
{
    int result = 0;
    int path[CITY + 1];

    int path_length = String_to_Integer(path, u.path);

    for (int i = 0; i < path_length - 1; i++) {
        result += adjacency_matrix[ path[i] ][ path[i + 1] ];
    }

    return result;
}

int String_to_Integer(int *array, char *string)
{
    int  length = 0;

    char temp[LENGTH];
    strcpy(temp, string);

    char *str = strtok(temp, ",");

    while (str != NULL) {
        /* Convert a string to an interger */
        *array++ = strtol(str, (char **) NULL, 10);
        str = strtok(NULL, ",");
        length++;
    }

    return length;
}
