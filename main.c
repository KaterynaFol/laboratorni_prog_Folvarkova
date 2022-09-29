//ignor oshibok//
#define _CRT_SECURE_NO_WARNINGS
#define _VCRUNTIME_DISABLED_WARNINGS
//ignor oshibok//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double num_comput_integral_l_re(double left_boundary_a, double right_boundary_b, unsigned int intervals);
double num_comput_integral_r_re(double left_boundary_a, double right_boundary_b, unsigned int intervals);
double num_comput_integral_Simps(double left_boundary_a, double right_boundary_b, unsigned int intervals);
double num_comput_integral_Trapecia(double left_boundary_a, double right_boundary_b, unsigned int intervals);
double integrand_expression(double x);

int main()
{
	double left_boundary_a = -1, right_boundary_b = 3; // obmezhennya Syla
	double measurement_error = 0, i1 = 0, i2 = 0;
	int intervals, var, i;
	double integral_s = 0;

	while (1)
	{
		//vvod
		/*printf("\n\tEnter the left boundary \n X(first)=");
		scanf("%lf", &left_boundary_a);
		printf("\n\tEnter the right boundary \n X(last)=");
		scanf("%lf", &right_boundary_b);*/
		//vvod

		printf("\n\tThe left boundary a = %.2lf", left_boundary_a);
		printf("\n\tThe right boundary b = %.2lf", right_boundary_b);


		//validacia
		do
		{
			printf("\tEnter the number of partition intervals (N>0)\nN=");
			scanf("%u", &intervals);
		} while (intervals <= 0);
		//validacia

		printf("\n\tEnter the measurment error of integration\n Measurment error=");
		scanf("%lf", &measurement_error);
		do
		{
			printf("\nChoose the method of calculating:\n");
			printf("\t1. By Left Rectangles :\n");
			printf("\t2. By Right Rectangles:\n");
			printf("\t4. By ntegral_Simps's method (parabola method):\n");
			scanf("%u", &var);
			if (var != 1 && var != 2 && var != 3 && var != 4)
				printf("\nYou are mistaken\n");
		} while (var != 1 && var != 2 && var != 3 && var != 4);
		system("cls");
		switch (var)
		{
		case 1:
		{
			integral_s = num_comput_integral_l_re(left_boundary_a, right_boundary_b, intervals);
			printf("\n\n\t*Left Rectangles method*\n");
			printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral = %.8lf \n\tN = %d", left_boundary_a, right_boundary_b, integral_s, intervals);
		}
		break;

		case 2:
		{
			printf("\n\n\t======*Right Rectangles method*======\n");
			i1 = num_comput_integral_r_re(left_boundary_a, right_boundary_b, intervals);
			//while real eror < need eror
			for (i = 0; i < 2; i++)
			{
				if (i == 1)
				{
					intervals += 2;
					i2 = num_comput_integral_r_re(left_boundary_a, right_boundary_b, intervals);
					if (fabs(i1 - i2) <= measurement_error)
						break;
				}
				else
				{
					i = 0;
				}
			}
			//while real eror < need eror
			printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral = %.8lf \n\tN = %d", left_boundary_a, right_boundary_b, i2, intervals);
		}
		break;
		case 3:
		{
			integral_s = num_comput_integral_Trapecia(left_boundary_a, right_boundary_b, intervals);
			printf("\n\n\t======*num_comput_integral_Trapecia method *======\n");
			printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral = %.8lf \n\tN = %d", left_boundary_a, right_boundary_b, integral_s, intervals);
		}
		break;
		case 4:
		{
			integral_s = num_comput_integral_Simps(left_boundary_a, right_boundary_b, intervals);
			printf("\n\n\t======*num_comput_integral_Simps's method *======\n");
			printf("\n\ta = %.2lf \n\tb = %.2lf \n\tIntegral = %.8lf \n\tN = %d", left_boundary_a, right_boundary_b, integral_s, intervals);
		}
		break;
		}
	}
	return 0;
}
// ���� �������, �� ������ ���������� �������� ���������� �����������
// ��������� ��������� �������.
// � ����� ��������, ���������� ���� ��������� ������ ������.
// ��� ����� ������ ������������ ���� ��������� �������.
// ���� ������� ������� ���� ��������� ��������� ���������.
double num_comput_integral_l_re(double left_boundary_a, double right_boundary_b, unsigned int intervals)
{
	double integral_s = 0, x = 0, h;
	unsigned int i;
	h = (right_boundary_b - left_boundary_a) / intervals;
	x = left_boundary_a; //x(n=0)
	for (i = 0; i <= (intervals - 1); i++)
	{
		integral_s += integrand_expression(x);
		x += h;
	}
	return integral_s * h;
}
double num_comput_integral_r_re(double left_boundary_a, double right_boundary_b, unsigned int intervals)
{
	double integral_s = 0, x = 0, h;
	unsigned int i;
	h = (right_boundary_b - left_boundary_a) / intervals;
	x = left_boundary_a + h; //x(n=1)
	for (i = 0; i <= intervals; i++)
	{
		integral_s += integrand_expression(x);
		x += h;
	}
	return integral_s * h;
}
double num_comput_integral_Trapecia(double left_boundary_a, double right_boundary_b, unsigned int intervals)
{
	double integral_s = 0, x = 0, h;
	unsigned int i;
	h = (right_boundary_b - left_boundary_a) / intervals;
	x = left_boundary_a + h; //x(n=1)
	for (i = 0; i <= (intervals - 1); i++)
	{
		integral_s += (integrand_expression(x) + integrand_expression(x + h)) / 2;
		x += h;
	}
	return integral_s * h;
}
double num_comput_integral_Simps(double left_boundary_a, double right_boundary_b, unsigned int intervals)
{
	double integral_s = 0, summ = 0, x = 0, h;
	unsigned int i;
	h = (right_boundary_b - left_boundary_a) / intervals;
	x = left_boundary_a; //x(n=0)
	integral_s = integrand_expression(x);
	x += h; //x(n=1)
	for (i = 1; i <= (intervals - 1); i += 2)
	{
		summ += integrand_expression(x);
		x += h;
	}
	integral_s += 4 * summ;
	summ = 0;
	x = left_boundary_a + 2 * h; //x(n=2)
	for (i = 2; i <= (intervals - 2); i += 2)
	{
		summ += integrand_expression(x);
		x += h;
	}
	integral_s += 2 * summ;
	return integral_s * h / 3;
}
double integrand_expression(double x) // ������� �������   X0
{
	return pow(x, 4) + 3 * x;// Syla function
}
