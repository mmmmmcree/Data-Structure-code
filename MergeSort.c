# include<stdio.h>
# include<stdlib.h>

# define NUL 2147483647
# define SIZE 9

void merge(int *a, int start, int split, int end){ // 分割点及其左边都属于L，分割点右边属于R
    int *L = (int*)malloc(sizeof(int) * (split - start + 2)), *R = (int*)malloc(sizeof(int) * (end - split + 1));
    int index = start;
    int i = 0, j = 0;
    while(index <= split){
        L[i++] = a[index++];
    }
    L[i] = NUL;
    while(index <= end){
        R[j++] = a[index++];
    }
    R[j] = NUL;
    i = 0, j = 0;
    for(int k = start; k <= end; k++){
        if(L[i] < R[j]){
            a[k] = L[i++];
        }
        else{
            a[k] = R[j++];
        }
    }
    free(L), free(R);
}

void merge_sort_recur(int *a, int start, int end){
    if(start == end){
        return;
    }
    int mid = (start + end) / 2;
    merge_sort_recur(a, start, mid);
    merge_sort_recur(a, mid + 1, end);
    merge(a, start, mid, end);
}

void merge_sort(int *a, int start, int end){
    if(start == end){
        return;
    }
    int step = 2;
    for(step; step <= end - start; step *= 2){
        for(int i = start; i < end; i += step){
            int j = (i + step - 1) > end? end: i + step - 1;
            merge(a, i, (i + j) / 2, j);
        }
    }
    int split = start + step / 2 - 1;
    merge(a, start, split, end);
}

void main(){
    int a[SIZE] = {10, 9, 6, 4, 1, 3, 2, 18, 21};
    int b[SIZE] = {10, 9, 6, 4, 1, 3, 2, 18, 21};
    merge_sort(a, 4, 7);
    merge_sort_recur(b, 0, SIZE - 1);
    for(int i = 0; i < SIZE; i++){
        printf("%3d", a[i]);
    }
    printf("\n");
    for(int i = 0; i < SIZE; i++){
        printf("%3d", b[i]);
    }
}