#include <iostream>
#include "Map.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	Map card;
	int answer = 0, max, switchTwo, counter = 0;
	dataType data;
	cout << "Красно-черное дерево:\n";
	cout << "Введите целое положительное число для определения количества узлов\n";
	cin >> max;
	cout << "Введите данные, разделяя их пробелами\n";
	for (counter = 0; counter < max; counter++)
	{
		cin >> data;
		card.insert(counter + 1, data);
	}
	cout << "\nДерево было созданно и заполнено, доступные операции";
	cout << "\n\t 1. Добавление нового узла в дерево";
	cout << "\n\t 2. Удаление узла из дерево";
	cout << "\n\t 3. Поиск узла в дереве";
	cout << "\n\t 4. Удаление ассоциативного массива";
	cout << "\n\t 5. Вывод ключей";
	cout << "\n\t 6. Вывод значений";
	cout << "\n\t 7. Вывод дерева на экран";
	cout << "\n\t 8. Выход";
	cout << "\nВаш выбор: ";
	do
	{
		cin >> switchTwo;
		switch (switchTwo)
		{
		case 1:
			cout << "\nВведите данные для внесения в дерево.\n";
			cin >> data;
			card.insert(counter + 1, data);
			cout << "\nДанные были внесены в дерево.\n";
			break;
		case 2:
			cout << "\nВведите ключ, который подлежит удалению.\n";
			dataType key;
			cin >> key;
			card.remove(key);
			break;
		case 3:
			cout << "\nВведите ключ, по которому будем делать поиск.\n";
			dataType key2;
			cin >> key2;
			card.find(key2);
			break;
		case 4:
			cout << "\nОчищение ассоциативного массива\n";
			card.clear();
			break;
		case 5:
			cout << "\n Вывод ключей на экран\n";
			List keys = card.get_keys();
			while (!keys.isEmpty())
			{
				cout << keys.getData() << " ";
				keys.Next();
			}
			break;
		case 6:
			cout << "\n Вывод значений на экран\n";
			List values = card.get_values();
			while (!values.isEmpty())
			{
				cout << values.getData() << " ";
				values.Next();
			}
			break;
		case 7:
			cout << "\n Вывод дерева на экран\n";
			card.print();
			break;
		case 8:
			answer = 1;
			break;
		default:
			cout << "\nОшибка! Введите правильный вариант.";
			break;
		}
		cout << "\nВведите следующую операцию:  ";
	} while (answer != 1);

	return 0;
}
