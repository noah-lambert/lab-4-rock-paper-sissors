#ifndef PAPER_H
#define PAPER_H

#include "wind.h"

/**
 * @class Paper
 * @author scrai002
 * @date 12/04/2019
 * @file paper.h
 * @brief A monster that always uses the paper attack
 * and is moved by the blowing wind.
 */
class Paper : public Monster
{
private:
    Wind *wind; // Pointer to the wind that drives this paper.
    
public:
    /**
     * @brief Construct a new paper monster.
     * @param x The location column
     * @param y The location row
     * @param monster_type  The type of monster
     * @param wind The wind that is to drive this paper
     */
    Paper(int x, int y, MonsterType monster_type, Wind &wind):
        Monster(x, y, monster_type), wind(&wind) {}
        
    /**
     * @brief Ask the monster what kind of attack it wants to use.
     * @param opponent_appearance What kind of monster the monster looks like.
     * @return A_paper.
     */
    virtual Attack get_attack(MonsterType UNUSED(opponent_appearance))
    {
        return Attack::A_paper;
    }
    
    /**
     * @brief Move as directed by the wind.
     * @return Whether the paper moved or not.
     */
    virtual bool clock()
    {   bool refresh=false;
        signed char d=wind->col();
        if(d)
        {
            x+=d;
            refresh=true;
        }
        
        d=wind->row();
        if(d)
        {
            y+=d;
            refresh=true;
        }
        
        return refresh;
    }
};

#endif // PAPER_H
