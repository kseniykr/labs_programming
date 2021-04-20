#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

void push_end(struct data data);
bool pop_all();
void pop();
void display();
void sell(struct data data);
void queueFileCreation();
void report();
void fileinsert();


struct data {

	string groupname;
	string name;
	int startprice;
	int quantity;
	int sellprice;
};

struct Node {
	struct data data;

	struct Node* next;
};

struct Node* first;
int total = 0, profit = 0;


int main()
{
	setlocale(LC_ALL, "rus");

	bool exit = 0;
	int ch;

	do {
		cout << "\nМеню:\n";
		cout << "1. Поступление товара\n";
		cout << "2. Считать товары из файла\n";
		cout << "3. Продажа товара\n";
		cout << "4. Создание файла очереди\n";
		cout << "5. Просмотреть склад\n";
		cout << "6. Отчёт\n";
		cout << "0. Выход\n";

		cin >> ch;

		switch (ch) {
		case 1: {
			struct data data;
			cout << "\nВведите название группы товара: "; cin >> data.groupname;
			cout << "Название товара: "; cin >> data.name;
			cout << "Закупочная стоимость: "; cin >> data.startprice;
			cout << "Количество товара: "; cin >> data.quantity;
			cout << "Цена продажи: "; cin >> data.sellprice;

			while (data.sellprice < data.startprice) {
				cout << "Стоимость продажи не может быть меньше закупочной! Попробуйте снова.\n"; cin >> data.sellprice;
			}

			push_end(data);
			break;
		}
		case 2: {
			cout << "Считывание из файла..." << endl;
			cout << "Считывание завершено\n";
			fileinsert();
			break;
		}

		case 3: {
			struct data data;

			cout << "Что продаём?\n";
			cout << "Название продукта: "; cin >> data.name;
			cout << "Количество товара: "; cin >> data.quantity;


			sell(data);
			break;

		}

		case 4: {
			queueFileCreation();
			break;
		}

		case 5: {
			display();
			break;
		}

		case 6: {
			report();
			break;
		}

		case 0: {
			exit = 1;
			break;
		}
		}


	} while (exit != 1);

}

void push_end(struct data data)

{


	// если очередь пуста - создаем первый элемент
	if (first == NULL)
	{
		first = new Node();
		first->next = NULL;
		first->data = data;
	}
	// иначе добавляем элемент в конец очереди
	else
	{
		// создаем новый узел temp и выделяем память
		struct Node* temp;

		temp = first;
		// идем в конец очереди
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		// выделяем память
		temp->next = new Node;


		// инициализируем данные в поле данных
		temp->next->data = data;

		// помещаем в next нулевой указатель
		temp->next->next = NULL; //

	}

	cout << "New element " << data.name << " is added" << endl;
}

// удаление первого элемента
void pop()
{
	// проверка на пустую очередь
	if (first == NULL) {
		cout << "\nQueue is empty" << endl;

		exit(1);
	}
	else {
		struct Node* temp;

		// помещаем второй элемент в temp
		temp = first->next;

		cout << "Element " << first->data.name << " is deleted" << endl;

		// освобождаем память первого узла
		free(first);

		// второй элемент становится новым первым
		first = temp;
	}
}

// печать всех элементов
void display()

{
	// проверка на пустую очередь
	if (first == NULL) {
		cout << "\nПусто...\n" << endl;
	}
	else {
		struct Node* temp;

		temp = first;

		cout << "Current queue: \n";
		while (temp != NULL)
		{
			// печать данных узла
			cout << "Группа товара: " << temp->data.groupname << endl;
			cout << "Наименование: " << temp->data.name << endl;
			cout << "Закупочная цена: " << temp->data.startprice << " ";
			cout << "Количество: " << temp->data.quantity << endl;
			cout << "Цена продажи: " << temp->data.sellprice << endl << endl;

			// переходим к следующему узлу очереди
			temp = temp->next;
		}

		cout << endl;
	}
}

bool pop_all() {

	while (first != NULL) {
		pop();
	}

	cout << "\nКорзина пуста\n";

	first = NULL;

	return 1;
};

