#include <iostream>
#include <vector>
#include <conio.h>
#include "Functions.h"

int main()
{
    setlocale(LC_ALL, "RUS");
    fullscreen();

    std::vector<student> students;
    
    getFromFile(students);

    int scroll = 0;
    bool isEnabled = true;
    while (isEnabled)
    {
        mainMenu(scroll);
        switch (_getch())
        {
        case 'w':
            if (scroll != 0) scroll--;
            else scroll = 8;
            break;
        case 's':
            if (scroll != 8)scroll++;
            else scroll = 0;
            break;
        case ' ':
            if (scroll == 0) isEnabled = false;
            selectedField(scroll, students);
            break;
        }
        system("Cls");
    }
    writeInToFile(students);
    return 0;
}