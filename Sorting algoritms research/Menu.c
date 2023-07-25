#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include "OutTable.h"
#include "FillArray.h"
#include "Measurement.h"
#include "Sort.h"
#include "Test.h"
#include "Menu.h"

int sortnum;
int fillnum;

float Select2_Order;
float Select2_Random;
float Select2_BackOrder;
float Exchange2_Order;
float Exchange2_Random;
float Exchange2_BackOrder;
float Shell_2_Order;
float Shell_2_Random;
float Shell_2_BackOrder;


int P = 2;
int N = 10;
int M = 200;

void Size(int ***A)//процедура зміни розміру масива
{
    system ("cls");
    printf("\nCurrent size A[%d][%d][%d] \n\n",P,N,M);
    for (int k=0; k<P; k++)//звільнення пам'яті від масиву
    {
        for (int i=0; i<N; i++)
        {
            free(A[k][i]);
        }
        free(A[k]);
    }
    printf("\nEnter size of the mas\n");//Задання розмірів нового масива
    printf("\nP = ");
    scanf("%d",&P);
    printf("\nN = ");
    scanf("%d",&N);
    printf("\nM = ");
    scanf("%d",&M);
    system("cls");
    MenuType();
}
void MenuType()//процедура для вибору користувачем того що він хоче зробити
{
    int ***Arr3D;  // оголошення динамічного тривимірного масиву
    Arr3D = (int***) malloc(P*sizeof(int**));
    for (int k = 0; k < P; k++)
    {
        Arr3D[k] = (int**) malloc(N*sizeof(int*));
        for (int i = 0; i < N; i++)
        {
            Arr3D[k][i] = (int*) malloc(M*sizeof(int));
        }
    }
    int B[P*N*M];//Оголошення вектору
    int type;
    system ("cls");
    printf("Select a menu item\n");//Вивід пунктів меню
    printf("1. Vector\n");
    printf("2. Paralelepiped\n");
    printf("3. Algorithm check\n");
    printf("4. Size change\n");
    while(1)
    {
        printf("\nEnter a number: ");
        scanf("%d", &type);
        switch(type)//Виклик пунктів меню
        {
            case 1: MenuSort(B,P*N*M); break;
            case 2: MenuSort3D(Arr3D, P, N, M); break;
            case 3: TestMenu();  break;
            case 4: Size(Arr3D); break;
            default: printf ("Wrong number.Try again\n");
        }
    }
}

void MenuSort(int *B, int M)//процедура для вибору користувачем алгоритму сортування вектора
{
    sortnum = 0;
    system ("cls");
    printf("Select a menu item\n");//Вивід пунктів меню
    printf("1. Select Sort\n");
    printf("2. Exchange Sort\n");
    printf("3. Shell Sort\n");
    printf("4. Packet mode\n");
    printf("5. Exit\n");
    while(1)
    {
        printf("\nEnter a number: ");
        scanf("%d", &sortnum);
        switch(sortnum)//Виклик пунктів меню
        {
            case 1: MenuFill(B, M); break;
            case 2: MenuFill(B, M); break;
            case 3: MenuFill(B, M); break;
            case 4: PackageMode(B, M); break;
            case 5: MenuType(); break;
            default: printf ("Wrong number.Try again\n");
        }
    }
}

void MenuSort3D(int ***A, int P, int N, int M)//процедура для вибору користувачем алгоритму сортування для паралелепіпеда
{
    sortnum = 0;
    system ("cls");
    printf("Select a menu item\n");//Вивід пунктів меню
    printf("1. Select Sort\n");
    printf("2. Exchange Sort\n");
    printf("3. Shell Sort\n");
    printf("4. Packet mode\n");
    printf("5. Exit\n");
    while(1)
    {
        printf("\nEnter a number: ");
        scanf("%d", &sortnum);
        switch(sortnum)//Виклик пунктів меню
        {
            case 1: MenuFill3D(A, P, N, M); break;
            case 2: MenuFill3D(A, P, N, M); break;
            case 3: MenuFill3D(A, P, N, M); break;
            case 4: PackageMode3D(A, P, N, M); break;
            case 5: MenuType(); break;
            default: printf ("Wrong number.Try again\n");
        }
    }
}

