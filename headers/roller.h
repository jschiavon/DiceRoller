#ifndef ROLLER_H
#define ROLLER_H

#include <iostream>
#include <random>
#include <string>
#include <vector>

class Roller{

  private:
    // Attributes
    int repeat;
    int number;
    int die;
    int modifier;
    bool reroll = false;

    std::mt19937_64 _generator;
    std::uniform_int_distribution<> _uniform;
    std::vector<int> results;

    // Private methods

  public:
    // Constructors
    Roller();
    Roller(int r, int n, int d, int m);
    Roller(std::string str);

    // Methods
    void activate_reroll() {reroll = true;};
    std::vector<int> roll();
    double expectation();
    void print_roll();
    void print_expectation();

    // Overloaded operator
    friend std::ostream& operator<<(std::ostream& os, const Roller& rd);
};


#endif // ROLLER_H
