# include<stdio.h>
# include<stdlib.h>

# define SIZE 9

void swap(int *a, int *b){
    int temp = *a;
    *a = *b, *b = temp;
}

int median_of_three(int *a, int left, int right){
    int mid = (left + right) / 2;
    if(a[left] > a[right]){
        swap(a + left, a + right);
    }
    if(a[mid] > a[right]){
        swap(a + mid, a + right);
    }
    if(a[mid] > a[left]){
        swap(a + mid, a + left);
    }
    return a[left];
}

int partition(int *a, int left, int right){
    int key = median_of_three(a, left, right);
    while(left < right){
        while(left < right && a[right] > key){
            right--;
        }
        a[left] = a[right];
        while(left < right && a[left] < key){
            left++;
        }
        a[right] = a[left];
    }
    a[left] = key;
    return left;
}

void quick_sort(int *a, int left, int right){
    int key_pos = partition(a, left, right);
    if(key_pos - 1 > left){
        quick_sort(a, left, key_pos - 1);
    }
    if(key_pos + 1 < right)
    {
        quick_sort(a, key_pos + 1, right);
    }
}

void main(){
    int a[SIZE] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int b[SIZE] = {10, 9, 6, 4, 1, 3, 2, 18, 21};
    quick_sort(a, 0, SIZE - 1);
    printf("\n");
    for(int i = 0; i < SIZE; i++){
        printf("%3d", a[i]);
    }
}