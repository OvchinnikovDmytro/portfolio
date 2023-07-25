#ifndef __FillArray_H__
#define __FillArray_H__

void FillArrayOrder(int ***A,int P, int N, int M);
void FillArrayRandom(int ***A,int P, int N, int M);
void FillArrayBackOrder(int ***A,int P, int N, int M);

void FillVectorOrder(int *B, int N);
void FillVectorRandom(int *B, int N);
void FillVectorBackOrder(int *B, int N);

#endif // __FillArray_H__