void fileinsert() {
	ifstream fin("Stack_File.txt");

	struct data data;

	while (fin >> data.groupname >> data.name >> data.startprice >> data.quantity >> data.sellprice) {
		push_end(data);
	}

	fin.close();
}

void queueFileCreation() {

	bool exit = 0;

	ofstream fout("Stack_File.txt", ios::ate);

	do {
		unsigned short int ch;
		cout << "\n1. Новый элемент\n";
		cout << "\n0. Выход\n";
		cin >> ch;

		if (ch == 0) exit = 1;
		if (ch == 1) {

			struct data data;

			cout << "Название группы: "; cin >> data.groupname;
			cout << "Наименование товара: "; cin >> data.name;

			do {
				cout << "Введите закупочную стоимость товара:"; cin >> data.startprice;
				if (data.startprice <= 0) cout << "\nВы ввели неверную закупочную стоимость";
			} while (data.startprice <= 0);
			do {
				cout << "Введите количество товара:"; cin >> data.quantity;
				if (data.quantity <= 0) cout << "\nВы ввели неверное количество товара";
			} while (data.quantity <= 0);
			do {
				cout << "Введите цену продажи товара:"; cin >> data.sellprice;
				if (data.startprice > data.sellprice) cout << "\nВы ввели неверную цену продажи\n";
			} while (data.startprice > data.sellprice);

			fout << data.groupname << " " << data.name << " " << data.startprice << " " << data.quantity << " " << data.sellprice << endl;

		}


	} while (exit != 1);

	fout.close();
}

void sell(struct data data) {

	if (first != NULL) {

		struct Node* temp = first;
		struct Node* temp1 = first;


		bool once_sell = 0, first_execute = 0;
		int sold_quantity = 0;
		do {

			if (temp->data.name == data.name) {
				if (temp->data.quantity >= data.quantity) {
					temp->data.quantity -= data.quantity;
					sold_quantity += data.quantity;
					total += data.quantity * temp->data.sellprice;
					profit += data.quantity * (temp->data.sellprice - temp->data.startprice);
				}
				else {
					cout << "\nНедостаточно товара на складе\n";
					cout << "\nПродать остаток? (1 - да) ";

					short int ch;
					cin >> ch;

					if (ch == 1) {


						total += temp->data.quantity * temp->data.sellprice;
						profit += temp->data.quantity * (temp->data.sellprice - temp->data.startprice);
						sold_quantity += temp->data.quantity;
						temp->data.quantity = 0;
						cout << "\nОстатки товара" << data.name << " проданы\n";
					}

				}

				once_sell = 1;

				if (temp->data.quantity == 0) {
					if (temp == first) {
						temp = temp->next;
						temp1 = temp1->next;
						pop();
					}
					else {

						temp1->next = temp->next;
						free(temp);
						temp = temp1->next;

					}



				}

			}

			if (first_execute == 1 && temp1 != NULL) {
				temp1 = temp1->next;
			}
			first_execute = 1;
			if (temp != NULL)temp = temp->next;




		} while (temp != NULL);


		if (once_sell == 1) {
			cout << "\nТовар " << data.name << " продан в количестве " << sold_quantity << endl;
		}
		else {
			cout << "\nТакого товара на складе нет\n";
		}

	}
	else {

		cout << "\nОчередь пуста\n";

	}

}

void report() {
	int counting = 0;
	int cost_all = 0;

	if (first == NULL) {
		cout << "\nСклад пуст\n" << endl;
	}
	else {
		struct Node* temp;

		temp = first;

		while (temp != NULL) {
			counting += temp->data.quantity;
			cost_all += temp->data.quantity * temp->data.startprice;

			// переходим к следующему узлу очереди
			if (temp != NULL) temp = temp->next;
		}

	}

	cout << endl;

	cout << "Количество товара на складе: " << counting;
	cout << "\nОбщая стоимость товаров на складе: " << cost_all << endl;

	cout << "Полученная прибыль: " << profit;

}
