#include <stdio.h>
#include <conio.h>

double power(double x, double exp);

int main()
{
    int N = 1;
    double a = 0, sum = 0;
    printf("Enter N(>=1)\nN = ");
    scanf("%d", &N);
    printf("Enter a\na = ");
    scanf("%lf", &a);
    sum += power(a, N-1);
    for (int i = 1; i <= N; i++)
        sum += i;
    printf("Sum = %lf", sum);
    getch();
    return 0;
}

double power(double x, double exp)
{
    if (exp >= 0)
    {
        double sum = 1;
        for (int i = 0; i < exp; i++)
            sum *= x;
        return sum;
    }
    else
    {
        double sum = 1;
        for (int i = 0; i > exp; i--)
            sum /= x;
        return sum;
    }
}