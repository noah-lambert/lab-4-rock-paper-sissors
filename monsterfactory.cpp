#include "monsterfactory.h"

#include "rock.h"
#include "paper.h"
#include "scissors.h"
#include "monster_noah.h"

const std::string MonsterFactory::names[]=                   // Plural name to describe MonsterTypes
{
    "Rocks",
    "Papers",
    "Scissors",
	"Aaron Judge"
};


/**
 * @brief Make a new monster.
 * @param column        The column of the monster's initial location.
 * @param row           The row of the monster's initial location.
 * @param monster_type  The type of monster to create.
 *                      If the type is not recognized (the default), a random type is selected.
 * @return A shared pointer to the new monster.
 */
std::shared_ptr<Monster> MonsterFactory::make(int column, int row, MonsterType monster_type)
{
    switch(monster_type)
    {
        case MonsterType::M_rock:
            return std::shared_ptr<Monster>(new Rock(column, row, monster_type));
            
        case MonsterType::M_paper:
            return std::shared_ptr<Monster>(new Paper(column, row, monster_type, wind));
            
        case MonsterType::M_scissors:
            return std::shared_ptr<Monster>(new Scissors(column, row, monster_type, *generator));
            
        default:
            // If the type is not recognized (the default), a random type is selected.
            return make(row, column, static_cast<MonsterType>(this->monster_type(*generator)));
    }
}