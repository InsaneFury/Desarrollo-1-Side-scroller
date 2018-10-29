#include "include/raylib.h"

#include "game.h"
#include "menu.h"
#include "credits.h"
#include "controls.h"
#include "over.h"

namespace Juego {

	GameScreen Screens;
	
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

	 bool gameOver;
	static bool pause;
	int score;
	static int framesSpeed;
	static int framesCounter;
	static int currentFrame;
	static int hiScore = 0;
	static int tubesSpeedX;
	static bool superfx;
	static int maxWall;
	static int wallWith;
	static int repeat = 0;

	static Player player;
	static Wall wall[100 * 2];
	static Vector2 wallPos[100];
	static Texture2D ship;
	static Texture2D shard;
	static Vector2 position;
	static Vector2 position1 = { 0.0f, 0.0f };
	static Vector2 position2 = { 400.0f, 150.0f };
	static Vector2 position3 = { 400.0f, 250.0f };
	static Rectangle frameRec;
	static Rectangle shardRect;
	static Music music;
	static Sound jump;
	static Rectangle rec1;
	Vector2 mousePoint;

	static void InitGame(void);         
	static void UpdateGame(void);       
	static void DrawGame(void);         
	static void UnloadGame(void);       
	static void UpdateDrawFrame(void);  

										
	void core()
	{
		
		InitWindow(screenWidth, screenHeight, "Shards");

		SetTargetFPS(60);

		InitGame();


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
			shard = LoadTexture("res/shard.png");

			InitAudioDevice();
			music = LoadMusicStream("res/background.ogg");
			jump = LoadSound("res/jump.wav");
			PlayMusicStream(music);
		

		player.radius = 24;
		player.position = { 80, (float)screenHeight / 2 - player.radius };
		tubesSpeedX = 40;
		framesCounter = 0;
		score = 0;
		framesSpeed = 8;
		currentFrame = 0;
		maxWall = 100;
		wallWith = 80;
		frameRec = { 0.0f, 0.0f, (float)ship.width / 2, (float)ship.height };
		shardRect = { 0.0f, 0.0f, (float)shard.width,(float)shard.height };
		position = { player.position.x - player.radius , (player.position.y / 2) - 1200 };

		rec1.x = 0;
		rec1.y = 400;
		rec1.height = 50;
		rec1.width = 100;

		for (int i = 0; i < maxWall; i++)
		{
			wallPos[i].x = 400 + 280 * i;
			wallPos[i].y = -GetRandomValue(0, 120);
		}

		for (int i = 0; i < maxWall * 2; i += 2)
		{
			wall[i].rec.x = wallPos[i / 2].x;
			wall[i].rec.y = wallPos[i / 2].y;
			wall[i].rec.width = wallWith;
			wall[i].rec.height = 255;

			wall[i + 1].rec.x = wallPos[i / 2].x;
			wall[i + 1].rec.y = 600 + wallPos[i / 2].y - 255;
			wall[i + 1].rec.width = wallWith;
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
				UpdateMusicStream(music);

				for (int i = 0; i < maxWall; i++) wallPos[i].x -= tubesSpeedX * GetFrameTime();

				for (int i = 0; i < maxWall * 2; i += 2)
				{
					wall[i].rec.x = wallPos[i / 2].x;
					wall[i + 1].rec.x = wallPos[i / 2].x;
				}

				if (IsKeyDown(KEY_SPACE) && !gameOver) 
				{
					player.position.y -= 160 * GetFrameTime();
					PlaySound(jump);
				}

				else
				{
					player.position.y += 60 * GetFrameTime();
				}

				position = { player.position.x - 1200 , (player.position.y / 2) - 1200 };

				for (int i = 0; i < maxWall * 2; i++)
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

				position1.x -= 100 * GetFrameTime();

				if (position1.x <= -100)
				{
					position1.x = screenWidth;
				}

				position2.x -= 100 * GetFrameTime();

				if (position2.x <= -100)
				{
					position2.x = screenWidth;
				}

				position3.x -= 100 * GetFrameTime();

				if (position3.x <= -100)
				{
					position3.x = screenWidth;
				}
				
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

				if (player.position.y > screenHeight)
				{
					gameOver = true;
				}
			}
		}
		else
		{
			Screens = over;
			/*if (IsKeyPressed(KEY_ENTER))
			{

				InitGame();
				gameOver = false;
			}*/
		}

		if (pause) 
		{
			PauseMusicStream(music);
		}

		else
		{
			ResumeMusicStream(music);
		}

	}

	void DrawGame(void)
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		if (!gameOver)
		{
			DrawRectangle(rec1.x, rec1.y, rec1.width, rec1.height, BLACK);
			DrawText("Pausa", rec1.x + 18, rec1.y + 10, 20, WHITE);

			DrawCircle(player.position.x, player.position.y, player.radius, DARKGRAY);

			DrawTextureRec(ship, frameRec, player.position, WHITE);
			DrawTextureRec(shard, shardRect, position1, WHITE);
			DrawTextureRec(shard, shardRect, position2, WHITE);

			for (int i = 0; i < maxWall; i++)
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
		//else DrawText("PRESS [ENTER] TO PLAY AGAIN", GetScreenWidth() / 2 - MeasureText("PRESS [ENTER] TO PLAY AGAIN", 20) / 2, GetScreenHeight() / 2 - 50, 20, GRAY);

		EndDrawing();
	}

	
	void Unload() 
	{
		UnloadTexture(ship);
		UnloadTexture(shard);
		UnloadMusicStream(music);
		CloseAudioDevice();
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
			repeat = 1;
			//InitGame();

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

		case over:
		{
			OverUpdate();

		} break;

		}
	}

	
}