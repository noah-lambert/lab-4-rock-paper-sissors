#ifndef ARENA_H
#define ARENA_H

#include <map>
#include <memory>
#include <set>
#include <sstream>
#include <utility>
#include <vector>

#include "monster.h"

typedef std::pair<int,int> Location;                    // x,y coordinates
typedef std::set<std::shared_ptr<Monster>> MonsterList; // A set of monsters
typedef std::map<Location, MonsterList> CollisionMap;   // The set of monsters at each location

/**
 * @class Arena
 * @author Dr. Steven P. Crain, s.crain@computer.org
 * @date 4/12/2019
 * @file arena.h
 * @brief   This class represents an arena where the monsters fight each other. 
 *          It manages theset of monsters and their fights.
 */
class Arena
{
private:
        std::default_random_engine generator;   // Source of randomness
        MonsterFactory factory;                 // Factory that makes monsters
        
        std::vector<std::shared_ptr<Monster>> monsters;
                                                // List of all living monsters
                                                
        int max_row,                            // Number of rows in the arena 
            max_column,                         // Number of columns in the arean
            countdown,                          // Time remaining until a winner is declared
            counts[MonsterType::M_NUM];         // The number of living monsters of each type
        
        /**
         * @brief Manage the process of deciding where to draw each monster.
         * @param app   The user interface that will show the monster.
         * @param monster   The monster to draw.
         * @param idx   An optional index that is used to detect collisions.
         */
        template<typename T>
        void draw_monster(T *app, std::shared_ptr<Monster> &monster, CollisionMap *idx=nullptr)
        {
            int x=monster->get_col()%max_column,
                y=monster->get_row()%max_row,
                ox=monster->get_old_col()%max_column,
                oy=monster->get_old_row()%max_row;
            
            if(x<0) x+=max_column;
            if(y<0) y+=max_row;
            if(ox<0) ox+=max_column;
            if(oy<0) oy+=max_row;

            if(x!=ox || y!=oy)
            {
                app->undraw_monster(ox,oy);
                if(idx) (*idx)[Location(ox,oy)].insert(monster);
            }
            
            app->draw_monster(*monster, x,y);
            if(idx && *monster) (*idx)[Location(x,y)].insert(monster);
        }
        
        /**
         * @brief Manage a fight between two monsters.
         * @param app   The UI that shows the fight happening.
         * @param a A monster in the fight.
         * @param b Another monster in the fight.
         */
        template<typename T>
        void fight(T *app, std::shared_ptr<Monster> a, std::shared_ptr<Monster> b)
        {
            if(!a->fight(*b))
                // The Monsters would not fight.
                return;
            
            if(!*a)
            {
                kill_monster(a);
                draw_monster<T>(app, a);
                if(!*b) kill_monster(b); // Should only happen if both monsters suicide.
                draw_monster<T>(app, b);
            } else
            {
                kill_monster(b);
                draw_monster<T>(app, b);
                draw_monster<T>(app, a);
            }
        }

        /**
         * @brief   Manage the collisions that happen at a single location.
         *          All pairs of monsters that are at this one location fight.
         * @param app   The UI to show the fights.
         * @param monsters  The set of monsters at this location.
         */
        template<typename T>
        void collisions(T *app, MonsterList &monsters)
        {
            // Loop over all pairs of monsters in the list.
            for(auto a=monsters.begin(); a!=monsters.end(); a++)
            {   auto b(a);
                for(b++; b!=monsters.end(); b++)
                    fight<T>(app, *a, *b);
            }
        }

        /**
         * @brief   Manage the collisions in the arena.
         *          All monsters that are in the same location fight each other.
         * @param app   The UI that will show the fights.
         * @param idx   The index of which monsters are at each location.
         */
        template<typename T>
        void collisions(T *app, CollisionMap &idx)
        {
            for(auto i=idx.begin(); i!=idx.end(); i++)
            {
                // This iterates over all the locations
                MonsterList &list=i->second;
                
                if(list.size()>1)
                {
                    // We have multiple monsters here. Let's get them to fight!
                    collisions<T>(app, list);
                }
            }
        }
        
public:
        /**
         * @brief Construct an arena.
         * @param max_row   The number of rows in the arena.
         * @param max_col   The number of columns in the arena.
         */
         Arena(int max_row, int max_column);

        /**
         * @brief Manage the process of removing a dead monster from the arena.
         * @param monster The monster that should be removed.
         */
        void kill_monster(std::shared_ptr<Monster> &monster);
        
        /**
         * @brief Manage the processing to display what is currently happening.
         * @param app The userinterface to show the arena.
         * @return The status message.
         */
        template<typename T>
        std::string onPaint(T *app) 
        {   CollisionMap idx;
            
            for(auto i=monsters.begin(); i!=monsters.end(); i++)
                draw_monster(app, *i, &idx);
            
            // Resolve any collisions
            collisions<T>(app, idx);

            // Update the status line
            std::ostringstream stat;
            int n=0, best=0;
            std::string winner;
            
            for(int t=0; t<MonsterType::M_NUM; t++)
            {
                stat << MonsterFactory::names[t] << ": " << counts[t] << " ";
                if(counts[t])
                {   n++;
                    if(counts[t]==best)
                        winner="Tie "+MonsterFactory::names[t]+" "+winner;
                    else if(counts[t]>best)
                    {
                        best=counts[t];
                        winner=MonsterFactory::names[t]+" Won!     ";
                    }
                }
            }
            
            if(!countdown)
                return winner+stat.str();
            else
                if(n>1)
                    return stat.str();
                else
                    return winner;
        }

        /**
         * @brief   Manage what happens at each point in time.
         *          The clock is delivered to everything in the arena.
         * @return 
         */
        bool clock();
};

#endif //ARENA_H
