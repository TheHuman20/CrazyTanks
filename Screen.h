#pragma once

class Screen
{
private:
	int width;
	int height;
	char* buf;

	void UpdateSize();
	void CleanBuf();
public:
	Screen();
	~Screen();

	void Prepare();
	void Write(int x, int y, char c);
	void Draw();

	bool IsValid(int x, int y)
	{
		return x > 1 && y > 1 && x < width-1 && y < height-1;
	}
};
