#include "Medic.h"


namespace mtm{

        Medic::Medic(units_t health, units_t ammo, Team team, units_t range, units_t power) :
        Character(health, ammo, team, range, power)
        {
            move_distance = 5;
            ammo_per_reload = 5;
        }

        void Medic::checkIfEnoughAmmo(const GridPoint &dst_coordinates,
                                      const std::vector<std::vector<std::shared_ptr<Character>>> &board) const
        {
            std::shared_ptr<Character> target = board[dst_coordinates.row][dst_coordinates.col];
            if(ammo>=1 || (target != nullptr && target->getTeam() == team))
            {
                return;
            }
            throw OutOfAmmo();

        }

        void Medic::checkIfLegalTarget(const GridPoint &src_coordinates, const GridPoint &dst_coordinates,
                                   const std::vector<std::vector<std::shared_ptr<Character>>> &board) const
        {
            if (src_coordinates==dst_coordinates || board[dst_coordinates.row][dst_coordinates.col] == nullptr)
            {
                throw IllegalTarget();
            }
        }

        void Medic::attack(const GridPoint &dst_coordinates, std::vector<std::vector<std::shared_ptr<Character>>> &board,
                           int &num_of_powerlifters, int &num_of_crossfitters)
        {
            std::shared_ptr<Character> &target  = board[dst_coordinates.row][dst_coordinates.col];
            if(target->getTeam()==team)
            {
                target->gotAttacked(-power, num_of_powerlifters, num_of_crossfitters, target);
            }
            else
            {
                target->gotAttacked(power, num_of_powerlifters, num_of_crossfitters, target);
                ammo--;
            }
        }

        char Medic::getTypeChar()
        {
            if(team==POWERLIFTERS)
            {
                return 'M';
            }
            return 'm';
        }

}
