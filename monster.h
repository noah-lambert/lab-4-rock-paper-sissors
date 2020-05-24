#ifndef MONSTERS_H
#define MONSTERS_H

#include <memory>
#include <set>
#include <utility>

// Source: https://stackoverflow.com/a/12891181
#ifdef __GNUC__
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif

#include "monsterfactory.h"

/**
 * The possible attacks. 
 *      None always loses. 
 *      Rock wins agains Scissors. 
 *      Paper wins agains Rock. 
 *      Scissors win against paper.
 */
enum Attack { A_none, A_rock, A_paper, A_scissors, A_NUM };

/**
 * @class Monster
 * @author scrai002
 * @date 4/12/2019
 * @file monster.h
 * @brief A class representing monsters that fight using the
 *        rock-paper-scissors game.
 */
class Monster
{
protected:
    int x, y;                   // Current location
    
private:
    int ox, oy;                 // Previous location
    MonsterType monster_type;   // Type of monster
    bool    dead,               // Whether monster is dead 
            winner;             // Whether monster has won a fight
    
public:
    /**
     * @brief Construct a monster
     * @param x The column where the monster is.
     * @param y The row where the monster is.
     * @param monster_type  The type of monster.
     */
    Monster(int x, int y, MonsterType monster_type):
        x(x), y(y), ox(x), oy(y), monster_type(monster_type),
        dead(false), winner(false) {}
     
    /**
     * @brief Destruct the monster.
     */
    virtual ~Monster() {}
     
    /**
     * @brief Ask the monster what kind of attack it wants to use.
     * @param opponent_appearance What kind of monster the monster looks like.
     * @return The selected attack.
     */
    virtual Attack get_attack(MonsterType UNUSED(opponent_appearance))=0;

    /**
     * @brief Ask the monster what it wants to look like.
     * @return The apparent type of monster.
     */
    virtual MonsterType get_appearance()
    {
        return monster_type;    // By default, the monster looks like itself.
    }
    
    /**
     * @brief Give the monster a chance to move.
     * @return Whether the monster moved.
     */
    virtual bool clock() 
    {   return false;
    }
    
    /**
     * @brief Get the type of monster.
     * @return The type of monster.
     */
    int get_monster_type()
    {
        return monster_type;
    }
    
    /**
     * @brief Get the monster's row.
     * @return The row.
     */
    int get_row() const
    {   return y;
    }
    
    /**
     * @brief Get the monter's column.
     * @return The column.
     */
    int get_col() const
    {   return x;
    }
    
    /**
     * @brief Get the monster's old row.
     * @return The row from the last time the monster was seen.
     */
    int get_old_row()
    {   int o=oy;
        oy=y;
        return o;
    }
    
    /**
     * @brief Get the monster's old column.
     * @return The column from the last time the monster was seen.
     */
    int get_old_col()
    {   int o=ox;
        ox=x;
        return o;
    }
    
    /**
     * @brief Fight with another monster.
     * @param other The monster to fight with.
     * @return Whether or not a monster died during the fight.
     */
    bool fight(Monster &other);
    
    /**
     * @brief Return whether the monster is alive.
     */
    operator bool()
    {
        return !dead;
    }
    
    /**
     * @brief Check if the monster recently won a fight.
     * @return Whether the monster won.
     */
    bool won()
    {
        bool yes=winner;
        winner=false;
        return yes;
    }
    
private:
    /**
     * @brief Validate the monster's attack.
     * This asks the monster what kind of attack it wants to use.
     * If the monster picks something illegal, the moster
     * dies and uses None for the attack.
     * @param opponent_appearance What the opponent looks like.
     * @return The validated attack.
     */
    Attack choose_attack(MonsterType opponent_appearance);
};

#endif //MONSTERS_H
