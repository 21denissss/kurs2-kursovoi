#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <random>
#include <SFML/Audio.hpp>
#include "HelpFile.hpp"
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <string.h>
#include <windows.h>
#include <ctime>
using namespace sf; 
using namespace std;
using namespace Btn;
int Volume[4] = {11,20,40};
Texture Textures[79];
Sprite Sprites[79];
int number = 0;
/*
1. Сделать игру
2. Пофиксить настройки(уровень музыки в главном меню)
*/

void init(RenderWindow& window)
{
	int CurrentFrame = 0, temp = 0;
	while (CurrentFrame != 79) {
		string name = "resources/gif/load/IMG000";
		temp = CurrentFrame / 10;
		if (temp != 0) {
			name = name + char(temp + 48) + char(CurrentFrame - temp * 10 + 48) + ".bmp";
		}
		else {
			name = name + '0' + char(CurrentFrame + 48) + ".bmp";
		}
		Textures[CurrentFrame].loadFromFile(name);
		Sprites[CurrentFrame].setTexture(Textures[CurrentFrame]);
		Sprites[CurrentFrame].setPosition(0, 0);
		CurrentFrame++;
	}
}

void load(RenderWindow& window)
{
	int CurrentFrame = 0;
	while (CurrentFrame != 79) {
		window.clear();
		window.draw(Sprites[CurrentFrame++]);
		window.display();
	}
}

String AboutSt[3] =
{
	/*0*/	"Над проектом трудился:",
	/*1*/	"Федорин Денис",
	/*2*/	"Версия 1.0"
};

void about(RenderWindow& window)
{

	setlocale(LC_ALL, "ru");
	Music music;
	music.openFromFile("resources/music/music.ogg");
	music.setVolume(Volume[1]);
	music.play();
	Texture AboutBack;
	AboutBack.loadFromFile("resources/about1.jpg");
	Sprite background(AboutBack);
	Label AboutLbl[3] = {
		{AboutSt[0],0,900,36,Color::White,Color::Black},
		{AboutSt[1],0,950,36,Color::White,Color::Black},
		{AboutSt[2],0,1000,36,Color::White,Color::Black}
	};
	while (window.isOpen())
	{
		if ( music.getStatus() == music.Stopped)
			return;
		Vector2i mouse = Mouse::getPosition(window);
		Event event;
		window.pollEvent(event);
		window.clear();
		for (int i = 0; i < 3; i++) {
			AboutLbl[i].changePos(0, -0.1);
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			music.stop();
			return;
		}
		window.draw(background);
		for (int i = 0; i < 3; i++) {
			AboutLbl[i].outHere(window);
		}
		window.display();
	}
}

void settings(RenderWindow& window)
{
	Texture SettingBack;
	SettingBack.loadFromFile("resources/setting.jpg");
	Button BackBtn("Back", 1350, 50, 80), SaveBtn("Save",1350,100,80);
	Sprite background(SettingBack);
	Label VolumeLbl("Volume",1350,200),MenuLbl("Menu:",1250,250), GameLbl("Game:", 1250, 320), AboutLbl("About: ",1250,390);
	TextBox MenuBox(1450,250), NewtonBox(1450,320), AboutBox(1450,390);
	while (window.isOpen())
	{
		Vector2i mouse = Mouse::getPosition(window);
		Event event;
		window.pollEvent(event);
		window.clear();
		if (MenuBox.getSelect(event, mouse)) {
			MenuBox.editText(event);
		}
		if (NewtonBox.getSelect(event, mouse)) {
			NewtonBox.editText(event);
		}
		if (AboutBox.getSelect(event, mouse)) {
			AboutBox.editText(event);
		}
		if (BackBtn.onClick(mouse,Color::Yellow)) {
			return;
		}
		if (SaveBtn.onClick(mouse, Color::Yellow)) {
			if(!NewtonBox.is_empty())
				Volume[0] = NewtonBox.getInt();
			if (!AboutBox.is_empty())
				Volume[1] = AboutBox.getInt();
			if (!MenuBox.is_empty())
				Volume[2] = MenuBox.getInt();
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			return;
		}
		window.draw(background);
		BackBtn.outHere(window);
		SaveBtn.outHere(window);
		VolumeLbl.outHere(window);
		MenuLbl.outHere(window);
		GameLbl.outHere(window);
		AboutLbl.outHere(window);
		AboutBox.outHere(window);
		NewtonBox.outHere(window);
		MenuBox.outHere(window);
		window.display();
	}
}

