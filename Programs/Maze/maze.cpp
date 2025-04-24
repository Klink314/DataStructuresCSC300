#include "maze.h"

Cell::Cell(int _x, int _y) 
{
    x = _x;
    y = _y;
    visited = false;
    walls[0] = walls[1] = walls[2] = walls[3] = true;
}

Maze::Maze(int r, int c)
{
    rows = r;
    cols = c;
    playerPosition = {0, 0};
    
    // Rewards addition
    rewardCount = 0; // Klink

    grid = new Cell**[rows];
    for (int i = 0; i < rows; ++i) {
        grid[i] = new Cell*[cols];
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = new Cell(i, j);
        }
    }
}

Maze::~Maze() 
{
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            delete grid[i][j];
        }
        delete[] grid[i];
    }
    delete[] grid;
}

void Maze::displayMaze() 
{
    for (int i = 0; i < rows; ++i) {
        // Print top walls
        for (int j = 0; j < cols; ++j) {
            cout << (grid[i][j]->walls[0] ? "+---" : "+   ");
        }
        cout << "+" << endl;

        // Print left walls and cells with content (player or reward)
        for (int j = 0; j < cols; ++j) {
            cout << (grid[i][j]->walls[3] ? "|" : " ");
            
            // Player takes priority if overlapping a reward
            if (playerPosition.first == i && playerPosition.second == j) {
                cout << " P ";
            } else {
                bool hasReward = false;
                for (int k = 0; k < rewardCount; ++k) {
                    if (rewardPositions[k] == make_pair(i, j)) {
                        hasReward = true;
                        break;
                    }
                }
                cout << (hasReward ? " $ " : "   ");
            }
        }

        cout << "|" << endl; // Right wall
    }

    // Print bottom line
    for (int j = 0; j < cols; ++j) {
        cout << "+---";
    }
    cout << "+" << endl;
}


void Maze::generateMaze() 
{
    // Implementing randomized DFS for maze generation using stack
    stack<Cell*> cellStack;
    Cell* startCell = grid[0][0];
    startCell->visited = true;
    cellStack.push(startCell);
    while (!cellStack.empty()) {
        Cell* current = cellStack.top();
        Cell* neighbors[4];
        int neighborCount = getUnvisitedNeighbors(current, neighbors);
        if (neighborCount > 0) {
            Cell* next = neighbors[rand() % neighborCount];
            removeWalls(*current, *next);
            next->visited = true;
            cellStack.push(next);
        } else {
            cellStack.pop();
        }
    }
    // Rewards 
    placeRewards(5); // Klink

}

void Maze::play() 
{
    char input;
    while (true) {
            system("cls"); // Clear screen for Windows

        displayMaze();
        cout << "Use WASD to move (W = up, A = left, S = down, D = right), U to undo move, H = hint, T = teleport, Q to quit." << endl;
        input = _getch();
        if (input == 'q' || input == 'Q') {
            break;
        } 
        // undo move additions Klink
        else if (input == 'u' || input == 'U') {
            undoMove(); 
        } 
        // Hint addition Klink
        else if (input == 'h' || input == 'H') {
            requestHint(); 
        } 
        // Teleport addition Klink
        else if (input == 't' || input == 'T') {
            checkTeleport(); 
        }
        
        
        movePlayer(input);
        if (playerPosition == make_pair(rows - 1, cols - 1)) {
            system("cls");

            displayMaze();
            cout << "Congratulations! You've reached the end of the maze!" << endl;
            break;
        }
    }
}

int Maze::getUnvisitedNeighbors(Cell* cell, Cell* neighbors[]) 
{
    int x = cell->x;
    int y = cell->y;
    int count = 0;

    // Check all four neighbors
    if (x > 0 && !grid[x - 1][y]->visited) neighbors[count++] = grid[x - 1][y];
    if (y > 0 && !grid[x][y - 1]->visited) neighbors[count++] = grid[x][y - 1];
    if (x < rows - 1 && !grid[x + 1][y]->visited) neighbors[count++] = grid[x + 1][y];
    if (y < cols - 1 && !grid[x][y + 1]->visited) neighbors[count++] = grid[x][y + 1];

    return count;
}

void Maze::removeWalls(Cell& current, Cell& next) 
{
    int xDiff = current.x - next.x;
    int yDiff = current.y - next.y;
    if (xDiff == 1) {
        current.walls[0] = false;
        next.walls[2] = false;
    } else if (xDiff == -1) {
        current.walls[2] = false;
        next.walls[0] = false;
    } else if (yDiff == 1) {
        current.walls[3] = false;
        next.walls[1] = false;
    } else if (yDiff == -1) {
        current.walls[1] = false;
        next.walls[3] = false;
    }
}

void Maze::movePlayer(char direction) 
{
    int x = playerPosition.first;
    int y = playerPosition.second;
    int newX = x, newY = y;

    if (direction == 'w' || direction == 'W') {
        if (x > 0 && !grid[x][y]->walls[0]) newX--;
    } else if (direction == 'a' || direction == 'A') {
        if (y > 0 && !grid[x][y]->walls[3]) newY--;
    } else if (direction == 's' || direction == 'S') {
        if (x < rows - 1 && !grid[x][y]->walls[2]) newX++;
    } else if (direction == 'd' || direction == 'D') {
        if (y < cols - 1 && !grid[x][y]->walls[1]) newY++;
    }

    if (make_pair(newX, newY) != playerPosition) {
        pushUndoPosition(x, y); // Save only if movement happens
        playerPosition = {newX, newY};
        checkReward(); //Klink
    }
}


// Undo move feature addition start - Klink
// Stores the current player position on the undo stack
void Maze::pushUndoPosition(int x, int y) {
    undoStack.push({x, y});
}

