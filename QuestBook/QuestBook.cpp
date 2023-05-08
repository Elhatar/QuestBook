#include <iostream>
#include <string>
#include <fstream> //библиотека для работы с файлами
#include <Windows.h>

//3. Функция выполнения задач
// Текущая идея: заменять символы пустого checkbox заполненным. В тексте *точно* не будет лишних чекбоксов
// П.С. Обновление можно сделать по тому же принцыпy
// П.П.С. Интересно как это сделанно в FTBQuests :thinking:
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
		return (type + ": " + condition + "\t" + to_string(isCompleted));
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
	cout << "3. Пересоздать файлы" << endl;
	cout << "4. Выход" << endl;
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
		daily.Recreate();
		main.Recreate();
		break;
	case 4:
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
//3. Функция выполнения задач
// 
//Доступно: 6:

//1. Создать 2 файла и реализовать доступ программы к ним
//2. Функция добавления задач
//3. Функция выполнения задач
//4. Функция сброса статуса ежедневных задач в 00:00
//5. Функция автозапуска программы
//6. Функция наград с лутбоксами

//Отложено: 0: