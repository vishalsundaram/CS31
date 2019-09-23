// yorps.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the utterly trivial
// functions (marked TRIVIAL).  Then get Arena::display going.  That gives
// you more flexibility in the order that you choose to tackle the rest of
// the functionality.  As you finish implementing each TODO: item, remove
// its TODO: comment; that makes it easier to find what you have left to do.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
#include <cassert>

using namespace std;


///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;            // max number of rows in the arena
const int MAXCOLS = 20;            // max number of columns in the arena
const int MAXYORPS = 100;          // max number of yorps allowed
const int MAXCOLORS = 3;           // max number of colors
const double WALL_DENSITY = 0.14;  // density of walls

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Yorp declaration.

class Yorp
{
public:
    // Constructor
    Yorp(Arena* ap, int r, int c, char color);
    
    // Accessors
    int  row() const;
    int  col() const;
    char color() const;
    bool isDead() const;
    
    // Mutators
    void forceMove(int dir);
    void move();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    char   m_color;
    int    m_damage; //checks how much damage yorp has taken
};

class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    string stand();
    string move(int dir);
    void   setDead();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

class Arena
{
public:
    // Constructor/destructor
    Arena(int nRows, int nCols);
    ~Arena();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     yorpCount() const;
    bool    hasWallAt(int r, int c) const;
    int     numberOfYorpsAt(int r, int c) const;
    void    display(string msg) const;
    
    // Mutators
    void   placeWallAt(int r, int c);
    bool   addYorp(int r, int c, char color);
    bool   addPlayer(int r, int c);
    string moveYorps(char color, int dir);
    
private:
    bool    m_wallGrid[MAXROWS][MAXCOLS];
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Yorp*   m_yorps[MAXYORPS];
    int     m_nYorps;
    
    // Helper functions
    void checkPos(int r, int c, string functionName) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nYorps);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    string takePlayerTurn();
    string takeYorpsTurn();
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char ch);
int randInt(int lowest, int highest);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Yorp implementation
///////////////////////////////////////////////////////////////////////////

