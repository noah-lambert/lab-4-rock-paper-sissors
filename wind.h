#ifndef WIND_H
#define WIND_H

#include <random>

/**
 * @class Wind
 * @author scrai002
 * @date 12/04/2019
 * @file wind.h
 * @brief A class representing relatively realistic wind.
 */
class Wind
{
    private:
        signed char dx,                     // Current horizontal wind 
                    dy;                     // Current vertical wind
        std::default_random_engine *gen;    // The source of randomness
        
        std::uniform_int_distribution<signed char> dir;
                                            // The random wind selector
                                            
        std::exponential_distribution<float> shift;
                                            // The random when-wind-direction-
                                            // will-switch seletor
                                            
        std::bernoulli_distribution eddy;   // The small eddy disturbance selector
        float next_shift;                   // The duration to the next wind shift
    
public:
        /**
         * @brief Construct a new wind.
         * @param gen The source of randomness.
         */
        Wind(std::default_random_engine &gen):
            dx(0), dy(0), gen(&gen), 
            dir(-1, 1),     // Wind direction is uniformly picked to be -1, 0 or +1. 
            shift(0.1f),    // Wind shifts on average every 10 seconds (0.1 comes from 1/10.0)
            eddy(0.1),      // Eddies happen 10% of the time.
            next_shift(0.f) // The first shift should happen immediately.
        {   clock();    // Select the initial wind.
        }
            
        /**
         * @brief Get the vertical wind.
         * @return The vertical part of the wind direction.
         */
        int row()
        { return eddy(*gen)?dir(*gen):dy; // The wind direction or a random direction if there is an eddy.
        }
        
        /**
         * @brief Get the horizontal wind.
         * @return The horizontal part of the wind direction.
         */
        int col()
        { return eddy(*gen)?dir(*gen):dx; // The wind direction or a random direction if there is an eddy.
        }
        
        /**
         * @brief Process any shifts in wind direction.
         */
        virtual void clock()
        {
            if(next_shift<=0.f)
            {   // Time for the wind to shift
                dx=dir(*gen); // Choose new direction
                dy=dir(*gen);
                next_shift+=shift(*gen); // Choose when to next shift.
            }
            
            next_shift--; // Take one second off the time.
        }
};

#endif // WIND_H