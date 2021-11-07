#include "game.hpp"

#include "op_result.hpp"


const unsigned int WIDTH = 1280;
const unsigned int HEIGHT = 720;


int main()
{
  Game game(WIDTH, HEIGHT);
  
  return (int)game.Run();
}
