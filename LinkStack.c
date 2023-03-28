# include<stdio.h>
# include<stdlib.h>
# include<assert.h>

# define EleType int

// 栈结点
typedef struct StackNode
{
    EleType data;
    struct StackNode *next;
}StackNode;
// 栈对象
typedef struct Stack
{
    /*
    在链表实现的栈对象中其实可以放一个伴随列表，用于记录栈中的data,
    这样可以方便通过下标来查找元素，而不用遍历一个链表。
    这个列表非常易于维护，因为只需在pop和push时改动列表的最后一个元素就行了。
    但是，栈的核心还是先进后出这一功能，对于一个栈重要的还是位于top的元素，故这里就不实现这个伴随列表了。
    */
    StackNode *top;
    size_t size;
    // 以下为C语言面向对象的测试，问题：python中的self参数怎么实现？？
    int (*_is_empty)();
    void (*_push)();
    EleType (*_top)();
    EleType (*_pop)();
}*Stack;
// 具有查看当前栈的大小和判断是否为空两个功能。每次断言都可以查看栈的大小，解决了断言的输出问题(否则得用宏改写断言输出)。
int is_empty(Stack stack){
    printf("current stack.size: %d\n", stack->size);
    return stack->top == NULL;
}

void push(Stack stack, EleType data){
    StackNode *stacknode =(StackNode*)malloc(sizeof(StackNode));
    /*
    这里遇到过问题！
    为什么是创建*stacknode而不是stacknode:
    遇到的问题：使用StackNode stacknode创建stacknode，用stack->top = &stacknode尝试将stacknode带出函数，发生错误
    错误原因: 这里的stack->top也是一个副本！！改变了这个副本不会影响函数外的stack->top
    其实可以通过*stack->top = stacknode的方式将stacknode带出，但由于stack->top可能为NULL，在这里行不通
    */
    stacknode->data = data;
    stacknode->next = stack->top;
    stack->top = stacknode;
    stack->size++;
}
// 查看栈顶数据
EleType top(Stack stack){
    /*
    这里用断言，而不用if is_empty(stack): return的原因:该函数返回值为ElyType, 无法返回空值，也就无法用返回值表示top为空
    由于使用了断言，当top为空时会直接停止程序
    不过引发这个问题的原因只有两个：查看空栈的top->data, 以及对空栈使用pop
    这些都是错误操作，应该使程序停止
    */
    assert(! is_empty(stack));
    return stack->top->data;
}

EleType pop(Stack stack){
    EleType temp = top(stack);
    StackNode *p = stack->top;
    stack->top = stack->top->next;
    free(p);
    stack->size --;
    return temp;
}

void init(Stack stack){
    stack->top = NULL;
    stack->size = 0;
    stack->_is_empty = is_empty;
    stack->_push = push;
    stack->_top = top;
    stack->_pop = pop;
}

Stack create_stack(){
    // 在create中完成内存分配、初始化两个操作，我认为比之前实现的在main中完成要好很多
    Stack stack = (Stack)malloc(sizeof(struct Stack));
    init(stack);
    return stack;
}

void main(){
    Stack stack = create_stack();
    stack->_push(stack, 5);
    push(stack, 6);
    push(stack, 7);
    printf("is empty? : %d\n", stack->_is_empty(stack));
    pop(stack);
    printf("%d", top(stack));
}