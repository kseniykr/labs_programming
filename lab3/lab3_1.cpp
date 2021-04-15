#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node* top;

void push(string name, double weight, string color, int cost, bool av);
void display();
void pop();
bool pop_all();
void FileCreation();
void fileInsert();
//void finding(string name, double weight, string color, int cost, bool av);
void finding(string index);


int main()
{
	setlocale(LC_ALL, "rus");

	bool exit = 0;

	do {
		cout << "Меню:\n";
		cout << "\n1. Просмотр корзины\n";
		cout << "\n2. Добавить товар в корзину\n";
		cout << "\n3. Удалить товар\n";
		cout << "\n4. Очистить корзину\n";
		cout << "\n5. Считать корзину из файла\n";
		cout << "\n6. Создание файла корзины\n";
		cout << "\n0. Выход\n";

		int ch;

		cout << "\nВаш выбор: ";
		cin >> ch;

		switch (ch) {
		case 1: {
			cout << "\n---Корзина--- \n";
			display();
			break;
		}
		case 2: {
			cout << "\nВведите данные товара:\n";

			string name, color;
			double weight;
			int cost;
			bool av;

			cout << "Вводите данные английскими буквами и цифрами для числовых данных :)\n";

			cout << "\n Наименование: ";
			cin >> name;

			cout << "Вес: ";
			cin >> weight;
			while (weight < 0) {
				cout << "Упс, вы ввели отрицательное число. Попробуйте снова.";
				cin >> weight;
				
			};

			cout << "Цвет: ";
			cin >> color;

			cout << "Стоимость (целое число): ";
			cin >> cost;
			while (cost < 0) {
				cout << "Упс, вы ввели отрицательное число. Попробуйте снова.";
				cin >> cost;
			};

			cout << "Наличие товара (где 1 - есть на складе, 0 - товар отсутствует): ";
			cin >> av;


			push(name, weight, color, cost, av);
			break;
		}

		case 3: {
			cout << "\nЧто ищем? \n";
			string index;

			cin >> index;

			finding(index);




			break;

		}
		case 4: {
			pop_all();
			break;
		}
		case 5: {
			fileInsert();
			break;
		}
		case 6: {
			FileCreation();
			break;
		}
		case 0: {
			exit = 1;
			break;
		}
		default: {
			cout << "\nУпс... Такого пункта нет, попробуйте снова!\n";
			break;
		}

		}
		
	} while (exit != 1);

	pop_all();

	return 0;
}

// Узел односвязнного списка
struct Node {
	string name;
	double weight;
	string color;
	int cost;
	bool availability;

	// указатель на следующий элемент
	struct Node* next;
};

void push(string name, double weight, string color, int cost, bool av)

{
	// создаем новый узел temp и выделяем память
	struct Node* temp;

	temp = new Node();

	// инициализируем данные в поле временных данных
	temp->name = name;
	temp->weight = weight;
	temp->color = color;
	temp->cost = cost;
	temp->availability = av;

	// помещаем в next указатель на верхний элемент
	temp->next = top;

	// делаем temp новым верхним элементом (вершина стека)
	top = temp;
	cout << "New element " << temp->name << " is added" << endl;
}

void pop()
{
	struct Node* temp;

	// проверка на пустой стек
	if (top == NULL) {
		cout << "\nКорзина пуста" << endl;

		exit(1);
	}
	else {
		// верхнее значение помещаем в temp
		temp = top;

		// в вершину стека кладем следующий узел сверху
		top = top->next;

		// разрушаем связь для удаляемого узла
		temp->next = NULL;

		cout << "Element " << temp->name << " is deleted" << endl;

		// освобождаем память верхнего узла
		free(temp);
	}
}


void display()

{
	struct Node* temp;

	// проверка на пустой стек
	if (!top) {
		cout << "\nТут пусто..." << endl;
		
	}

	else {
		temp = top;
		cout << "Current stack: \n";
		while (temp != NULL) {
			// печать данных узла
			cout << "Название: " << temp->name << endl;
			cout << "Вес: " << temp->weight << "кг. ";
			cout << "Цвет: " << temp->color << endl;
			cout << "Стоимость: " << temp->cost << " руб. ";
			cout << "Наличие: " << (temp->availability == true ? "Есть" : "Нет") << endl << endl;

			// переходим к следующему узлу стека
			temp = temp->next;
		}
		cout << endl;
	}
}

bool pop_all() {

	while (top != NULL) {
		pop();
	}

	cout << "\nКорзина пуста\n";

	top = NULL;
	
	return 1;
};

void fileInsert() {

	ifstream fin("StackFile.txt");

	string name;
	double weight;
	string color;
	int cost;
	bool availability;

	while (fin >> name >> weight >> color >> cost >> availability) {
		push(name, weight, color, cost, availability);
	}

	fin.close();
}

void FileCreation() {

	bool exit = 0;

	ofstream fout("StackFile.txt", ios::ate);

	do {
		unsigned short int ch;
		cout << "\n1. Внести новый элемент\n";
		cout << "\n0. Выход\n";
		cin >> ch;

		if (ch == 0) exit = 1;
		if (ch == 1) {

			string name;
			double weight;
			string color;
			int cost;
			bool availability;

			cout << "\n Наименование: ";
			cin >> name;

			cout << "Вес: ";
			cin >> weight;
			while (weight < 0) {
				cout << "Упс, вы ввели отрицательное число. Попробуйте снова.";
				cin >> weight;
			};

			cout << "Цвет: ";
			cin >> color;

			cout << "Стоимость (целое число): ";
			cin >> cost;
			while (cost < 0) {
				cout << "Упс, вы ввели отрицательное число. Попробуйте снова.";
				cin >> cost;
			};

			cout << "Наличие товара (где 1 - есть на складе, 0 - товар отсутствует): ";
			cin >> availability;

			fout << name << " " << weight << " " << color << " " << cost << " " << availability << endl;

		}


	} while (exit != 1);

	fout.close();

}

void finding(string index) {

	if (top != NULL) {
		int index_int;
		float index_float;

		struct Node* temp;
		struct Node* temp1;
		temp1 = top;
		temp = top;

		index_int = atoi(index.c_str());
		index_float = atof(index.c_str());

		bool once = 0, check = 0;

		while (temp1 != NULL && temp != NULL) {


			if (index == temp1->name || index_float == temp1->weight || index_int == temp1->cost) {

				if (once == 0) {
					cout << "\nНайдены товары:\n";
					once = 1;
				}

				cout << "Название: " << temp1->name << endl;
				cout << "Вес: " << temp1->weight << "кг. ";
				cout << "Цвет: " << temp1->color << endl;
				cout << "Стоимость: " << temp1->cost << " руб. ";
				cout << "Наличие: " << (temp1->availability == true ? "Есть" : "Нет") << endl << endl;

				cout << endl;

				if (temp1 != top) {
					temp->next = temp1->next;

					free(temp1);
					temp1 = temp->next;

				}
				else {
					temp1 = top->next;
					temp = top->next;
					pop();
				}

				cout << "\nТовар удален из корзины\n";

			}
			else {
				if (temp1 != NULL && temp != NULL) {
					if (check == 1) {
						temp = temp->next;
					}
					temp1 = temp1->next;
					check = 1;
				}

			}

		}

		if (once == 0) {
			cout << "\nТаких товаров не найдено\n";
		}
		else {
			cout << "\nТовары удалены\n";
		}

	}
	else {

		cout << "\nКорзина пуста\n";

	}

}