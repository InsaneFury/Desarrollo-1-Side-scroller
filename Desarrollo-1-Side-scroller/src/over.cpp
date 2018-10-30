#include "include/raylib.h"

#include "over.h"
#include "game.h"

namespace Juego
{

	static Rectangle rec1;
	static Rectangle rec2;
	static Rectangle rec3;

	void OverUpdate()
	{
		OverDraw();
		mousePoint = GetMousePosition();
		rec1.x = screenWidth / 2 - 50;
		rec1.y = screenHeight / 2;
		rec1.height = 50;
		rec1.width = 100;

		rec2.x = screenWidth / 2 - 50;
		rec2.y = screenHeight / 2 + 80;
		rec2.height = 50;
		rec2.width = 200;

		
		if (CheckCollisionPointRec(mousePoint, rec2))
		{

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				gameOver = false;
				ReStart();
				Screens = menu;
			}
		}
		


	}

	void OverDraw()
	{
		BeginDrawing();

		ClearBackground(DARKGRAY);


		DrawRectangle(rec2.x, rec2.y, rec2.width, rec2.height, BLACK);

		DrawText("Shards", screenWidth/ 2 - 70, screenHeight / 2 - 99, 50, MAROON);
		DrawText("Perdiste", screenWidth / 2 - 70, screenHeight / 2 - 49, 30, WHITE);
		DrawText(FormatText("%04i", score), rec1.x + 18, rec1.y + 10, 30, WHITE);
		//DrawText();
		DrawText("Version 1.0", 10, screenHeight - 10, 10, MAROON);
		DrawText("Volver a jugar", rec2.x + 18, rec2.y + 10, 20, MAROON);
		DrawText("Puntos: ", screenWidth / 2 - 170, rec1.y + 10, 30, WHITE);

		EndDrawing();
	}

}