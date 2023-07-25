
#ifndef __Sort_H__
#define __Sort_H__

clock_t Select2Sort(int ***A,int P, int N, int M);
clock_t Exchange2Sort(int ***A,int P, int N, int M);
clock_t Shell_2Sort(int ***A,int P, int N, int M);

clock_t SelectSort(int *B, int N);
clock_t ExchangeSort(int *B, int N);
clock_t ShellSort(int *B, int N);

#endif // __Sort_H__