void MenuFill(int *B, int M)//процедура для вибору користувачем методу заповнення вектору
{
    system ("cls");
    fillnum = 0;
    printf("Select a menu item\n");//Вивід пунктів меню
    printf("1. Ordered\n");
    printf("2. Random\n");
    printf("3. BackOrdered\n");
    printf("4. Exit\n");
    while(1)
    {
        printf("\nEnter a number: ");
        scanf("%d", &fillnum);
        switch(fillnum)//Виклик пунктів меню
        {
            case 1: SoloMode(B, M); break;
            case 2: SoloMode(B, M); break;
            case 3: SoloMode(B, M); break;
            case 4: MenuSort(B, M); break;
            default: printf ("Wrong number.Try again\n");
        }
    }
}

void MenuFill3D(int ***A, int P, int N, int M)//процедура для вибору користувачем методу заповнення масиву
{
    system ("cls");
    fillnum = 0;
    printf("Select a menu item\n");//Вивід пунктів меню
    printf("1. Ordered\n");
    printf("2. Random\n");
    printf("3. BackOrdered\n");
    printf("4. Exit\n");
    while(1)
    {
        printf("\nEnter a number: ");
        scanf("%d", &fillnum);
        switch(fillnum)//Виклик пунктів меню
        {
            case 1: SoloMode3D(A, P, N, M); break;
            case 2: SoloMode3D(A, P, N, M); break;
            case 3: SoloMode3D(A, P, N, M); break;
            case 4: MenuSort3D(A, P, N, M); break;
            default: printf ("Wrong number.Try again\n");
        }
    }
}

void PackageMode(int *B, int M)//процедура для запуску пакетного режиму вимірювання часу роботи алгоритмів сортування векторів
{

    srand(time(NULL));
    char button;

    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування впорядкованого вектора методом вибору
    {
        FillVectorOrder(B, M);
        Res[i] = SelectSort(B, M);
    }
    Select2_Order = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування рандомного вектора методом вибору
    {
        FillVectorRandom(B, M);
        Res[i] = SelectSort(B, M);
    }
    Select2_Random = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування обернено впорядкованого вектора методом вибору
    {
        FillVectorBackOrder(B, M);
        Res[i] = SelectSort(B, M);
    }
    Select2_BackOrder = MeasurementProcessing();



    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування впорядкованого вектора методом обміну
    {
        FillVectorOrder(B, M);
        Res[i] = ExchangeSort(B, M);
    }
    Exchange2_Order = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування рандомного вектора методом обміну
    {
        FillVectorRandom(B, M);
        Res[i] = ExchangeSort(B, M);
    }
    Exchange2_Random = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування обернено впорядкованого вектора методом обміну
    {
        FillVectorBackOrder(B, M);
        Res[i] = ExchangeSort(B, M);
    }
    Exchange2_BackOrder = MeasurementProcessing();



    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування впорядкованого вектора методом Шелла
    {
        FillVectorOrder(B, M);
        Res[i] = ShellSort(B, M);
    }
    Shell_2_Order = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування рандомного вектора методом Шелла
    {
        FillVectorRandom(B, M);
        Res[i] = ShellSort(B, M);
    }
    Shell_2_Random = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування оберненно впорядкованого вектора методом Шелла
    {
        FillVectorBackOrder(B, M);
        Res[i] = ShellSort(B, M);
    }
    Shell_2_BackOrder = MeasurementProcessing();


    system ("cls");
    OutTable(M,Select2_Order, Select2_Random, Select2_BackOrder, Exchange2_Order, Exchange2_Random, Exchange2_BackOrder, Shell_2_Order, Shell_2_Random, Shell_2_BackOrder); //функція побудови таблиці результатів вимірювань
    printf("\nPress Space to go to main menu");
    while(1)// цикл для виходу користувача у головне меню
    {
        char button = getch();
        if(button == ' ')
        {
           MenuType();
        }
    }
}

