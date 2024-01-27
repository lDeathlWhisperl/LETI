#include <unistd.h>
#include <termios.h>
#include <fstream>

#include "Menu.h"
#include "HeapSort.h"

char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
        
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
        
    if(read(0, &buf, 1) < 0)
        perror("read()");
        
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

int Menu::id, Menu::choice;
bool Menu::is_menu_active = true;
std::list<Book> Menu::books;

void Menu::draw()
{
    while(is_menu_active)
    {
        draw_menu();
        controller();
        clear_screen;
    }
}

void Menu::draw_menu()
{
    const char menu_list[][22] = 
    {
        "[        Exit       ]",
        "[    Manual input   ]",
        "[    Example file   ]",
        "[        Sort       ]",
        "[ Display all books ]"
    };
      
    for(int i = 0; i < 5; ++i)
    {
        if(i == id) std::cout << "\x1b[30;44m";
        std::cout << menu_list[i] << "\x1b[0m\n";
    }
}

void Menu::controller()
{
    switch(getch())
    {
    case W:
    case w:
        if(id != 0) --id;
        break;
    case S:
    case s:
        if(id != 4) ++id;
        break;
    case ENTER:
    case SPACE:
        choice = id;
        select_option();
        break;
    case ESC:
        is_menu_active = false;
    }
}

void Menu::select_option()
{
    switch(choice)
    {
    case 0:
        is_menu_active = false;
        break;
    case 1:
        manual_input();
        break;
    case 2:
        example();
        break;
    case 3:
        sort();
        break;
    case 4:
        display();
        break;
    }
}

void Menu::manual_input()
{
    clear_screen;
    std::cout << "Type ~ at the end to finish\n\n";
    char ch;
      
    while(ch != '~')
    {
        Book book;
        std::cin >> book;
        ch = getch();
        books.push_back(book);
    }
}

void Menu::example()
{
    std::ifstream fin("example.txt");
        
    for(int i = 0; i < 5; ++i)
    {
        Book book;
        fin >> book;
        books.push_back(book);
    }
}
    
void Menu::sort()
{
    size_t size = books.size();
    Book *temp_book = new Book[size];
    int i = 0;
  
    for(Book book : books)
        temp_book[i++] = book;
    
    heapSort(temp_book, size);
	
    books.clear();
    for(i = 0; i < size; ++i)
    books.push_back(temp_book[i]);
  	delete[] temp_book;
}
    
void Menu::display()
{
    clear_screen;
    for(Book book : books)
        std::cout << book << '\n';
    getch();
}
