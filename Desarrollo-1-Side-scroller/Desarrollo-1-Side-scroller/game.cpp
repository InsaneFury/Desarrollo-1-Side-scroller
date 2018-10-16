#include "include/raylib.h"

#include "game.h"
#include "menu.h"

namespace Juego {

	GameScreen Screens;

	Rectangle player;

	int screenWidth = 800;
	int screenHeight = 450;

	void core()
	{

		InitWindow(screenWidth, screenHeight, "Asteroids");

		//InitAudioDevice();
		InitGame();
		

		while (!WindowShouldClose())
		{
			Change();

		}
		UnloadGame();

		//CloseAudioDevice();
		CloseWindow();

	
	}

	void InitGame() 
	{
		player.x = (float)screenWidth / 8;
		player.y = (float)screenHeight / 2;
		player.height = 25;
		player.width = 25;
	}

	void UpdateGame() 
	{

	}

	void DrawGame()
	{
		DrawRectangle(player.x, player.y, player.width, player.height, BLACK);
	}

	void UnloadGame()
	{
		// TODO: Unload all dynamic loaded data (textures, sounds, models...)
	}

	void Change()
	{
		switch (Screens)
		{
		case menu:
		{
			UpdateDrawFrame();

		} break;
		}
	}

	void UpdateDrawFrame()
	{
		UpdateGame();
		DrawGame();
	}
}