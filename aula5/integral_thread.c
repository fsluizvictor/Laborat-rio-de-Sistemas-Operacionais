#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

double integral = 0.0;

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

void *funcao1()
{
    double area1 = CalculaArea(0.0, 0.5, 500000000 / 2);
    integral += area1;
    return NULL;
}

void *funcao2()
{
    double area2 = CalculaArea(0.5, 1, 500000000 / 2);
    integral += area2;
    return NULL;
}

int main(int argc, char const *argv[])
{
    printf("\tDESENVOLVIDO POR: LUIZ VICTOR FERREIRA SANTOS\n");

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, funcao1, NULL);
    pthread_create(&thread2, NULL, funcao2, NULL);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("A área da curva é:\n%.12lf\n", integral);

    return 0;
}
