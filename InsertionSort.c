# include<stdio.h>
# include<stdlib.h>

# define SIZE 9

void insertion_sort(int *array){
    for (size_t i = 1; i < SIZE; i++)
    {
        int temp = array[i];
        int j = i - 1;
        if (temp < array[j])
        {
            for (j; j >= 0 && temp < array[j] ; j--)
            {
                array[j + 1] = array[j];
            }
            array[j + 1] = temp;
        }
    }
}

void main(){
    int a[9] = {9, 1, 5, 8, 3, 7, 4, 6, 2};

    insertion_sort(a);
    for (size_t i = 0; i < SIZE; i++)
    {
        printf("%3d", a[i]);
    }
    return;
}