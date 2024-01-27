#include "functions.h"
#include "Tree.h"
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <fstream>

enum colors
{
    BLACK = 0,
    GREEN = 2,
    BLUE  = 3,
    RED   = 4,
    WHITE = 15
};

enum buttons
{
    ENTER       = 13,
    ESC         = 27,
    SPACE       = 32,
    ARROW_UP    = 72, // ↑ (24)
    ARROW_LEFT  = 75, // ← (27)
    ARROW_RIGHT = 77, // → (26)
    ARROW_DOWN  = 80, // ↓ (25)
    S           = 83,
    W           = 87,
    s           = 115,
    w           = 119
};

void setColor(int text, int background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

void timer(int count)
{
    for (int i = count; i >= 0; i--)
    {
        std::cout << " [" << i << "] sec ";
        Sleep(1000);
        std::cout << "\b\b\b\b\b\b\b\b\b\b";
    }
}

void fullscreen()
{
    ShowWindow(GetForegroundWindow(), SW_SHOWMAXIMIZED);
}

int getRandomNumber(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void drawMainMenu(int id , bool &isAvailable)
{
    system("cls");
    std::cout << "\n\n";
    char menu[13][24] = {
        "[        Exit         ]",
        "[    Set tree size    ]",
        "[     Input items     ]",
        "[    Get from file    ]",
        "[    Show the tree    ]",
        "[ Print into the file ]",
        "[       Delete        ]",
        "[     Get an item     ]",
        "[  Straight traversal ]",
        "[  Reverse traversal  ]",
        "[ Symmetric traversal ]",
        "[  Breadth traversal  ]",
        "[        Erase        ]"};

    for (int i = 0; i < 13; i++)
    {
        if (i == id)
            std::cout << "   ";

        std::cout << menu[i] << ' ';

        if (!isAvailable && id > 3 && i == id)
        {
            setColor(BLACK, RED);
            std::cout << "[ UNAVAILABLE IF THE TREE HAS NO ITEMS ]";
            setColor(WHITE, BLACK);
        }

        std::cout << '\n';
    }
}

void setTreeSize(Tree &tr, bool & isAvailable)
{
    system("cls");
    int size;
    std::cout << "Input the tree size: ";
    std::cin >> size;

    if (std::cin.fail()) {
        system("cls");
        std::cout << '\n';
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "\x1b[31m [UNACCEPTABLE VALUE]\x1b[0m" << '\n';
        timer(3);
        return;
    }

    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < size; i++)
        tr.insert(getRandomNumber(-99, 99));

    system("cls");

    if (tr.getSize())
    {
        isAvailable = true;
        std::cout << "\x1b[32m\n\n [COMPLETED]\x1b[0m" << '\n';
    }
    else
        std::cout << "\x1b[31m\n\n [THE TREE IS EMPTY]\x1b[0m" << '\n';
    timer(3);
}

void input(Tree& tr, bool &isAvailable)
{
    system("cls");
    int num;

    std::cout << "\nEnter any character (not a number) to complete the sequence\n\n";
    while (std::cin >> num)
        tr.insert(num);

    std::cin.clear();
    std::cin.ignore(32767, '\n');

    system("cls");

    if (tr.getSize())
    {
        isAvailable = true;
        std::cout << "\x1b[32m\n\n [COMPLETED]\x1b[0m" << '\n';
    }
    else
        std::cout << "\x1b[31m\n\n [THE TREE IS EMPTY]\x1b[0m" << '\n';
    timer(3);
}

void fromFile(Tree &tr, bool &isAvailable)
{
    system("cls");
    std::ifstream fin("Nums.txt");
    int num;

    while (fin >> num)
        tr.insert(num);

    fin.clear();
    fin.ignore(32767, '\n');

    fin.close();
    if (tr.getSize())
    {
        isAvailable = true;
        std::cout << "\x1b[32m\n\n [COMPLETED]\x1b[0m" << '\n';
    }
    else
        std::cout << "\x1b[31m\n\n [THE FILE HAS NO NUMS]\x1b[0m" << '\n';
    timer(3);
    
}

void print(Tree &tr)
{
    system("cls");
    tr.print();
    std::cout << "Size: " << tr.getSize() << '\n';
    system("pause");
}

void intoFile(Tree &tr)
{
    system("cls");
    tr.print(false);
    std::cout << "\x1b[32m\n\n [COMPLETED]\x1b[0m" << '\n';
    timer(3);
}

void del(Tree &tr, bool &isAvailable)
{
    system("cls");
    tr.print();
    std::cout << "Enter the number what would be deleted: ";
    int num;
    std::cin >> num;

    if (std::cin.fail()) {
        system("cls");
        std::cout << '\n';
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "\x1b[31m [UNACCEPTABLE VALUE]\x1b[0m" << '\n';
        timer(3);
        return;
    }

    if (!tr.find(num))
    {
        system("cls");
        std::cout << "\x1b[31m [DID NOT FIND]\x1b[0m" << '\n';
        timer(3);
        return;
    }

    tr.del(num);

    std::cout << "New tree: ";
    if (tr.getSize() == 0)
        std::cout << "is empty";
    tr.print();

    std::cout << "\x1b[32m\n\n [COMPLETED]\x1b[0m" << '\n';
    timer(3);

    if (tr.getSize() == 0)
        isAvailable = false;
}

void getItem(Tree &tr)
{
    system("cls");
    std::cout << "Enter the num to search for: ";
    int num;
    std::cin >> num;

    if (std::cin.fail()) {
        system("cls");
        std::cout << '\n';
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        std::cout << "\x1b[31m [UNACCEPTABLE VALUE]\x1b[0m" << '\n';
        timer(3);
        return;
    }

    system("cls");

    if(tr.find(num))
        std::cout << "\x1b[32m [FOUND]\x1b[0m" << '\n';
    else
        std::cout << "\x1b[31m [DID NOT FIND]\x1b[0m" << '\n';

    timer(3);
}

void straight(Tree &tr)
{
    system("cls");
    tr.print();
    std::cout << "\nThe straight traversal: ";
    tr.straight();
    std::cout << '\n';
    system("pause");
}

void reverse(Tree& tr)
{
    system("cls");
    tr.print();
    std::cout << "\nThe reverse traversal: ";
    tr.reverse();
    std::cout << '\n';
    system("pause");
}

void symmetric(Tree &tr)
{
    system("cls");
    tr.print();
    std::cout << "\nThe symmetric traversal: ";
    tr.symmetrical();
    std::cout << '\n';
    system("pause");
}

void breadth(Tree& tr)
{
    system("cls");
    tr.print();
    std::cout << "\nThe breadth traversal: ";
    tr.breadth();
    std::cout << '\n';
    system("pause");
}

void erase(Tree& tr, bool& isAvailable)
{
    system("cls");
    tr.~Tree();
    std::cout << "\x1b[32m\n\n [COMPLETED]\x1b[0m" << '\n';
    timer(3);
    isAvailable = false;
}

void choose(Tree &tr, int id, bool &isAvailable, bool &isEnable)
{
    switch (id)
    {
    case 0:
        isEnable = false;
        break;
    case 1:
        setTreeSize(tr, isAvailable);
        break;
    case 2:
        input(tr, isAvailable);
        break;
    case 3:
        fromFile(tr, isAvailable);
        break;
    }

    if(isAvailable)
        switch (id)
        {
        case 4:
            print(tr);
            break;
        case 5:
            intoFile(tr);
            break;
        case 6:
            del(tr, isAvailable);
            break;
        case 7:
            getItem(tr);
            break;
        case 8:
            straight(tr);
            break;
        case 9:
            reverse(tr);
            break;
        case 10:
            symmetric(tr);
            break;
        case 11:
            breadth(tr);
            break;
        case 12:
            erase(tr, isAvailable);
        }
}

void mainMenu()
{
    Tree tr;
    int id = 0;
    bool isEnable = true,
        isAvailable = false;

    while (isEnable)
    {
        drawMainMenu(id, isAvailable);
        switch (_getch())
        {
        case W:
        case w:
        case ARROW_UP:
            if (id != 0) id--;
            else id = 12;
            break;
        case S:
        case s:
        case ARROW_DOWN:
            if (id != 12) id++;
            else id = 0;
            break;
        case ENTER:
        case SPACE:
            choose(tr, id, isAvailable, isEnable);
            break;
        case ESC:
            isEnable = false;
            break;
        }
    }
    system("cls");
}