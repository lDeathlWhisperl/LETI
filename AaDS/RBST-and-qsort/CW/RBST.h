#pragma once
#include <iostream>

struct Client
{
    std::string name;
    std::string deposit;
    unsigned long long amount{};
    unsigned long long duration{};

    bool operator>(Client&);
    bool operator<(Client&);
    bool operator==(Client&);
};

std::ostream& operator<<(std::ostream&, Client&);
std::istream& operator>>(std::istream&, Client&);

struct RBS_Tree
{
    Client key;
    int size;
    RBS_Tree* left;
    RBS_Tree* right;
    RBS_Tree(Client k) : key(k), left(0), right(0), size(1) {}
};

namespace RBST
{
    RBS_Tree* find(RBS_Tree*, Client&);

    RBS_Tree* insert(RBS_Tree*, Client&);

    int getsize(RBS_Tree*);

    RBS_Tree* insertroot(RBS_Tree*, Client&);

    RBS_Tree* join(RBS_Tree*, RBS_Tree*);

    RBS_Tree* remove(RBS_Tree*, Client&);
}