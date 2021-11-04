#ifndef ROLLER_H
#define ROLLER_H

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <cmath>

class Roller{

  private:
    // Attributes
    int repeat;
    int number;
    int die;
    int modifier;
    int boon = 0;
    int bane = 0;
    bool reroll = false;

    std::mt19937_64 _generator;
    std::uniform_int_distribution<> _roller;
    std::uniform_int_distribution<> _boonbane = std::uniform_int_distribution<>(1, 6);
    std::vector<int> results;

    // Private methods
    int roll_boonbane(int b);
    double exp_boonbane(int b);

  public:
    // Constructors
    Roller();
    Roller(int r, int n, int d, int m);
    Roller(std::string str);

    // Methods
    void activate_reroll() {reroll = true;};
    void set_boon_bane(int, int);
    std::vector<int> roll();
    double expectation();
    void print_roll();
    void print_expectation();

    // Overloaded operator
    friend std::ostream& operator<<(std::ostream& os, const Roller& rd);
};


#endif // ROLLER_H
