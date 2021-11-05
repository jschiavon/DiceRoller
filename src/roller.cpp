#include "include/roller.h"

// Constructors
Roller::Roller()
{
   std::random_device rd;
   _generator = std::mt19937_64(rd());
   _roller = std::uniform_int_distribution<>(1, base_die.die);
}

Roller::Roller(int r, int n, int d, int m)
{
    base_die.repeat = r;
    base_die.number = n;
    base_die.die = d;
    base_die.modifier = m;
    std::random_device rd;
    _generator = std::mt19937_64(rd());
    _roller = std::uniform_int_distribution<>(1, base_die.die);
}

Roller::Roller(std::string rolls)
{
    std::string::iterator end_pos = std::remove(rolls.begin(), rolls.end(), ' ');
    rolls.erase(end_pos, rolls.end());

    if (rolls != std::string("")){
        auto pos = rolls.find("x");
        if (pos != std::string::npos){
            base_die.repeat = std::stoi(rolls.substr(0, pos));
            rolls = rolls.substr(pos + std::string("x").length());
        } else {base_die.repeat = 1;}

        pos = rolls.find("+");
        if (pos != std::string::npos){
            base_die.modifier = std::stoi(rolls.substr(pos, std::string::npos));
            rolls = rolls.substr(0, pos);
        } else {base_die.modifier = 0;}

        pos = rolls.find("d");
        if (pos != std::string::npos){
            base_die.number = std::stoi(rolls.substr(0, pos));
            rolls = rolls.substr(pos + std::string("x").length());
        } else {base_die.number = 1;}

        base_die.die = std::stoi(rolls);
    }
    std::random_device rd;
    _generator = std::mt19937_64(rd());
    _roller = std::uniform_int_distribution<>(1, base_die.die);
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
    for (int i=0; i<base_die.repeat; i++){
        results.push_back(base_die.modifier);
        if (boon > 0){results[i] += roll_boonbane(boon);}
        if (bane > 0){results[i] -= roll_boonbane(bane);}
        for (int j=0; j<base_die.number; j++){
            rolled = _roller(_generator);
            if ((rolled == 1) && (reroll)) rolled = _roller(_generator);
            if (adv){
                int r = _roller(_generator);
                if (r > rolled) rolled = r;
            }
            if (dis){
                int r = _roller(_generator);
                if (r < rolled) rolled = r;
            }
            results[i] += rolled;
        }
    }
    return results;
}

double Roller::expectation()
{
    double res;
    if (reroll) {
        res = 0.5 * (base_die.die + 2.) - 1. / (2. * base_die.die);
    } else if (adv){
        res = 0;
        for (int k = 1; k <= base_die.die; k++){
            res += ((pow(k, 2) - pow(k-1, 2)) / pow(base_die.die, 2)) * k;
        }
    } else if (dis){
        res = 0;
        for (int k = 1; k <= base_die.die; k++){
            res += ((pow(base_die.die - k + 1, 2) - pow(base_die.die - k, 2)) / pow(base_die.die, 2)) * k;
        }
    } else {
        res = 0.5 * (base_die.die + 1.);
    }

    if (boon > 0){res += exp_boonbane(boon);}
    if (bane > 0){res -= exp_boonbane(bane);}

    res *= base_die.number;
    res += base_die.modifier;

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

void Roller::set_advantages(bool a, bool d)
{
    if (a != d){
        adv = a;
        dis = d;
    }
}

// Overloaded operator
std::ostream& operator<<(std::ostream& os, const Roller& rd)
{
        os << "Roll " ;
        if (rd.base_die.repeat > 1){
            os << rd.base_die.repeat << " times ";
        }

        os << rd.base_die.number << " " << rd.base_die.die
                << "-sided ";
        if (rd.base_die.number > 1) {os << "dices";}
        else {os << "die";}

        if (rd.base_die.modifier > 0){
            os <<  " plus " << rd.base_die.modifier;
        }

        if (rd.reroll){
            os << " with reroll";
        }
        return os;
    }
