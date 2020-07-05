#include "pch.h"
#include "ScoreRegister.h"

void ScoreRegister::registerScore(string username, int score)
{
	ofstream scoreFile;
	scoreFile.open("data/scores", std::ios_base::app);
	scoreFile << username << "\t" << score << "\n";
	scoreFile.close();
}

vector<string> ScoreRegister::readScores()
{
	ifstream scoreFile;
	scoreFile.open("data/scores");
	vector<string> scores;
	string score;

	while (getline(scoreFile, score)) {
		scores.push_back(score);
	}
	// TODO : sort scores before returning them
	return scores;
}

string ScoreRegister::getRandomUsername()
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(3, 0);
	std::generate_n(str.begin(), 3, randchar);
	return str;
}
