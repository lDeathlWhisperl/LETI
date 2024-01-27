#include "Functions.h"
#include "List.h"
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <conio.h> 
#include <chrono>

void error(int& index, int size)
{
    while (index < 0 || index >= size)
    {
        std::cout << "\x1b[31m[INCORRECT INDEX, TRY AGAIN]: \x1b[0m";
        std::cin >> index;
    }
}

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
    ARROW_DOWN  = 80  // ↓ (25)
};

void fullscreen()
{
    ShowWindow(GetForegroundWindow(), SW_SHOWMAXIMIZED);
}
void setColor(int text, int background)
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
int getRandomNumber(int min, int max)
{
    return min + rand() % (max - min + 1);
}

void insert(List* list)
{
    system("cls");
    int pos, num;
    std::cout << "\nEnter the position for inserting [0," << list->getSize() << "]: ";
    std::cin >> pos;

    error(pos, list->getSize() + 1);

    std::cout << "\nInput the number: ";
    std::cin >> num;


    auto begin = std::chrono::steady_clock::now();
    list->insert(pos, num);
    auto end = std::chrono::steady_clock::now();

    std::cout << "\nInserted for " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds\n";
    system("pause");
}
void deleting(List* list, bool& isChangeable, bool& canBeShowed, bool& isEnable)
{
    system("cls");
    int pos;
    std::cout << "\nEnter the index of deleteable item [0," << list->getSize()-1<< "]: ";
    std::cin >> pos;

    error(pos, list->getSize());

    auto begin = std::chrono::steady_clock::now();
    list->del(pos);
    auto end = std::chrono::steady_clock::now();

    std::cout << "\nDeleted for " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds\n";
    system("pause");

    if (!list->getSize()) isEnable = canBeShowed = isChangeable = false;
}
void exchange(List* list)
{
    system("cls");
    int num_1, num_2;
    std::cout << "\nEnter the two indexes that will be swaped [0," << list->getSize() - 1 << "]: ";
    std::cin >> num_1 >> num_2;

    if (num_1 < 0 || num_1 >= list->getSize())
    {
        std::cout << "\x1b[31m[FIRST INDEX]: \x1b[0m\t";
        error(num_1, list->getSize());
    }
    if (num_2 < 0 || num_2 >= list->getSize())
    {
        std::cout << "\x1b[31m[SECOND INDEX]: \x1b[0m\t";
        error(num_2, list->getSize());
    }

    std::cout << "\nlist: [ ";
    list->print(num_1, num_2);
    std::cout << "]\n";

    auto begin = std::chrono::steady_clock::now();
    list->swap(num_1, num_2);
    auto end = std::chrono::steady_clock::now();

    std::cout << "\nlist: [ ";
    list->print(num_1, num_2);
    std::cout << ']' << '\n';

    std::cout << "\nSwapped for " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds\n";
    system("pause");
}
void receive(List* list)
{
    system("cls");
    int pos;
    std::cout << "\nEnter the index of item [0," << list->getSize() - 1 << "]: ";
    std::cin >> pos;

    error(pos, list->getSize());

    auto begin = std::chrono::steady_clock::now();
    list->print((unsigned)pos);
    auto end = std::chrono::steady_clock::now();

    std::cout << "\nReceived for " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds\n";
    system("pause");
}
void annihilator(List* list, bool& isChangeable, bool& canBeShowed, bool& isEnable)
{
    int id = 0;
    char str[][8] = { "[ No ]", "[ Yes ]" };
    bool isChoosen = true;

    while (isChoosen)
    {
        system("cls");
        std::cout <<
            "+===============================================+\n"
            "|  Are you sure you want to delete this entry?  |\n"
            "+===============================================+\n"
            "|                                               |\n"
            "|           ";


        for (int i = 1; i >= 0; i--)
        {
            if (i == 0 && i == id) setColor(0, 2);
            if (i == 1 && i == id) setColor(0, 4);
            std::cout << str[i];
            setColor(15, 0);
            std::cout << "           ";
        }

        std::cout << " |\n"
            "|                                               |\n"
            "+===============================================+\n";

        switch (_getch())
        {
        case 'A':
        case 'a':
        case ARROW_LEFT:
            if (id != 0) id--;
            else id = 1;
            break;
        case 'D':
        case 'd':
        case ARROW_RIGHT:
            if (id != 1) id++;
            else id = 0;
            break;
        case SPACE:
        case ENTER:
            isChoosen = false;
            if (id == 1)
            {
                auto begin = std::chrono::steady_clock::now();
                list->erase();
                auto end = std::chrono::steady_clock::now();
                isEnable = isChangeable = canBeShowed = false;

                std::cout << "\nErased for " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds\n";
                system("pause");
            }
            break;
        case ESC:
            isChoosen = false;
            break;
        }
    }

}

