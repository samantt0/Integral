#include <stdio.h>
#include <math.h>

double f(double x) //функция для записи кривой
{
    return x * x * x + x * x - 5 * x + 3;
}

double find(double left, double right) //функция для точки пересеч. с OX
{
    double mid;
    while (right - left > 1e-7) {
        mid = (left + right) / 2;
        if (f(left) * f(mid) <= 0)
            right = mid;
        else
            left = mid;
    }
    return (left + right) / 2;
}

double trapezoid(double a, double b, int n) //функция для метода трапеций
{
    double h = (b - a) / n; //кол-во разбиений отрезка интегрирования
    double area = 0;

    for (int i = 0; i < n; i++)
    {
        double x1 = a + i * h;
        double x2 = x1 + h;

        double y1 = f(x1);
        double y2 = f(x2);

        if (y1 >= 0 && y2 >= 0)
            area += (y1 + y2) * h / 2;
        else if (y1 <= 0 && y2 <= 0)
            continue;
        else //меняет знак
        {
            double xr = find(x1, x2);
            double yr = 0;
            double width;

            if (y1 > 0) {
                width = xr - x1;
                area += (y1 + yr) * width / 2;
            }
            if (y2 > 0) {
                width = x2 - xr;
                area += (yr + y2) * width / 2;
            }
        }

        return area;
    }

}

double fault(double a, double b, int n) //функция погрешности
{
    double integ_1 = trapezoid(a, b, n);
    double integ_2 = trapezoid(a, b, 2 * n);
    printf("First integral: %lf\n", integ_1);
    printf("Second integral: %lf\n", integ_2);
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

