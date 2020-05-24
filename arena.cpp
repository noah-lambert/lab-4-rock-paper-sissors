#include <ctime>
#include <map>
#include <random>
#include <iostream>
#include <string>
#include <sstream>

#include "arena.h"

Arena::Arena(int max_row, int max_column) : factory(generator), max_row(max_row), max_column(max_column), countdown(300)
{   int i=-1, j=0;
    std::exponential_distribution<float> gap(1.f/19.f);
    
    // Simple seeding so random numbers are not always the same.
    generator.seed(time(nullptr));
    
    for(int i=0; i<MonsterType::M_NUM; i++)
        counts[i]=0;
    
    while(j<max_row)
    {
        i+=int(gap(generator)+1.f);
        j+=i/max_column;
        i%=max_column;
        
        if(j<max_row)
        {   std::shared_ptr<Monster> m=factory.make(j,i);
            monsters.push_back(m);
            counts[m->get_monster_type()]++;
        }
    }
}

void Arena::kill_monster(std::shared_ptr<Monster> &monster)
{
    auto m=monsters.begin();
    for( ; m!=monsters.end() && (*m).get()!=monster.get(); m++);
    if(m!=monsters.end()) monsters.erase(m);
    
    int mt=monster->get_monster_type();
    if(counts[mt]>0) counts[mt]--;
}

bool Arena::clock() 
{   
    bool refresh=false;
    if(countdown>0) countdown--;
    factory.clock();
    for(auto i=monsters.begin(); i<monsters.end(); i++)
    {
        Monster &m=**i;
        if(m.clock())
            refresh=true;
    }
    
    return refresh;
}