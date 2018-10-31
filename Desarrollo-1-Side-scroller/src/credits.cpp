#include "include/raylib.h"

#include "credits.h"
#include "game.h"

namespace Juego
{
	static Rectangle atras;

	void CreditsUpdate()
	{
		CreditsDraw();
		mousePoint = GetMousePosition();

		atras.x = 20;
		atras.y = GetScreenHeight() - atras.height - 25;
		atras.height = 50;
		atras.width = 200;

		if (CheckCollisionPointRec(mousePoint, atras))
		{
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				Screens = menu;
			}
		}
	}


	void CreditsDraw() 
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawRectangle(atras.x, atras.y, atras.width, atras.height, MAROON);

		DrawText("ATRAS", atras.x + atras.width / 2 - MeasureText("ATRAS", 20) / 2, atras.y + 18, 20, WHITE);

		DrawText("Shards, v1.0 Martin Concetti, v1.1 update by Ivan Castellano", 20, 160, 25, MAROON);
		DrawText("Funciones creadas por Ian Eito, Albert Martos y Ramon Santamaria", 20, 200, 20, LIGHTGRAY);
		DrawText("Copyright (c) 2015 Ramon Santamaria (@raysan5)", 20, 220, 20, LIGHTGRAY);
		DrawText("Creado usando raylib, chip tone, beep box, piskel, ", 20, 240, 20, LIGHTGRAY);
		DrawText("Consultantes: Baretto, Sergio", 20, 260, 20, LIGHTGRAY);

		EndDrawing();
	}
}