void PackageMode3D(int ***A, int P, int N, int M)//процедура для запуску пакетного режиму вимірювання часу роботи алгоритмів сортування тривимірного масиву
{
    srand(time(NULL));
    char button;

    for (int i = 0; i < measurements_number; i++) //Запуск вимірювання часу роботи алгоритму сортування впорядкованого масиву методом вибору
    {
        FillArrayOrder(A, P, N, M);
        Res[i] = Select2Sort(A, P, N, M);
    }
    Select2_Order = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування рандомного масиву методом вибору
    {
        FillArrayRandom(A, P, N, M);
        Res[i] = Select2Sort(A, P, N, M);
    }
    Select2_Random = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування обернено впорядкованого масиву методом вибору
    {
        FillArrayBackOrder(A, P, N, M);
        Res[i] = Select2Sort(A, P, N, M);
    }
    Select2_BackOrder = MeasurementProcessing();



    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування впорядкованого масиву методом обміну
    {
        FillArrayOrder(A, P, N, M);
        Res[i] = Exchange2Sort(A, P, N, M);
    }
    Exchange2_Order = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування рандомного масиву методом обміну
    {
        FillArrayRandom(A, P, N, M);
        Res[i] = Exchange2Sort(A, P, N, M);
    }
    Exchange2_Random = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування обернено впорядкованого масиву методом обміну
    {
        FillArrayBackOrder(A, P, N, M);
        Res[i] = Exchange2Sort(A, P, N, M);
    }
    Exchange2_BackOrder = MeasurementProcessing();



    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування впорядкованого масиву методом Шелла
    {
        FillArrayOrder(A, P, N, M);
        Res[i] = Shell_2Sort(A, P, N, M);
    }
    Shell_2_Order = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++)//Запуск вимірювання часу роботи алгоритму сортування рандомного масиву методом Шелла
    {
        FillArrayRandom(A, P, N, M);
        Res[i] = Shell_2Sort(A, P, N, M);
    }
    Shell_2_Random = MeasurementProcessing();
    for (int i = 0; i < measurements_number; i++) //Запуск вимірювання часу роботи алгоритму сортування оберненно впорядкованого масиву методом Шелла
    {
        FillArrayBackOrder(A, P, N, M);
        Res[i] = Shell_2Sort(A, P, N, M);
    }
    Shell_2_BackOrder = MeasurementProcessing();


    system ("cls");
    OutTable3D(P,N,M,Select2_Order, Select2_Random, Select2_BackOrder, Exchange2_Order, Exchange2_Random, Exchange2_BackOrder, Shell_2_Order, Shell_2_Random, Shell_2_BackOrder); //функція побудови таблиці результатів вимірювань
    printf("\nPress Space to go to main menu");
    for (int k=0; k<P; k++)//звільнення пам'яті від масиву
    {
        for (int i=0; i<N; i++)
        {
            free(A[k][i]);
        }
        free(A[k]);
    }
    while(1) // цикл для виходу користувача у головне меню
    {
        char button = getch();
        if(button == ' ')
        {
           MenuType();
        }
    }
}

