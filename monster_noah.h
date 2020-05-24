#ifndef NOAH_H
#define NOAH_H

#include "monster.h"

/*
 * Lab 4:  Noah's Monster
 * Author:  Noah Lambert
 * Date 4/22/19
 */
class Aaron_Judge : public Monster
{
private:
        std::default_random_engine *gen;    // The source of randomness
        
        std::uniform_int_distribution<signed char> dir;
                                            // The random motion selector
public:
    Aaron_Judge(int x, int y, MonsterType monster_type, std::default_random_engine &gen):
        Monster(x, y, monster_type), gen(&gen), dir(-2,2) {}
		
    virtual Attack get_attack(MonsterType opponent_appearance)
    {
        switch(opponent_appearance):	//checks the type of monster its about to fight 
		case scissors:					//Attacks scissors with rock  
			return Attack::A_rock;		
			break;
		case paper:						//Attacks paper with scissors 
			return Attack::A_scissors;
			break;
		case rock:						//Attacks rock with paper 
			return Attack::A_paper;
			break
		default:						//Defaults to rock 
			return Attack::A_rock;
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

#endif // NOAH_H