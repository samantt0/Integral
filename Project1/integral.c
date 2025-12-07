#include <stdio.h>
#include <math.h>

double f(double x) //функция для записи кривой
{
    return x * x * x + x * x - 5 * x + 3;
}

double trapezoid(double a, double b, int n) //функция для метода трапеций
{
    double h = (b - a) / n; //кол-во разбиений отрезка интегрирования
    double sum = 0;

    for (int i = 1; i < n; i++)
    {
        double x = a + i * h;
        sum += fabs(f(x));
    }

    //сумма площадей трапеций
    return (fabs(f(a)) + 2 * sum + fabs(f(b))) * h / 2;
    //точки помимо крайних используются два раза

}

double fault(double a, double b, int n) //функция погрешности
{
    double integ_1 = trapezoid(a, b, n);
    double integ_2 = trapezoid(a, b, 2 * n);
    printf("First integral (n): %lf\n", integ_1);
    printf("Second integral (2n): %lf\n", integ_2);
    return fabs(integ_1 - integ_2);
}


int main(void)
{
    int choice;
    double a = 0., b = 1.;
    int n = 1;

    do {
        system("cls"); //очистка экрана
        printf("\n----Program \"Integral\". Menu----\n");
        printf("Please, input the item.\n");
        printf("1. Lower limit of integration (default - 0). \
Current value: %lf\n", a);
        printf("2. Upper limit of Integration (default - 1). \
Current value: %lf\n", b);
        printf("3. Number of trapezoids (default - 1). \
Current value: %d\n", n);
        printf("4. Derive the integral.\n");
        printf("5. Derive the fault.\n");
        printf("6. End program.\n");
        printf("Your choice: ");
        scanf_s("%d", &choice);
        printf("\n");
        printf("-----------------\n");
        printf("\n");

        switch (choice)
        {
        case 1: //ввод нижнего предела
            printf("Enter Lower limit a: ");
            if (scanf_s("%lf", &a) != 1)
            {
                printf("Invalid input\n");
                a = 0.;
                while (getchar() != '\n');
            }
            break;

        case 2: //ввод верхнего предела
            printf("Enter Upper limit b: ");
            if (scanf_s("%lf", &b) != 1)
            {
                printf("Invalid input\n");
                b = 1.;
                while (getchar() != '\n');
            }
            break;

        case 3: //ввод трапеций
            printf("Enter Number of trapezoids n: ");
            if (scanf_s("%d", &n) != 1 || n <= 0)
            {
                printf("Invalid input\n");
                n = 1;
                while (getchar() != '\n');
            }
            break;

        case 4: //вывод интеграла
            if (a >= b)
            {
                printf("Error: Upper limit \"<\" or \"=\" than Lower limit.\n");
                break;
            }
            if (n < 2) printf("Warning, number of trapezoids \
is too small for accuracy.\n");

            double integ = trapezoid(a, b, n);
            printf("Integral value (with n trapezoids): %lf\n", integ);
            break;

        case 5: //вывод погрешности
            if (a >= b)
            {
                printf("Error: Upper limit \"<\" or \"=\" than Lower limit.\n");
                break;
            }
            if (n < 2) printf("Warning, number of trapezoids \
is too small for accuracy.\n");
            double accurate_integral = trapezoid(a, b, 2 * n);
            double absolute_fault = fault(a, b, n);
            double percent_fault = (absolute_fault / fabs(accurate_integral)) 
                * 100;

            printf("\n");
            printf("-----------------\n");
            printf("\n");
            printf("Absolute fault: %lf\n", absolute_fault);
            printf("Percent fault: %.3lf%%\n", percent_fault);
            break;

        case 6: //завершение
            break;

        }
        if (choice != 6)
        {
            printf("\n");
            printf("\n----Press Enter to continue...----");
            while (getchar() != '\n');  //очистка буфера
            getchar();
        }

    } while (choice != 6);


    return 0;
}