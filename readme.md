Multithreaded Limit Order Book Simulator (C++)
Overview
This project implements a simple, multithreaded Limit Order Book (LOB) simulator in C++. It models the core behavior of an exchange matching engine: multiple trader threads submit buy/sell limit orders concurrently while a matching-engine thread continuously matches compatible orders (best bid ≥ best ask). The implementation focuses on clarity and basic correctness rather than production-grade performance.

Key goals:

Demonstrate an object-oriented approach to an order book.
Show multithreading with thread-safe order submission and matching.
Use standard C++ containers (map, queue, priority_queue) and synchronization primitives (mutex).
Features
Order submission (buy/sell) with price and quantity.
Continuous matching engine that executes trades when the best bid ≥ best ask.
Thread-safe operations on the order book.
Simple simulation of concurrent traders submitting randomized orders.
Final order book display after simulation completes.
Repository layout
All code is located under src/:

src/
├── main.cpp          # Simulation entry point, trader threads, matching engine thread
├── order.h           # Order class declaration
├── order.cpp         # Order class implementation (header-only contents included)
├── orderbook.h       # OrderBook class declaration
└── orderbook.cpp     # OrderBook implementation (add, match, cancel, display)
Requirements
C++17 compatible compiler (g++ or clang++)
POSIX threads support (or equivalent) — program compiles with -pthread
Linux, macOS, or Windows (with an appropriate toolchain)
Build and run
Open a terminal inside the src/ folder and run:

g++ -std=c++17 main.cpp order.cpp orderbook.cpp -o limit_order_book -pthread
./limit_order_book
Flags:

-std=c++17 — use C++17
-pthread — enable multithreading support
-o limit_order_book — output executable
Design & Key Types
class order (src/order.h)
Represents a single limit order.

class order {
public:
    int id;      // unique identifier (int)
    char pos;    // 'B' for buy, 'S' for sell
    double price;
    int qty;

    order(int orid, char s, double cost, int amt)
      : id(orid), pos(s), price(cost), qty(amt) {}

    order() : id(0), pos('B'), price(0), qty(0) {}
};