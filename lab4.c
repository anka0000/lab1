#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble_sort(int *a, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

void insertion_sort(int *a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

void fill_random(int *a, int n) {
    for (int i = 0; i < n; i++)
        a[i] = rand() % 10000;
}

double test_sort(void (*sort_func)(int*, int), int *a, int n) {
    clock_t start = clock();
    sort_func(a, n);
    clock_t end = clock();
    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main() {
    srand(time(NULL));
 
    int sizes[] = {10, 1000, 10000, 100000};
    int count = 4;

    printf("Размер | Пузырек (с) | Вставки (с) | Слияние (с)\n");
    printf("-----------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        int n = sizes[i];


        int *a = malloc(n * sizeof(int));
        int *b = malloc(n * sizeof(int));
        int *c = malloc(n * sizeof(int));

        fill_random(a, n);
        for (int j = 0; j < n; j++) b[j] = a[j];
        for (int j = 0; j < n; j++) c[j] = a[j];

        double t_bubble = test_sort(bubble_sort, a, n);
        double t_insert = test_sort(insertion_sort, b, n);
       

        printf("%6d | %12f | %11f\n", n, t_bubble, t_insert);

        free(a);
        free(b);
        
    }

    return 0;
}
