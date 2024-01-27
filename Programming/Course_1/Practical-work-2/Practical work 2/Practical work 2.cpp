#include <iostream>
#include <windows.h>
#include "Functions.h"

using namespace std;

int main()
{
    setlocale(LC_ALL, "");

    ShowWindow(GetForegroundWindow(), SW_SHOWMAXIMIZED); //fullscreen

    char ask = '#';
    const int SIZE = 100;
    int sorted[SIZE],
        unsorted[SIZE],
        userNum;

    task1(sorted, unsorted, SIZE);          //README

    do
    {
        quicksort(sorted, SIZE);            //README
        cleanScreen();

        cout << "[x] Exit\n\n";
        for (int i = 1; i <= 8; i++)
        {
            cout << "[" << i << "] Task №" << i;
            if (i == 1)
                cout << " (creates a new array)";
            cout << '\n';
        }

        cin >> ask;
        cin.sync();

        switch (ask)
        {
        case '1':
            cleanScreen();

            cout << "Task №1\n";

            task1(sorted, unsorted, SIZE);

            arrOutput(unsorted, SIZE);

            pause();
            break;

        case '2':
            cleanScreen();

            cout << "Task №2\n";

            task2(sorted, SIZE);

            pause();
            break;

        case '3':
            cleanScreen();

            cout << "Task №3\n";

            task3(sorted, unsorted, SIZE);

            pause();
            break;

        case '4':
            cleanScreen();

            cout << "Task №4\n\n";

            task4(sorted, SIZE);

            pause();
            break;

        case '5':
            cleanScreen();

            cout << "Task №5\nEnter a number less than which will be displayed: ";

            cin >> userNum;
            cin.sync();

            task5(sorted, SIZE, userNum);

            pause();
            break;

        case '6':
            cleanScreen();

            cout << "Task №6\nEnter a number more than which will be displayed: ";

            cin >> userNum;
            cin.sync();

            task6(sorted, SIZE, userNum);

            pause();
            break;

        case '7':
            cleanScreen();

            cout << "Task №7\n";

            arrOutput(sorted, SIZE);

            cout << "\n\nEnter a number which index will be displayed: ";
            cin >> userNum;
            cin.sync();

            task7(sorted, SIZE, userNum);

            pause();
            break;

        case '8':
            cleanScreen();

            cout << "Task №8\n";

            task8(sorted, SIZE);

            pause();
            break;

        case 'x':
        case 'х':
        case 'X':
        case 'Х':
            ask = 'x';
            break;
        }
    } while (ask != 'x');
    return 0;
}