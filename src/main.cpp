#include<bits/stdc++.h>
#include"orderbook.h"
#include<thread>
using namespace std;
typedef long long ll;

void simulate(orderbook &book , int no_orders){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> price_dist(1,100);
    uniform_int_distribution<> qty_dist(1,10);
    uniform_int_distribution<> stat_dist(0,1); 

    for(int i = 1 ;i<= no_orders ; i++){
        double cur_price = price_dist(gen);
        ll qty = qty_dist(gen);
        char pos = (stat_dist(gen) == 0)?('B'):('S');
        order new_order(i,pos,cur_price,qty);
        book.add(new_order);
        this_thread::sleep_for(chrono::milliseconds(100));

    }
    return;
}

void engine(orderbook &book , bool& flag){
    while(flag){
        book.match();
        this_thread::sleep_for(chrono::milliseconds(200));
    }
    return ;
}

int main(){
    orderbook book;
    bool flag = true;

    thread thread_s1(simulate , ref(book), 5);
    thread thread_s2(simulate , ref(book), 5);

    thread thread_e(engine , ref(book) , ref(flag));

    thread_s1.join();
    thread_s2.join();
    flag = false;
    thread_e.join();

    cout << "FINAL ORDER BOOK " << endl;
    book.display();
}

