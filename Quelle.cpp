#include <iostream>
#include <time.h>
#include <vector>
#include <stdlib.h>
#include <string>

using namespace std;

int feldBreite = 25;
int numberOfMines = 0;
int elementPerLine;
char guess;
int shiftChars = 97;


 void startGame()
{
	string a = "GAME STARTS";
	int parameter1, parameter2;
	cout << "WELCOME IN THE GAME" << endl << endl << "Choose the parameters of your Mine Field \n\n" << "~*~GAME MENU~*~" << endl << endl;
	cout << "Aviable maps: " << endl << endl << "1) small map -> 3x3" << endl << "2) medium map -> 5x5" << endl << "3) large map -> 10x10 (still BetaVersion)" << endl << endl;
	cout << "Type 1, 2 or 3 to choose" << endl;
	cin >> parameter1;
	if (cin.fail()) {
		system("CLS");
		cout << "YOU HAVE TO CHOOSE A NUMBER" << endl << endl;
		cin.clear();
		cin.ignore();
		system("PAUSE");
		system("CLS");
		startGame();
	}
	else
		if (parameter1 == 1) { ::feldBreite = 9; ::elementPerLine = 3; system("CLS"); cout << "\t" << a << endl << endl; }
		else if (parameter1 == 2) { ::feldBreite = 25; ::elementPerLine = 5; system("CLS"); cout << "\t" << a << endl << endl; }
		else if (parameter1 == 3) { ::feldBreite = 100; ::elementPerLine = 10; system("CLS"); cout << "\t" << a << endl << endl; }
		else
		{
			system("CLS");
			cout << "Your number has to be between 1 and 3!" << endl << endl;
			cin.clear();
			cin.ignore();
			system("PAUSE");
			system("CLS");
			startGame();
		}
	cout << "~*~GAME MENU~*~" << endl << endl << "Avaiable levels: " << endl << endl << "1) easy" << endl << "2) medium" << endl << "3) hard" << endl << "4) insane" << endl << endl;
	cout << "Type 1, 2, 3 or 4 to choose" << endl;
	cin >> parameter2; 
	cout << endl;
		
	if (cin.fail()) {
		system("CLS");
		cout << "YOU HAVE TO CHOOSE A NUMBER" << endl << endl;
		cin.clear();
		cin.ignore();
		system("PAUSE");
		system("CLS");
		startGame();
	}
	else
		if (parameter2 == 1) { ::numberOfMines = 2 * (elementPerLine/3); system("CLS"); cout << "\t" << a << endl << endl; }
		else if (parameter2 == 2) { ::numberOfMines = 5 * (elementPerLine/3); system("CLS"); cout << "\t" << a << endl << endl;}
		else if (parameter2 == 3) { ::numberOfMines = 8 * (elementPerLine / 3); system("CLS"); cout << "\t" << a << endl << endl;}
		else if (parameter2 == 4) { ::numberOfMines = 13 * (elementPerLine / 3); system("CLS"); cout << "\t" << a << endl << endl;}
		else
		{
			system("CLS");
			cout << "Your number has to be between 1 and 4!" << endl << endl;
			cin.clear();
			cin.ignore();
			system("PAUSE");
			system("CLS");
			startGame();
		}
}
vector<char> fieldCreator() 
{
	vector<char> v;
	if (feldBreite == 100)
		::shiftChars = 49;
	for (int i = shiftChars; i < (feldBreite + shiftChars); i++)
	{
		v.push_back(i);
	}
	return v;
}

void show(vector<char> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << "\t";
		if ((i + 1) % elementPerLine == 0)
			cout << "\n\n";
	}
}

vector<char> minefieldCreator()
{
	vector<char> v;
	for (int i = 0; i < feldBreite; i++)
	{
		v.push_back('0');
	}
	for (int i = 0; i < numberOfMines; i++)
	{
		while (true)
		{
			unsigned int mine = rand() % (v.size());
			if (v[mine] != 'M')
			{
				v[mine] = 'M';
				break;
			}
		}
	}
	for (int i = 0; i < v.size(); i++)
	{
		if ((i - (elementPerLine - 1)) % elementPerLine != 0)
			if (v[i + 1] == 'M' && v[i] != 'M')
				v[i] = (v[i] + 1);
		if (i % elementPerLine != 0)
			if (v[i - 1] == 'M' && v[i] != 'M')
				(v[i] = (v[i] + 1));
		if (i < (feldBreite - elementPerLine))
			if (v[i + elementPerLine] == 'M' && v[i] != 'M')
				(v[i] = (v[i] + 1));
		if (i >= elementPerLine)
			if (v[i - elementPerLine] == 'M' && v[i] != 'M')
				(v[i] = (v[i] + 1));
	}
	return v;
}
vector<char> placeBombs(vector<char> v)
{
	for (int i = 0; i < numberOfMines; i++)
	{
		while (true)
		{
			unsigned int mine = rand() % (v.size());
			if (v[mine] != 'M')
			{
				v[mine] = 'M';
				break;
			}
		}
		return v;
	}
}
bool checkForMine(char guess, vector<char> v)
{
	if (v[(int)guess - shiftChars] == 'M')
		return true;
	else
		return false;
}
char shoot(char guess, vector<char> v)
{
	if (checkForMine(guess, v))
		return 'M';
}
int main()
{
	startGame();
	srand(time(NULL));
	if (numberOfMines != 0)
	{
		vector<char> field = fieldCreator();
		vector<char> minefield = minefieldCreator();
		show(field);
		for (int i = 0; i < (feldBreite - numberOfMines); i++)
		{
			cout << endl << "Enter your guess:" << endl;
			cout << ">";
			cin >> guess;
			system("CLS");
			field[(int)guess - 97] = minefield[(int)guess - 97];
			
			if (shoot(guess, minefield) == 'M')
			{
				show(minefield);
				cout << "GAME OVER" << endl;
				system("pause");
				return -1;
			}
			show(field);
			cout << endl;
		}

		cout << "YOU WIN" << endl;
		system("pause");
		//cout << endl << endl << elementPerLine << endl << endl << feldBreite; //DEBUG
		return 0;
	}
}