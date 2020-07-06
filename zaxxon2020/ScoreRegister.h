#pragma once

class ScoreRegister
{
public:
	static void registerScore(string username, int score);
	static vector<string> readScores();
	static string getRandomUsername();
};