void drawEditingMenu(int id)
{
    system("cls");
    std::cout << '\n';
    char menu[][22] = {
        "[    Back to menu   ]",
        "[  Insert an item   ]",
        "[  Delete an item   ]",
        "[ Exchange an items ]",
        "[  Receive an item  ]",
        "[   Show the list   ]",
        "[  Erase the list   ]" };

    for (int i = 0; i < 7; i++)
    {
        if (i == id)
        {
            std::cout << "   ";
            if (id != 0 && id != 5 && id != 6) setColor(BLACK, GREEN);
            else if (id == 0) setColor(BLACK, BLUE);
            else if (id == 5) setColor(BLACK, WHITE);
            else if (id == 6) setColor(BLACK, RED);
        }
        std::cout << menu[i] << '\n';
        setColor(WHITE, BLACK);
        if (i == 4) std::cout << "---------------------\n";
    }
}
void editingMenu(List* list, bool& isChangeable, bool& canBeShowed)
{
    bool isEnable = true;
    int id = 0;

    while (isEnable)
    {
        drawEditingMenu(id);
        switch (_getch())
        {
        case 'W':
        case 'w':
        case ARROW_UP:
            if (id != 0) id--;
            else id = 6;
            break;
        case 'S':
        case 's':
        case ARROW_DOWN:
            if (id != 6) id++;
            else id = 0;
            break;
        case ENTER:
        case SPACE:
            if (id == 0) isEnable = false;
            else if (id == 1) insert(list);
            else if (id == 2) deleting(list, isChangeable, canBeShowed, isEnable);
            else if (id == 3)
            {
                if (list->getSize() > 1)
                    exchange(list);
                else
                {
                    system("cls");
                    std::cout << "The lise size is less than 2\n";
                    system("pause");
                }
            }
            else if (id == 4) receive(list);
            else if (id == 5)
            {
                system("cls");
                std::cout << "\nlist: [ ";
                list->print();
                std::cout << "] \nsize: " << list->getSize() << "\n\n";
                system("pause");
            }
            else if (id == 6) annihilator(list, isChangeable, canBeShowed, isEnable);
            break;
        case ESC:
            isEnable = false;
        }
    }
}

void setSize(List* list, bool& isChangeable, bool& canBeShowed)
{
    system("cls");
    int size;
    std::cout << "\nEnter the list size: ";
    std::cin >> size;

    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < size; i++)
        list->addTail(getRandomNumber(0, 99));
    if (list->getSize()) canBeShowed = isChangeable = true;
}
void inputItems(List* list, bool& isChangeable, bool& canBeShowed)
{
    system("cls");
    int num = '0';

    std::cout << "\nEnter any character (not a number) to complete the sequence";
    std::cout << "\nThe list will be filled by the next numbers: ";

    while (std::cin >> num)
        list->addTail(num);

    std::cin.clear();
    std::cin.ignore(32767, '\n');

    if (list->getSize()) canBeShowed = isChangeable = true;
}

void manual()
{
    std::cout << 
        "+=============================================+\n"
        "|                   Manual                    |\n"
        "+=============================================+\n"
        "| [w]     -> scroll up    (alt: arrow up)     |\n"
        "| [s]     -> scroll down  (alt: arrow down)   |\n"
        "| [a]     -> switch left  (alt: arrow left)   |\n"
        "| [d]     -> switch right (alt: arrow right)  |\n"
        "| [space] -> select       (alt: enter)        |\n"
        "| [esc]   -> exit/back    (only in menu)      |\n"
        "+=============================================+\n"
        "| P.S.                                        |\n";

    auto begin = std::chrono::steady_clock::now();
    List list;
    auto end = std::chrono::steady_clock::now();
    std::cout << "| List created for " << std::left << std::setw(5) << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " nanoseconds          |\n";
    std::cout << "+=============================================+\n";
}

void drawMainMenu(int id, bool isChangeable, bool canBeShowed)
{
    system("cls");
    std::cout << '\n';

    char menu[][60] = {
        "[                          Exit                         ]",
        "[                      Set list size                    ]",
        "[                Enter the items yourself               ]",
        "[ Inserting, deleting, exchanging and receiving an item ]",
        "[                     Show the list                     ]" };

    for (int i = 0; i < 5; i++)
    {
        if (i == id)
        {
            std::cout << "   ";
            if (id != 0 && id != 4 && id != 3) setColor(BLACK, GREEN);
            else if (id == 0) setColor(BLACK, BLUE);
            else if (id == 3 && isChangeable) setColor(BLACK, GREEN);
            else if (id == 3 && !isChangeable || id == 4 && !canBeShowed) setColor(BLACK, RED);
            else if (id == 4 && canBeShowed) setColor(BLACK, WHITE);
        }
        std::cout << menu[i] << '\n';
        setColor(WHITE, BLACK);
        if (i == 3) std::cout << "---------------------------------------------------------\n";
    }
}
void mainMenu()
{
    bool isEnable = true,
        isChangeable = false,
        canBeShowed = false;
    int id = 0;

    
    manual();

    List list;

    system("pause");
    system("cls");
    while (isEnable)
    {
        drawMainMenu(id, isChangeable, canBeShowed);
        switch (_getch())
        {
        case 'W':
        case 'w':
        case ARROW_UP:
            if (id != 0) id--;
            else id = 4;
            break;
        case 'S':
        case 's':
        case ARROW_DOWN:
            if (id != 4) id++;
            else id = 0;
            break;
        case ENTER:
        case SPACE:
            if (id == 0) isEnable = false;
            else if (id == 1) setSize(&list, isChangeable, canBeShowed);
            else if (id == 2) inputItems(&list, isChangeable, canBeShowed);
            else if (id == 3 && list.getSize()) editingMenu(&list, isChangeable, canBeShowed);
            else if (id == 4 && list.getSize())
            {
                system("cls");
                std::cout << "\nlist: [ ";
                list.print();
                std::cout << "] \nsize: " << list.getSize() << "\n\n";
                system("pause");
            }
            break;
        case ESC:
            isEnable = false;
            break;
        }
    }
}