#include "game.hpp"

#include "op_result.hpp"


const unsigned int WIDTH = 1920;
const unsigned int HEIGHT = 1080;


int main()
{
  Game game(WIDTH, HEIGHT);
  
  return (int)game.Run();
}
