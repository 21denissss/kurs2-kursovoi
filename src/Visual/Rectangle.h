#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <GL/glut.h>
#include <sstream>
#include <iostream>
#include <locale>
#include <string.h>
#include <windows.h>

using namespace sf;
using namespace std;

class Rectangle {
protected:
	Vector2i coord;
	Vector2i size;
	RectangleShape rect, shadowRect;
	Color color;
	void setSize(Vector2i size);
	bool select(Vector2i mouse, Color color = Color::Yellow);
	void click();
public:
	Rectangle(int x = 650, int y = 300, int weight = 75, int height = 75);
	
	Vector2i getPosition();
	void setPosition(Vector2i coord);
	void OutHere(RenderWindow& window);
	Vector2i getSize();
	bool onClick(Vector2i mouse, Color col_in = Color::Yellow);
};

