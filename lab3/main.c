#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <time.h>

double f(double x);                                     // вихідна функція
double method_divide(double x1, double x2, double eps);  // метод половинчастого ділення
double method_hord(double x1, double x2, double eps);   // метод хорд
int choose_method();                                    // вибір методу

int main()
{
    double X1, X2, root, eps;


    printf("\nEnter arguments: \n");
    do {
        printf("\nX1 = ");
        scanf_s("%lf", &X1);
        printf("X2 = ");
        scanf_s("%lf", &X2);
        if (f(X1) * f(X2) > 0)
            printf("\nChoose another arguments\n");
    }

    while (f(X1) * f(X2) > 0);
    printf("Epsillon = ");
    scanf_s("%lf", &eps);
    system("cls");

    switch (choose_method())
    {
    case 1:
        root = method_divide(X1, X2, eps);
        break;
    case 2:
        root = method_hord(X1, X2, eps);
    }
    printf("\nroot = %lf, X1 = %.0lf, X2 = %.0lf, eps = %lf", root, X1, X2, eps);

    return 0;
}

//////////////////////////

double f(double x)
{
    return (pow(x, 3) / -25 + 10 * pow(x, 2) - 15000);
}

//////////////////////////

double method_divide(double x1, double x2, double eps)
{
    double xi;
    int iter_count = 0, N = 5, flag = 0;
    int answer;

    clock_t start, end;
    double delta_t;

    start = clock();

    do {
        iter_count++;

        xi = (x1 + x2) / 2;

        if (f(xi) * f(x1) > 0)
            x1 = xi;
        else
            x2 = xi;

        if ((iter_count % N) == 0 && flag == 0)
        {
            printf("\n iterations done = %u", iter_count);
            printf("\n current x = %lf", xi);
            printf("   f(x) = %lf", f(xi));

            do {
                printf("\n 1 - exit, 2 - continue, 3 - proceed to the end\n\n>");
                scanf_s("%u", &answer);

                if (answer == 1)
                {
                    printf("\n current x = %lf", xi);
                    printf("   f(x) = %lf", f(xi));
                    exit(0);
                }
                else if (answer == 2)
                    break;
                else if (answer == 3)
                    flag = 1;

                if (answer != 1 && answer != 2 && answer != 3)
                    printf("\n!!!Invalid input");

            } while (answer != 1 && answer != 2 && answer != 3);
        }
    } while (fabs(x1 - x2) >= eps);

    end = clock();

    delta_t = (end - start) / CLOCKS_PER_SEC;

    printf("\n\ndelta time = %lf", delta_t);

    return xi;

}
double method_hord(double x1, double x2, double eps)
{
    double xi;
    int iter_count = 0, N = 5, flag = 0;
    int answer;

    clock_t start, end;
    double delta_t;

    start = clock();

    do {
        iter_count++;

        xi = (x1 * f(x2) - x2 * f(x1)) / (f(x2) - f(x1));

        if (f(x1) * f(xi) > 0)
            x1 = xi;
        else
            x2 = xi;

        if ((iter_count % N) == 0 && flag == 0)
        {
            printf("\n iterations done = %u", iter_count);
            printf("\n current x = %lf", xi);
            printf("   f(x) = %lf", f(xi));

            do {
                printf("\n 1 - exit, 2 - continue, 3 - proceed to the end\n\n>");
                scanf_s("%u", &answer);

                if (answer == 1)
                {
                    printf("\n current x = %lf", xi);
                    printf("   f(x) = %lf", f(xi));
                    exit(0);
                }
                else if (answer == 2)
                    break;
                else if (answer == 3)
                    flag = 1;

                if (answer != 1 && answer != 2 && answer != 3)
                    printf("\n!!!Invalid input");

            } while (answer != 1 && answer != 2 && answer != 3);
        }

    } while (fabs(f(xi)) >= eps);

    end = clock();

    delta_t = (end - start) / CLOCKS_PER_SEC;

    printf("\n\ndelta time = %lf", delta_t);
return xi;
}
/////////////////////////////
int choose_method()
{
    int answer;
    do {
        printf("\ndivision method - 1, hord method - 2\n>");
        scanf_s("%u", &answer);
        if (answer != 1 && answer != 2)
            printf("\n!!!Invalid input");
    } while (answer != 1 && answer != 2);
}
