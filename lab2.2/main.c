// LABKU ROBILI: SYZKO, SYLA, FOLVARKOVA //
// LABKU ROBILI: SYZKO, SYLA, FOLVARKOVA //
// LABKU ROBILI: SYZKO, SYLA, FOLVARKOVA //
// LABKU ROBILI: SYZKO, SYLA, FOLVARKOVA //
// LABKU ROBILI: SYZKO, SYLA, FOLVARKOVA //
// LABKU ROBILI: SYZKO, SYLA, FOLVARKOVA //
// LABKU ROBILI: SYZKO, SYLA, FOLVARKOVA //
// LABKU ROBILI: SYZKO, SYLA, FOLVARKOVA //
// LABKU ROBILI: SYZKO, SYLA, FOLVARKOVA //
//
//ignor oshibok//
#define _CRT_SECURE_NO_WARNINGS
#define _VCRUNTIME_DISABLED_WARNINGS
//ignor oshibok//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double l_rect(double border_a, double border_b, unsigned int intervals);
double r_rect(double border_a, double border_b, unsigned int intervals);
double simps(double border_a, double border_b, unsigned int intervals);
double trapecia(double border_a, double border_b, unsigned int intervals);
double func(double x);
int num_set_difference(double border_a, double border_b, int var);



int main()
{
	double border_a = 0, border_b = 1; // obmezhennya Folvarkova
	double measurement_error = 0, i1 = 0, i2 = 0;
	int intervals, var, i;
	double integral_sum = 0;

	while (1)
	{
		printf("\n\tThe left boundary a = %.2lf", border_a);
		printf("\n\tThe right boundary b = %.2lf\n", border_b);

		//validacia
		do
		{
			printf("\tEnter the number of partition intervals (N>0)\nN=");
			scanf("%u", &intervals);
		} while (intervals <= 0);
		//validacia

		do
		{
			printf("\nChoose the method of calculating:\n");
			printf("\t1. By Left Rectangles:\n");
			printf("\t2. By Right Rectangles:\n");
			printf("\t3. By Trapecia:\n");
			printf("\t4. By Simps:\n");
			scanf("%u", &var);
			if (var != 1 && var != 2 && var != 3 && var != 4)
				printf("\nYou are mistaken\n");
		} while (var != 1 && var != 2 && var != 3 && var != 4);
		system("cls");
		switch (var)
		{
		case 1:
		{
			int N_err = num_set_difference(border_a, border_b, var);
			double i1 = l_rect(border_a, border_b, N_err);
			integral_sum = l_rect(border_a, border_b, intervals);
			printf("\n\n\t*Left Rectangles method*\n");
			printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral = %.6lf \n\tN = %d \n\ti1 = %.6lf \n\tNpoh = %d", border_a, border_b, integral_sum, intervals, i1, N_err);
		}
		break;
		case 2:
		{
			int N_err = num_set_difference(border_a, border_b, var);
			double i1 = r_rect(border_a, border_b, N_err);
			integral_sum = r_rect(border_a, border_b, intervals);
			printf("\n\n\t======*Right Rectangles method*======\n");
			printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral = %.6lf \n\tN = %d \n\ti1 = %.6lf \n\tNpoh = %d", border_a, border_b, integral_sum, intervals, i1, N_err);
		}
		break;
		case 3:
		{
			int N_err = num_set_difference(border_a, border_b, var);
			double i1 = trapecia(border_a, border_b, N_err);
			integral_sum = trapecia(border_a, border_b, intervals);
			printf("\n\n\t======*trapecia method *======\n");
			printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral = %.6lf \n\tN = %d \n\ti1 = %.6lf \n\tNpoh = %d", border_a, border_b, integral_sum, intervals, i1, N_err);
		}
		break;
		case 4:
		{
			int N_err = num_set_difference(border_a, border_b, var);
			double i1 = simps(border_a, border_b, N_err);
			integral_sum = simps(border_a, border_b, intervals);
			printf("\n\n\t======*simps's method *======\n");
			printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral = %.6lf \n\tN = %d \n\ti1 = %.6lf \n\tNpoh = %d", border_a, border_b, integral_sum, intervals, i1, N_err);
		}
		break;
		}
	}
	return 0;
}

double l_rect(double border_a, double border_b, unsigned int intervals)
{
	double integral_sum = 0, x = 0, h;
	unsigned int i;
	h = (border_b - border_a) / intervals;
	x = border_a; //x(n=0)
	for (i = 0; i <= (intervals - 1); i++)
	{
		integral_sum += func(x);
		x += h;
	}
	return integral_sum * h;
}
double r_rect(double border_a, double border_b, unsigned int intervals)
{
	double integral_sum = 0, x = 0, h;
	unsigned int i;
	h = (border_b - border_a) / intervals;
	x = border_a + h; //x(n=1)
	for (i = 0; i <= intervals; i++)
	{
		integral_sum += func(x);
		x += h;
	}
	return integral_sum * h;
}
double trapecia(double border_a, double border_b, unsigned int intervals)
{
	double integral_sum = 0, x = 0, h;
	unsigned int i;
	h = (border_b - border_a) / intervals;
	x = border_a + h; //x(n=1)
	for (i = 0; i <= (intervals - 1); i++)
	{
		integral_sum += (func(x) + func(x + h)) / 2;
		x += h;
	}
	return integral_sum * h;
}
double simps(double border_a, double border_b, unsigned int intervals)
{
	double integral_sum = 0, sum1 = 0, sum2 = 0, h = 0;

	h = (border_b - border_a) / intervals;

	for (int i = 1; i <= (intervals - 1); i++)
	{
		if (i % 2 != 0)
			sum1 += func(border_a + h * i);
		else
			sum2 += func(border_a + h * i);
	}
	return (func(border_a) + func(border_b) + 4 * sum1 + 2 * sum2) * h / 3;
}
double func(double x)
{
	return pow(x, 3) / (pow(x, 8) + 1);// Folvarkova function
}
int num_set_difference(double border_a, double border_b, int var)
{
	double error = 0.00001;

	switch (var)
	{
	case 1:
	{
		int N_err = 0, i1, i2;
		do
		{
			N_err += 2;
			i1 = l_rect(border_a, border_b, N_err);
			i2 = l_rect(border_a, border_b, N_err + 2);
		} while (fabs(i2 - i1) > error);
		return N_err;
	}
	break;
	case 2:
	{
		int N_err = 0, i1, i2;
		do
		{
			N_err += 2;
			i1 = r_rect(border_a, border_b, N_err);
			i2 = r_rect(border_a, border_b, N_err + 2);
		} while (fabs(i2 - i1) > error);
		return N_err;
	}
	break;
	case 3:
	{
		int N_err = 0, i1, i2;
		do
		{
			N_err += 2;
			i1 = trapecia(border_a, border_b, N_err);
			i2 = trapecia(border_a, border_b, N_err + 2);
		} while (fabs(i2 - i1) > error);
		return N_err;
	}
	break;
	case 4:
	{
		int N_err = 0, i1, i2;
		do
		{
			N_err += 2;
			i1 = simps(border_a, border_b, N_err);
			i2 = simps(border_a, border_b, N_err + 2);
		} while (fabs(i2 - i1) > error);
		return N_err;
	}
	break;
	}
}