void SoloMode(int *B, int M)//процедура для запуску вибраного режиму вимірювання часу роботи алгоритмів для вектору
{

    srand(time(NULL));

    float SoloTime;
    char button;
    if(sortnum == 1)//перевірка який саме алгоритм вибрав користувач(у данному випадку алгоритм сортування вибору)
    {
        if(fillnum == 1)//перевірка як саме користувач хоче заповнити масив(у данному випадку впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillVectorOrder(B, M);
                Res[i] = SelectSort(B, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 2)//перевірка як саме користувач хоче заповнити масив(у данному випадку рандомно)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillVectorRandom(B, M);
                Res[i] = SelectSort(B, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 3)//перевірка як саме користувач хоче заповнити масив(у данному випадку обернено впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillVectorBackOrder(B, M);
                Res[i] = SelectSort(B, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
    }
    else if(sortnum == 2)//перевірка який саме алгоритм вибрав користувач(у данному випадку алгоритм сортування Обміну)
    {
        if(fillnum == 1)//перевірка як саме користувач хоче заповнити масив(у данному випадку впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillVectorOrder(B, M);
                Res[i] = ExchangeSort(B, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 2)//перевірка як саме користувач хоче заповнити масив(у данному випадку рандомно)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillVectorRandom(B, M);
                Res[i] = ExchangeSort(B, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 3)//перевірка як саме користувач хоче заповнити масив(у данному випадку обернено впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillVectorBackOrder(B, M);
                Res[i] = ExchangeSort(B, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
    }
    else if(sortnum == 3)//перевірка який саме алгоритм вибрав користувач(у данному випадку алгоритм сортування Шелла)
    {
        if(fillnum == 1)//перевірка як саме користувач хоче заповнити масив(у данному випадку впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillVectorOrder(B, M);
                Res[i] = ShellSort(B, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 2)//перевірка як саме користувач хоче заповнити масив(у данному випадку рандомно)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillVectorRandom(B, M);
                Res[i] = ShellSort(B, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 3)//перевірка як саме користувач хоче заповнити масив(у данному випадку обернено впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillVectorBackOrder(B, M);
                Res[i] = ShellSort(B, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
    }
}

void SoloMode3D(int ***A, int P, int N, int M)//процедура для запуску вибраного режиму вимірювання часу роботи алгоритмів
{

    srand(time(NULL));

    float SoloTime;
    char button;
    if(sortnum == 1)//перевірка який саме алгоритм вибрав користувач(у данному випадку алгоритм сортування вибору)
    {
        if(fillnum == 1)//перевірка як саме користувач хоче заповнити масив(у данному випадку впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillArrayOrder(A, P, N, M);
                Res[i] = Select2Sort(A, P, N, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button ==' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 2)//перевірка як саме користувач хоче заповнити масив(у данному випадку рандомно)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillArrayRandom(A, P, N, M);
                Res[i] = Select2Sort(A, P, N, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 3)//перевірка як саме користувач хоче заповнити масив(у данному випадку обернено впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillArrayBackOrder(A, P, N, M);
                Res[i] = Select2Sort(A, P, N, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
    }
    else if(sortnum == 2)//перевірка який саме алгоритм вибрав користувач(у данному випадку алгоритм сортування обміну)
    {
        if(fillnum == 1)//перевірка як саме користувач хоче заповнити масив(у данному випадку впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillArrayOrder(A, P, N, M);
                Res[i] = Exchange2Sort(A, P, N, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 2)//перевірка як саме користувач хоче заповнити масив(у данному випадку рандомно)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillArrayRandom(A, P, N, M);
                Res[i] = Exchange2Sort(A, P, N, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 3)//перевірка як саме користувач хоче заповнити масив(у данному випадку обернено впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillArrayBackOrder(A, P, N, M);
                Res[i] = Exchange2Sort(A, P, N, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
    }
    else if(sortnum == 3)//перевірка який саме алгоритм вибрав користувач(у данному випадку алгоритм сортування Шелла)
    {
        if(fillnum == 1)//перевірка як саме користувач хоче заповнити масив(у данному випадку впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillArrayOrder(A, P, N, M);
                Res[i] = Shell_2Sort(A, P, N, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 2)//перевірка як саме користувач хоче заповнити масив(у данному випадку рандомно)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillArrayRandom(A, P, N, M);
                Res[i] = Shell_2Sort(A, P, N, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
        else if(fillnum == 3)//перевірка як саме користувач хоче заповнити масив(у данному випадку обернено впорядковано)
        {
            for (int i = 0; i < measurements_number; i++)
            {
                FillArrayBackOrder(A, P, N, M);
                Res[i] = Shell_2Sort(A, P, N, M);
            }
            SoloTime = MeasurementProcessing();
            system ("cls");
            printf("Time: %f \n", SoloTime);
            printf("\nPress Space to go to main menu");
            while(1)// цикл для виходу користувача у головне меню
            {
                char button = getch();
                if(button == ' ')
                {
                   MenuType();
                }
            }
        }
    }
    for (int k=0; k<P; k++)//звільнення пам'яті від масиву
    {
        for (int i=0; i<N; i++)
        {
            free(A[k][i]);
        }
        free(A[k]);
    }
}

