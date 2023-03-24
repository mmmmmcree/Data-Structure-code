#include<stdio.h>
# include<stdlib.h>

# define Pass 1
# define Error 0
# define Status int
# define EleType int

// 顺序栈
typedef struct SqStack
{
    int MAXSIZE;
    EleType* Stack;
    int top;
}SqStack;

Status sqstack_init(SqStack* SqStack, int MAXSIZE){
    SqStack->MAXSIZE = MAXSIZE;
    SqStack->top = -1;
    SqStack->Stack = (EleType*)malloc(sizeof(EleType) * MAXSIZE);
    printf("The sqstack is initialized. Volume: %d\n", MAXSIZE);
    return Pass;
}

Status sqstack_push(SqStack* SqStack, EleType element){
    if (SqStack->top == SqStack->MAXSIZE - 1)
    {
        printf("Out of range!\n");
        return Error;
    }
    SqStack->top += 1;
    SqStack->Stack[SqStack->top] = element;
    return Pass;
}

void describe_sqstack(SqStack SqStack){
    if (SqStack.top == -1)
    {
        printf("Empty stack");
        return;
    }
    printf("stack: [");
    for (int i = 0; i < SqStack.top; i++)
    {
        printf("%d, ", SqStack.Stack[i]);
    }
    printf("%d]\nCurrent elements number: %d, Empty positions: %d\n",
     SqStack.Stack[SqStack.top], SqStack.top + 1, SqStack.MAXSIZE - SqStack.top - 1);
}

Status sqstack_pop(SqStack* SqStack){
    if (SqStack->top == -1)
    {
        printf("Nothing to pop!\n");
        return Error;
    }
    SqStack->top -= 1;
    return Pass;
}

void main(){
    SqStack sqstack;
    sqstack_init(&sqstack, 100);
    for (int i = 0; i < 50; i++)
    {
        sqstack_push(&sqstack, (EleType)i);
    }
    describe_sqstack(sqstack);
}