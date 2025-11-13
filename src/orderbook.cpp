#include<bits/stdc++.h>
#include<mutex>
#include "orderbook.h"
using namespace std;


void orderbook::add(order &item){
    lock_guard<mutex> lock(order_mutex);

    if(item.pos == 'B'){
        buy_map[item.price].push(item);
        buy_cost.push(item.price);
        cout << "buy order added successfully  " << item.id << " at " << item.price << " for " << item.qty << " orders" << endl;
    } else{
        sell_map[item.price].push(item);
        sell_cost.push(item.price);
        cout << "sell order added successfully  " << item.id << " at " << item.price << " for " << item.qty << " orders" << endl;
    }
}

void orderbook::cancel(int id){
    lock_guard<mutex> lock(order_mutex);
    cout << " please Resolve abhi bugged hai " << endl; // need attention here
}

void orderbook::match(){
    lock_guard<mutex> lock(order_mutex);

    while(!buy_cost.empty() && !sell_cost.empty()){
        double bid = buy_cost.top();
        double ask = sell_cost.top();

        if(bid < ask) break;

        if(buy_map.find(bid) == buy_map.end()){
            buy_cost.pop();
            continue;
        }

        if(sell_map.find(ask) == sell_map.end()){
            sell_cost.pop();
            continue;
        }

        auto & bqueue = buy_map[bid];
        auto & squeue = sell_map[ask];

        order border = bqueue.front();
        order sorder = squeue.front();

        int trade = min(border.qty , sorder.qty);

        cout << "Trade done " << endl;
        cout << "BUY id " << border.id << " Sell id " << sorder.id << " at price " << ask << " quantity : " << trade << endl; 


        border.qty -= trade;
        sorder.qty -= trade;

        bqueue.pop();
        squeue.pop();

        (border.qty == 0)?(squeue.push(sorder)):(bqueue.push(border));
        if(bqueue.empty()){
            buy_map.erase(bid);
            buy_cost.pop();
        }
        if(squeue.empty()){
            sell_map.erase(ask);
            sell_cost.pop();
        }
    }
}

void orderbook::display(){
    lock_guard<mutex> lock(order_mutex);
    cout << "\n    ORDER BOOK\n";
    cout << "BUY ORDERS\n";
    for(auto it = buy_map.rbegin() ; it != buy_map.rend() ; it++){
        cout << "Price :" << it->first << " order :" << it->second.size() << endl;
    }
    cout << "SELL ORDERS\n";
    for(auto it = sell_map.rbegin() ; it != sell_map.rend() ; it++){
        cout << "Price :" << it->first << " order :" << it->second.size() << endl;
    }
}
