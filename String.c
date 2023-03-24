#include<stdio.h>
# include<stdlib.h>
# include<string.h>

# define Pass 1
# define Error 0
# define Status int
# define True 1
# define False 0
# define Bool int
// 串
typedef struct String{
    char* string;
    int length;
}String;

Status string_init(String* str, char* s){
    str->string = s;
    str->length = strlen(s);
    return Pass;
}
// 得到最大重复子串的长度
int* get_repeatLength(String T){
    int* repeatLength = (int*)malloc(sizeof(int) * T.length);  
    /*
    该数组中每一位的数字n与输入字符串的每一位字母按顺序一一对应，表示对应位置字母之前最多有n位与字符串开头的n位相同。
    (注：若该字符之前完全相同，则n == 相同个数 - 1, 因为至少要差一位才能开始比较)
    n用于KMP匹配中固定子串的位置。
    repeatLength[0]固定为-1；repeatLength[1]根据定义，一定为0。
    */
    repeatLength[0] = -1;
    int i = 0 , k = -1; // k是游标, i是字符串下标。在满足相等条件之前i不变，k改变。满足相等条件后i往后移一位，又因为T[i] == T[k], k也往后移一位
    while (i < T.length)
    {
        if (k == -1|| T.string[i] == T.string[k])
        {
            i++;
            k++;
            repeatLength[i] = k;
        }
        else
            k = repeatLength[k]; // 回溯操作，相当于跳回上一个等价字符串，从等价字符的前一个字符开始重新比较
            /*
            触发条件：T.string[i] != T.string[k]
            说明i、k后移一位的新字符串不再相等，那么则需要找到包含于新字符串之内的最大子字符串，使得该字符串的最后一位满足T.string[i] == T.string[k]的条件。
            由于T.string[k]一定不符合，那么与新字符串等价的前一个字符串中，与T.string[k]相等的那个字母也一定不符合。
            故本次回溯就回溯到前一个等价字符串的相等字母上，从那个字母前一位开始重新比较。
            repeatLength[k]中包含了前一个等价字符串的长度信息，故通过k = repeatLength[k]进行回溯。
            */
    }
    return repeatLength;
    
}
// 对repeatLength数组做更适合KMP的优化
void upgrade_repeatLength(String T, int* repeatLenth){
    for (int i = 0; i < T.length; i++)  // 遍历repeatLenth
    {
        int k = repeatLenth[i];
        if (T.string[i] == T.string[k]) 
        /* 
        如果满足这一条件，说明该字符本身也可算进最大重复子串中。
        那么如果使用repeatLenth[i]作为"卡扣"，也同样可以使用repeatLenth[k]作为"卡扣"。
        */
            repeatLenth[i] = repeatLenth[k];  // 故用repeatLenth[k]代替repeatLenth[i]，这样可以跳跃更远的距离。
    }
}
// 做一个链式队列，把查找到所有符合的下标装进队列返回
typedef struct Node
{
    int data;
    struct Node* next;
}Node, *LinkQueue;

void linkqueue_init(LinkQueue linkqueue){
    linkqueue->data = 0;
    linkqueue->next = NULL;
}

void linkqueue_add(LinkQueue linkqueue, int element){
    linkqueue->data += 1;
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = element;
    p->next = NULL;
    if (linkqueue->next == NULL)
        linkqueue->next = p;
    else
    {
        Node* tail = linkqueue->next;
        while (tail->next != NULL)
            tail = tail->next;
        tail->next = p;
    }
}

void print_linkqueue(LinkQueue linkqueue){
    printf("Total: %d Indexes: [", linkqueue->data);
    if (linkqueue->next)
    {
        while (linkqueue->next->next != NULL){
            printf("%d, ", linkqueue->next->data);
            linkqueue = linkqueue->next;
        }
        printf("%d]", linkqueue->next->data);
    }
    else
        printf("]");
}
// KMP匹配
LinkQueue kmp_search(String S, String T){
    int* replen = get_repeatLength(T);
    upgrade_repeatLength(T, replen);
    int k = 0;
    LinkQueue linkqueue = (LinkQueue)malloc(sizeof(Node));
    linkqueue_init(linkqueue);
    for (int index = 0; index <= S.length - T.length; index++)
    {
        int i = index;
        while (S.string[i] == T.string[k])
        {
            i++;
            k++;
        }
        if (k >= T.length) // 这里是大于等于，因为有可能在末尾出现"\0"与"\0"的比较。
        {
            linkqueue_add(linkqueue, index);
            k = 0;
        }
        else if (k > 0)
        {
            index += k - 1;
            if (replen[k] != -1)  // 为了适配改进之后的kmp做的优化
                k = replen[k];
            else
                k = 0;
        }
        
    }
    return linkqueue;
}

void main(){
    String str, t;
    string_init(&str, "cdababaaaba");
    string_init(&t, "ababaaaba");
    int* replen = get_repeatLength(t);
    upgrade_repeatLength(t, replen);
    for (int i = 0; i < t.length; i++)
    {
        printf("%d  ", replen[i]);
    }
    printf("\n");
    print_linkqueue(kmp_search(str, t));

}