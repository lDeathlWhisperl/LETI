#include <iostream>
#include <time.h>
#include <chrono>
#include "Functions.h"

using namespace std;
using namespace chrono;

int getRandomNumber(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void quicksort(int* arr, const int SIZE)
{
    int right = 0,
        left = SIZE - 1,
        mid = arr[SIZE / 2];

    do {
        while (arr[right] < mid)
            right++;

        while (arr[left] > mid)
            left--;

        if (right <= left)
        {
            int tmp = arr[right];
            arr[right] = arr[left];
            arr[left] = tmp;

            right++;
            left--;
        }
    } while (right <= left);

    if (left > 0)
        quicksort(arr, left + 1);
    if (right < SIZE)
        quicksort(&arr[right], SIZE - right);
}

void findMaxMin(int* arr, const int SIZE, int& max, int& min)
{
    for (int i = 0; i < SIZE; i++)
    {
        if (arr[i] > max)
            max = arr[i];
        if (arr[i] < min)
            min = arr[i];
    }
}

int binarySearch(int search, int* arr, const int SIZE, int& left, int& right)
{
    while (left < right)
    {
        int mid = left + (right - left) / 2;
        search <= arr[mid] ? right = mid : left = mid + 1;
    }
    return right;
}

int commonSearch(int search, int* arr, const int SIZE)
{
    for (int i = 0; i < SIZE; i++)
        if (arr[i] == search)
            return i;
    return -1;
}

void arrOutput(int* arr, const int SIZE, int num1, int num2)
{
    int count = 0;
    std::cout << "\nThe array looks like this now:\n\n";
    for (int i = 0; i < SIZE; i++)
    {
        count++;
        if (i % 10 != 0)
            cout << '\t';

        if (i == num1 || i == num2)
        {
            cout << "\x1b[31m" << '[' << i << ']' << " = " << arr[i] << "\x1b[0m" << ' ';
            continue;
        }

        cout << '[' << i << ']' << " = " << arr[i] << ' ';

        if (count % 10 == 0)
            putchar('\n');
    }
}


void pause()
{
    cout << "\n\n";
    system("Pause");
}

void cleanScreen()
{
    system("Cls");
}


void task1(int* sorted, int* unsorted, const int SIZE)
{
    srand(static_cast<unsigned int>(time(0)));

    for (int i = 0; i < SIZE; i++)
    {
        sorted[i] = getRandomNumber(-99, 99);
        unsorted[i] = sorted[i];
    }
}

void task2(int* sorted, const int SIZE)
{
    auto begin = steady_clock::now();
    quicksort(sorted, SIZE);
    auto end = steady_clock::now();

    arrOutput(sorted, SIZE);

    cout << "\n\nSorted in : " << duration_cast<nanoseconds>(end - begin).count() << " nanoseconds\n\n"; \
}

void task3(int* sorted, int* unsorted, const int SIZE)
{
    arrOutput(sorted, SIZE);

    int max = -100,
        min = 100;

    cout << "\n\nIn unsorted array:\n";

    auto begin = steady_clock::now();
    findMaxMin(unsorted, SIZE, max, min);
    auto end = steady_clock::now();

    cout << "    Max value: " << max << " Min value: " << min
       << "\n    Found in: " << duration_cast<nanoseconds>(end - begin).count() << " nanoseconds\n\n"
        << "In sorted array:\n";

    begin = steady_clock::now();
    max = sorted[SIZE-1], min = *sorted;
    end = steady_clock::now();

    cout << "    Max value: " << max << " Min value: " << min
       << "\n    Found in: " << duration_cast<nanoseconds>(end - begin).count() << " nanoseconds\n\n";
}

void task4(int* sorted, const int SIZE)
{
    arrOutput(sorted, SIZE);

    cout << "\n\nIndexes of elements equal to " << '(' << *sorted << " + " << sorted[SIZE - 1] << ") / 2 = " << (*sorted + sorted[SIZE - 1]) / 2 << ": ";

    int   mid = (*sorted + sorted[SIZE-1]) / 2,
        count = 0,
        right = SIZE - 1,
         left = 0, 
        index = binarySearch(mid, sorted, SIZE, left, right);

    for (int i = index - 5; i < index + 5; i++)
    {
        if (sorted[i] > sorted[index])
            break;
        else if (sorted[i] == mid)
        {
            cout << i << ' ';
            count++;
        }
    }

    if (count != 0)
        cout << "\n    and their count: " << count << "\n\n";
    else
        cout << "\n    There are no such numbers";
}

void task5(int* sorted, const int SIZE, int userNum)
{
    int count = 0;

    cout << "    Numbers which less than " << userNum << ": ";

    for (int i = 0; i < SIZE; i++)
    {
        if (sorted[i] >= userNum)
            break;
        cout << sorted[i] << ' ';
        count++;
    }

    if (count == 0)
        cout << "There are no such numbers";
}

void task6(int* sorted, const int SIZE, int userNum)
{
    int count = 0;

    cout << "    Numbers which bigger than " << userNum << ": ";

    for (int i = SIZE - 1; i >= 0; i--)
    {
        if (sorted[i] <= userNum)
            break;
        cout << sorted[i] << ' ';
        count++;
    }

    if (count == 0)
        cout << "There are no such numbers";
}

void task7(int* sorted, const int SIZE, int userNum)
{
    int right = SIZE - 1,
         left = 0;

    cout << "\n    Binary search: \n";

    auto begin = steady_clock::now();
    int index  =  binarySearch(userNum, sorted, SIZE, left, right);
    auto end   = steady_clock::now();

    if (sorted[index] == userNum)
        cout << "        The found number is under the index " << index;
    else
        cout << "        There are no such numbers";

    cout << "\n        Found in: " << duration_cast<nanoseconds>(end - begin).count() << " nanoseconds\n\n";

    cout << "    Common search: \n";

    begin = steady_clock::now();
    index = commonSearch(userNum, sorted, SIZE);
    end   = steady_clock::now();

    if (index >= 0)
        cout << "        The found number is under the index " << index << '\n';
    else
        cout << "        There are no such numbers\n";

    cout << "        Found in: " << duration_cast<nanoseconds>(end - begin).count() << " nanoseconds\n\n";
}

void task8(int* sorted, const int SIZE)
{
    arrOutput(sorted, SIZE);

    cout << "\n\nWhich two elements should be swapped?\n";

    int num1, num2;

    cin >> num1 >> num2;
    cin.sync();
    while (num1 < 0 || num1 > 99 || num2 < 0 || num2 > 99 || num1 == num2)
    {
        cout << "\nYou have intered numbers which are go beyond of the array or equal to each other, try again\n";
        cin >> num1 >> num2;
    }

    auto begin = steady_clock::now();
    swap(sorted[num1], sorted[num2]);
    auto end = steady_clock::now();

    cout << "\nElements swapped in: " << duration_cast<nanoseconds>(end - begin).count() << " nanoseconds\n\n";
    arrOutput(sorted, SIZE, num1, num2);
}