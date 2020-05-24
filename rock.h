#ifndef ROCK_H
#define ROCK_H

#include "monster.h"

/**
 * @class Rock
 * @author scrai002
 * @date 12/04/2019
 * @file rock.h
 * @brief A monster that always uses the rock attack.
 */
class Rock : public Monster
{
public:
    /**
     * @brief Construct a new rock monster.
     * @param x The location column
     * @param y The location row
     * @param monster_type  The type of monster
     */
    Rock(int x, int y, MonsterType monster_type):
        Monster(x, y, monster_type) {}
        
    /**
     * @brief Ask the monster what kind of attack it wants to use.
     * @param opponent_appearance What kind of monster the monster looks like.
     * @return A_rock.
     */
    virtual Attack get_attack(MonsterType UNUSED(opponent_appearance))
    {
        return Attack::A_rock;
    }
};

#endif // SCISSORS_H