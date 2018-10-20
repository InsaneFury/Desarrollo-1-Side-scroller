#include "include/raylib.h"

#include "game.h"
#include "menu.h"

namespace Juego {

	GameScreen Screens;

	struct Player {
		Vector2 position;
		int radius;
		Color color;
	};

	int screenWidth = 800;
	int screenHeight = 450;

	static Player player;


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

		player.radius = 20;
		player.position = { 80, (float)screenHeight / 2 - player.radius };
	}

	void UpdateGame() 
	{
		if (IsKeyDown(KEY_SPACE) ) player.position.y -= 3 * GetFrameTime();
		else player.position.y += 1 * GetFrameTime();
	}

	void DrawGame()
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawCircle(player.position.x, player.position.y, player.radius, DARKGRAY);

		EndDrawing();

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