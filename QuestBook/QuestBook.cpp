#include <iostream>
#include <string>
#include <fstream> //библиотека для работы с файлами
#include <Windows.h>
#include <ctime>

//5. Функция наград с лутбоксами
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
		string type;
		Quest quest;
		cout << "Напиши условие задания здесь:" << endl;
		SetConsoleCP(1251);
		cin.get();
		getline(std::cin, condition);
		cout << "Это Ежедневное задание, или Основное?" << endl;
		cin >> type;
		SetConsoleCP(866);
		quest.type = type;
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

int main()//////////////Вход в программу (а то теряю его уже)
{
	setlocale(LC_ALL, "rus");
	File daily, main;
	Date date;
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
	cout << "4. Пересоздать файлы" << endl;
	cout << "5. Выход" << endl;
	int input;
	cin >> input;
	switch (input)
	{
	case 1:
		cout << "Задания:" << endl;
		daily.PrintFile();
		main.PrintFile();
		cout << endl;
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
			daily.CompleteQuest();
			break;
		}
		break;
	case 4:
		daily.Recreate();
		main.Recreate();
		break;
	case 5:
		date.WriteCurrentDateToFile();
		return 0;
	}
	
	goto m1;//Конец меню
}

/*Пример:
* Ежедневные задания:
* 1. Спорт				1
* 2. Программирование	1
* 
* Сюжетные задания:
* 1. Документы в универ 	0
* 2. Лабы по АрхПК			0
*/

//Тикеты:

//Активно: 1:
// 
//5. Функция наград с лутбоксами
// 
//Доступно: 5:

//1. Создать 2 файла и реализовать доступ программы к ним
//2. Функция добавления задач
//3. Функция выполнения задач
//4. Функция сброса статуса ежедневных задач в 00:00
//5. Функция наград с лутбоксами

//Отложено: 0: