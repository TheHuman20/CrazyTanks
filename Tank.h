#ifndef TANK1_H
#define TANK1_H

#include "stdafx.h"
#include "enums.h"
#include "Screen.h"

using namespace constSpace;
/*
void main()
{
	Screen screen;
	...
		while (true) // main loop
		{
			screen.Prepare();
			for (int i = 0; i < objectCnt; i++)
			{
				objects[i]->Update(screen);
			}
			for (int i = 0; i < objectCnt; i++)
			{
				objects[i]->Draw(screen);
			}
			screen.Draw();

			for (int i = 0; i < objectCnt; i++)
			{
				auto Shot* shot = dynamic_cast<Shot>(objects[i]);
				if (shot && shot->IsObsolete())
					RemoveShot(i);
			}
		}
	...
}
*/
class BaseScreenObject
{
protected:
	int x;
	int y;
	eDirection direction;

	void MoveByDir(int& x, int& y, eDirection dir)
	{
		switch (dir)
		{
		case eDirection::UP: y -= 1; break;
		case eDirection::LEFT: x -= 1; break;
		case eDirection::RIGHT: x += 1; break;
		case eDirection::DOWN: y += 1; break;
		}
	}
public:
	virtual void Update(Screen& screen) abstract;
	virtual void Draw(Screen& screen, BaseScreenObject* bso) abstract;

	void SetPosDir(int x, int y, eDirection dir)
	{
		this->x = x;
		this->y = y;
		this->direction = dir;
	}

	int X() { return x; }
	int Y() { return y; }
	eDirection GetDirection() { return direction; }
};

class Tank;
class Shot : public BaseScreenObject
{
protected:
	bool isObsolete = false;
	Tank* tank;
public:
	Shot(Tank* tank)
	{
		this->tank = tank;
	}

	void Update(Screen& screen)
	{
		MoveByDir(x, y, direction);
		if (!screen.IsValid(x, y))
			isObsolete = true;
	}

	void Draw(Screen& screen, BaseScreenObject* bso)
	{
		screen.Write(x, y, '*');
	}

	Tank* Tank() const { return tank; }

	bool IsObsolete() { return isObsolete; }
};

class Tank : public BaseScreenObject
{
public:
	bool Move(Screen& screen, eDirection newDir)
	{
		//int group;
		this->direction = newDir;
		int newX = x;
		int newY = y;
		MoveByDir(newX, newY, direction);

		if (!screen.IsValid(newX, newY))
			return false;

		x = newX;
		y = newY;
		return true;
	}

	void Update(Screen& screen)
	{
	}

	void Draw(Screen& screen, BaseScreenObject* bso)
	{
 		eDirection dir = bso->GetDirection();

		if (dir == UP)
			screen.Write(x, y, '^');
		else if (dir == DOWN)
			screen.Write(x, y, 'v');
		else if (dir == LEFT)
			screen.Write(x, y, '<');
		else if (dir == RIGHT)
			screen.Write(x, y, '>');
	}
	Tank::Tank(int x, int y, eDirection direction) {
		this->x = x;
		this->y = y;
		this->direction = direction;
	}
	Tank::Tank() {
		
	}
};

/*
class Tank
{
public:
	int x;
	int y;
	eDirection direction;
	int hp;
	


public:
	virtual void setPosDir(int x, int y, eDirection direction);
//	virtual void Move(Player playerTank, int sizeOfFiled) = 0;
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	int getHP();
	eDirection getDirection();
	Tank();
	~Tank();
};
*/
#endif