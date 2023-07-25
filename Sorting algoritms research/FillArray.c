#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "FillArray.h"
#include "Menu.h"

void FillArrayOrder(int ***A, int P, int N, int M)// процедура заповнення масиву впорядковано
{
    int number = 0;
    for (int k = 0; k < P; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                A[k][i][j] = number++;
            }
        }
    }
}

void FillArrayRandom(int ***A, int P, int N, int M)// процедура заповнення масиву рандомно
{
    srand(time(NULL));
    for (int k = 0; k < P; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                A[k][i][j] = rand() % (P*N*M);
            }
        }
    }
}

void FillArrayBackOrder(int ***A, int P, int N, int M)// процедура заповнення масиву обернено впорядковано
{
    int number =  P*M*N;
    for (int k = 0; k < P; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                A[k][i][j] = number--;
            }
        }
    }
}
void FillVectorOrder(int *B, int N)// процедура заповнення вектору впорядковано
{
    int number=0;
    for (int i = 0; i < N; i++)
    {
        B[i] = number++;
    }
}
void FillVectorRandom(int *B, int N)// процедура заповнення вектору рандомно
{
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        B[i] = rand() % N;
    }
}
void FillVectorBackOrder(int *B, int N)// процедура заповнення вектору обернено впорядковано
{

    int number=N;
    for (int i = 0; i < N; i++)
    {
        B[i] = number--;
    }
}
