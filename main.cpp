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
const int RECTANGLENUMBERS = 16;
int Volume[4] = {11,20,40};
Texture Textures[79];
Sprite Sprites[79];
string Name;
int number = 0;
/*
1. Передалать все под принципы ооп
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

void login(RenderWindow& window)
{
	Texture LoginBack;
	LoginBack.loadFromFile("resources/main2.png");
	Sprite background(LoginBack);
	Label YourName("Input your name:", 10, 10);
	TextBox NameBox(310,10);
	Button UseBtn("Use", 430, 10, 60);
	while (window.isOpen())
	{
		Vector2i mouse = Mouse::getPosition(window);
		Event event;
		window.pollEvent(event);
		window.clear();
		if (NameBox.getSelect(event, mouse)) {
			NameBox.editTextString(event);
		}
		if (UseBtn.onClick(mouse, Color::Yellow)) {
			if (NameBox.getString() == "") {
				Name = "User";
			}
			else
				Name = NameBox.getString();
			return;
		}
		window.draw(background);
		UseBtn.outHere(window);
		YourName.outHere(window);
		NameBox.outHere(window);
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
			MenuBox.editTextInt(event);
		}
		if (NewtonBox.getSelect(event, mouse)) {
			NewtonBox.editTextInt(event);
		}
		if (AboutBox.getSelect(event, mouse)) {
			AboutBox.editTextInt(event);
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
	music.setLoop(1);
	Texture GameBack1;
	Btn::Rectangle rect[RECTANGLENUMBERS];
	GameBack1.loadFromFile("resources/game1.jpg");
	TextBox CodeBox(1400, 700);
	Label WinLbl("", 50, 50), OutLbl("", 50, 350), UserLbl("",0,0);
	Sprite background(GameBack1);
	Button BackBtn("Back", 1350, 50, 80),RestartBtn("Restart",1350,100,140),CheckBtn("Check Code",1350,650,160);
	while (window.isOpen())
	{
		UserLbl.setText(Name);
		Vector2i mouse = Mouse::getPosition(window);
		Event event;
		window.pollEvent(event);
		window.clear();

		if (BackBtn.onClick(mouse, Color::Yellow)) {
			return;
		}
		if (RestartBtn.onClick(mouse, Color::Yellow)) {
			for (int i = 0; i < 3*RECTANGLENUMBERS; i++) {
				Vector2i vect1, vect2;
				int rand1 = rand()%(RECTANGLENUMBERS-1), rand2 = rand()%(RECTANGLENUMBERS - 1);
				vect1 = rect[rand1].getPosition();
				vect2 = rect[rand2].getPosition();
				rect[rand1].setPosition(vect2);
				rect[rand2].setPosition(vect1);
			}
		}
		if (CodeBox.getSelect(event, mouse)) {	
			{
				CodeBox.editTextString(event);
			}
		}
		if (CheckBtn.onClick(mouse, Color::Yellow)) {
			if(CodeBox.getString() == "win")
			for (int i = 0; i < RECTANGLENUMBERS; i++) {
				Vector2i vect = rect[i].getWinPosition();
				rect[i].setPosition(vect);
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape)) {
			return;
		}
		for (int i = 0; i < RECTANGLENUMBERS; i++) {
			if (rect[i].onClick(mouse)) {
				Vector2i vect1, vect2;
				vect1 = rect[i].getPosition();
				vect2 = rect[0].getPosition();
				if ((abs(vect1.x - vect2.x) == 75) || (abs(vect1.y - vect2.y) == 75))
					if ((abs(vect1.x - vect2.x) == 0) || (abs(vect1.y - vect2.y) == 0)) {
						rect[i].setPosition(vect2);
						rect[0].setPosition(vect1);
						break;
					}
			}
		}
		//Ячейки менять местами путем переноса одной яйчейки на другую
		/*for (int i = 0; i < RECTANGLENUMBERS; i++) {
			if (rect[i].onClick(mouse)) {
				Vector2i mouse2 = Mouse::getPosition(window);
				for (int j = 0; j < RECTANGLENUMBERS; j++){
					if (rect[j].select(mouse2, Color::Yellow) && rect[j].getNumber() == 0) {
						Vector2i vect1, vect2;
						vect1 = rect[i].getPosition();
						vect2 = rect[j].getPosition();
						if((abs(vect1.x - vect2.x) == 75)||(abs(vect1.y-vect2.y) == 75))
						if((abs(vect1.x - vect2.x) == 0) || (abs(vect1.y - vect2.y) == 0)){
							rect[i].setPosition(vect2);
							rect[j].setPosition(vect1);
							break;
						}
					}
				}
			}
		}*/
		for (int i = 0; i < RECTANGLENUMBERS; i++) {
			Vector2i vect1, vect2;
			WinLbl.setText("Status: Not Win");
			vect1 = rect[i].getPosition();
			vect2 = rect[i].getWinPosition();
			if (vect1 == vect2) {
				if(i != RECTANGLENUMBERS-1)
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
		CheckBtn.outHere(window);
		CodeBox.outHere(window);
		UserLbl.outHere(window);
		OutLbl.outHere(window);
		for (int i = 0; i < RECTANGLENUMBERS; i++) {
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
	Texture MenuBackground;
	MenuBackground.loadFromFile("resources/city.jpg");
	Sprite Background(MenuBackground);
	bool IsMenu = 1;
	int MenuNum = 0;
	Background.setPosition(0, 0);
	Button AboutBtn("About",100,400,100), ExitBtn("Exit",100,500,80), SettingBtn("Settings",1350,50,150), PlayBtn("Play",100,300,150);
	Label UserLbl("", 0, 0);
	while (IsMenu) {
		Event event;
		window.pollEvent(event);
		Vector2i mouse = Mouse::getPosition(window);
		window.clear();
		UserLbl.setText(Name);
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
			return;
		}
		window.draw(Background);
		PlayBtn.outHere(window);
		AboutBtn.outHere(window);
		SettingBtn.outHere(window);
		UserLbl.outHere(window);
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
	login(window);
	load(window);
	menu(window);
	window.close();
	return 0;
}
