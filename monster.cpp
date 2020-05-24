#include "monster.h"

Attack Monster::choose_attack(MonsterType opponent_appearance)
{
    if(dead)
        return Attack::A_none;
    
    Attack attack=get_attack(opponent_appearance);
    
    switch(attack)
    {
        case Attack::A_rock:
        case Attack::A_paper:
        case Attack::A_scissors:
            return attack;
            
        default:
            dead=true;
            return Attack::A_none;
    }
}

bool Monster::fight(Monster &b)
{
    if(get_monster_type()==b.get_monster_type()  || !*this || !b)
        // The Monsters are buddies, or one is already dead, and will not fight.
        return false; // Nobody died.
        
    MonsterType img_a=get_appearance();
    Attack attack_a=choose_attack(b.get_appearance()),
           attack_b=b.choose_attack(img_a);
    
    if(attack_a==Attack::A_none)
        return b.winner=true;
    
    if(attack_b==Attack::A_none)
        return winner=true;
        
    switch((attack_a-attack_b+2)%3)
    {
        case 0: // Monster A wins
            b.dead=true;
            return winner=true;
            
        case 1: // Monster B wins
            dead=true;
            return b.winner=true;
    }
    
    return false;
}