# include<stdio.h>
# include<stdlib.h>

# define Pass 1
# define Error 0
# define Status int
# define EleType char

char str[23] = "abdh#k###e##cfi###g#j##";  // 用这个字符串构建二叉树，#代表空
int idx = 0;

typedef struct BINode
{
    EleType data;
    struct BINode *lchild, *rchild;
}BINode, *BITree;
// 创建二叉树，通过所有叶节点的两个"子节点"都为空退出递归。因为要把空节点设为NULL，故函数参数为BITree(BITree是BINode的指针)的指针。
void create_binaryTree(BITree *T){
    EleType ch = str[idx++];
    if (ch != '#')
    {
        (*T)->data = ch;
        (*T)->lchild = (BITree)malloc(sizeof(BINode));
        create_binaryTree(&(*T)->lchild);
        (*T)->rchild = (BITree)malloc(sizeof(BINode));
        create_binaryTree(&(*T)->rchild);
        return;
    }
    else
    {
        *T = NULL;
        return;
    }
    return;
}
// 前序遍历，print在进入lchild之前
void preorder_traverse(BITree T){
    if (T == NULL)
    {
        return;
    }
    else{
        printf("%c", T->data);
        preorder_traverse(T->lchild);
        preorder_traverse(T->rchild);
    }
}
// 中序遍历，print在进入lchild之后，进入rchild之前
void inorder_traverse(BITree T){
    if (T == NULL)
    {
        return;
    }
    else{
        inorder_traverse(T->lchild);
        printf("%c", T->data);
        inorder_traverse(T->rchild);
    }
}
// 后序遍历，print在进入rchild之后
void postorder_traverse(BITree T){
    if (T == NULL)
    {
        return;
    }
    else{
        postorder_traverse(T->lchild);
        printf("%c", T->data);
        postorder_traverse(T->rchild);
    }
}

void main(){
    BITree T = (BITree)malloc(sizeof(BINode));
    create_binaryTree(&T);
    preorder_traverse(T);
    printf("\n");
    inorder_traverse(T);
}