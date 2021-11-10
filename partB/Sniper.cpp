#include "Sniper.h"

namespace mtm{

    Sniper::Sniper(units_t health, units_t ammo, Team team, units_t range, units_t power, units_t attacks) :
    Character(health, ammo, team, range, power), attacks(attacks)
    {
        move_distance = 4;
        ammo_per_reload = 2;
    }

    void Sniper::checkIfDstInRange (const GridPoint& src_coordinates, const GridPoint& dst_coordinates) const
    {
        int distance = GridPoint::distance(src_coordinates, dst_coordinates);
        if(distance>range || distance < roundUp(range, 2))
        {
            throw OutOfRange();
        }
    }

    void Sniper::checkIfLegalTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates,
                            const std::vector<std::vector<std::shared_ptr<Character>>>& board) const
    {
        std::shared_ptr<Character> target = board[dst_coordinates.row][dst_coordinates.col];
        if (target == nullptr || target->getTeam() == team)
        {
            throw IllegalTarget();
        }
    }

    void Sniper::attack(const GridPoint& dst_coordinates, std::vector<std::vector<std::shared_ptr<Character>>>& board,
                            int& num_of_powerlifters, int& num_of_crossfitters)
    {
       std::shared_ptr<Character> &target = board[dst_coordinates.row][dst_coordinates.col];
       ammo--;
       attacks++;
       if(attacks %3 == 0)
       {
           target->gotAttacked(2*power, num_of_powerlifters, num_of_crossfitters, target);
       }
       else
       {
           target->gotAttacked(power, num_of_powerlifters, num_of_crossfitters, target);
       }
    }

    char Sniper::getTypeChar()
    {
        if(team==POWERLIFTERS)
    {
            return 'N';
    }
        return 'n';
    }


}