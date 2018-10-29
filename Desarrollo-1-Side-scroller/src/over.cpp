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
		rec2.width = 100;

		rec3.x = screenWidth / 2 - 50;
		rec3.y = screenHeight / 2 + 160;
		rec3.height = 50;
		rec3.width = 100;

		if (CheckCollisionPointRec(mousePoint, rec1))
		{

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				gameOver = false;
				Screens = menu;
			}
		}
		


	}

	void OverDraw()
	{
		BeginDrawing();

		ClearBackground(DARKGRAY);


		DrawRectangle(rec1.x, rec1.y, rec1.width, rec1.height, BLACK);
		DrawRectangle(rec2.x, rec2.y, rec2.width, rec2.height, BLACK);
		DrawRectangle(rec3.x, rec3.y, rec3.width, rec3.height, BLACK);

		DrawText("Shards", screenWidth/ 2 - 70, screenHeight / 2 - 99, 50, MAROON);
		DrawText("Perdiste", screenWidth / 2 - 70, screenHeight / 2 - 49, 30, WHITE);
		DrawText(FormatText("%04i", score), rec1.x + 18, rec1.y + 10, 30, WHITE);
		//DrawText();
		DrawText("Version 0.5", 10, screenHeight - 10, 10, MAROON);

		EndDrawing();
	}

}