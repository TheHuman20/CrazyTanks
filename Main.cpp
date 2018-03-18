// Main.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "Main.h"
#include "Screen.h"
#include "vector"

using namespace std;
using namespace constSpace;

/*
bool gameOver;
int sizeOfField = 30;
int x, y, score;
eDirection direction;

void Run() {
	gameOver = false;
	direction = UP;
	x = sizeOfField / 2;
	y = sizeOfField - 1;
}

void Draw(Player& playerTank) {
	system("cls");
	int x = playerTank.getX();
	int y = playerTank.getY();
	eDirection dir = playerTank.getDirection();

	for (int i = 0; i < sizeOfField; ++i)
	{
		for (int j = 0; j < sizeOfField; j++)
		{
			if (i == 0 || i == sizeOfField - 1 || j == 0 || j == sizeOfField - 1) cout << "#";
			else if ((i == x && j == y)||(i == x - 1 && j == y)||(i == x + 1 && j == y)
				||(i == x && j == y - 1)||(i == x && j == y + 1))
			{
				cout << char(219);
			}
			else if (((i == x + 1 && j == y - 1) 
				|| (i == x + 1 && j == y + 1))
				&& dir == UP)
				cout << char(219);

			else if (((i == x - 1 && j == y - 1)
				|| (i == x - 1 && j == y + 1)) 
				&& dir == DOWN)
				cout << char(219);

			else if (((i == x - 1 && j == y + 1)
				|| (i == x + 1 && j == y + 1)) 
				&& dir == LEFT)
				cout << char (219);

			else if (((i == x - 1 && j == y - 1)
				|| (i == x + 1 && j == y - 1))
				&& dir == RIGHT)
				cout << char(219);
			else cout << ' ';

		}
		cout << endl;
	}
}


void test(){
int ch;

	while ((ch = _getch()) != 27) / * 27 = Esc key * / 
	{
		printf("%d", ch);
		if (ch == 0 || ch == 224)
			printf(", %d", _getch());
		printf("\n");
	}

	printf("ESC %d\n", ch);
}
*/

void Fire(vector<BaseScreenObject*>& objects, Tank& tank)
{
	auto* shot = new Shot(&tank);
	shot->SetPosDir(tank.X(), tank.Y(), tank.GetDirection());
	objects.push_back(shot);
}

int main()
{
	Screen screen;
	screen.Prepare();

	Tank tank1;
	Tank tankE1(34, 65, DOWN);
	Tank tankE2(22,7,UP);
	Tank tankE3(6, 30, UP);
	Tank tankE4(2, 43, DOWN);

	tank1.SetPosDir(10, 10, eDirection::UP);
	vector<BaseScreenObject*> objects;
	objects.push_back(&tank1); 
	objects.push_back(&tankE1);
	objects.push_back(&tankE2);
	objects.push_back(&tankE3);
	objects.push_back(&tankE4);

	while (true) // main loop
	{
		screen.Prepare();



		if (kbhit())
		{
			auto ch = getch();
			if (ch != 0)
			{
				switch (ch)
				{
				case 119: tank1.Move(screen, eDirection::UP); break;
				case 115: tank1.Move(screen, eDirection::DOWN); break;
				case 97: tank1.Move(screen, eDirection::LEFT); break;
				case 100: tank1.Move(screen, eDirection::RIGHT); break;
				case ' ': Fire(objects, tank1); break;
				}
			}
		}

		int i = 0;
		while (i < objects.size())
		{
			objects[i]->Update(screen);
			Shot* shot = dynamic_cast<Shot*>(objects[i]);
			if (shot && shot->IsObsolete())
			{
				objects.erase(objects.begin() + i);
				continue;
			}
			i++;
		}

		for (int i = 0; i < objects.size(); i++)
		{
			objects[i]->Draw(screen, objects[i]);
		}
		screen.Draw();

		Sleep(50);
	}

	screen.Draw();
	getch();
	/*

	system("mode con cols=100 lines=40");
	Run();
	Player playerTank((sizeOfField - 1) / 2, (sizeOfField - 1) / 2, UP);
	while (!gameOver) {
		Draw(playerTank);
		playerTank.Move(playerTank, sizeOfField);
	}
	*/
	return 0;
}
