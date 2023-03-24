#include<stdio.h>
# include<stdlib.h>

# define Pass 1
# define Error 0
# define Status int
# define True 1
# define False 0
# define Bool int
# define EleType int

// 循环队列
typedef struct Queue
{
    int SIZE; //假想的SIZE，比队列的真实size多1
    int front;
    int rear;
    EleType* queue;
}Queue;

Status queue_init(Queue* queue, int size){
    queue->SIZE = size + 1;
    queue->front = queue->rear = 0;
    queue->queue = (EleType*)malloc(sizeof(EleType) * queue->SIZE);
    printf("The queue is initialized. Volume: %d\n", size);
    return Pass;
}

int queue_len(Queue queue){
    int len = (queue.rear - queue.front + queue.SIZE) % queue.SIZE;
    return len;
}

Status queue_enter(Queue* queue, EleType element){
    if (queue_len(*queue) == queue->SIZE - 1)
    {
        printf("The queue is full!\n");
        return Error;
    }
    queue->queue[queue->rear] = element;
    queue->rear = (queue->rear + 1) % queue->SIZE;
}

Status queue_exit(Queue* queue){
    if (queue_len(*queue) == 0)
    {
        printf("The queue is empty!\n");
        return Error;
    }
    queue->front = (queue->front + 1) % queue->SIZE;
    return Pass;
}

void queue_describe(Queue queue){
    if (queue_len(queue) == 0)
    {
        printf("Empty queue");
        return;
    }
    int len = queue_len(queue);
    printf("queue: [");
    for (int i = queue.front; i < queue.front + len - 1; i++)
    {
        printf("%d, ", queue.queue[i % queue.SIZE]);
    }
    printf("%d]\nCurrent elements number: %d, Empty positions: %d\n",
    queue.queue[(queue.front + len - 1) % queue.SIZE], len, queue.SIZE - len - 1);
}

void main(){
    Queue queue;
    queue_init(&queue, 4);
    queue_enter(&queue, 10);
    queue_enter(&queue, 5);
    queue_enter(&queue, 4);
    queue_enter(&queue, 7);
    queue_enter(&queue, 7);
    queue_exit(&queue);
    queue_exit(&queue);
    queue_enter(&queue, 1);
    queue_enter(&queue, 2);
    queue_describe(queue);
}