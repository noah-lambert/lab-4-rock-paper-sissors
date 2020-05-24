#ifndef MONSTERFACTORY_H
#define MONSTERFACTORY_H

#include <memory>
#include <random>
#include <string>

#include "wind.h"

class Monster;

enum MonsterType    // List of known monster types
{
        M_rock,     // rock.h
        M_paper,    // paper.h
        M_scissors, // scissors.h
		M_Aaron_Judge // monster_noah.h
        M_NUM       // Constant equalling the number of monster types
};

/**
 * @class MonsterFactory
 * @author scrai002
 * @date 12/04/2019
 * @file monsterfactory.h
 * @brief Factory used to create instances of monsters.
 */
class MonsterFactory
{
    private:
        std::default_random_engine *generator;              // Source of randomness
        std::uniform_int_distribution<int> monster_type;    // Random MonsterType picker
        Wind wind;                                          // Wind to drive motion of paper
        
    public:
        static const std::string names[];                   // Plural names to describe MonsterTypes

        /**
         * @brief Create an object to help make monsters.
         * @param generator A source of randomness that is used by both the factory
         *                  and the monsters that it makes.
         */
		MonsterFactory(std::default_random_engine &generator):
            generator(&generator), monster_type(0, MonsterType::M_NUM-1),
            wind(generator) {}
            
        /**
         * @brief Update the factory every time game time advances.
         */
		void clock()
        {
            wind.clock();
        }
        
        /**
         * @brief Make a new monster.
         * @param column        The column of the monster's initial location.
         * @param row           The row of the monster's initial location.
         * @param monster_type  The type of monster to create.
         *                      If the type is not recognized (the default), a random type is selected.
         * @return A shared pointer to the new monster.
         */
        std::shared_ptr<Monster> make(int column, int row, MonsterType monster_type=MonsterType::M_NUM);
};

#endif //MONSTERFACTORY_H
