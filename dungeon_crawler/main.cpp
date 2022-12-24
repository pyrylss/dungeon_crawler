#include <SFML/Graphics.hpp>
#include "game.cpp"

int main()
{
    //Find the current working directory (!!ASSUMING BUILT WITH CMAKE!!)
    std::filesystem::path source_path = __FILE__; //Where are we running the application from?
    source_path = source_path.parent_path().parent_path(); //Going from build folder to root
    std::filesystem::current_path(source_path); //Set our working directory to root
    std::cout << std::filesystem::current_path() << std::endl; //Print directory to console

    Game game;
    game.run();
    return 0;
}
