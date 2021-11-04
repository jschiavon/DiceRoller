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
   _roller = std::uniform_int_distribution<>(1, die);
}

Roller::Roller(int r, int n, int d, int m)
{
    repeat = r;
    number = n;
    die = d;
    modifier = m;
    std::random_device rd;
    _generator = std::mt19937_64(rd());
    _roller = std::uniform_int_distribution<>(1, die);
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
    _roller = std::uniform_int_distribution<>(1, die);
}


// Private methods
int Roller::roll_boonbane(int b)
{
    int rolled;
    int result = 0;
    for (int i=0; i<b; i++){
        rolled = _boonbane(_generator);
        if (rolled > result) {result = rolled;}
    }
    return result;
}

double Roller::exp_boonbane(int b)
{
    double res = 0.;
    for (int i=1; i<7; i++){
        res += ((pow(i, b) - pow(i-1, b)) / pow(6., b)) * i;
    }
    return res;
}

// Public method
std::vector<int> Roller::roll()
{
    int rolled;
    std::vector<int> results;
    for (int i=0; i<repeat; i++){
        results.push_back(modifier);
        if (boon > 0){results[i] += roll_boonbane(boon);}
        if (bane > 0){results[i] -= roll_boonbane(bane);}
        for (int j=0; j<number; j++){
            rolled = _roller(_generator);
            if ((rolled == 1) && (reroll)) rolled = _roller(_generator);
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
    if (boon > 0){res += exp_boonbane(boon);}
    if (bane > 0){res -= exp_boonbane(bane);}

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

void Roller::set_boon_bane(int bo=0, int ba=0)
{
    int net_boon = bo - ba;
    if (net_boon == 0) {boon = 0; bane = 0;}
    else if (net_boon > 0) {boon = bo - ba; bane = 0;}
    else if (net_boon < 0) {boon = 0; bane = ba - bo;}
}

// Overloaded operator
std::ostream& operator<<(std::ostream& os, const Roller& rd)
{
        os << "Roll " ;
        if (rd.repeat > 1){
            os << rd.repeat << " times ";
        }

        os << rd.number << " " << rd.die
                << "-sided ";
        if (rd.number > 1) {os << "dices";}
        else {os << "die";}

        if (rd.modifier > 0){
            os <<  " plus " << rd.modifier;
        }

        if (rd.reroll){
            os << " with reroll";
        }
        return os;
    }
