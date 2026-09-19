// === Курсовой проект : Умный дом        ===
// === Группа ПИ - 51. Тухватуллин Ильдар ===

#include <iostream>

// Блок подключений: заголовочные файлы 
//#include "ubogov.h"
//#include "tuhvatullin.h"
// Конец блока подключений

using namespace std;

// ===== Главная функция: меню =====
int main() {
	system("chcp 1251");
	setlocale(LC_ALL, "Rus");

	int choice;

	do {
		cout << "\n=== Курсовой проект: Умный дом ===\n";
		// === БЛОК МЕНЮ ===
		cout << "1. Начать симуляцию\n";
		cout << "2. Добавить устройство \n";
		cout << "3. Изменить параментры симуляции\n";
		// === КОНЕЦ БЛОКА МЕНЮ ===
		cout << "0. Выход\n";
		cout << "Выберите пункт меню: ";
		cin >> choice;
		switch (choice) {
		case 0:
			cout << "Работа завершена.\n";
			break;
		default:
			cout << "Такого пункта нет.\n";
		}
	} while (choice != 0);
	return 0;
}