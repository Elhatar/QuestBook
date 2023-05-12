#include <iostream>
#include <string>
#include <fstream> //библиотека для работы с файлами
#include <Windows.h>
#include <ctime>
#include<random>

using namespace std;

class Quest
{
	string type;
	string condition;
	bool isCompleted = 0;
public:
	void SetType(string val)
	{
		type = val;
	}
	string GetType()
	{
		return type;
	}
	void SetCondition(string val)
	{
		condition = val;
	}
	void CompleteQuest()
	{
		isCompleted = true;
	}
	string QuestToString()
	{
		char crutch;
		if (isCompleted)
			crutch = (char)2;
		else
			crutch = (char)1;
		return (type + ": " + condition + "\t" + crutch);
	}
	Quest GetNewQuestFromConsole() //Получает новый квест из консоли и возвращает его
	{
		string condition;
		int type;
		Quest quest;
		cout << "Напиши условие задания здесь:" << endl;
		SetConsoleCP(1251);
		cin.get();
		getline(std::cin, condition);
		cout << "Введи тип задания: 1. Ежедневное, 2. Основное" << endl;
		cin >> type;
		switch (type)
		{
		case 1:
			quest.type = "Ежедневное";
			break;
		case 2:
			quest.type = "Основное";
			break;
		}
		SetConsoleCP(866);
		quest.condition = condition;
		return quest;
	}
};

class File
{
	string fileName;

public:
	void SetFileName(string name)
	{
		fileName = name + ".txt";
	}
	void Recreate() //Создает файлы
	{
		ofstream questFile (fileName);
	}
	void WriteQuestToFile(Quest quest)
	{
		fstream file(fileName, fstream::in | fstream::out | fstream::app);
		file << quest.QuestToString() << endl;
		file.close();
	}
	void PrintFile()
	{
		string line;
		fstream file(fileName);
		while (!file.eof())
		{
			line = "";
			getline(file, line);
			cout << line << endl;
		}
	}
	void CompleteQuest()
	{
		int i = 0, qNum;
		cout << "Введите номер квеста" << endl;
		cin >> qNum;
		fstream file(fileName, ios::in | ios::out | ios::binary);
		if (!file)
			cout << "Ошибка чтения файла" << endl;
		else
		{
			while (file)
			{
				if (file.get() == (char)1)
				{
					i++;
					if (i == qNum)
					{
						file.seekp(-1, file.cur);
						file.put((char)2);
						file.flush();
					}

				}
			}
		}
		file.close();
	}
	void Reset()
	{
		fstream file(fileName, ios::in | ios::out | ios::binary);
		if (!file)
			cout << "Ошибка чтения файла" << endl;
		else
		{
			while (file)
			{
				if (file.get() == (char)2)
				{
					file.seekp(-1, file.cur);
					file.put((char)1);
					file.flush();
				}
			}
		}
		file.close();
	}

};

class Date
{
	int currentDate;
public:
	void SetCurrentDate() //Записывает в currentDate сегодняшний день
	{
		time_t now = time(0);
		#pragma warning(suppress : 4996)
		tm* ltm = localtime(&now);
		currentDate = ltm->tm_mday;
	}
	string GetCurrentDate()
	{
		return to_string(currentDate);
	}
	string GetLastDateFromFile()
	{
		string line;
		fstream file("date");
		getline(file, line);
		return line;
	}
	void WriteCurrentDateToFile()
	{
		ofstream file("date", fstream::in | fstream::out | fstream::app);
		file << currentDate << endl;
		file.close();
	}
};

class Loot
{
	public:
	void GetReward()
	{
		string line;
		int lineCount = 0, value;
		fstream file("rewards.txt");
		if (!file)
			cout << "Ошибка" << endl;
		else
		{
			while (!file.eof())
			{
				getline(file, line);
				lineCount++;
			}
		}
		value = rand() % lineCount;
		while (!file.eof())
		{
			getline(file, line);			
			if (value == 0)
				break;
			value--;
		}
		cout << "Ваша награда - " << line << endl;
		file.close();
	}
	void AddReward()
	{
		SetConsoleCP(1251);
		string reward;
		cout << "Введите название награды:" << endl;
		cin.get();
		getline(cin, reward);
		SetConsoleCP(866);
		fstream file("rewards.txt", fstream::in | fstream::out | fstream::app);
		file << reward << endl;
		file.close();
	}
};

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	File daily, main;
	Date date;
	Loot reward;
	daily.SetFileName("dailyQuests");
	main.SetFileName("mainQuests");
	date.SetCurrentDate();
	if (date.GetCurrentDate() == date.GetLastDateFromFile())
	{
		daily.Reset();
	}
	cout << "Задания:" << endl;
	daily.PrintFile();
	main.PrintFile();

	cout << "Для доступа в меню нажмите любую кнопку" << endl;
	system("pause");

	m1: //Начало меню
	cout << "\n" << "Меню:" << endl;
	cout << "Выбери действие" << endl;
	cout << "1. Отобразить задания" << endl;
	cout << "2. Добавить задание" << endl;
	cout << "3. Выполнить задание" << endl;
	cout << "4. Добавить награду в лутбокс" << endl;
	cout << "5. Пересоздать файлы" << endl;
	cout << "6. Выход" << endl;
	int input;
	cin >> input;
	switch (input)
	{
	case 1:
		cout << "Задания:" << endl;
		daily.PrintFile();
		main.PrintFile();
		break;
	case 2:
		{
		Quest newQuest = newQuest.GetNewQuestFromConsole();
		if (newQuest.GetType() == "Ежедневное")
			daily.WriteQuestToFile(newQuest);
		else if (newQuest.GetType() == "Основное")
			main.WriteQuestToFile(newQuest);
		else
		{
			cout << "Error, wrong quest type. Try again" << endl;
			break;
		}
		cout << "Успешно создано" << endl;
		}
		break;
	case 3:
		int num;
		cout << "Какое задание?\n" << "1. Ежедневное\n" << "2. Основное" << endl;
		cin >> num;
		switch (num)
		{
		case 1:
			daily.CompleteQuest();
			break;
		case 2:
			main.CompleteQuest();
			reward.GetReward();
			break;
		}
		break;
	case 4:
		reward.AddReward();
		break;
	case 5:
		daily.Recreate();
		main.Recreate();
		break;
	case 6:
		date.WriteCurrentDateToFile();
		return 0;
	default:
		cout << "Попробуйте снова" << endl;
		goto m1;
	}
	
	goto m1;//Конец меню
}