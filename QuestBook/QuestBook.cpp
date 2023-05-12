#include <iostream>
#include <string>
#include <fstream> //библиотека для работы с файлами
#include <Windows.h>

//4. Функция сброса статуса ежедневных задач в 00:00
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

};

int main()
{
	setlocale(LC_ALL, "rus");
	File daily, main;
	daily.SetFileName("dailyQuests");
	main.SetFileName("mainQuests");

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
//4. Функция сброса статуса ежедневных задач в 00:00
// 
//Доступно: 6:

//1. Создать 2 файла и реализовать доступ программы к ним
//2. Функция добавления задач
//3. Функция выполнения задач
//4. Функция сброса статуса ежедневных задач в 00:00
//5. Функция автозапуска программы
//6. Функция наград с лутбоксами

//Отложено: 0: