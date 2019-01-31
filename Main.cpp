#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <time.h>  
#include <Windows.h>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ifstream;
using std::to_string;

struct Word{
	string spelling;
	string hint;
};

class Hangman {
public:
	vector<Word> word_list;
	string revealed_char;
	string false_guess;
	vector<int> index_of_taken_word;
public:
	Hangman(string file_name) {
		word_list = read_file(file_name + ".txt");
		cout << "Welcome to Hangman\nTip: Enter repeating character will result in penalty" << endl;
		mainloop();
	}
private: 
	string line, word1, word2;
	string delimiter = ",";
	ifstream file;
	bool running = true;
	int score = 0, remaining_attempt = 10 ;
	int word_index;
	bool get_new_word = true;
	char letter;
	int letter_guessed;
	string user_input = "";
	string correct_attempt = "";

private:
	vector<Word> read_file(string file_name) {
		vector<Word> temp_list;
		file.open(file_name);
		while (getline(file, line)) {
			word1 = line.substr(0, line.find(delimiter));
			word2 = line.substr(line.find(delimiter) + 1, line.size());
			temp_list.push_back({ word1, word2 });
		}
		return temp_list;
	}

	void mainloop() {
		while (running) {

			if (get_new_word) {
				word_index = rand() % (word_list.size());
				get_new_word = false;
				remaining_attempt = word_list[word_index].spelling.size() + 4;
				cout << "\nHint: " << word_list[word_index].hint << endl << endl;
			}
			letter_guessed = 0;
			for(int i = 0; i < word_list[word_index].spelling.size(); i++){
				if ((revealed_char.find(word_list[word_index].spelling[i]) != std::string::npos)){
					cout << word_list[word_index].spelling[i] << " ";
					letter_guessed += 1;
				}
				else if(word_list[word_index].spelling[i] == '_') {
					letter_guessed += 1;
					cout << "  ";
				}
				else 
					cout << "_ ";
			}

			if (letter_guessed == word_list[word_index].spelling.size() || remaining_attempt == 0) {
				cout << "Correct answer: " << word_list[word_index].spelling << endl;
				while (user_input != "yes" || user_input != "no") {
					cout << "\nDo you want to try again (yes/no)" << " Total score: " << score <<endl;
					cin >> user_input;
					if (user_input == "yes") {
						get_new_word = true;
						false_guess = "";
						revealed_char = "";
						correct_attempt = "";
						score += word_list[word_index].spelling.size() + remaining_attempt;
						if (remaining_attempt > 0)
							cout << "Bonus remaining attempt!!" << endl;
						break;
					}
					else if (user_input == "no")
						return;
					else
						cout << "Invalid input: " << endl;
				}
			}

			if (!get_new_word) {

				cout << "score: " << score << " remaining attempt: " << remaining_attempt << "  False guess: " << false_guess;
				cout << endl;
				cin.clear();
				
				cout << "Enter a letter: ";
				cin >> letter;
				cin.clear();
				
				

				if (word_list[word_index].spelling.find(letter) != std::string::npos) {
					revealed_char += letter;
					cout << endl;
					if (!(correct_attempt.find(letter) != std::string::npos)) {
						correct_attempt += letter;
						score += 5;
					}
				}
				else {
					if (isalpha(letter) && !(false_guess.find(letter) != std::string::npos)) {
						false_guess += letter;
						false_guess += " ";
					}
				}
				remaining_attempt -= 1;
			}
			
			cout << endl;

		}
	}
};

int main(){
	srand(time(NULL));
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 14);
	string category[2] = { "Influencial_figures", "Animal_name" };
	for (int i = 0; i < sizeof(category)/sizeof(category[0]); i++ ) {
		cout << i + 1 << " " << category[i] << endl;
	}
	int input;
	cin >> input;
	cout << category[input - 1] << endl<< endl;
	Hangman game(category[input - 1]);
	system("pause");
}