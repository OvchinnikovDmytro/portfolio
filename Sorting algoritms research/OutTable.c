#include <stdio.h>
#include <stdlib.h>

#include "OutTable.h"

void OutTable3D(int P,int N,int M,float SelectOrder, float SelectRandom, float SelectBackOrder, float ExchangeOrder, float ExchangeRandom, float ExchangeBackOrder, float ShellOrder, float ShellRandom, float ShellBackOrder)
{ //процедура створення таблиці вимірів часу роботи алгоритмів сортування
    printf("A[%d][%d][%d]\n",P,N,M);
    printf("%7s \t %7s \t %7s \t %7s \n"," ", "Order", "Random", "Backorder");
    printf("%7s \t %7.2f \t %7.2f \t %7.2f \n", "SelectSort", SelectOrder, SelectRandom, SelectBackOrder);
    printf("%7s \t %7.2f \t %7.2f \t %7.2f \n", "ExchangeSort", ExchangeOrder, ExchangeRandom, ExchangeBackOrder);
    printf("%7s \t %7.2f \t %7.2f \t %7.2f \n", "ShellSort", ShellOrder, ShellRandom, ShellBackOrder);
    printf("\n\n");
}

void OutTable(int M,float SelectOrder, float SelectRandom, float SelectBackOrder, float ExchangeOrder, float ExchangeRandom, float ExchangeBackOrder, float ShellOrder, float ShellRandom, float ShellBackOrder)
{ //процедура створення таблиці вимірів часу роботи алгоритмів сортування
    printf("A[%d]\n",M);
    printf("%7s \t %7s \t %7s \t %7s \n"," ", "Order", "Random", "Backorder");
    printf("%7s \t %7.2f \t %7.2f \t %7.2f \n", "SelectSort", SelectOrder, SelectRandom, SelectBackOrder);
    printf("%7s \t %7.2f \t %7.2f \t %7.2f \n", "ExchangeSort", ExchangeOrder, ExchangeRandom, ExchangeBackOrder);
    printf("%7s \t %7.2f \t %7.2f \t %7.2f \n", "ShellSort", ShellOrder, ShellRandom, ShellBackOrder);
    printf("\n\n");
}

void Print(int ***A,int P, int N, int M)//процедура виводу 3 вимірного масиву
{
    for(int k=0;k<P;k++)
    {
        for(int i=0; i<N; i++)
        {
            for(int j=0;j<M;j++)
            {
                printf(" %4d",A[k][i][j]);
            }
            printf("\n");
        }
        printf("\n\n\n");
    }
}
