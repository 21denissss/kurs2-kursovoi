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
bool isCaps = false;
#include "src/Logic/Converting.h"
#include "src/Visual/Rectangle.h"
#include "src/Visual/BBRect.h"
#include "src/Visual/Label.h"
#include "src/Visual/Button.h"
#include "src/Visual/TextBox.h"
using namespace sf; 
using namespace std;
extern int NUMBER;
extern int NUMBERCHESS;

namespace Btn {

	class ChessRect :public Rectangle {
		Texture texture;
		Sprite sprite;
		string type;
		const int num;
		char team;
		bool isSelect;
		void setSprite()
		{
			string st = "resources/chess/";
			st = st + type + '_' + team + ".png";
			texture.loadFromFile(st);
			sprite.setTexture(texture);
		}
	public:
		ChessRect(int x = 300, int y = 150, int weight = 75, int height = 75) :num(NUMBERCHESS)
		{
			x = x + weight * (num % 8);
			y = y + height * (num / 8);

			if ((x - y) % 2 != 0) {
				rect.setFillColor(Color(128, 128, 128));
			}
			isSelect = false;
			color = Color::Black;
			setSize(Vector2i(weight, height));
			rect.setSize(Vector2f(weight - 4, height - 4));
			shadowRect.setSize(Vector2f(weight, height));
			shadowRect.setFillColor(color);
			string st = "resources/chess/";
			switch (num) {
			case 0:
			case 7:
				st += "rook_b.png";
				type = "rook";
				team = 'b';
				break;
			case 56:
			case 63:
				st += "rook_w.png";
				type = "rook";
				team = 'w';
				break;
			case 1:
			case 6:
				st += "knight_b.png";
				type = "knight";
				team = 'b';
				break;
			case 57:
			case 62:
				st += "knight_w.png";
				type = "knight";
				team = 'w';
				break;
			case 2:
			case 5:
				st += "bishop_b.png";
				type = "bishop";
				team = 'b';
				break;
			case 58:
			case 61:
				st += "bishop_w.png";
				type = "bishop";
				team = 'w';
				break;
			case 3:
				st += "queen_b.png";
				type = "queen";
				team = 'b';
				break;
			case 59:
				st += "queen_w.png";
				type = "queen";
				team = 'w';
				break;
			case 4:
				st += "king_b.png";
				type = "king";
				team = 'b';
				break;
			case 60:
				st += "king_w.png";
				type = "king";
				team = 'w';
				break;
			default:
				type = "n";
				team = 'n';
				break;
			}
			if (num >= 8 && num <= 15) {
				st += "pawn_b.png";
				type = "pawn";
				team = 'b';
			}
			if (num >= 48 && num <= 55) {
				st += "pawn_w.png";
				type = "pawn";
				team = 'w';
			}
			if (num < 16 || num > 47) {
				texture.loadFromFile(st);
				sprite.setTexture(texture);
			}

			setPosition(Vector2i(x, y));
			NUMBERCHESS++;
		}
		string getType()
		{
			return type;
		}
		char getTeam()
		{
			return team;
		}
		void outMove()
		{
			int i = 1;
			if (team == 'w') {
				i *= -1;
			}
			if (getType() == "pawn") {
				
			}else
			if (getType() == "rook") {

			}else
			if (getType() == "knight") {

			}
			else
			if (getType() == "queen") {

			}
			else
			if (getType() == "king") {

			}
			else
			if (getType() == "bishop") {

			}
		}
		void changeType(string type)
		{
			this->type = type;
			setSprite();
		}
		void killFig()
		{
			this->type = "n";
			team = 'n';
			setSprite();
		}
		Vector2i getSize()
		{
			return size;
		}
		void setPosition(Vector2i coord)
		{
			this->coord = coord;
			shadowRect.setPosition(coord.x, coord.y);
			rect.setPosition(coord.x + 2, coord.y + 2);
			sprite.setPosition(coord.x + 2, coord.y + 2);
		}
		bool getSelect(Vector2i mouse)
		{
			if (select(mouse)&& Mouse::isButtonPressed(Mouse::Left)) {
				shadowRect.setFillColor(Color::Magenta);
				isSelect = true;
				//click();
			}
			if (!select(mouse)&&Mouse::isButtonPressed(Mouse::Left)) {
				shadowRect.setFillColor(Color::Black);
				isSelect = false;
				//click();
			}
			return isSelect;
		}
		void OutHere(RenderWindow& window)
		{
			window.draw(shadowRect);
			window.draw(rect);
			window.draw(sprite);
		}
	};

