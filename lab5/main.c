#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h>

// input.txt//
//  - початкове значення аргументу математичної функції;
//  − кінцеве значення аргументу математичної функції;
//  − кількість точок, в яких обчислюється значення математичної функції;
//  − крок зміни аргументу математичної функції;
//  - метод;
//  − шифр навчальної групи;
//  − прізвище та ім’я студента, який виконує лабораторну роботу

void scan_line(FILE *fp, char *str);
void erase_str(FILE *fp, char *str, unsigned int size);
void erase_and_open_file(FILE *fp);
void erase_and_open_bin_file(FILE *fp);
double function(double x);

#define ARRAY_SIZE 50

int main()
{
    FILE *fp;

    char group[ARRAY_SIZE], student[ARRAY_SIZE];
    erase_str(fp, group, ARRAY_SIZE);
    erase_str(fp, student, ARRAY_SIZE);
    double F = 0, x1 = 0, x2 = 0, delta = 0, x = 0;
    int t = 0;
    unsigned int method = 0, N = 0, N2 = 0;

    if ((fp = fopen("input.txt", "r")) != 0)
    {
        fscanf(fp, "%lf", &x1);
        fscanf(fp, "%lf", &x2);
        fscanf(fp, "%u", &N);
        fscanf(fp, "%lf", &delta);
        fscanf(fp, "%u", &method);
        scan_line(fp, group);
        scan_line(fp, student);

        printf("%lf\n", x1);
        printf("%lf\n", x2);
        printf("%u\n", N);
        printf("%lf\n", delta);
        printf("%u\n", method);
        printf("%s", group);
        printf("%s", student);

        fclose(fp);

        erase_and_open_file(fp);
        x = x1;
        fprintf(fp, "----------------------------------");
        fprintf(fp, "\n|    N    |    X    |    F(X)    |");
        fprintf(fp, "\n----------------------------------\n");
        if (method == 1)
        {
            delta = (x2 - x) / (N - 1);
            N2 = N;
            for (int i = 1; i <= N; i++)
            {
                fprintf(fp, "|%4d  |%10.2lf |%12.2lf |", i, x, F);
                fprintf(fp, "\n----------------------------------\n");
                x += delta;
                F = function(x);
            }
        }
        else
        {
            for (int i = 1; x <= x2; i++)
            {
                fprintf(fp, "|%4d  |%10.2lf |%12.2lf |", i, x, F);
                fprintf(fp, "\n----------------------------------\n");
                x += delta;
                F = function(x);
                N2 = i;
            }
        }
        fprintf(fp, "%s", group);
        fprintf(fp, "%s", student);
        fclose(fp);

        erase_and_open_bin_file(fp);
        x = x1;
        fprintf(fp, "%u\n", N2);
        if (method == 1)
        {
            delta = (x2 - x) / (N - 1);
            for (int i = 1; i <= N; i++)
            {
                fprintf(fp, "%.3lf\n%.3lf\n", x, F);
                x += delta;
                F = function(x);
            }
        }
        else
        {
            for (int i = 1; x <= x2; i++)
            {
                fprintf(fp, "%.3lf\n%.3lf\n", x, F);
                x += delta;
                F = function(x);
            }
        }
        fclose(fp);

        fp = fopen("output.bin", "rb");
        fscanf(fp, "%u", &N);
        double *arr = (double *)malloc(2 * N * sizeof(double));
        printf("\n\n--------------------------------");
        printf("\n| N |      X      |    F(X)    |");
        printf("\n--------------------------------\n");
        for (int i = 0; i < N * 2; i++)
        {
            fscanf(fp, "%lf", &arr[i]);
        }
        for (int i = 0; i < N * 2; i++)
        {
            printf("|%3u|%3lf |%3lf|\n", (i/2 + 1), arr[i], arr[++i]);
            printf("--------------------------------\n");
        }
        
        free(arr);
        fclose(fp);
    }
    else
    {
        printf("Error! File cannot be opened 1 ");
        getch();
        return 0;
    }
    getch();
    return 0;
}


void scan_line(FILE *fp, char *str)
{
    do
        str[0] = fgetc(fp);
    while (str[0] == '\n');
    for (int i = 1; str[i - 1] != '\n'; i++)
        str[i] = fgetc(fp);
}

void erase_str(FILE *fp, char *str, unsigned int size)
{
    for (int i = 0; i < size; i++)
        str[i] = '\0';
}

void erase_and_open_file(FILE *fp)
{
    remove("output.txt");
    fp = fopen("output.txt", "w");
}

void erase_and_open_bin_file(FILE *fp)
{
    remove("output.bin");
    fp = fopen("output.bin", "wb");
}

double function(double x)
{
    return pow(x, 3) / -25 + 10 * pow(x, 2) - 15000;
}