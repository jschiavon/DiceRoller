#include "include/roller.h"

// Constructors
Roller::Roller()
{
   repeat = 1;
   number = 1;
   die = 6;
   modifier = 0;
   reroll = false;
   std::random_device rd;
   _generator = std::mt19937_64(rd());
   _uniform = std::uniform_int_distribution<>(1, die);
}

Roller::Roller(int r, int n, int d, int m)
{
    repeat = r;
    number = n;
    die = d;
    modifier = m;
    std::random_device rd;
    _generator = std::mt19937_64(rd());
    _uniform = std::uniform_int_distribution<>(1, die);
}

Roller::Roller(std::string rolls)
{
    if (rolls == std::string("")){
        repeat = 1;
        number = 1;
        die = 6;
        modifier = 0;
    } else {
        auto pos = rolls.find("x");
        if (pos != std::string::npos){
            repeat = std::stoi(rolls.substr(0, pos));
            rolls = rolls.substr(pos + std::string("x").length());
        } else {repeat = 1;}

        pos = rolls.find("+");
        if (pos != std::string::npos){
            modifier = std::stoi(rolls.substr(pos, std::string::npos));
            rolls = rolls.substr(0, pos);
        } else {modifier = 0;}

        pos = rolls.find("d");
        if (pos != std::string::npos){
            number = std::stoi(rolls.substr(0, pos));
            rolls = rolls.substr(pos + std::string("x").length());
        } else {number = 1;}

        die = std::stoi(rolls);
    }
    std::random_device rd;
    _generator = std::mt19937_64(rd());
    _uniform = std::uniform_int_distribution<>(1, die);
}


// Private methods


// Public method
std::vector<int> Roller::roll()
{
    int rolled;
    std::vector<int> results;
    for (int i=0; i<repeat; i++){
        results.push_back(modifier);
        for (int j=0; j<number; j++){
            rolled = _uniform(_generator);
            if ((rolled == 1) && (reroll)) rolled = _uniform(_generator);
            results[i] += rolled;
        }
    }
    return results;
}

double Roller::expectation()
{
    double res;
    if (reroll) {
        res = 0.5 * (die + 2.) - 1. / (2. * die);
    } else {
        res = 0.5 * (die + 1.);
    }
    res *= number;
    res += modifier;
    return res;
}

void Roller::print_roll()
{
    std::cout << this << "..." << std::endl;
    std::vector <int> results = roll();

    if (results.size() == 1){
        std::cout << results[0] << std::endl;
    } else {
        std::cout << std::endl;
        int counter = 1;
        for (int r : results){
            std::cout << "\tRoll " << counter << ": " << r << std::endl;
            counter += 1;
        }
    }
}

void Roller::print_expectation()
{
    std::cout << "If you want to " << this << "..." << std::endl;
    std::cout << "Expect: " << expectation() << std::endl;
}

// Overloaded operator
std::ostream& operator<<(std::ostream& os, const Roller& rd)
{
        os << "Roll " ;
        if (rd.repeat > 1){
            os << rd.repeat << " times ";
        }

        os << rd.number << " " << rd.die
                << "-sided dices";

        if (rd.modifier > 0){
            os <<  " plus " << rd.modifier;
        }

        if (rd.reroll){
            os << " with reroll";
        }
        return os;
    }
