#pragma once

class order{
    public :
    int id;
    char pos ;
    double price;
    int qty;

    order(int orid , char s , double cost , int amt)
    : id(orid), pos(s),price(cost),qty(amt) {}

    order():id(0),pos('B'),price(0),qty(0){}

};
