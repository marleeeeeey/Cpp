#include "Game.h"

void main(int argc, void** argv[]){
	// Program entry point.
	Game game;
	while(!game.GetWindow()->IsDone()){
		game.HandleInput();
		game.Update();
		game.Render();
		game.RestartClock();
	}
}