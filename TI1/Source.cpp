#include <stdio.h>
#include <string>
#include <cmath>
#include <random>
#include <iostream>
#include <time.h>
#include <fstream>

#define Random(a, b) (double)rand()/(RAND_MAX+1) * (b-a) + a

using namespace std;

ifstream fRead;
ofstream fWrite;

string GenerateWord(string alphabet, int len);
string CompareWords(string *words, string alphabet, int n, int len);

/*
string CreateSentence()
{
	cout << "[1]: Подобрать последовательность частей речи в предложении самостоятельно\n[2]: Сгенерировать последовательность частей речи\n";
	int choice;
	string skeletSpeech = "";
	cin >> choice;
	if (choice == 0) {
		cin >> skeletSpeech;
	}
	else
	{
		for (int i = 0; i < Random(3, 6); i++)
		{
			choice = Random(0, 2);
			switch (choice)
			{
			case 0: { skeletSpeech += "Подлежащее "; break; }
			case 1: { skeletSpeech += "Сказуемое "; break; }
			default: { skeletSpeech += "Определение "; break; }
			}
		}
	}
}
*/

string CompareWords(string *words, string alphabet, int n, int len)
{
	string word;
	bool t = true;
	int length = Random(1, len);
	word = GenerateWord(alphabet, length);
	for (int i = 0; i < n; i++)
	{
		if (word == words[i])
			word = GenerateWord(alphabet, length);
	}
	return word;
}

string GenerateWord(string alphabet, int len)
{
	string word = "";
	for (int i = 0; i < len; i++)
	{
		word += alphabet[Random(0, alphabet.length() - 1)];
	}
	return word;
}

void createWords()
{
	int n, combinationsCount = 0;
	string alphabet;
	cout << "Введите строку альфавитных букв\n";
	cin >> alphabet;
	cout << "Какова максимальная длина слов?\n";
	cin >> n;
	fWrite << "Алфавит: " << alphabet << endl;
	fWrite << "Максимальная длина слов = " << n << endl;
	for (int i = 1; i <= n; i++)
	{
		combinationsCount += pow(alphabet.length(), i);
	}
	string *words;
	int iter = 0, curiter = 0;
	int wordCount;
	if (combinationsCount < 300)
		wordCount = combinationsCount;
	else wordCount = 300;
	words = new string[wordCount];
	string *subjects = new string[300];
	string *verbs = new string[300];
	string *allwords = new string[100000];
	string* adjectives = new string[300];
	cout << combinationsCount << endl;
	int notEmpty = 0;
	string word;
	//Цикл задающий длину
	iter = 0;
	for (int i = 1; i < n+1; i++)
	{
		//Проходим по всем комбинациям текущей длины
		for (int k = 0; k < pow(alphabet.length(), i); k++)
		{
			allwords[iter] = string(i, alphabet[0]);
			int numToWord = k;	// численное представление слова
			int iterWord = i-1; // итератор по слову
			while (numToWord > 0 && iterWord >= 0)
			{	//		слово	  [i]	   = символ в n-ичной системе
				allwords[iter][iterWord--] = alphabet[numToWord % alphabet.length()];
				numToWord /= alphabet.length();
			}
			cout << allwords[iter] << endl;
			curiter += 1;
		}
		iter++;
		//iter += pow(alphabet.length(), i);
	}
	// текущая длина слов
	for (int i = 0; i < wordCount; i++)
	{
		words[i] = CompareWords(words, alphabet, i, n);
	}
	int subjectsCount = 0, verbsCount = 0, adjectivesCount = 0;
	for (int i = 0; i < wordCount; i++)
	{
		cout << words[i] << endl;
		fWrite << words[i] << endl;
		if (i % 3 == 0)
		{
			subjects[subjectsCount] = words[i];
			subjectsCount++;
		}
		else if (i % 3 == 1)
		{
			verbs[verbsCount] = words[i];
			verbsCount++;
		}
		else
		{
			adjectives[adjectivesCount] = words[i];
			adjectivesCount++;
		}
	}
	fWrite << "\nСуществительных " << subjectsCount << endl;
	for (int i = 0; i <= subjectsCount; i++)
	{
		fWrite << subjects[i] << endl;
	}
	fWrite << "Глаголов " << verbsCount << endl;
	for (int i = 0; i <= verbsCount; i++)
	{
		fWrite << verbs[i] << endl;
	}
	fWrite << "Определений " << adjectivesCount << endl;
	for (int i = 0; i <= adjectivesCount; i++)
	{
		fWrite << adjectives[i] << endl;
	}
	fWrite << "Создано 300 слов из " << combinationsCount << " возможных" << endl;
	cout << "Существительных - " << subjectsCount << endl;
	cout << "Глаголов - " << verbsCount << endl;
	cout << "Дополнений - " << adjectivesCount << endl;
	system("pause");
}

void main()
{
	fRead.open("wordslog.txt");
	fWrite.open("wordslog.txt");
	srand(time(0));
	setlocale(0, "");
	createWords();
	fRead.close();
	fWrite.close();
}