#include <iostream>
#include <fstream>
#include <conio.h>

#include "Functions.h"

void qsort(Client* arr, const int size)
{
    int left = 0;
    int right = size - 1;
    Client mid = arr[size / 2];

    do
    {
        while (arr[left] < mid) left++;

        while (arr[right] > mid)  right--;

        if (left <= right) std::swap(arr[left++], arr[right--]);
    } while (left <= right);

    if (right > 0) qsort(arr, right + 1);
    if (left < size) qsort(&arr[left], size - left);
}

void templ()
{
    system("cls");
    std::cout
        << "Template:\n"
        << "Name             [enter]\n"
        << "Deposit number   [enter]\n"
        << "Deposit amount   [enter]\n"
        << "Deposit duration [enter]\n\n";
}

void manual(RBS_Tree* tree, std::list<Client>& clients)
{
    templ();
    std::cout << "Type '\\' to finish (at the end)\n\n";
    char ch = '0';

    while (ch != '\\')
    {
        Client temp;
        std::cin >> temp;
        ch = _getch();
        tree = RBST::insert(tree, temp);
        clients.push_back(temp);
    }
}

void find(RBS_Tree* tree, Client& to_find)
{
    templ();

    std::cin >> to_find;
    if (RBST::find(tree, to_find))
        std::cout << "Entry is found\n";
    else
        std::cout << "Entry not found\n";
}

void remove(RBS_Tree* tree, Client& to_find)
{
    templ();

    std::cin >> to_find;
    if (RBST::find(tree, to_find))
    {
        RBST::remove(tree, to_find);
        std::cout << "Entry is found and deleted\n";
    }
    else std::cout << "Entry not found\n";
}

void sort(std::list<Client>& clients)
{
    if (clients.size() == 0) return;

    Client* temp = new Client[clients.size()];
    size_t i = 0;

    for (Client cl : clients)
        temp[i++] = cl;

    qsort(temp, (int)clients.size());

    size_t size = clients.size();
    clients.clear();

    for (i = 0; i < size; ++i)
        clients.push_back(temp[i]);

    delete[] temp;
}

void menu()
{
    int choice;
    std::list<Client> clients;
    Client to_find;
    std::ifstream fin;
    RBS_Tree* tree = nullptr;

    while (true)
    {
        do
        {
            std::cout
                << "[0] Exit\n"
                << "[1] The worst qsort case (file)\n"
                << "[2] Average qsort case   (file)\n"
                << "[3] The best qsort case  (file)\n"
                << "[4] Manual input\n"
                << "[5] Find an entry\n"
                << "[6] Delete an entry\n"
                << "[7] Sort\n"
                << "[8] Show all entries\n";

            std::cin >> choice;
        } while (choice < 0 || choice > 8);

        switch (choice)
        {
        case 0:
            exit(0);
            break;
        case 1:
            fin.open("the worst-case.txt");
            break;
        case 2:
            fin.open("average-case.txt");
            break;
        case 3:
            fin.open("the best-case.txt");
            break;
        case 4:
            manual(tree, clients);
            break;
        case 5:
            find(tree, to_find);
            break;
        case 6:
            remove(tree, to_find);
            break;
        case 7:
            sort(clients);
            break;
        case 8:
            for (Client cl : clients)
                std::cout << cl << '\n';
            break;
        }

        if (fin.is_open())
        {
            for (int i = 0; i < 5; ++i)
            {
                Client temp;
                fin >> temp;

                tree = RBST::insert(tree, temp);

                clients.push_back(temp);
            }
            fin.close();
        }

        system("pause");
        system("cls");
    }
}