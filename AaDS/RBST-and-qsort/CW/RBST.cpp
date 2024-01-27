#include "RBST.h"
#include <string>

bool Client::operator>(Client& cl)
{
    return duration > cl.duration;
}

bool Client::operator<(Client& cl)
{
    return duration < cl.duration;
}

bool Client::operator==(Client& cli)
{
    if (name == cli.name && deposit == cli.deposit &&
        amount == cli.amount && duration == cli.duration)
        return true;
    return false;
}

std::ostream& operator<<(std::ostream& out, Client& cl)
{
    return out
        << "Client name: " << cl.name << '\n'
        << "   Depostit: " << cl.deposit << '\n'
        << "     Amount: " << cl.amount << '\n'
        << "   Duration: " << cl.duration << '\n';
}

std::istream& operator>>(std::istream& in, Client& cl)
{
    std::getline(in >> std::ws, cl.name);
    std::getline(in >> std::ws, cl.deposit);
    return in
        >> cl.amount
        >> cl.duration;
}
//////////////////////////////////////////////////////////
namespace RBST
{
    int getsize(RBS_Tree* p)
    {
        if (!p) return 0;
        return p->size;
    }

    void fixsize(RBS_Tree* p)
    {
        p->size = getsize(p->left) + getsize(p->right) + 1;
    }

    RBS_Tree* find(RBS_Tree* p, Client& k)
    {
        if (!p) return 0;

        if (k == p->key)
            return p;

        if (k < p->key)
            return find(p->left, k);
        else
            return find(p->right, k);
    }

    RBS_Tree* insert(RBS_Tree* p, Client& k)
    {
        if (!p) return new RBS_Tree(k);

        if (rand() % (p->size + 1) == 0)
            return insertroot(p, k);

        if (p->key > k)
            p->left = insert(p->left, k);
        else
            p->right = insert(p->right, k);

        fixsize(p);
        return p;
    }

    RBS_Tree* rotateright(RBS_Tree* p)
    {
        RBS_Tree* q = p->left;
        if (!q) return p;

        p->left = q->right;
        q->right = p;
        q->size = p->size;

        fixsize(p);
        return q;
    }

    RBS_Tree* rotateleft(RBS_Tree* q)
    {
        RBS_Tree* p = q->right;
        if (!p) return q;

        q->right = p->left;
        p->left = q;
        p->size = q->size;

        fixsize(q);
        return p;
    }

    RBS_Tree* insertroot(RBS_Tree* p, Client& k)
    {
        if (!p) return new RBS_Tree(k);

        if (k < p->key)
        {
            p->left = insertroot(p->left, k);
            return rotateright(p);
        }
        else
        {
            p->right = insertroot(p->right, k);
            return rotateleft(p);
        }
    }

    RBS_Tree* join(RBS_Tree* p, RBS_Tree* q)
    {
        if (!p) return q;
        if (!q) return p;

        if (rand() % (p->size + q->size) < p->size)
        {
            p->right = join(p->right, q);
            fixsize(p);
            return p;
        }
        else
        {
            q->left = join(p, q->left);
            fixsize(q);
            return q;
        }
    }

    RBS_Tree* remove(RBS_Tree* p, Client& k)
    {
        if (!p) return p;

        if (p->key == k)
        {
            RBS_Tree* q = join(p->left, p->right);
            delete p;
            return q;
        }
        else if (k < p->key)
            p->left = remove(p->left, k);
        else
            p->right = remove(p->right, k);

        return p;
    }
}