	ChessRect* getMoveRect(ChessRect* chess,int pos)
	{
		int i = 1, j = 0;
		Vector2i temp = chess[pos].getPosition();
		ChessRect* moveRect = new ChessRect[64];
		if (chess[pos].getTeam() == 'w') {
			i *= -1;
		}
		if (chess[pos].getType() == "pawn") {
			for (int i = 0; i < 64; i++) {
				Vector2i vect = chess[i].getPosition(), size = chess[i].getSize();
				if (abs(vect.x - temp.x)==size.x || abs(vect.y - temp.y)==size.y)
				if ((abs(vect.x - temp.x) == 0) || (abs(vect.y - temp.y) == 0)){
					//moveRect[j++] = chess[i];
				}
			}
		}else
		if (chess[pos].getType() == "rook") {

		}else
		if (chess[pos].getType() == "knight") {

		}
		else
		if (chess[pos].getType() == "queen") {

		}
		else
		if (chess[pos].getType() == "king") {

		}
		else
		if (chess[pos].getType() == "bishop") {

		}
		return moveRect;
	}


	

	


	
}





//Rectangle
//Btn::Rectangle::Rectangle(int x = 650, int y = 300, int weight = 75, int height = 75)
//{
//	extern int number;
//	num = number;
//	col = Color::Black;
//	if (number == 0)
//		number = 16;
//	x = x + weight * ((number - 1) % 4);
//	y = y + height * ((number - 1) / 4);
//	x_win = x;
//	y_win = y;
//	if (number == 16)
//		number = 0;
//	font.loadFromFile("resources/comic.ttf");
//	rect.setSize(sf::Vector2f(weight - 4, height - 4));
//	shadowRect.setSize(sf::Vector2f(weight, height));
//	shadowRect.setFillColor(col);
//	this->weight = weight;
//	this->height = height;
//	this->x = x;
//	this->y = y;
//	text = string2text(int2string(number));
//	text.setFillColor(col);
//	text.setFont(font);
//	text.setCharacterSize(36);
//	number++;
//}
//bool Btn::Rectangle::select(Vector2i mouse, Color col)
//{
//	if ((mouse.x > x && mouse.x < x + weight) && (mouse.y > y && mouse.y < y + height)) {
//		text.setFillColor(col);
//		return true;
//	}
//	else {
//		text.setFillColor(this->col);
//		return false;
//	}
//}
//Vector2i Btn::Rectangle::getPosition()
//{
//	Vector2i vect;
//	vect.x = x;
//	vect.y = y;
//	return vect;
//}
//Vector2i Btn::Rectangle::getWinPosition()
//{
//	Vector2i vect;
//	vect.x = x_win;
//	vect.y = y_win;
//	return vect;
//}
//void Btn::Rectangle::setPosition(Vector2i mouse)
//{
//	x = mouse.x;
//	y = mouse.y;
//}
//bool Btn::Rectangle::onClick(Vector2i mouse, Color col_in = Color::Yellow)
//{
//	if (select(mouse, col_in) && Mouse::isButtonPressed(Mouse::Left)) {
//		while (Mouse::isButtonPressed(Mouse::Left));
//		Music music;
//		music.openFromFile("resources/music/click.ogg");
//		music.setVolume(100);
//		music.play();
//		Sleep(125);
//		return true;
//	}
//	else
//		return false;
//}