#include <iostream>
#include <thread>
#include <random>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Number {
private:
    string name;
    int total;

public:
    explicit Number(string n) : name(std::move(n)), total(0) {}

    void run() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(1, 1000);

        for (int i = 0; i < 100; i++) {
            total += dist(gen);
        }
    }

    int getTotal() const { return total; }
    string getName() const { return name; }
};

int main() {
    // Create Number1 - Number10
    vector<Number> numbers;
    for (int i = 1; i <= 10; i++) {
        numbers.emplace_back("Number" + to_string(i));
    }

    // Launch threads
    vector<thread> threads;
    for (auto& n : numbers) {
        threads.emplace_back(&Number::run, &n);
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    // Print all scores
    for (const auto& n : numbers) {
        cout << n.getName() << " scored: " << n.getTotal() << '\n';
    }

    // Sort numbers in descending order by total
    sort(numbers.begin(), numbers.end(),
         [](const Number& a, const Number& b) {
             return a.getTotal() > b.getTotal();
         });

    // Winner is the first element after sorting
    cout << "\nThe winner is: " << numbers.front().getName()
         << " with " << numbers.front().getTotal() << " points\n";

    return 0;
}