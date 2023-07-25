#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Test.h"
#include "FillArray.h"
#include "OutTable.h"
#include "Menu.h"


int testfill;
int testsort;
int p;
int n;
int m;
void TestMenu()//меню вибору варіанту тестування
{
    srand(time(NULL));
    system ("cls");
    printf("\nEnter size of the mas\n");
    printf("\nP = ");
    scanf("%d",&p);
    printf("\nN = ");
    scanf("%d",&n);
    printf("\nM = ");
    scanf("%d",&m);
    system("cls");
    int ***A;  // оголошення динамічного тривимірного масиву
    A = (int***) malloc(p*sizeof(int**));
    for (int k = 0; k < p; k++)
    {
        A[k] = (int**) malloc(n*sizeof(int*));
        for (int i = 0; i < n; i++)
        {
            A[k][i] = (int*) malloc(m*sizeof(int));
        }
    }
    printf("Select a menu item\n");
    printf("1. Select Sort\n");
    printf("2. Exchange Sort\n");
    printf("3. Shell Sort\n");
    printf("4. Exit\n");
    while(1)
    {
        printf("\nEnter a number: ");
        scanf("%d", &testsort);
        switch(testsort)
        {
            case 1: Select(A,p,n,m);return; break;
            case 2: Exchange(A,p,n,m);return; break;
            case 3: Shell(A,p,n,m); break;
            case 4: MenuType();return; break;
            default: printf ("Wrong number.Try again\n");
        }
    }
}

void Select(int ***A,int p, int n, int m)//Тестування алгоритму вибору 2
{
    system ("cls");
    printf("\n\nSelect a menu item\n");
    printf("1. Order\n");
    printf("2. Random\n");
    printf("3. BackOrder\n");
    printf("4. Exit\n");
    while(1)//Вибір заповненності масиву
    {
        printf("\nEnter a number: ");
        scanf("%d", &testfill);
        if(testfill==1)
        {
            FillArrayOrder(A,p,n,m);
            break;
        }
        else if(testfill==2)
        {
            FillArrayRandom(A,p,n,m);
            break;
        }
        else if(testfill==3)
        {
            FillArrayBackOrder(A,p,n,m);
            break;
        }
        else if (testfill==4)
            TestMenu();
        else
            printf ("Wrong number.Try again\n");
    }
    printf("\nBEFORE\n");
    Print(A,p,n,m);
    //Сортування алгоритсос вибору №2
    int imin,tmp;
    for(int k=0;k<p;k++)
    {
        for(int s=0; s<m-1; s++)
        {
            imin=s;
            for(int j=s+1; j<m; j++)
                if (A[k][0][j]<A[k][0][imin])
                {
                    imin=j;
                }
            for (int i=0;i<n;i++)
            {
                tmp=A[k][i][imin];
                A[k][i][imin]=A[k][i][s];
                A[k][i][s]=tmp;
            }
        }
    }

    printf("\nAFTER\n");
    Print(A,p,n,m);
        for (int k=0; k<p; k++)//звільнення пам'яті від масиву
    {
        for (int i=0; i<n; i++)
        {
            free(A[k][i]);
        }
        free(A[k]);
     }
    free(A);
    getch();
    MenuType();
}

void Exchange(int ***A,int p, int n, int m)//Тестування алгоритму обміну 2 з прапорцем
{
    system ("cls");
    printf("\n\nSelect a menu item\n");
    printf("1. Order\n");
    printf("2. Random\n");
    printf("3. BackOrder\n");
    printf("4. Exit\n");
    while(1)//Вибір варіанту заповнення
    {
        printf("\nEnter a number: ");
        scanf("%d", &testfill);
        if(testfill==1)
        {
            FillArrayOrder(A,p,n,m);
            break;
        }
        else if(testfill==2)
        {
            FillArrayRandom(A,p,n,m);
            break;
        }
        else if(testfill==3)
        {
            FillArrayBackOrder(A,p,n,m);
            break;
        }
        else if (testfill==4)
            TestMenu();
        else
            printf ("Wrong number.Try again\n");
    }
    printf("\nBEFORE\n");
    Print(A,p,n,m);
    //Сортування методом обміну №2 з флажком
    int R, flag, tmp;
    for(int k=0;k<p;k++)
    {
        R=m-1; flag=1;
        while(flag == 1)
        {
            flag=0;
            for(int j=0; j<R; j++)
            {
                if (A[k][0][j]>A[k][0][j+1])
                {
                    for (int i=0;i<n;i++)
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

    printf("\nAFTER\n");
    Print(A,p,n,m);
    for (int k=0; k<p; k++)//звільнення пам'яті від масиву
    {
        for (int i=0; i<n; i++)
        {
            free(A[k][i]);
        }
        free(A[k]);
     }
    free(A);
    getch();
    MenuType();
}


void Shell(int ***A,int p, int n, int m)//Тестування алгоритму Шелла 2
{
    system ("cls");
    printf("\n\nSelect a menu item\n");
    printf("1. Order\n");
    printf("2. Random\n");
    printf("3. BackOrder\n");
    printf("4. Exit\n");
    while(1)//Вибір варіанту заповнення масиву
    {
        printf("\nEnter a number: ");
        scanf("%d", &testfill);
        if(testfill==1)
        {
            FillArrayOrder(A,p,n,m);
            break;
        }
        else if(testfill==2)
        {
            FillArrayRandom(A,p,n,m);
            break;
        }
        else if(testfill==3)
        {
            FillArrayBackOrder(A,p,n,m);
            break;
        }
        else if (testfill==4)
            TestMenu();
        else
            printf ("Wrong number.Try again\n");
    }
    printf("\nBEFORE\n");
    Print(A,p,n,m);
    //Виконання сортування Шелла №2
    int tmp, t, j, k;
    if (m<4) t=1;
    else
        t=(int)log2f((float)m)-1;
    int Stages[t];
    Stages[t-1]=1;
    for (int i=t-2; i>=0; i--)
        Stages[i]=2*Stages[i+1]+1;
    for(int K=0;K<p;K++)
    {
        for (int x=0; x<t; x++)
        {
            k=Stages[x];
            for (int i=k; i<m; i++)
            {
                j=i;
                while (j>=k && A[K][0][j]<A[K][0][j-k])
                {
                    for (int z=0;z<n;z++)
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
    printf("\nAFTER\n");
    Print(A,p,n,m);
    for (int k=0; k<p; k++)//звільнення пам'яті від масиву
    {
        for (int i=0; i<n; i++)
        {
            free(A[k][i]);
        }
        free(A[k]);
    }
    free(A);
    getch();
    MenuType();
}
