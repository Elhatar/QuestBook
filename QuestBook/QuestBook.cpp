#include <iostream>
#include <string>
#include <fstream> //библиотека для работы с файлами
#include <Windows.h>

//3. Функция выполнения задач
using namespace std;

void createFiles();
void writeQuest(int a);
void getQuests(string path);

int main()
{
	setlocale(LC_ALL, "rus");
	cout << "ЕЖЕДНЕВНЫЕ ЗАДАНИЯ" << endl;
	getQuests("dailyQuests.txt");
	cout << "СЮЖЕТНЫЕ ЗАДАНИЯ" << endl;
	getQuests("mainQuests.txt");
	cout << "Для доступа в меню нажмите любую кнопку" << endl;
	system("pause");
	m1:
	cout << "\n" << "Меню:"<< "\n" << "Выбери действие" << endl << "1. Пересоздать файлы" << endl << "2. Добавить задание" << endl << "3. Выход" << endl;
	int input;
	cin >> input;
	switch (input)
	{
	case 1:
		createFiles();
		cout << "Успешно пересоздано" << endl;
		break;
	case 2:
		{
		cout << "1. Ежедневное задание" << endl << "2. Основное задание" << endl;
		int a;
		cin >> a;
		writeQuest(a);
		}
		break;
	case 3:
		return 0;
		break;
	}
	
	goto m1;
}

void createFiles() //Здесь мы создаем файлы для хранения заданий
{
	ofstream dailyQuests("dailyQuests.txt");
	ofstream mainQuests("mainQuests.txt");
	return;
}

void writeQuest(int a)//Здесь мы добавляем новые квесты в квестбук
{
	fstream dailyQuests("dailyQuests.txt", fstream::in | fstream:: out | fstream::app);
	fstream mainQuests("mainQuests.txt", fstream::in | fstream::out | fstream::app);
	cout << "Напиши свое задание здесь:" << endl;
	string input;
	SetConsoleCP(1251);
	cin.get();//игнорируем последний введенный символ в буфере
	getline(std::cin, input);
	switch (a)
	{
	case 1:
		if (dailyQuests.is_open())
		{
			dailyQuests << input << "\n";
		}
		else
		{
			cout << "Error file isn't open";
		}
		SetConsoleCP(866);
		dailyQuests.close();
		mainQuests.close();
		break;
	case 2:
		if (mainQuests.is_open())
		{
			mainQuests << input << "\n";
		}
		else
		{
			cout << "Error file isn't open";
		}
		SetConsoleCP(866);
		dailyQuests.close();
		mainQuests.close();
		break;
	}
}

void getQuests(string path)//Здесь мы выводим один из видов квестов
{
	string line;
	fstream file(path);
	while (!file.eof())
	{
		line = "";
		getline(file, line);
		cout << line << endl;
	}
}

/*Пример:
* Ежедневные задания:
* 1. Спорт..............☑
* - 15 отжиманий;
* - 15 приседани;
* - 15 пресс;
* 2. Программирование:..☑
* - Видео по С++ 3 штуки;
* 
* Сюжетные задания:
* 1. Документы в универ 0/1..🮱
* 2. Лабы по АрхПК 0/6.......🮱
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