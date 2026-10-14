#pragma once

#include "lisad.h"
#include <vector>

using namespace std;

struct stock_box
{
    Item* object;
    int amount;
};

struct history_line
{
    string operation;
    Item* object;
    int amount;
};

class Stock
{
    vector<stock_box*> stock_total;

    stock_box* lookup(Item* p)
    {
        for (int i = 0; i < stock_total.size(); i++)
        {
            if (p->equals(stock_total[i]->object))
                return stock_total[i];
        }

        return NULL;
    }

public:

    vector<history_line*> history;


    bool add(Order* o)
    {
        for (int i = 0; i < o->order_total.size(); i++)
        {
            stock_box* r = lookup(o->order_total[i]->object);

            if (r != NULL)
            {
                r->amount += o->order_total[i]->amount;
            }

            else
            {
                stock_box* x = new stock_box();

                x->object = o->order_total[i]->object;

                x->amount = o->order_total[i]->amount;

                stock_total.push_back(x);
            }

            history_line* h = new history_line();

            h->operation = "Lisa";

            h->object = o->order_total[i]->object;

            h->amount = o->order_total[i]->amount;

            history.push_back(h);
        }

        return true;
    }


    bool remove(Order* o)
    {
        for (int i = 0; i < o->order_total.size(); i++)
        {
            stock_box* r = lookup(o->order_total[i]->object);

            if (r == NULL ||
                r->amount < o->order_total[i]->amount)
            {
                return false;
            }

            r->amount -= o->order_total[i]->amount;

            history_line* h = new history_line();

            h->operation = "Eemalda";

            h->object = o->order_total[i]->object;

            h->amount = o->order_total[i]->amount;

            history.push_back(h);
        }

        return true;
    }



    bool thief(Item* p, int amount)
{
    stock_box* r = lookup(p);

    if (r != NULL && r->amount >= amount)
    {
        r->amount -= amount;


        return true;
    }

    return false;
}

    

    bool check_stock()
    {
        for (int i = 0; i < stock_total.size(); i++)
        {
            int calc = 0;

            for (int j = 0; j < history.size(); j++)
            {
                if (stock_total[i]->object->equals(history[j]->object))
                {
                    if (history[j]->operation == "Lisa")
                        calc += history[j]->amount;

                    if (history[j]->operation == "Eemalda")
                        calc -= history[j]->amount;
                }
            }

            if (calc != stock_total[i]->amount)
                return false;
        }

        return true;
    }



    string string_out()
    {
        string result = "Laoseis:\n";

        for (int i = 0; i < stock_total.size(); i++)
        {
            result += stock_total[i]->object->string_out()
                + " x "
                + to_string(stock_total[i]->amount)
                + "\n";
        }

        return result;
    }
};