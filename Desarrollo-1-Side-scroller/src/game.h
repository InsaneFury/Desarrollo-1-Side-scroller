#ifndef game_H
#define game_H

namespace Juego
{

	enum GameScreen { menu = 0, game, over, credits, controls };
	extern GameScreen Screens;

	void core();
	static void InitGame();
	static void UpdateGame();
	static void DrawGame();
	static void Unload();
	static void UnloadGame();
	static void UpdateDrawFrame();
	static void Change();
	void ReStart();

}

#endif // !game_H