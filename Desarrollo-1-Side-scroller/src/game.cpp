#include "include/raylib.h"

#include "game.h"
#include "menu.h"
#include "credits.h"


namespace Juego {

	GameScreen Screens;

#define MAX_TUBES 100

	struct Player {
		Vector2 position;
		int radius;
		Color color;
	};

	struct Wall{
		Rectangle rec;
		Color color;
		bool active;
	};

	int screenWidth = 800;
	int screenHeight = 450;
	static bool gameOver;
	static bool pause;
	static int score;
	static int hiScore = 0;

	static Player player;

	static Wall wall[MAX_TUBES * 2];
	static Vector2 tubesPos[MAX_TUBES];
	static int tubesSpeedX;
	static bool superfx;

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

		for (int i = 0; i < MAX_TUBES; i++)
		{
			tubesPos[i].x = 400 + 280 * i;
			tubesPos[i].y = -GetRandomValue(0, 120);
		}

		for (int i = 0; i < MAX_TUBES * 2; i += 2)
		{
			wall[i].rec.x = tubesPos[i / 2].x;
			wall[i].rec.y = tubesPos[i / 2].y;
			wall[i].rec.width = 80;
			wall[i].rec.height = 255;

			wall[i + 1].rec.x = tubesPos[i / 2].x;
			wall[i + 1].rec.y = 600 + tubesPos[i / 2].y - 255;
			wall[i + 1].rec.width = 80;
			wall[i + 1].rec.height = 255;

			wall[i / 2].active = true;
		}
	}

	void UpdateGame() 
	{
		if (!gameOver)
		{
			if (IsKeyPressed('P')) pause = !pause;

			if (!pause)
			{
				for (int i = 0; i < MAX_TUBES; i++) tubesPos[i].x -= tubesSpeedX ;

				for (int i = 0; i < MAX_TUBES * 2; i += 2)
				{
					wall[i].rec.x = tubesPos[i / 2].x ;
					wall[i + 1].rec.x = tubesPos[i / 2].x ;
				}

				if (IsKeyDown(KEY_SPACE) && !gameOver) player.position.y -= 3 * GetFrameTime();
				else player.position.y += 1 * GetFrameTime();

				// Check Collisions
				for (int i = 0; i < MAX_TUBES * 2; i++)
				{
					if (CheckCollisionCircleRec(player.position, player.radius, wall[i].rec))
					{
						gameOver = true;
						pause = false;
					}
					else if ((tubesPos[i / 2].x < player.position.x) && wall[i / 2].active && !gameOver)
					{
						score += 100;
						wall[i / 2].active = false;

						superfx = true;

						if (score > hiScore) hiScore = score;
					}
				}
			}
		}
		else
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				InitGame();
				gameOver = false;
			}
		}
	}

	void DrawGame()
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawCircle(player.position.x, player.position.y, player.radius, DARKGRAY);

		for (int i = 0; i < MAX_TUBES; i++)
		{
			DrawRectangle(wall[i * 2].rec.x, wall[i * 2].rec.y, wall[i * 2].rec.width, wall[i * 2].rec.height, GRAY);
			DrawRectangle(wall[i * 2 + 1].rec.x, wall[i * 2 + 1].rec.y, wall[i * 2 + 1].rec.width, wall[i * 2 + 1].rec.height, GRAY);
		}

		if (superfx)
		{
			DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
			superfx = false;
		}

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
			MenuUpdate();

		} break;
		case game:
		{
			UpdateDrawFrame();

		} break;
		case credits:
		{
			CreditsUpdate();

		} break;
		}
	}

	void UpdateDrawFrame()
	{
		UpdateGame();
		DrawGame();
	}
}