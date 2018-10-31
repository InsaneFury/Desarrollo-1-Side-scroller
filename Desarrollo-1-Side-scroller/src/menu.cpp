#include "include/raylib.h"

#include "menu.h"
#include "game.h"

namespace Juego
{
	static Rectangle jugar;
	static Color jugarColor;
	static Rectangle multiplayer;
	static Color multiplayerColor;
	static Rectangle creditos;
	static Color creditosColor;
	static Rectangle controles;
	static Color controlesColor;

	void MenuUpdate()
	{
		MenuDraw();
		mousePoint = GetMousePosition();
		jugar.x = screenWidth / 2 - jugar.width/2;
		jugar.y = screenHeight / 2 - 40;
		jugar.height = 50;
		jugar.width = 200;
		jugarColor = MAROON;

		multiplayer.x = screenWidth / 2 - multiplayer.width/2;
		multiplayer.y = screenHeight / 2 + 20;
		multiplayer.height = 50;
		multiplayer.width = 200;
		multiplayerColor = MAROON;

		creditos.x = screenWidth / 2 - creditos.width/2;
		creditos.y = screenHeight / 2 + 80;
		creditos.height = 50;
		creditos.width = 200;
		creditosColor = MAROON;

		controles.x = screenWidth / 2 - controles.width/2;
		controles.y = screenHeight / 2 + 140;
		controles.height = 50;
		controles.width = 200;
		controlesColor = MAROON;

		if (CheckCollisionPointRec(mousePoint, jugar))
		{

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				isMultiplayerEnabled = false;
				Screens = game;
			}
		}
		if (CheckCollisionPointRec(mousePoint, multiplayer))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				isMultiplayerEnabled = true;
				Screens = game;
			}
		}
		if (CheckCollisionPointRec(mousePoint, creditos))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				Screens = credits;
			}
		}
		if (CheckCollisionPointRec(mousePoint, controles))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				Screens = controls;
			}
		}
	}

	void MenuDraw()
	{
		BeginDrawing();

		ClearBackground(RAYWHITE);

		DrawRectangle(jugar.x, jugar.y, jugar.width, jugar.height, jugarColor);
		DrawRectangle(multiplayer.x, multiplayer.y, multiplayer.width, multiplayer.height, multiplayerColor);
		DrawRectangle(creditos.x, creditos.y, creditos.width, creditos.height, creditosColor);
		DrawRectangle(controles.x, controles.y, controles.width, controles.height, controlesColor);

		DrawText("JUGAR", jugar.x + jugar.width/2 - MeasureText("JUGAR",18)/2, jugar.y + 18, 18, WHITE);

		DrawText("MULTIPLAYER", multiplayer.x + multiplayer.width / 2 - MeasureText("MULTIPLAYER", 18) / 2, 
				                                                             multiplayer.y + 18, 18, WHITE);

		DrawText("CREDITOS", creditos.x + creditos.width / 2 - MeasureText("CREDITOS", 18) / 2, 
																			 creditos.y + 18, 18, WHITE);

		DrawText("CONTROLES", controles.x + controles.width / 2 - MeasureText("CONTROLES", 18) / 2, 
																			 controles.y + 18, 18, WHITE);

		DrawText("SHARDS", screenWidth / 2 - MeasureText("SHARDS",80)/2, 80, 80, MAROON);
		DrawText("v1.1", 10 , screenHeight - 30, 30, MAROON);

		EndDrawing();
	}

}