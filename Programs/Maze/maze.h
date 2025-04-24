#ifndef MAZE_H
#define MAZE_H

#include <iostream>
#include <stack>
#include <queue>
#include <cstdlib>  
#include <conio.h> 

using namespace std;

// Maze structure 
struct Cell {
    int x, y;
    bool visited;
    bool walls[4]; // Top, Right, Bottom, Left

    Cell(int _x, int _y);
};

class Maze {
    private:
        int rows, cols;
        Cell*** grid;
        pair<int, int> playerPosition;
        //Klink: Teleport destination (optional for display or further use)
        pair<int, int> teleportDestination;


        //undo feature addition Start
        stack<pair<int, int>> undoStack; //Klink: undo stack to store previous positions
        //undo feature addition End

        //Rewards addition Start
        const static int MAX_REWARDS = 20;
        pair<int, int> rewardPositions[MAX_REWARDS]; 
        string rewardNames[MAX_REWARDS]; 
        int rewardCount; 
        int goldCoinsCollected = 0; // Klink: total gold coins collected
        //Rewards addition end

        int getUnvisitedNeighbors(Cell* cell, Cell* neighbors[]);
        void removeWalls(Cell& current, Cell& next);
        void movePlayer(char direction);

        // --- Teleportation Feature using Arrays ---
        const static int MAX_TELEPORTS = 10;
        pair<int, int> teleportFrom[MAX_TELEPORTS];
        pair<int, int> teleportTo[MAX_TELEPORTS];
        int teleportCount = 0;

    public:
        Maze(int r, int c);
        ~Maze();

        void displayMaze();
        void generateMaze();
        void play();

        // --- Additions start here ---

        // Undo Feature
        void pushUndoPosition(int x, int y);
        void undoMove();

        // Reward Collection
        void placeRewards(int count); 
        void checkReward(); 

        // Teleportation Feature
        //void setupTeleportPoints(); 
        void checkTeleport();

        // Hint Feature using BFS
        void requestHint();            // prompt and call BFS
        void showHint(pair<int, int> goalPosition); // BFS logic
};

#endif
