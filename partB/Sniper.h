#ifndef SNIPER_H_
#define SNIPER_H_
#include <memory>
#include "Auxiliaries.h"
#include "Character.h"
#include "Game.h"

namespace mtm{

    /** A class that represents the Sniper type of character. It will inherit from the character class. */
    class Sniper : public Character{

    private:
        units_t attacks;

    public:
        Sniper(units_t health, units_t ammo, Team team, units_t range, units_t power, units_t attacks =0);

        ~Sniper() override = default;

        /** A method used to check if the given destination coordinates are in the range of attack of
        * the sniper found on the source coordinates. */
        void checkIfDstInRange (const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const override;

        /** A method used to check if on the given destination coordinates there is a valid target to attack. */
        void checkIfLegalTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates,
                                const std::vector<std::vector<std::shared_ptr<Character>>>& board) const override;

        /** A method used to make an attack on the character found on the destination coordinates. */
        void attack(const GridPoint& dst_coordinates, std::vector<std::vector<std::shared_ptr<Character>>>& board,
                    int& num_of_powerlifters, int& num_of_crossfitters) override;

        /** A method that returns the char that represents a sniper, 
         * 'N' for a powerlifter and 'n' for a crossfitter. */
        char getTypeChar() override;

        /** A method that makes a copy of a sniper. */
        std::shared_ptr<Character> clone() override
        {
            return std::shared_ptr<Character> (new Sniper(health, ammo, team, range, power, attacks));
        }

    };
}

#endif //SNIPER_H_