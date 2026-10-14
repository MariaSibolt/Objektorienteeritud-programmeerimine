#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;

class Item
{
    string name;
    float price;

public:
    Item(string n, float h)
    {
        name = n;
        price = h;
    }

    bool equals(Item* p)
    {
        return name == p->name && price == p->price;
    }

    float getPrice()
    {
        return price;
    }

    string string_out()
    {
        stringstream ss;
        ss << fixed << setprecision(2);
        ss << name << " " << price;
        return ss.str();
    }
};

struct order_line
{
    Item* object;
    int amount;

    string string_out()
    {
        stringstream ss;
        ss << fixed << setprecision(2);
        ss << object->string_out() << " x " << amount;
        return ss.str();
    }
};


int order_index = 1000;

class Order
{
public:
    Order();
    Order(vector<order_line*> l);

    int nr;
    vector<order_line*> order_total;

    order_line* lookup(Item* p)
    {
        for (int i = 0; i < order_total.size(); i++)
        {
            if (p->equals(order_total[i]->object))
                return order_total[i];
        }
        return NULL;
    }

    bool add_line(Item* p, int n)
    {
        if (n <= 0)
            return false;

        order_line* r = lookup(p);

        if (r != NULL)
        {
            r->amount += n;
            return true;
        }

        order_line* x = new order_line;
        x->object = p;
        x->amount = n;

        order_total.push_back(x);
        return true;
    }

    string string_out()
    {
        stringstream ss;
        ss << "Tellimus nr " << nr << ":\n";

        for (int i = 0; i < order_total.size(); i++)
            ss << order_total[i]->string_out() << "\n";

        return ss.str();
    }
};

Order::Order()
{
    order_index = order_index + 1;
    nr = order_index;
}

Order::Order(vector<order_line*> l)
{
    order_index = order_index + 1;
    nr = order_index;

    for (int i = 0; i < l.size(); i++)
        order_total.push_back(l[i]);
}