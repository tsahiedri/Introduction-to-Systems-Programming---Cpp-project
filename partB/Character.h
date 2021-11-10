#ifndef CHARACTER_H_
#define CHARACTER_H_
#include <memory>
#include <vector>
#include "Auxiliaries.h"
#include "Exceptions.h"

namespace mtm{
    /** A class that represents a character. This class is an abstract class, which means some of its methods are
     * pure virtual and objects of "character" type can't be created and used.*/
    class Character{
    protected:
        units_t health;
        units_t ammo;
        units_t move_distance;
        units_t ammo_per_reload;
        Team team;
        units_t range;
        units_t power;
        static int roundUp(int num, int divider)
        {
            if (num %divider == 0)
            {
                return num/divider;
            }
            else
                return (num/divider +1);
        }

    public:
        Character(units_t health, units_t ammo, Team team, units_t range, units_t power) :
        health(health), ammo(ammo),team(team), range(range), power(power) {}

        virtual ~Character() {}
        Character & operator=(const Character & character) = default;

        /** A method that returns the team of a character.*/
        Team getTeam() const
        {
            return team;
        }

        /** A method that checks if the given move is possible, using the GridPoint::distance function. */
        void checkIfMovePossible(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const
        {
            if(GridPoint::distance(src_coordinates, dst_coordinates)>move_distance)
            {
                throw MoveTooFar();
            }
        }

        /** A method used to check if the given destination coordinates are in the range of attack of
         * the character found in the source coordinates. 
         * It can be overrided by characters with special attack rules. */
        virtual void checkIfDstInRange(const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const
        {
            if (GridPoint::distance(src_coordinates, dst_coordinates) > range)
            {
                throw OutOfRange();
            }
        }

        /** A method that checks if there is enough ammo to make an attack. 
         * It can be overrided by characters with special ammo rules */
        virtual void checkIfEnoughAmmo(const GridPoint& dst_coordinates,
                                       const std::vector<std::vector<std::shared_ptr<Character>>> & board) const
        {
            if(ammo<1)
            {
                throw OutOfAmmo();
            }
        }

        /** A virtual function that checks if the target coordinates can be attacked by the given character.
         * It doesn't check the range, only the target. Since there are different conditions on the target for each
         * character type, this function is pure virtual. */
        virtual void checkIfLegalTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates,
                                        const std::vector<std::vector<std::shared_ptr<Character>>> & board) const = 0;

        /** A virtual function that causes this character to attack the target on the given coordinates.
         * It's pure virtual because each character type attacks differently */
        virtual void attack(const GridPoint& dst_coordinates,
                            std::vector<std::vector<std::shared_ptr<Character>>> & board,
                            int& num_of_powerlifters, int& num_of_crossfitters) = 0;
        
        /** A method that adds ammo to the character according to the ammo_per_reload parameter, that was determined by
         * the character type. */
        void reload()
        {
            ammo += ammo_per_reload;
        }

        /** A method that returns the letter that represents the character when printing the game. */ 
        virtual char getTypeChar() = 0;

        /**  A method that creates a copy of a character. */
        virtual std::shared_ptr<Character> clone() = 0;
        
        /** A method used in order to deal damage to a character. It reduces the damage from the character's health points.
         * If the character is left with an amount of health points that is less or equal to zero,
         * it will remove it from the game. When a character is healed, we call this function with negative damage. */
        void gotAttacked(int damage, int& num_of_powerlifters,
                         int& num_of_crossfitters, std::shared_ptr<Character>& address)
        {
            health -= damage;
            if (health <= 0)
            {
                if (team == POWERLIFTERS)
                {
                    num_of_powerlifters--;
                } else {
                    num_of_crossfitters--;
                }
                address = nullptr;
            }
        }

    };
}

#endif //CHARACTER_H_