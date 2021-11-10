#ifndef GAME_H_
#define GAME_H_
#include <memory>
#include <iostream>
#include <vector>
#include "Auxiliaries.h"
#include "Exceptions.h"
#include "Character.h"



namespace mtm{

    /**
     *The Game class. It will organize the details of a specific game, including the board, his properties,
     * and the number of players in each of the teams. This class also has the functions the players can use.*/
    class Game{
    private:
        int height;
        int width;
        int num_of_powerlifters;
        int num_of_crossfitters;
        std::vector<std::vector<std::shared_ptr<Character>>> board;

        /** Checks if the given point is within the limits of the permitted range,
         * and if not it throws the appropriate exception. */
        void checkCoordinates(const GridPoint & coordinates)
        {
            if (coordinates.row < 0 || coordinates.col < 0 || coordinates.row >= height || coordinates.col >= width)
            {
                throw IllegalCell();
            }
        }

        /** Checks if the given point is empty and throws the appropriate exception if it is. */
        void checkSrcEmpty(const GridPoint & coordinates)
        {
            if (board[coordinates.row][coordinates.col] == nullptr)
            {
                throw CellEmpty();
            }
        }

        /** Checks if the given point is already occupied by a character and throws the appropriate
         * exception if it is.*/
        void checkOccupied(const GridPoint & coordinates)
        {
            if (board[coordinates.row][coordinates.col] != nullptr)
            {
                throw CellOccupied();
            }
        }

    public:
        /** A Game constructor. It checks the given height and width and resize the board to fit them. */
        Game(int height, int width);

        /** The default destructor made by the compiler. */
        ~Game() = default;

        /** A copy constructor used to copy a game. The new game and the original one will be independent. */
        Game(const Game & game);

        /** An assignment operator for the game. */
        Game & operator=(const Game & game);

        /** Adds a character to the given point if possible, and throws the relevant exception if it isn't.
         * It also updates the number of characters at the relevant team. */
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);

        /** Creates a character with the given properties, and returns a shared_ptr to it. */
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                        units_t health, units_t ammo, units_t range, units_t power);

        /** Moves a character from the source coordinates to the destination coordinates after making sure that there's
         * a character on the source coordinates, that the destination coordinates are empty and that this is a
         * legitimate move for the character that is supposed to move. */
        void move(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

        /** Causes the character in the source coordinates to attack the character in the destination coordinates
         * if as a result from the attack the attacked character has 0 health, it will be removed from the game. */
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

        /** Adding ammo to the character found at the given coordinates. If there isn't one,
         * an exception will be thrown. Each character type has a different amount of ammo added at a reload. */
        void reload(const GridPoint & coordinates);

        /** Overloading the '<<' operator in order to be able to print the game. */
        friend std::ostream& operator<<(std::ostream& os, const Game& game);

        /** Checks if at the current board status there's a winning team.
         * This will happen if there are only characters from one team on the board. */
        bool isOver(Team* winningTeam=NULL) const;
    };
}

#endif //GAME_H_