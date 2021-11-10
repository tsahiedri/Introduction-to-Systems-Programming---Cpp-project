#ifndef SOLDIER_H_
#define SOLDIER_H_
#include "Character.h"
#include "Auxiliaries.h"
#include "Game.h"


namespace mtm{

    /** A class that represents the Soldier type of character. it will inherit from Character class. */
    class Soldier : public Character{
    public:
        Soldier(units_t health, units_t ammo, Team team, units_t range, units_t power);

        ~Soldier() override= default;



        /** A method used to check if on the given destination coordinates there is a valid target to attack. */
        void checkIfLegalTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates,
                                const std::vector<std::vector<std::shared_ptr<Character>>> & board) const override;

        /** A method used to make an attack on the character found on the destination coordinates. */
        void attack(const GridPoint& dst_coordinates, std::vector<std::vector<std::shared_ptr<Character>>> & board,
                            int& num_of_powerlifters, int& num_of_crossfitters) override;

        /** A method that returns the char that represents a soldier,
         * 'S' for a powerlifter and 's' for a crossfitter. */
        char getTypeChar() override;

        /** A method that makes a copy of a soldier. */
        std::shared_ptr<Character> clone() override
        {
            return (std::shared_ptr<Character> (new Soldier(health, ammo, team, range, power)));
        }

    };
}

#endif // SOLDIER_H_