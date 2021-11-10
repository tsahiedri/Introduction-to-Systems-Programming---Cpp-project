#ifndef MEDIC_H_
#define MEDIC_H_
#include <memory>
#include "Auxiliaries.h"
#include "Character.h"
#include "Game.h"

namespace mtm{

    /** A class that represents the Medic type of character. It will inherit from the character class. */
    class Medic : public Character{

    public:

        Medic(units_t health, units_t ammo, Team team, units_t range, units_t power);

        ~Medic() override = default;

        /** A method that checks if there is enough ammo to make an attack.
         * If the target is on the same team as the attacking medic the attack won't take ammo.*/
        void checkIfEnoughAmmo(const GridPoint& dst_coordinates,
                               const std::vector<std::vector<std::shared_ptr<Character>>>& board) const override;

        /** A method used to check if on the given destination coordinates there is a valid target to attack. */
        void checkIfLegalTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates,
                                const std::vector<std::vector<std::shared_ptr<Character>>>& board) const override;

        /** A method used to make an attack on the character found on the destination coordinates. */
        void attack(const GridPoint& dst_coordinates, std::vector<std::vector<std::shared_ptr<Character>>>& board,
                    int& num_of_powerlifters, int& num_of_crossfitters) override;

        /** A method that returns the char that represents a medic, 'M' for a powerlifter and 'm' for a crossfitter. */
        char getTypeChar() override;

        /** A method that makes a copy of a medic. */
        std::shared_ptr<Character> clone() override
        {
            return std::shared_ptr<Character>(new Medic(health, ammo, team, range, power));
        }

    };
}

#endif //MEDIC_H_