void game(RenderWindow& window)
{
	Music music;
	number = 0;
	music.openFromFile("resources/music/play.ogg");
	music.setVolume(Volume[0]);
	music.play();
	Texture GameBack1;
	Btn::Rectangle rect[16];
	GameBack1.loadFromFile("resources/game1.jpg");
	Label WinLbl("", 50, 50);// , OutLbl("", 50, 350);
	Sprite background(GameBack1);
	Button BackBtn("Back", 1350, 50, 80),RestartBtn("Restart",1350,100,140),WinBtn("Win",1350,150,60);
	while (window.isOpen())
	{
		Vector2i mouse = Mouse::getPosition(window);
		Event event;
		window.pollEvent(event);
		window.clear();
		if (BackBtn.onClick(mouse, Color::Yellow)) {
			return;
		}
		if (RestartBtn.onClick(mouse, Color::Yellow)) {
			for (int i = 0; i < 39; i++) {
				Vector2i vect1, vect2;
				int rand1 = rand()%15, rand2 = rand()%15;
				vect1 = rect[rand1].getPosition();
				vect2 = rect[rand2].getPosition();
				rect[rand1].setPosition(vect2);
				rect[rand2].setPosition(vect1);
			}
		}
		if (WinBtn.onClick(mouse, Color::Yellow)) {
			for (int i = 0; i < 16; i++) {
				Vector2i vect = rect[i].getWinPosition();
				rect[i].setPosition(vect);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			return;
		}
		for (int i = 0; i < 16; i++) {
			if (rect[i].onClick(mouse)) {
				mouse = Mouse::getPosition(window);
				for (int j = 0; j < 16; j++){
					if (rect[j].select(mouse, Color::Yellow) && rect[j].getNumber() == 0) {
						Vector2i vect1, vect2;
						vect1 = rect[i].getPosition();
						vect2 = rect[j].getPosition();
						if((abs(vect1.x - vect2.x) == 75)||(abs(vect1.y-vect2.y) == 75))
						if(!((abs(vect1.x - vect2.x) == 75) && (abs(vect1.y - vect2.y) == 75))){
							rect[i].setPosition(vect2);
							rect[j].setPosition(vect1);
							break;
						}
					}
				}
			}
		}
		for (int i = 0; i < 16; i++) {
			Vector2i vect1, vect2;
			WinLbl.setText("Status: Not Win");
			vect1 = rect[i].getPosition();
			vect2 = rect[i].getWinPosition();
			if (vect1 == vect2) {
				if(i != 15)
					continue;
			}
			else
				break;
			WinLbl.setText("Status: Win");
		}
		window.draw(background);
		BackBtn.outHere(window);
		WinLbl.outHere(window);
		RestartBtn.outHere(window);
		WinBtn.outHere(window);
		//OutLbl.outHere(window);
		for (int i = 0; i < 16; i++) {
			rect[i].OutHere(window);
		}
		window.display();
	}
}

void menu(RenderWindow& window)
{
	Music music;
	music.openFromFile("resources/music/main.ogg");
	music.play();
	music.setLoop(1);
	Texture MenuBackground, AboutBack;
	AboutBack.loadFromFile("resources/aboutback.png");
	MenuBackground.loadFromFile("resources/city.jpg");
	Sprite Background(MenuBackground),About(AboutBack);
	bool IsMenu = 1;
	int MenuNum = 0;
	Background.setPosition(0, 0);
	Button AboutBtn("About",100,400,100), ExitBtn("Exit",100,500,80), SettingBtn("Settings",1350,50,150), PlayBtn("Play",100,300,150);
	while (IsMenu) {
		Event event;
		window.pollEvent(event);
		Vector2i mouse = Mouse::getPosition(window);
		window.clear();
		music.setVolume(Volume[2]);
		if (PlayBtn.onClick(mouse)) {
			music.pause();
			load(window);
			game(window);
			load(window);
			music.play();
		}
		if (AboutBtn.onClick(mouse)) {
			music.pause();
			load(window);
			about(window);
			load(window);
			music.play();
		}
		if (SettingBtn.onClick(mouse)) {
			load(window);
			settings(window);
			load(window);
		}
		if (ExitBtn.onClick(mouse)) {
			window.close(); 
			exit(0);
		}
		window.draw(Background);
		PlayBtn.outHere(window);
		AboutBtn.outHere(window);
		SettingBtn.outHere(window);
		ExitBtn.outHere(window);
		window.display();
	}
}


int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	//FreeConsole();
	RenderWindow window(VideoMode(1600, 900), "15");
	init(window);
	load(window);
	menu(window);
	return 0;
}
