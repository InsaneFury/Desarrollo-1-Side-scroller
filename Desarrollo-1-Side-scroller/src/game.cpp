#include "include/raylib.h"

#include "game.h"
#include "menu.h"
#include "credits.h"


namespace Juego {

	GameScreen Screens;

#define MAX_TUBES 2
#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

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
	static Vector2 position;
	static Rectangle frameRec;
	static int framesCounter;
	static int framesSpeed;
	static int currentFrame;
	static int tubesSpeedX;
	static bool superfx;

	Texture2D ship;

	void core()
	{

		InitWindow(screenWidth, screenHeight, "Asteroids");

		InitGame();

		while (!WindowShouldClose())
		{
			Change();

		}
		UnloadGame();
		CloseWindow();

	
	}

	void InitGame() 
	{
		ship = LoadTexture("res/ship.png");


		player.radius = 20;
		player.position = { 80, (float)screenHeight / 2 - player.radius };

		tubesSpeedX = 99;

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

		position = { 350.0f, 280.0f };
		frameRec = { 0.0f, 0.0f, (float)ship.width / 2, (float)ship.height };
		currentFrame = 0;

		framesCounter = 0;
		framesSpeed = 2;
		UnloadTexture(ship);

	}

	void UpdateGame() 
	{
		if (!gameOver)
		{
			if (IsKeyPressed('P')) pause = !pause;

			if (!pause)
			{

				framesCounter++;

				if (framesCounter >= (60 / framesSpeed))
				{
					framesCounter = 0;
					currentFrame++;

					if (currentFrame > 5) currentFrame = 0;

					frameRec.x = (float)currentFrame*(float)ship.width / 6;
				}

				if (IsKeyPressed(KEY_RIGHT)) framesSpeed++;
				else if (IsKeyPressed(KEY_LEFT)) framesSpeed--;

				if (framesSpeed > MAX_FRAME_SPEED) framesSpeed = MAX_FRAME_SPEED;
				else if (framesSpeed < MIN_FRAME_SPEED) framesSpeed = MIN_FRAME_SPEED;

				//for (int i = 0; i < MAX_TUBES; i++) tubesPos[i].x -= tubesSpeedX ;

				/*for (int i = 0; i < MAX_TUBES * 2; i += 2)
				{
					wall[i].rec.x = tubesPos[i / 2].x ;
					wall[i + 1].rec.x = tubesPos[i / 2].x ;
				}*/

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

		/*for (int i = 0; i < MAX_TUBES; i++)
		{
			DrawRectangle(wall[i * 2].rec.x, wall[i * 2].rec.y, wall[i * 2].rec.width, wall[i * 2].rec.height, GRAY);
			DrawRectangle(wall[i * 2 + 1].rec.x, wall[i * 2 + 1].rec.y, wall[i * 2 + 1].rec.width, wall[i * 2 + 1].rec.height, GRAY);
		}
		*/
		if (superfx)
		{
			DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
			superfx = false;
		}

		DrawTexture(ship, 15, 40, WHITE);
		DrawRectangleLines(15, 40, ship.width, ship.height, LIME);
		DrawRectangleLines(15 + frameRec.x, 40 + frameRec.y, frameRec.width, frameRec.height, RED);

		for (int i = 0; i < MAX_FRAME_SPEED; i++)
		{
			if (i < framesSpeed ) DrawRectangle(250 + 21 * i, 205, 20, 20, RED);
			DrawRectangleLines(250 + 21 * i, 205, 20, 20, MAROON);
		}

		DrawTextureRec(ship, frameRec, position, RED);

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
			//MenuUpdate();
			UpdateDrawFrame();

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