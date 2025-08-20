#include <iostream>
#include <thread>
#include <random>
#include <string>
#include <vector>

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

    // Find the winner
    int maxScore = -1;
    string winner;

    for (const auto& n : numbers) {
        cout << n.getName() << " scored: " << n.getTotal() << '\n';
        if (n.getTotal() > maxScore) {
            maxScore = n.getTotal();
            winner = n.getName();
        }
    }

    cout << "\nThe winner is: " << winner << " with " << maxScore << " points\n";
    return 0;
}