#ifndef PRIORITY_QUEUE_MIN_H_
#define PRIORITY_QUEUE_MIN_H_

#include <stdint.h>
#include <stdbool.h>

typedef struct _Node {
    int  level;      /* The level of tree */
    char *path;      /* Part of tour of this node */
    int  bound;
    bool *is_use;    /* The point of tour is used or not */
} Node;

typedef struct _Queue {
    int  front, rear;
    int  length;
    Node *data;
} Queue;

typedef struct _Node_Algo {
    void (*Create)(Node *, int);
    void (*Delete)(Node);
} _Node_Algo;

typedef struct _Priority_Queue_Algo {
    void (*Create)(Queue *, int);
    void (*Delete)(Queue);

    bool (*Is_Empty)(Queue);
    bool (*Is_Full)(Queue);

    void (*Insert)(Queue *, Node);
    void (*Remove)(Queue *, Node *);
} _Priority_Queue_Algo;

extern _Node_Algo Node_Algo;
extern _Priority_Queue_Algo Priority_Queue_Algo;

#endif /* PRIORITY_QUEUE_MIN_H_ */
