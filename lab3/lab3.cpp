#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Node* top;

void push();
void display();
void pop();



int main()
{
	setlocale(LC_ALL, "rus");

	bool exit = 0;

	do {
		cout << "\nМеню:\n";
		cout << "\n1. Просмотр корзины\n";
		cout << "\n2. Добавить товар в корзину\n";
		cout << "\n3. Удалить товар\n";
		cout << "\n4. Очистить корзину\n";
		cout << "\n0. Выход\n";


		switch (ch) {
		case 1: {
			cout << "\n---Корзина--- \n";
			display();
		}
		case 2: {

		}

		case 3: {

		}
		case 4: {

		}
		case 5: {

		}
		case 6: {

		}
		case 0: {

		}
		default: {
			cout << "\nУпс... Такого пункта нет, попробуйте снова!\n";
		}

		}
	}
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
		cout << "\nStack is empty" << endl;

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
	if (top == NULL) {
		cout << "\nStack is empty" << endl;

		exit(1);
	}
	else {
		temp = top;
		cout << "Current stack: ";
		while (temp != NULL) {
			// печать данных узла
			cout << temp->name << endl;
			cout << "Вес: " << temp->weight << "кг. ";
			cout << "Цвет: " << temp->color << endl;
			cout << "Стоимость: " << temp->cost << "рублей. ";
			cout << "Наличие: " << (temp->availability == true ? "Есть" : "Нет") << endl;

			// переходим к следующему узлу стека
			temp = temp->next;
		}
		cout << endl;
	}
}



