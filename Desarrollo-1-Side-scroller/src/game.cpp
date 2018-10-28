#include "include/raylib.h"

#include "game.h"
#include "menu.h"
#include "credits.h"
#include "controls.h"


namespace Juego {

	GameScreen Screens;

#define MAX_WALL 100
#define WALL_WIDTH 80

	
	 struct Player {
		Vector2 position;
		int radius;
		Color color;
	} ;

	 struct Wall {
		Rectangle rec;
		Color color;
		bool active;
	} ;

	
	 int screenWidth = 800;
	 int screenHeight = 450;

	static bool gameOver;
	static bool pause;
	static int score;
	static int framesSpeed;
	static int framesCounter;
	static int currentFrame;
	static int hiScore = 0;
	static int tubesSpeedX;
	static bool superfx;

	static Player player;
	static Wall wall[MAX_WALL * 2];
	static Vector2 wallPos[MAX_WALL];
	Texture2D ship;
	Vector2 position;
	Rectangle frameRec;

	static void InitGame(void);         
	static void UpdateGame(void);       
	static void DrawGame(void);         
	static void UnloadGame(void);       
	static void UpdateDrawFrame(void);  

										
	void core()
	{
		
		InitWindow(screenWidth, screenHeight, "Basic side scroler");

		InitGame();

		SetTargetFPS(60);

		while (!WindowShouldClose())    
		{
			
			Change();
		}

		         
		Unload();
		CloseWindow();        						
	}
	
	void InitGame()
	{
		ship = LoadTexture("res/ship.png");

		player.radius = 24;
		player.position = { 80, (float)screenHeight / 2 - player.radius };
		tubesSpeedX = 40;
		framesCounter = 0;
		score = 0;
		framesSpeed = 8;
		currentFrame = 0;
		frameRec = { 0.0f, 0.0f, (float)ship.width / 2, (float)ship.height };
		position = { player.position.x -(player.position .x / 2), player.position.y / 2 };

		for (int i = 0; i < MAX_WALL; i++)
		{
			wallPos[i].x = 400 + 280 * i;
			wallPos[i].y = -GetRandomValue(0, 120);
		}

		for (int i = 0; i < MAX_WALL * 2; i += 2)
		{
			wall[i].rec.x = wallPos[i / 2].x;
			wall[i].rec.y = wallPos[i / 2].y;
			wall[i].rec.width = WALL_WIDTH;
			wall[i].rec.height = 255;

			wall[i + 1].rec.x = wallPos[i / 2].x;
			wall[i + 1].rec.y = 600 + wallPos[i / 2].y - 255;
			wall[i + 1].rec.width = WALL_WIDTH;
			wall[i + 1].rec.height = 255;

			wall[i / 2].active = true;
		}

		gameOver = false;
		superfx = false;
		pause = false;

	}

	void UpdateGame()
	{
		if (!gameOver)
		{
			if (IsKeyPressed('P')) pause = !pause;

			if (!pause)
			{
				for (int i = 0; i < MAX_WALL; i++) wallPos[i].x -= tubesSpeedX * GetFrameTime();

				for (int i = 0; i < MAX_WALL * 2; i += 2)
				{
					wall[i].rec.x = wallPos[i / 2].x;
					wall[i + 1].rec.x = wallPos[i / 2].x;
				}

				if (IsKeyDown(KEY_SPACE) && !gameOver) player.position.y -= 160 * GetFrameTime();
				else player.position.y += 60 * GetFrameTime();
				
				position = player.position;

				for (int i = 0; i < MAX_WALL * 2; i++)
				{
					if (CheckCollisionCircleRec(player.position,player.radius ,wall[i].rec))
					{
						gameOver = true;
						pause = false;
					}
					else if ((wallPos[i / 2].x < player.position.x) && wall[i / 2].active && !gameOver)
					{
						score += 100;
						wall[i / 2].active = false;

						superfx = true;

						if (score > hiScore) hiScore = score;
					}
				}

				framesCounter++;

				if (framesCounter >= (60 / framesSpeed))
				{
					framesCounter = 0;
					currentFrame++;

					if (currentFrame > 5) currentFrame = 0;

					frameRec.x = (float)currentFrame*(float)ship.width / 2;
				}

				if (player.position.y < 0 ) 
				{
					gameOver = true;
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

	void DrawGame(void)
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if (!gameOver)
		{
		
			DrawCircle(player.position.x, player.position.y, player.radius, DARKGRAY);

			DrawTextureRec(ship, frameRec, player.position, WHITE);

			for (int i = 0; i < MAX_WALL; i++)
			{
				DrawRectangle(wall[i * 2].rec.x, wall[i * 2].rec.y, wall[i * 2].rec.width, wall[i * 2].rec.height, GRAY);
				DrawRectangle(wall[i * 2 + 1].rec.x, wall[i * 2 + 1].rec.y, wall[i * 2 + 1].rec.width, wall[i * 2 + 1].rec.height, GRAY);
			}
			
			if (superfx)
			{
				DrawRectangle(0, 0, screenWidth, screenHeight, WHITE);
				superfx = false;
			}

			DrawText(FormatText("%04i", score), 20, 20, 40, GRAY);
			DrawText(FormatText("HI-SCORE: %04i", hiScore), 20, 70, 20, LIGHTGRAY);

			if (pause) 
			{
				DrawText("Pausa", screenWidth / 4, screenHeight / 3, 50, WHITE);
				DrawText("P para resumir", screenWidth / 4, screenHeight / 3 + 60, 50, WHITE);
				DrawText("Escape para salir", screenWidth / 4, screenHeight / 3 + 120, 50, WHITE);
			}
		}
		else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

		EndDrawing();
	}

	
	void Unload() 
	{
		UnloadTexture(ship);
		UnloadGame();
	}
	void UnloadGame()
	{
	}

	void UpdateDrawFrame()
	{
		UpdateGame();
		DrawGame();
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
		case controls:
		{
			ControlsUpdate();

		} break;
		}
	}

	
}