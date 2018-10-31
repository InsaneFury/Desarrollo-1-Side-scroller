#ifndef game_H
#define game_H

namespace Juego
{

	enum GameScreen { menu = 0, game, over, credits, controls };
	extern GameScreen Screens;
	extern bool isMultiplayerEnabled;
	extern bool gameOver;
	void core();
	void InitGame();
	static void UpdateGame();
	static void DrawGame();
	static void UnloadGame();
	static void Unload();
	static void Change();
	static void UpdateDrawFrame();

}

#endif // !game_H