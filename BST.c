# include<stdio.h>
# include<stdlib.h>

# define INFINITY 2147483647
# define SIZE 11

typedef struct TNode{
    struct TNode * p, *left, *right;
    int key;
}TNode;

void tnode_init(TNode *t){
    t->key = INFINITY;
    t->left = NULL, t->right = NULL, t->p = NULL;
}

TNode create_tnode(){
    TNode tnode;
    tnode_init(&tnode);
    return tnode;
}

void insert_node(TNode *root, int num){
    TNode tnode = create_tnode(), *p = NULL, *q = NULL;
    tnode.key = num;
    if(root == NULL){
        root = (TNode*)malloc(sizeof(TNode));
        *root = tnode;
    }
    else{
        p = root;
        while(p != NULL){
            q = p;
            if(tnode.key < p->key){p = p->left;}
            else{p = p->right;}
        }
        tnode.p = q;
        if(tnode.key < q->key){
            q->left = (TNode*)malloc(sizeof(TNode));
            *(q->left) = tnode;
        }
        else{
            q->right = (TNode*)malloc(sizeof(TNode));
            *(q->right) = tnode;
        }
    }
}

TNode *built_bst(int *nums, int numsSize){
    TNode *t = NULL;
    for(int i = 0; i < numsSize; i++){
        if(t == NULL){
            TNode tnode = create_tnode();
            tnode.key = nums[i];
            t = (TNode*)malloc(sizeof(TNode));
            *t = tnode;
        }
        else{insert_node(t, nums[i]);}
    }
    return t;
}

TNode* search_node(TNode *tnode, int num){
    if(tnode == NULL){return NULL;}
    if(tnode->key == num){return tnode;}
    return tnode->key < num? search_node(tnode->right, num): search_node(tnode->left, num);
}

TNode* get_minNode(TNode * tnode){
    if(tnode == NULL){return NULL;}
    while(tnode->left != NULL){tnode = tnode->left;}
    return tnode;
}

TNode* get_maxNode(TNode * tnode){
    if(tnode == NULL){return NULL;}
    while(tnode->right != NULL){tnode = tnode->right;}
    return tnode;
}

TNode* get_successor(TNode *root){
    if(root == NULL || root->right == NULL){return NULL;}
    else{get_minNode(root->right);}
}

TNode* get_predecessor(TNode *root){
    if(root == NULL || root->left == NULL){return NULL;}
    else{get_maxNode(root->left);}
}
// 用结点v替换结点u
void node_transplant(TNode *u, TNode *v){
    if(u->p == NULL){u = v;}
    else if(u->p->left = u){
        u->p->left = v;
    }
    else if(u->p->right = u){
        u->p->right = v;
    }
}

void delete_node(TNode *root, int num){
    TNode *t = search_node(root, num);
    if(t->right == NULL){node_transplant(t, t->left);}
    else if(t->left == NULL){node_transplant(t, t->right);}
    else{
        TNode *p = get_successor(t);
        t->key = p->key;
    }
}

void inorder_traverse(TNode *tnode){
    if (tnode == NULL){return;}
    else{
        inorder_traverse(tnode->left);
        printf("%4d", tnode->key);
        inorder_traverse(tnode->right);
    }
} 

void main(){
    int a[SIZE] = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    TNode *bst = built_bst(a, SIZE);
    printf("\n%d\n", search_node(bst, 17));
    printf("%d\n", get_minNode(bst)->key);
    printf("%d\n", get_maxNode(bst)->key);
    insert_node(bst, 36);
    printf("%d\n", get_successor(search_node(bst, 20))->key);
    printf("%d\n", get_predecessor(bst)->key);
    delete_node(bst, 15);
    inorder_traverse(bst);
}