// Moves the player back to the last recorded position
void Maze::undoMove() {
    if (!undoStack.empty()) {
        playerPosition = undoStack.top();  // Restore last position
        undoStack.pop();                   // Remove that step from history
        displayMaze();                     // Refresh the maze on screen
    } else {
        cout << "No moves to undo!" << endl;
    }
}
// Undo move feature addition end

// Rewards addition start - Klink
// Randomly places rewards in valid positions in the maze
void Maze::placeRewards(int count) {
    int placed = 0;
    while (placed < count && rewardCount < MAX_REWARDS) {
        int x = rand() % rows;
        int y = rand() % cols;
        pair<int, int> pos = {x, y};

        // Make sure reward isn't already placed, and not at start or end
        bool exists = false;
        for (int i = 0; i < rewardCount; ++i) {
            if (rewardPositions[i] == pos) {
                exists = true;
                break;
            }
        }

        // If position is valid, add the reward
        if (!exists && pos != make_pair(0, 0) && pos != make_pair(rows - 1, cols - 1)) {
            rewardPositions[rewardCount] = pos;
            rewardNames[rewardCount] = "Gold Coin"; // Currently only one type
            rewardCount++;
            placed++;
        }
    }
}

// Checks if player is standing on a reward and processes it
void Maze::checkReward() {
    for (int i = 0; i < rewardCount; ++i) {
        if (rewardPositions[i] == playerPosition) {
            cout << "\nYou found a " << rewardNames[i] << "!\n";

            // Update coin counter if the reward is a gold coin
            if (rewardNames[i] == "Gold Coin") {
                goldCoinsCollected++;
                cout << "Total Gold Coins: " << goldCoinsCollected << endl;
            }

            // Remove reward from the array by shifting remaining items left
            for (int j = i; j < rewardCount - 1; ++j) {
                rewardPositions[j] = rewardPositions[j + 1];
                rewardNames[j] = rewardNames[j + 1];
            }

            rewardCount--;
            system("pause");
            break;
        }
    }
}
// Rewards addition end

// Hint feature start
// Shows the next best step from the player to the goal
void Maze::showHint(pair<int, int> goalPosition) {
    queue<pair<int, int>> q;
    pair<int, int> parent[100][100];
    bool visited[100][100] = {false};

    // Start BFS from the player's current position
    q.push(playerPosition);
    visited[playerPosition.first][playerPosition.second] = true;

    // Direction arrays for navigating the maze
    int dirX[4] = {-1, 0, 1, 0}; // Up, Right, Down, Left
    int dirY[4] = {0, 1, 0, -1};

    // BFS to find the shortest path to the goal
    while (!q.empty()) {
        pair<int, int> cell = q.front(); q.pop();
        int x = cell.first;
        int y = cell.second;

        if (x == goalPosition.first && y == goalPosition.second) {
            break;
        }

        for (int d = 0; d < 4; ++d) {
            int nx = x + dirX[d];
            int ny = y + dirY[d];

            // Only move if next cell is within bounds, not visited, and no wall in the way
            if (nx >= 0 && ny >= 0 && nx < rows && ny < cols &&
                !visited[nx][ny] && !grid[x][y]->walls[d]) {
                visited[nx][ny] = true;
                parent[nx][ny] = make_pair(x, y); // Store parent for backtracking
                q.push(make_pair(nx, ny));
            }
        }
    }

    // If goal wasn't reached, inform the player
    if (!visited[goalPosition.first][goalPosition.second]) {
        cout << "No path to the goal!" << endl;
        system("pause");
        return;
    }

    // Trace back the path manually from goal to player
    pair<int, int> path[10000]; // Holds path cells
    int pathLen = 0;

    pair<int, int> curr = goalPosition;
    while (!(curr == playerPosition)) {
        path[pathLen++] = curr;
        curr = parent[curr.first][curr.second];
    }
    path[pathLen++] = playerPosition;

    // Display the second last step as the recommended next move
    if (pathLen > 1) {
        pair<int, int> nextStep = path[pathLen - 2];
        cout << "Hint: Try moving to cell (" << nextStep.first << ", " << nextStep.second << ")" << endl;
    } else {
        cout << "You're already at the goal!" << endl;
    }

    system("pause");
}

// Trigger for hint request, always aims for bottom-right goal
void Maze::requestHint() {
    pair<int, int> goal = make_pair(rows - 1, cols - 1);
    showHint(goal);
}
// Hint feature end

// Teleport feature start
// Randomly teleports player to a reachable cell
void Maze::checkTeleport() {
    while (true) {
        int tx = rand() % rows;
        int ty = rand() % cols;

        // BFS to make sure destination is reachable from current position
        queue<pair<int, int>> q;
        bool visited[100][100] = {false};

        q.push(playerPosition);
        visited[playerPosition.first][playerPosition.second] = true;

        int dirX[4] = {-1, 0, 1, 0};
        int dirY[4] = {0, 1, 0, -1};

        bool found = false;

        while (!q.empty()) {
            pair<int, int> cell = q.front(); q.pop();
            int x = cell.first;
            int y = cell.second;

            if (x == tx && y == ty) {
                found = true;
                break;
            }

            for (int d = 0; d < 4; ++d) {
                int nx = x + dirX[d];
                int ny = y + dirY[d];
                if (nx >= 0 && ny >= 0 && nx < rows && ny < cols &&
                    !visited[nx][ny] && !grid[x][y]->walls[d]) {
                    visited[nx][ny] = true;
                    q.push(make_pair(nx, ny));
                }
            }
        }

        // If a valid location is found, teleport the player
        if (found) {
            playerPosition = make_pair(tx, ty);
            cout << "\nYou teleported to (" << tx << ", " << ty << ")!\n";
            system("pause");
            return;
        }
    }
}
// Teleport feature end
