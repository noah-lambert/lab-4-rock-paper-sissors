#ifndef SCISSORS_H
#define SCISSORS_H

#include "monster.h"

/**
 * @class Scissors
 * @author scrai002
 * @date 12/04/2019
 * @file scissors.h
 * @brief A monster that always uses the scissors attack
 * and moves randomly.
 */
class Scissors : public Monster
{
private:
        std::default_random_engine *gen;    // The source of randomness
        
        std::uniform_int_distribution<signed char> dir;
                                            // The random motion selector
public:
    /**
     * @brief Construct a scissors monster.
     * @param x The location column
     * @param y The location row
     * @param monster_type  The type of monster
     * @param gen The source of randomness
     */
    Scissors(int x, int y, MonsterType monster_type, std::default_random_engine &gen):
        Monster(x, y, monster_type), gen(&gen), dir(-2,2) {}
        
     /**
     * @brief Ask the monster what kind of attack it wants to use.
     * @param opponent_appearance What kind of monster the monster looks like.
     * @return A_scissors.
     */
    virtual Attack get_attack(MonsterType UNUSED(opponent_appearance))
    {
        return Attack::A_scissors;
    }
    
    /**
     * @brief Move randomly.
     * @return Always returns true, which is correct 96% of the time.
     */
    virtual bool clock()
    {
        x+=dir(*gen);
        y+=dir(*gen);
        return true;
    }
};

#endif // SCISSORS_H