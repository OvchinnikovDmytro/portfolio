#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Sort.h"


clock_t Select2Sort(int ***A,  int P, int N, int M)// функція сортування 3-х вимірного масиву методом прямого вибору
{
    int imin,tmp;
    clock_t time_start, time_stop;

    time_start = clock();

    for(int k=0;k<P;k++)
    {
        for(int s=0; s<M-1; s++)
        {
            imin=s;
            for(int j=s+1; j<M; j++)
                if (A[k][0][j]<A[k][0][imin])
                {
                    imin=j;
                }
            for (int i=0;i<N;i++)
            {
                tmp=A[k][i][imin];
                A[k][i][imin]=A[k][i][s];
                A[k][i][s]=tmp;
            }
        }
    }

    time_stop = clock();

    return time_stop - time_start;
}

clock_t SelectSort(int *A, int N)// функція сортування вектору методом прямого вибору
{
    int imin, tmp;
    clock_t time_start, time_stop;

    time_start = clock();

    for(int s=0; s<N-1; s++)
    {
        imin=s;
        for(int i=s+1; i<N; i++)
        {
            if (A[i]<A[imin]) imin=i;
        }
            tmp=A[imin];
            A[imin]=A[s];
            A[s]=tmp;
    }

    time_stop = clock();

    return time_stop - time_start;
}

clock_t Exchange2Sort(int ***A, int P, int N, int M)// функція сортування 3-х вимірного масиву методом прямого обміну з використанням прапорця
{
    int R, flag, tmp;
    clock_t time_start, time_stop;

    time_start = clock();

    for(int k=0;k<P;k++)
    {
        R=M-1; flag=1;
        while(flag == 1)
        {
            flag=0;
            for(int j=0; j<R; j++)
            {
                if (A[k][0][j]>A[k][0][j+1])
                {
                    for (int i=0;i<N;i++)
                    {
                        tmp=A[k][i][j];
                        A[k][i][j]=A[k][i][j+1];
                        A[k][i][j+1]=tmp;
                    }
                    flag=1;
                }
            }
            R--;
        }
    }

    time_stop = clock();

    return time_stop - time_start;
}

clock_t Shell_2Sort(int ***A,int P, int N, int M)// функція сортування 3-х вимірного масиву методом сортування Шелла (спосіб реалізації на основі гібридного алгоритму «вставка-обмін)
{
    int tmp, t, j, k;
    clock_t time_start, time_stop;
    if (M<4) t=1;
    else
        t=(int)log2f((float)M)-1;
    int Stages[t];

    time_start = clock();

    if (M<4) t=1;
    else
        t=(int)log2f((float)M)-1;
    Stages[t-1]=1;
    for (int i=t-2; i>=0; i--)
        Stages[i]=2*Stages[i+1]+1;
    for(int K=0;K<P;K++)
    {
        for (int p=0; p<t; p++)
        {
            k=Stages[p];
            for (int i=k; i<M; i++)
            {
                j=i;
                while (j>=k && A[K][0][j]<A[K][0][j-k])
                {
                    for (int z=0;z<N;z++)
                    {
                        tmp=A[K][z][j];
                        A[K][z][j]=A[K][z][j-k];
                        A[K][z][j-k]=tmp;
                    }
                    j=j-k;
                }
            }
        }
    }

    time_stop = clock();

    return time_stop - time_start;
}



clock_t ExchangeSort(int *A, int N)// функція сортування вектору методом прямого обміну з використанням прапорця
{
    int R, flag, tmp;
    clock_t time_start, time_stop;

    time_start = clock();

    R=N-1; flag=1;
    while(flag == 1)
    {
        flag=0;
        for(int i=0; i<R; i++)
            if (A[i]>A[i+1])
            {
                tmp=A[i];
                A[i]=A[i+1];
                A[i+1]=tmp;
                flag=1;
            }
        R--;
    }

    time_stop = clock();

    return time_stop - time_start;
}

clock_t ShellSort(int *A, int N)// функція сортування вектору методом сортування Шелла (спосіб реалізації на основі гібридного алгоритму «вставка-обмін)
{
    int tmp, t, j, k;
    clock_t time_start, time_stop;
    if (N<4) t=1;
    else t=(int)log2f((float)N)-1;
    int Stages[t];

    time_start = clock();

    if (N<4) t=1;
    else t=(int)log2f((float)N)-1;

    Stages[t-1]=1;
    for (int i=t-2; i>=0; i--)
        Stages[i]=2*Stages[i+1]+1;
    for (int p=0; p<t; p++)
    {
        k=Stages[p];
        for (int i=k; i<N; i++)
        {
            j=i;
            while (j>=k && A[j]<A[j-k])
            {
                tmp=A[j];
                A[j]=A[j-k];
                A[j-k]=tmp;
                j=j-k;
            }
        }
    }

    time_stop = clock();

    return time_stop - time_start;
}

