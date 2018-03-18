#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Priority_Queue_Min.h"

static void Copy_Struct(Node *a, Node *b, int len)
{
    a->level = b->level;
    a->bound = b->bound;
    memcpy(a->path, b->path, sizeof(a->path[0]) * len);
    memcpy(a->is_use, b->is_use, sizeof(a->is_use[0]) * len);
}

static void Create_Node(Node *node, int length)
{
    node->path   = (char *) calloc(length, sizeof(char));
    node->is_use = (bool *) calloc(length, sizeof(bool));
}

static void Delete_Node(Node node)
{
    free(node.path);
    free(node.is_use);
}

static void Create(Queue *queue, int length)
{
    /* Allocated enough memory to handle the queue data structure */
    queue->front  = -1;
    queue->rear   = -1;
    queue->length = length;

    queue->data = (Node *) calloc(queue->length, sizeof(Node));

    for (int i = 0; i < queue->length; i++) {
        queue->data[i].path   = (char *) calloc(length, sizeof(char));
        queue->data[i].is_use = (bool *) calloc(length, sizeof(bool));
    }
}

static void Delete(Queue queue)
{
    for (int i = 0; i < queue.length; i++) {
        free(queue.data[i].path);
        free(queue.data[i].is_use);
    }

    free(queue.data);
}

static bool Is_Empty(Queue q)
{
    return (q.front == -1 && q.rear == -1);
}

static bool Is_Full(Queue q)
{
    return (q.rear == q.length - 1);
}

static void Insert(Queue *q, Node node)
{
    if (Is_Full(*q)) {
        printf("Queue is full!\n");
    } else if (Is_Empty(*q)) {
        q->front = 0;
        q->rear  = 0;
        Copy_Struct(&q->data[q->rear], &node, q->length);
    } else {
        for (int i = 0; i <= q->rear; i++) {
            if (node.bound < q->data[i].bound) {
                for (int j = q->rear + 1; j > i; j--) {
                    Copy_Struct(&q->data[j], &q->data[j - 1], q->length);
                }

                q->rear++;
                Copy_Struct(&q->data[i], &node, q->length);
                return;
            }
        }

        q->rear++;
        Copy_Struct(&q->data[q->rear], &node, q->length);
    }
}

static void Remove(Queue *q, Node *node)
{
    if (Is_Empty(*q)) {
        printf("Queue is empty!\n");
        return;
    }

    Copy_Struct(node, &q->data[q->front], q->length);

    for (int i = q->front; i < q->rear; i++) {
        Copy_Struct(&q->data[i], &q->data[i + 1], q->length);
    }

    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
        q->rear--;
    }
}

_Node_Algo Node_Algo = {
    .Create   = Create_Node,
    .Delete   = Delete_Node,
};

_Priority_Queue_Algo Priority_Queue_Algo = {
    .Create   = Create,
    .Delete   = Delete,

    .Is_Empty = Is_Empty,
    .Is_Full  = Is_Full,
    .Insert   = Insert,
    .Remove   = Remove,
};
