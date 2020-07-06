#include "pch.h"
#include "ScoreRegister.h"

void ScoreRegister::registerScore(string username, int score)
{
	ofstream scoreFile;
	scoreFile.open("data/scores", std::ios_base::app);
	scoreFile << username << "\t" << score << "\n";
	scoreFile.close();
}

bool compareScore(string score1, string score2)
{
	if (stoi(score1.substr(4, score1.length()-1)) > stoi(score2.substr(4, score2.length() - 1))) {
		return true;
	}
	return false;
}

vector<string> ScoreRegister::readScores()
{
	ifstream scoreFile;
	scoreFile.open("data/scores");
	vector<string> scores;
	string score;
	int score_number = 0;

	while (getline(scoreFile, score)) {
		scores.push_back(score);
		score_number++;
		if (score_number > 8) {
			break;
		}
	}

	sort(scores.begin(), scores.end(), compareScore);

	return scores;
}

string ScoreRegister::getRandomUsername()
{
	auto randchar = []() -> char
	{
		const char charset[] =
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			/*"abcdefghijklmnopqrstuvwxyz"*/;
		const size_t max_index = (sizeof(charset) - 1);
		return charset[rand() % max_index];
	};
	std::string str(3, 0);
	std::generate_n(str.begin(), 3, randchar);
	return str;
}
