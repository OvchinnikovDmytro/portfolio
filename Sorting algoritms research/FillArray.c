#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "FillArray.h"
#include "Menu.h"

void FillArrayOrder(int ***A, int P, int N, int M)// ��������� ���������� ������ ������������
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

void FillArrayRandom(int ***A, int P, int N, int M)// ��������� ���������� ������ ��������
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

void FillArrayBackOrder(int ***A, int P, int N, int M)// ��������� ���������� ������ �������� ������������
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
void FillVectorOrder(int *B, int N)// ��������� ���������� ������� ������������
{
    int number=0;
    for (int i = 0; i < N; i++)
    {
        B[i] = number++;
    }
}
void FillVectorRandom(int *B, int N)// ��������� ���������� ������� ��������
{
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        B[i] = rand() % N;
    }
}
void FillVectorBackOrder(int *B, int N)// ��������� ���������� ������� �������� ������������
{

    int number=N;
    for (int i = 0; i < N; i++)
    {
        B[i] = number--;
    }
}
