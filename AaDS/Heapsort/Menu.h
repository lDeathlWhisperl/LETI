#include <list>

#include "Book.h"

#define clear_screen system("clear")

class Menu final
{
    Menu();
    static int id, choice;
    static bool is_menu_active;
    static std::list<Book> books;
    
    enum
    {
        ENTER = 13,
        ESC   = 27,
        SPACE = 32,
    
        S = 83,
        W = 87,
    
        s = 115,
        w = 119
    };
public:
    static void draw();
private:
    static void draw_menu();

    static void controller();
    
    static void select_option();
    
    static void manual_input();
    
    static void example();
    
    static void sort();
    
    static void display();
};
