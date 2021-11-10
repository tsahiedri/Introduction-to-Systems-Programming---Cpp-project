#include "Soldier.h"

namespace mtm{

    Soldier::Soldier(units_t health, units_t ammo, Team team, units_t range, units_t power) :
    Character(health,ammo,team, range,power)
    {
        move_distance = 3;
        ammo_per_reload = 3;
    }

    void Soldier::checkIfLegalTarget(const GridPoint& src_coordinates, const GridPoint& dst_coordinates,
                                     const std::vector<std::vector<std::shared_ptr<Character>>> & board) const
    {
        if (src_coordinates.row != dst_coordinates.row && src_coordinates.col != dst_coordinates.col )
        {
            throw IllegalTarget();
        }
    }

    void Soldier::attack(const GridPoint& dst_coordinates, std::vector<std::vector<std::shared_ptr<Character>>> & board,
                int& num_of_powerlifters, int& num_of_crossfitters)
    {
        ammo--;
        std::shared_ptr<Character> &target = board[dst_coordinates.row][dst_coordinates.col];
        if (target != nullptr && team != target->getTeam())
        {
            target->gotAttacked(power, num_of_powerlifters, num_of_crossfitters,target);
        }
        int height = (int)board.size();
        int width = (int)board[0].size();
        GridPoint point(0,0);
        int range_area = roundUp(range,3);
        int dmg_area = roundUp(power,2);
        for(int i=0; i<height; i++)
        {
            for(int j=0; j<width; j++)
            {
                point.row = i;
                point.col = j;
                int distance = GridPoint::distance(dst_coordinates,point);
                if (distance <= range_area && distance !=0 )
                {
                    std::shared_ptr<Character> &new_target = board[i][j];
                    if (new_target != nullptr && team != new_target->getTeam())
                    {
                        new_target->gotAttacked(dmg_area, num_of_powerlifters, num_of_crossfitters, new_target);
                    }
                }
            }
        }
    }

    char Soldier::getTypeChar()
    {
        if(team == POWERLIFTERS)
        {
            return 'S';
        }
        return 's';
    }

}