Yorp::Yorp(Arena* ap, int r, int c, char color)
{
    if (ap == nullptr)
    {
        cout << "***** A yorp must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Yorp created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
    {
        cout << "***** Yorp created with invalid color " << color << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_color = color;
    m_damage = 0;
}

int Yorp::row() const
{
    return m_row;
}

int Yorp::col() const
{
    return m_col;
}

char Yorp::color() const
{
    return m_color;
}

bool Yorp::isDead() const
{
    const int& dam = m_damage;
    if(dam == 3){
        return true;
    }
    return false;
}

void Yorp::forceMove(int dir)
{
    if(!isDead()){
        bool move = attemptMove(*m_arena, dir , m_row, m_col);
        if(!move){
            m_damage++;
        }
    }
}

void Yorp::move()
{
    // Attempt to move in a random direction; if can't move, don't move
    if (!isDead()){
        attemptMove(*m_arena, randInt(0, NUMDIRS-1), m_row, m_col);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

string Player::stand()
{
    return "Player stands.";
}

string Player::move(int dir)
{
    // TODO:  Attempt to move the player one step in the indicated
    //        direction.  If this fails,
    //        return "Player couldn't move; player stands."
    //        A player who moves onto a yorp dies, and this
    //        returns "Player walked into a yorp and died."
    //        Otherwise, return one of "Player moved north.",
    //        "Player moved east.", "Player moved south.", or
    //        "Player moved west."
    bool move = attemptMove(*m_arena, dir, m_row, m_col);
    if(move){
        if((*m_arena).numberOfYorpsAt(m_row, m_col) > 0){
            setDead();
            return "Player walked into a yorp and died.";
        }
        if(dir == 2){
            return "Player moved south.";
        }
        if(dir == 0){
            return "Player moved north.";
        }
        if(dir == 3){
            return "Player moved west.";
        }
        if(dir == 1){
            return "Player moved east.";
        }
    }
    return "Player couldn't move; player stands.";  // This implementation compiles, but is incorrect.
}

bool Player::isDead() const
{
    return m_dead;
}

void Player::setDead()
{
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nYorps = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            m_wallGrid[r-1][c-1] = false;
}

Arena::~Arena()
{
    delete m_player;
    for(int c = 0; c < m_nYorps; c++){
        delete m_yorps[c];
    }
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::yorpCount() const
{
    return m_nYorps;
}

bool Arena::hasWallAt(int r, int c) const
{
    checkPos(r, c, "Arena::hasWallAt");
    return m_wallGrid[r-1][c-1];
}

int Arena::numberOfYorpsAt(int r, int c) const
{
    // TODO:  Return the number of yorps at row r, column c.
    int count = 0;
    /*if(m_nYorps){
        for(Yorp* abc : m_yorps){
            if(abc != nullptr){
                if(abc->row() == r && abc->col() == c){
                    count++;
                }
            }
        }
    }
     */
    for (int i = 0; i < m_nYorps; ++i)
    {
        if (m_yorps[i] != nullptr && m_yorps[i]->row() == r && m_yorps[i]->col() == c)
            count++;
    }
    return count;
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill displayGrid with dots (empty) and stars (wall)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (hasWallAt(r, c) ? '*' : '.');
    
    // Indicate yorp positions by their colors.  If more than one yorp
    // occupies a cell, show just one (any one will do).
    
    // TODO:  For each yorp, set the grid cell to that yorp's color character.
    for(int b = 0; b < m_nYorps; b++){
        if(m_yorps[b] != nullptr && (m_yorps[b] -> row() > 0 && m_yorps[b] -> row() <= MAXROWS) && (m_yorps[b] -> col() > 0 && m_yorps[b] -> col() <= MAXCOLS)){
            displayGrid[(m_yorps[b] -> row()) - 1][(m_yorps[b] -> col()) - 1] = m_yorps[b] -> color();
        }
    }
    // Indicate player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');
    
    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
    
    // Write message, yorp, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << yorpCount() << " yorps remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
}

void Arena::placeWallAt(int r, int c)
{
    checkPos(r, c, "Arena::placeWallAt");
    m_wallGrid[r-1][c-1] = true;
}

bool Arena::addYorp(int r, int c, char color)
{
    if (hasWallAt(r, c))
        return false;
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
        return false;
    if (m_nYorps == MAXYORPS)
        return false;
    m_yorps[m_nYorps] = new Yorp(this, r, c, color);
    m_nYorps++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (m_player != nullptr  ||  hasWallAt(r, c))
        return false;
    if (numberOfYorpsAt(r, c) > 0)
        return false;
    m_player = new Player(this, r, c);
    return true;
}

string Arena::moveYorps(char color, int dir)
{
    // Yorps of the indicated color will follow that color with probability 1/2
    bool willFollow = (randInt(0, 1) == 0);
    
    // Move all yorps
    int nYorpsOriginally = m_nYorps;
    
    // TODO:  Move each yorp.  Force yorps of the indicated color to move
    //        in the indicated direction if willFollow is true.  If
    //        willFollow is false, or if the yorp is of a different color,
    //        it just moves.  Mark the player as dead necessary.  Release
    //        any dead dynamically allocated yorps.
    if(willFollow){
        for(int a = 0; a < nYorpsOriginally; a++){
            if(m_yorps[a] != nullptr){
            if((m_yorps[a] -> color()) == color){
                /*int r1 = (*m_yorps[a]).row();
                int c1 = (*m_yorps[a]).col();
                int& r = r1;
                int& c = c1;
                attemptMove(*this, dir, r, c);*/
                m_yorps[a] -> forceMove(dir);
            }
            else {
                m_yorps[a] -> move();
            }
            if((m_yorps[a] -> row() == m_player -> row()) && (m_yorps[a] -> col() == m_player -> col())){
                (*m_player).setDead();
            }
            if((*m_yorps[a]).isDead()){
                delete m_yorps[a];
                m_yorps[a] = nullptr;
            }
            }
        }
    }
    else {
        for(int a = 0; a < nYorpsOriginally; a++){
            if(m_yorps[a] != nullptr){
                (*m_yorps[a]).move();
                if((*m_yorps[a]).row() == (*m_player).row() && (*m_yorps[a]).col() == (*m_player).col()){
                    (*m_player).setDead();
                }
                if(m_yorps[a] -> isDead()){
                    delete m_yorps[a];
                    m_yorps[a] = nullptr;
                }
            }
        }
    }
    int count = 0;
    for(int c = 0; c < nYorpsOriginally; c++){ //loop to find real number of yorps
        if(m_yorps[c] != nullptr){
            count++;
        }
    }
    m_nYorps = count; //setting m_nYorps to the right amount of Yorps bc it wasn't ending the game when all the Yorps died
    
    if (m_nYorps < nYorpsOriginally)
        return "Some yorps have been destroyed.";
    else
        return "No yorps were destroyed.";
}

void Arena::checkPos(int r, int c, string functionName) const
{
    if (r < 1  ||  r > m_rows  ||  c < 1  || c > m_cols)
    {
        cout << "***** " << "Invalid arena position (" << r << ","
        << c << ") in call to " << functionName << endl;
        exit(1);
    }
}

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nYorps)
{
    if (nYorps < 0  ||  nYorps > MAXYORPS)
    {
        cout << "***** Game created with invalid number of yorps:  "
        << nYorps << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nYorps - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
        << cols << " arena, which is too small too hold a player and "
        << nYorps << " yorps!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add some walls in WALL_DENSITY of the empty spots
    assert(WALL_DENSITY >= 0  &&  WALL_DENSITY <= 1);
    int nWalls = static_cast<int>(WALL_DENSITY * nEmpty);
    while (nWalls > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (m_arena->hasWallAt(r, c))
            continue;
        m_arena->placeWallAt(r, c);
        nWalls--;
    }
    
    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->hasWallAt(rPlayer, cPlayer));
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with yorps
    while (nYorps > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (m_arena->hasWallAt(r, c)  ||  (r == rPlayer && c == cPlayer))
            continue;
        const char colors[MAXCOLORS] = { 'R', 'Y', 'B' };
        m_arena->addYorp(r, c, colors[randInt(1, MAXCOLORS)-1]);
        nYorps--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x or nothing): ";
        string playerMove;
        getline(cin, playerMove);
        
        Player* player = m_arena->player();
        int dir;
        
        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->stand();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->stand();
            else
            {
                dir = decodeDirection(tolower(playerMove[0]));
                if (dir != -1)
                    return player->move(dir);
            }
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x." << endl;
    }
}

string Game::takeYorpsTurn()
{
    for (;;)
    {
        cout << "Color thrown and direction (e.g., Rn or bw): ";
        string colorAndDir;
        getline(cin, colorAndDir);
        if (colorAndDir.size() != 2)
        {
            cout << "You must specify a color followed by a direction." << endl;
            continue;
        }
        char color = toupper(colorAndDir[0]);
        if (color != 'R'  &&  color != 'Y'  &&  color != 'B')
        {
            cout << "Color must be upper or lower R, Y, or B." << endl;
            continue;
        }
        int dir = decodeDirection(tolower(colorAndDir[1]));
        if (dir != -1)
            return m_arena->moveYorps(color, dir);
        cout << "Direction must be n, e, s, or w." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    Player* player = m_arena->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_arena->yorpCount() > 0)
    {
        string msg = takePlayerTurn();
        m_arena->display(msg);
        if (player->isDead())
            break;
        msg = takeYorpsTurn();
        m_arena->display(msg);
    }
    if (player->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'n':  return NORTH;
        case 'e':  return EAST;
        case 's':  return SOUTH;
        case 'w':  return WEST;
    }
    return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

// Return false without changing anything if moving one step from (r,c)
// in the indicated direction would hit a wall or run off the edge of the
// arena.  Otherwise, update r and c to the position resulting from the
// move and return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
    int* row = &r;
    int* col = &c;
    if(dir == 2){ //south
        if(r != a.rows() && !(a.hasWallAt(r + 1, c))){
            *row += 1;
            return true;
        }
    }
    if(dir == 0){ //north
        if(r > 1 && !(a.hasWallAt(r - 1, c))){
            *row -= 1;
            return true;
        }
    }
    if(dir == 3){ //west
        if(c > 1 && !(a.hasWallAt(r, c - 1))){
            *col -= 1;
            return true;
        }
    }
    if(dir == 1){ //east
        if(c != a.cols() && !(a.hasWallAt(r, c + 1))){
            *col += 1;
            return true;
        }
    }
    return false;
}

// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should stand; otherwise, bestDir is
// set to the recommended direction to move.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    // TODO:  replace this implementation:
    int countYorps = 0;
    int dir = -1;
    if(r - 1 > 0){
        int n = a.numberOfYorpsAt(r - 1, c);
        if(n > 0){
            countYorps++;
        }
    }
    if(r + 1 < a.rows()){
        int s = a.numberOfYorpsAt(r + 1, c);
        if(s > 0){
            countYorps++;
        }
    }
    if(c - 1 > 0){
        int w = a.numberOfYorpsAt(r , c - 1);
        if(w > 0){
            countYorps++;
        }
    }
    if(c + 1 < a.cols()){
        int e = a.numberOfYorpsAt(r , c + 1);
        if(e > 0){
            countYorps++;
        }
    }
    if(r - 1 > 0 && a.numberOfYorpsAt(r - 1, c) == 0){ //northCheck
        if(!(a.hasWallAt(r - 1, c))){
        int nyorps = 0;
        if(r - 2 > 0){
            if(a.numberOfYorpsAt(r - 2, c) > 0){
                nyorps++;
            }
        }
        if(r < a.rows()){
            if(a.numberOfYorpsAt(r, c) > 0){
                nyorps++;
            }
        }
        if(c - 1 > 0){
            if(a.numberOfYorpsAt(r - 1, c - 1) > 0){
                nyorps++;
            }
        }
        if(c + 1 < a.cols()){
            if(a.numberOfYorpsAt(r - 1, c + 1) > 0){
                nyorps++;
            }
        }
        if(nyorps < countYorps){
            countYorps = nyorps;
            dir = 0;
        }
        }
    }
    if(r + 1 < a.rows() && a.numberOfYorpsAt(r + 1, c) == 0){ //southCheck
        if(!(a.hasWallAt(r + 1, c))){
        int syorps = 0;
        if(r > 0){
            if(a.numberOfYorpsAt(r , c) > 0){
                syorps++;
            }
        }
        if(r + 2 < a.rows()){
            if(a.numberOfYorpsAt(r + 2, c) > 0){
                syorps++;
            }
        }
        if(c - 1 > 0){
            if(a.numberOfYorpsAt(r + 1, c - 1) > 0){
                syorps++;
            }
        }
        if(c + 1 < a.cols()){
            if(a.numberOfYorpsAt(r + 1, c + 1) > 0){
                syorps++;
            }
        }
        if(syorps < countYorps){
            countYorps = syorps;
            dir = 2;
        }
        }
    }
    if(c - 1 > 0 && a.numberOfYorpsAt(r, c-1) == 0){ //westCheck
        if(!(a.hasWallAt(r, c-1))){
        int wyorps = 0;
        if(r - 1 > 0){
            if(a.numberOfYorpsAt(r - 1, c - 1) > 0){
                wyorps++;
            }
        }
        if(r + 1 < a.rows()){
            if(a.numberOfYorpsAt(r + 1, c - 1) > 0){
                wyorps++;
            }
        }
        if(c - 2> 0){
            if(a.numberOfYorpsAt(r, c - 2) > 0){
                wyorps++;
            }
        }
        if(c < a.cols()){
            if(a.numberOfYorpsAt(r, c) > 0){
                wyorps++;
            }
        }
        if(wyorps < countYorps){
            countYorps = wyorps;
            dir = 3;
        }
        }
    }
    if(c + 1 < a.cols() && a.numberOfYorpsAt(r, c+1) == 0){ //eastCheck
        if(!(a.hasWallAt(r, c+1))){
        int eyorps = 0;
        if(r - 1 > 0){
            if(a.numberOfYorpsAt(r - 1, c + 1) > 0){
                eyorps++;
            }
        }
        if(r + 1 < a.rows()){
            if(a.numberOfYorpsAt(r + 1, c + 1) > 0){
                eyorps++;
            }
        }
        if(c > 0){
            if(a.numberOfYorpsAt(r, c) > 0){
                eyorps++;
            }
        }
        if(c + 2 < a.cols()){
            if(a.numberOfYorpsAt(r, c + 2) > 0){
                eyorps++;
            }
        }
        if(eyorps < countYorps){
            countYorps = eyorps;
            dir = 1;
        }
        }
    }
    if(dir == -1){
        return false;
    }
    bestDir = dir;
    return true;
    // Your replacement implementation should do something intelligent.
    // For example, if you're standing next to four zurts, and moving
    // north would put you next to two zurts, but moving east would put
    // you next to none, moving east is a safer choice than standing or
    // moving north.
}

///////////////////////////////////////////////////////////////////////////
// main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(10, 12, 50);
    
    // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
