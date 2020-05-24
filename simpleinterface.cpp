#include <iostream>

#include "arena.h"
#include "monsterfactory.h"

class SimpleInterface
{
private:
    Arena arena;
    
public:
    SimpleInterface(): arena(25,40) {}
    
    void undraw_monster(int UNUSED(x), int UNUSED(y)) {}

    void draw_monster(Monster &monster, int UNUSED(x), int UNUSED(y))
    {
        if(!monster) 
            std::cout << '\t' << MonsterFactory::names[monster.get_monster_type()] << " lost to ";
            
        if(monster.won())
            std::cout << MonsterFactory::names[monster.get_monster_type()] << ", the champion!" << std::endl;
    }

    void clock()
    {
        if(arena.clock())
        {
            std::string status=arena.onPaint<SimpleInterface>(this);
            std::cout << status << std::endl;
        }
    }
};

int main()
{
    SimpleInterface ui;
    
    for(int i=0; i<300; i++)
        ui.clock();
}