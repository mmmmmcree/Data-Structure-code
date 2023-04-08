# include<stdio.h>
# include<stdlib.h>

typedef struct Array
{
    int *array;
    int size;
}Array;


void shell_sort(Array *array){
    int increase = array->size;
    do
    {
        increase /= 2;
        for (size_t i = increase; i < array->size; i++)
        {
            int temp = array->array[i];
            int j = i - increase;
            for (j; j >= 0 && temp < array->array[j]; j -= increase)
            {
                if (temp < array->array[j])
                    array->array[j + increase] = array->array[j];
            }
            array->array[j + increase] = temp;
        } 
    } while (increase > 1);
    
}

void main(){
    Array array;
    int a[9] = {9, 1, 5, 8, 3, 7, 4, 6, 2};
    array.array = a;
    array.size = 9;
    shell_sort(&array);
    for (size_t i = 0; i < array.size; i++)
    {
        printf("%3d", array.array[i]);
    }
    return;
}