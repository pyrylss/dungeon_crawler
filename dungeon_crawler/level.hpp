class Level
//The level class contains everything needed for a single room to be created and maintained during the game's runtime
{
    public:
        Level(); //Constructor creates an empty room
        void createObstacles(); //Create obstacles (TODO)
        void createBorder(); //Create the level border of default side, and render it into input render window
        void createMonsters(int points); //Randomly generate monsters for the room
        void DrawAll(sf::RenderWindow& window); //Draw all objects in the level into the render window
    public:
        std::vector<Monster> monsterList_; //List of monsters in the room, used to draw all monsters
        int points_; //Points used to spawn monsters according to players level, currently set to 3 by default
        sf::RectangleShape levelPiece_;
        sf::Texture levelTexture_;
};