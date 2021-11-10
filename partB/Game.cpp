#include "Game.h"
#include <iostream>
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"

namespace mtm {
    Game::Game(int height, int width) : height(height), width(width), num_of_powerlifters(0), num_of_crossfitters(0) {
        if (height <= 0 || width <= 0)
        {
            throw IllegalArgument();
        }
        board.resize(height);
        for (int i = 0; i < height; ++i)
        {
            board[i].resize(width);
        }
    }

    Game &Game::operator=(const Game &game)
        {
        if (this == &game)
        {
            return *this;
        }
        height = game.height;
        width = game.width;
        num_of_powerlifters = game.num_of_powerlifters;
        num_of_crossfitters = game.num_of_crossfitters;
        board.resize(height);
        for (int k = 0; k < height; ++k)
        {
            board[k].resize(width);
        }
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; j++)
            {
                if (game.board[i][j] != nullptr)
                {
                    board[i][j] = (game.board[i][j]->clone());
                }
                else
                {
                    board[i][j] = nullptr;
                }
            }
        }
        return *this;
    }

    Game::Game(const Game &game)
    {
        *this = game;
    }

    std::shared_ptr<Character> Game::makeCharacter(CharacterType type, Team team,
                                                   units_t health, units_t ammo, units_t range, units_t power)
        {
        if (health <= 0 || ammo < 0 || range < 0 || power < 0)
        {
            throw IllegalArgument();
        }
        switch (type) {
            case (SOLDIER) :
            {
                return std::shared_ptr<Character>(new Soldier(health, ammo, team, range, power));
            }
            case (MEDIC) :
            {
                return std::shared_ptr<Character>(new Medic(health, ammo, team, range, power));
            }
            case (SNIPER) :
            {
                return std::shared_ptr<Character>(new Sniper(health, ammo, team, range, power));
            }
        }
        //Will never Get here
        return nullptr;
    }


    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character)
    {
        checkCoordinates(coordinates);
        checkOccupied(coordinates);
        board[coordinates.row][coordinates.col] = character;
        if (character->getTeam() == POWERLIFTERS)
        {
            num_of_powerlifters++;
        }
        else
        {
            num_of_crossfitters++;
        }
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        checkCoordinates(src_coordinates);
        checkCoordinates(dst_coordinates);
        checkSrcEmpty(src_coordinates);
        std::shared_ptr<Character> character = board[src_coordinates.row][src_coordinates.col];
        character->checkIfMovePossible(src_coordinates, dst_coordinates);
        checkOccupied(dst_coordinates);
        board[dst_coordinates.row][dst_coordinates.col] = character;
        board[src_coordinates.row][src_coordinates.col] = nullptr;
    }

    bool Game::isOver(Team *winningTeam) const
    {
        if (num_of_powerlifters > 0 && num_of_crossfitters == 0)
        {
            if (winningTeam != nullptr)
            {
                *winningTeam = POWERLIFTERS;
            }
            return true;
        }
        if (num_of_crossfitters > 0 && num_of_powerlifters == 0)
        {
            if (winningTeam != nullptr)
            {
                *winningTeam = CROSSFITTERS;
            }
            return true;
        }
        return false;
    }

    void Game::reload(const GridPoint &coordinates)
    {
        checkCoordinates(coordinates);
        checkSrcEmpty(coordinates);
        std::shared_ptr<Character> character = board[coordinates.row][coordinates.col];
        character->reload();
    }

    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        checkCoordinates(src_coordinates);
        checkCoordinates(dst_coordinates);
        checkSrcEmpty(src_coordinates);
        std::shared_ptr<Character> src_character = board[src_coordinates.row][src_coordinates.col];
        src_character->checkIfDstInRange(src_coordinates, dst_coordinates);
        src_character->checkIfEnoughAmmo(dst_coordinates, board);
        src_character->checkIfLegalTarget(src_coordinates, dst_coordinates, board);
        src_character->attack(dst_coordinates, board, num_of_powerlifters, num_of_crossfitters);
    }

    std::ostream &operator<<(std::ostream &os, const Game &game)
    {
        std::vector<char> board_to_print;
        for (int row = 0; row < game.height; row++)
        {
            for (int col = 0; col < game.width; col++)
            {
                std::shared_ptr<Character> character = game.board[row][col];
                if (character == nullptr)
                {
                    board_to_print.insert(board_to_print.end(), ' ');
                }
                else
                {
                    board_to_print.insert(board_to_print.end(), character->getTypeChar());
                }
            }
        }
        printGameBoard(os, &board_to_print[0], &board_to_print[game.height * game.width], game.width);
        return os;
    }


}
