#pragma once
#include "pch.h"
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

/*   SCORE-004000 HI-006000 REST-03   */
class Scoreboard {
	sf::Font gameFont;
	sf::Text gameData;
	sf::Vector2f position{ WINDOW_SIZE_X / 4, WINDOW_SIZE_Y - BLOCK_SIZE_Y };
	sf::Vector2f size{ WINDOW_SIZE_X, BLOCK_SIZE_Y };
	int score, topScore;
	string str1 = "SCORE-", str2 = " HI-", str3 = " REST-0", str_score, str_top_score, str_rest; // 17 letters + 17 numbers
public:
	// initialize gameData, set font size, color, outline...
	Scoreboard() {
		score = 0;
		topScore = 0;
		if (!gameFont.loadFromFile("fonts/ponderosa.regular.ttf"))
			myLog(Logger::ERR) << "Failed loading fonts" << endl;
		gameData.setFont(gameFont);
		gameData.setCharacterSize(BLOCK_SIZE_Y / 4 * 3);
		gameData.setFillColor(sf::Color::White);
		gameData.setOutlineColor(sf::Color::Black);
		gameData.setOutlineThickness(BLOCK_SIZE_Y / 8);
		gameData.setPosition(position);
	}
	void addPoint(int add) {
		score += add; // coin = 500, level = 2000
		fillTable();
	}
	void looseHeart() {
		lives -= 1; //
		fillTable();
	}
	void annulatePoint() {
		score = 0;
		lives = LIVES_CONST;
		fillTable();
	}
	// convert ints into strings and add them to the table
	void fillTable() {
		stringstream ss; // stream
		ss.setf(ios::right); // formatting to make 000000
		ss.width(6); 
		ss.fill('0');
		ss << score;
		str_score = ss.str(); // to get data stored in ss
		if (score >= topScore) { // increase top score
			topScore = score;
			str_top_score = str_score;
		}
		str_rest = to_string(lives); // int -> string
		gameData.setString(str1 + str_score + str2 + str_top_score + str3 + str_rest); // make sentence
	}
	// draw game info on to the screen
	void drawTo(sf::RenderWindow &window) {
		window.draw(gameData);
	}
};