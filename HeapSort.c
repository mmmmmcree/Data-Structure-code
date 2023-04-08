# include<stdio.h>
# include<stdlib.h>

typedef struct Array{
    int *a;
    int numsSize;
}Array;

void swap(int *a, int *b){
    int temp = *a;
    *a = *b, *b = temp;
}
/*
处理a[oper_index]，维护大顶堆。
此时oper_index相当于一个根节点。
如果oper_index的两个子节点中<最大>的对应值比a[oper_index]大，则交换，并且那个对应值<最大>最大的子节点成为新的根节点，重复操作。
操作完毕后，oper_index对应的二叉树是大顶堆。
*/
void heap_adjust(int *a, int oper_index, int numsSize){
    for(int j = 2 * oper_index + 1; j < numsSize; j = j * 2 + 1){  // j = 2 * oper_index + 1, 即j是oper_index的left child
        if(j + 1 < numsSize && a[j] < a[j + 1]){  // 如果右节点存在，且对应值更大
            j++;
        }
        if(a[j] > a[oper_index]){
            swap(a + j, a + oper_index);
            oper_index = j;
        }
    }
}

void heap_sort(int *a, int numsSize){
    for(int i = numsSize / 2 - 1; i >= 0; i--){  // 自底向上把所有母结点变成大顶堆，完成操作后整个数组就是一个大顶堆。维护次数为母结点总数。
        heap_adjust(a, i, numsSize);
    }
    while(numsSize-- > 0){  // 把大顶堆顶部的值与大顶堆最后一个值交换
        swap(a, a + numsSize);
        heap_adjust(a, 0, numsSize);  // 此时大顶堆顶部变为oper_index，对oper_index进行维护。由于只有oper_index是例外，只用维护一次。
    }
}

void main(){
    Array array;
    int aa[12] = {90, 52, 67, 38, 99, 80, 106, 49, 806, 221, 216, 198};
    array.a = aa, array.numsSize = 12; 
    heap_sort(array.a, 12);
    for(int i = 0; i < array.numsSize; i++){
        printf("%4d", array.a[i]);
    }    
}