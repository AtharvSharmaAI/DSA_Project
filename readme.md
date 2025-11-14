# Multithreaded Limit Order Book Simulator (C++)

## Overview
This project implements a simple, multithreaded Limit Order Book (LOB) simulator in C++. It models the core behavior of an exchange matching engine: multiple trader threads submit buy/sell limit orders concurrently while a matching-engine thread continuously matches compatible orders (best bid ≥ best ask). The implementation focuses on clarity and basic correctness rather than production-grade performance.

Key goals:
- Demonstrate an object-oriented approach to an order book.
- Show multithreading with thread-safe order submission and matching.
- Use standard C++ containers (map, queue, priority_queue) and synchronization primitives (mutex).

## Features
- Order submission (buy/sell) with price and quantity.
- Continuous matching engine that executes trades when the best bid ≥ best ask.
- Thread-safe operations on the order book.
- Simple simulation of concurrent traders submitting randomized orders.
- Final order book display after simulation completes.

## Repository layout
All code is located under `src/`:

```
src/
├── main.cpp          # Simulation entry point, trader threads, matching engine thread
├── order.h           # Order class declaration
├── order.cpp         # Order class implementation (header-only contents included)
├── orderbook.h       # OrderBook class declaration
└── orderbook.cpp     # OrderBook implementation (add, match, cancel, display)
```

## Requirements
- C++17 compatible compiler (g++ or clang++)
- POSIX threads support (or equivalent) — program compiles with `-pthread`
- Linux, macOS, or Windows (with an appropriate toolchain)

## Build and run

Open a terminal inside the `src/` folder and run:

```bash
g++ -std=c++17 main.cpp order.cpp orderbook.cpp -o limit_order_book -pthread
./limit_order_book
```

Flags:
- `-std=c++17` — use C++17
- `-pthread` — enable multithreading support
- `-o limit_order_book` — output executable

## Design & Key Types

### class order (src/order.h)
Represents a single limit order.

```cpp
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
```

### class orderbook (src/orderbook.h / src/orderbook.cpp)
Manages orders and matching. Important members:
- `map<double, queue<order>> buy_map;` — buy orders keyed by price (price -> FIFO queue)
- `map<double, queue<order>> sell_map;` — sell orders keyed by price
- `priority_queue<double> buy_cost;` — buy price heap (max-heap)
- `priority_queue<double, vector<double>, greater<double>> sell_cost;` — sell price heap (min-heap)
- `mutex order_mutex;` — protects book operations

Key public methods:
- `void add(order &item);` — thread-safe order submission (pushes to proper queue and pushes price into heap)
- `void match();` — attempts to match top-of-book buy and sell orders while best bid ≥ best ask; executes trades, updates quantities and price levels
- `void cancel(int id);` — placeholder: cancellation is marked as buggy in current implementation and needs fixes
- `void display();` — prints the current order book (price levels and order counts)

Notes about behavior:
- Matching dequeues from per-price FIFO queues to preserve time priority among same-price orders.
- After a trade, if an order still has residual quantity, it is pushed back to its respective queue.
- Empty price levels are erased and the corresponding price is popped from the heap.
- All public methods that mutate or traverse the order book use `lock_guard<mutex>` to maintain thread-safety.

## Multithreading / Simulation
- The simulation in `main.cpp` launches multiple trader threads (function `simulate`) that generate random orders:
  - Random price (1–100), quantity (1–10), and side (buy/sell).
  - Each trader submits a fixed number of orders and sleeps briefly between submissions to mimic delay.
- A separate engine thread (function `engine`) loops, calling `orderbook.match()` on an interval (e.g., every 200 ms) while a control flag is true.
- Once trader threads finish, the control flag is cleared and the engine thread is joined. Finally, the final order book is displayed.

## Example output (sample)
```
buy order added successfully 1 at 45 for 3 orders
sell order added successfully 2 at 47 for 5 orders
Trade done
BUY id 1 Sell id 2 at price 47 quantity : 3
...
FINAL ORDER BOOK
    ORDER BOOK
BUY ORDERS
Price :44 order :1
SELL ORDERS
Price :48 order :2
```

## Contributing
Contributions are welcome. Suggested workflow:
1. Fork the repository.
2. Create a descriptive branch (e.g., `fix/cancel-order` or `enhancement/condition-var`).
3. Add tests if possible and keep changes focused.
4. Open a pull request with a clear description of the change.

Before submitting larger changes, open an issue to discuss design choices.

## License
MIT License — see LICENSE (project currently indicates MIT).

## Contact
If you have questions, issues, or feature requests, please open an issue in this repository.
