#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

double AreaTrapezio(double dx, double h1, double h2)
{
    double area;
    area = dx * (h1 + h2) / 2;
    return area;
}

double f(double x)
{
    return (4 / (1 + x * x));
}

double CalculaArea(double a, double b, int N)
{
    int i;
    double area = 0.0, dx, x1, x2, f1, f2;
    dx = (b - a) / N;
    for (i = 0; i < N; i++)
    {
        x1 = a + dx * i;
        x2 = a + dx * (i + 1);
        f1 = f(x1);
        f2 = f(x2);
        area += AreaTrapezio(dx, f1, f2);
    }
    return area;
}

int main(int argc, char const *argv[])
{
    printf("\tDESENVOLVIDO POR: LUIZ VICTOR FERREIRA SANTOS\n");
    double a = 0.0, b = 1.0, area;
    int n = 500000000;

    area = CalculaArea(a, b, n);
    printf("A área da curva é:\n%.12lf\n", area);

    return 0;
}
