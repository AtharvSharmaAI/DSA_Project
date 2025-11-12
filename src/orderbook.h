#pragma once
#include<bits/stdc++.h>
#include "order.h"
using namespace std;

class orderbook{
    private:
    map<double,queue<order>> buy_map;
    map<double,queue<order>> sell_map;

    priority_queue<double> buy_cost;
    priority_queue<double , vector<double> , greater<double>> sell_cost;

    mutex order_mutex;

    public:
    void add(order &item);
    void cancel(int id);
    void match();
    void display();

};