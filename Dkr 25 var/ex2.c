#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int mult(int *array, const int array_size);

#define ARRAY_SIZE 5

int main()
{
    int arr[ARRAY_SIZE];

    printf("\nenter a values of array:\n"); // вивід тексту
    for (int i = 0; i < ARRAY_SIZE; i++)    // перебір всіх елементів масиву
    {
        printf("arr[%d] = ", i); // виведення індексу елемента
        scanf("%d", &arr[i]);    // отримання значення елементу масива
    }
    printf("multiplicate = %d", mult(&arr[0], ARRAY_SIZE));
    getch();
    return 0;
}

int mult(int *array, const int array_size)
{
    int sum = 1;
    for (int i = 0; i < array_size; i++)
        if (i % 2)           // якщо індекс непарний
            sum *= array[i]; // додати елемент до суми
    return sum;
}