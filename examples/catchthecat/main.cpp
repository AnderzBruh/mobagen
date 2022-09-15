#include <Engine.h>
#include "World.h"
// Main code
int main(int, char**) {
  SDL_Log("Creating Engine");
  auto engine = new Engine();
  SDL_Log("Engine Created");

  SDL_Log("Starting Engine");
  if(engine->Start("Editor")) {
    new World(engine,21);
    SDL_Log("Engine Started");
    engine->Run();
  }

  SDL_Log("Exiting Engine");
  engine->Exit();
  SDL_Log("Engine Exited");

  return 0;
}

