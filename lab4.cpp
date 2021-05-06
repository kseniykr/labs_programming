#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdlib.h>


using namespace std;

struct Node {
	char* seria;
	struct Node* next;

};

//указатель на первый узел
struct Node* first;

struct Data {

	string name;
	int cost;
	bool av;
	float weight;

};

//Возвращает сериализованные данные
char* returnSeria(struct Data);

//десериализация данных
Data unSeria(char*);
bool pop();
bool pop_all();
bool push_back(struct Data);
void print();
void fileInsert();
void finding(string index);
void queueFileCreation();
void clearFile();



int main()
{
	setlocale(LC_ALL, "rus");

	bool exit = 0;

	do {
		cout << "\nМеню:\n";
		cout << "1. Посмотреть корзину\n";
		cout << "2. Добавить новый товар в корзину\n";
		cout << "3. Вытащить товар из корзины\n";
		cout << "4. Очистить корзину\n";
		cout << "5. Считать корзину из файла\n";
		cout << "6. Создание файла корзины\n";
		cout << "7. Очистка файла\n";
		cout << "0. Выход\n";
	

		short int ch;

		cin >> ch;

		switch (ch)
		{

		case 1: {
			print();
			break;
		}

		case 2: {
			struct Data data;

			cout << "\nВведите название: "; cin >> data.name;
			cout << "\nВведите цену="; cin >> data.cost;
			cout << "\nНаличие (где 1 - есть на складе, 0 - товар отсутствует): "; cin >> data.av;
			cout << "\nВведите вес: "; cin >> data.weight;

			//Вводим данные и пихаем их
			push_back(data);
			break;
		}

		case 3: {

			cout << "\nВведите что искать:\n";
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
			queueFileCreation();
			break;
		}

		case 7: {
			clearFile();
			break;
			cout << "\nФайл очищен!\n";
		}

		case 0: {
			exit = 1;
			break;
		}

		default:
			cout << "\nПункт меню выбран неправильно! Попробуйте снова.\n";
			break;
		}



	} while (exit != 1);


	//Очистка памяти
	pop_all();
	//Очистка файла (предотвращение ошибок)
	clearFile();

	return 0;
}

bool push_back(struct Data data) {

	struct Node* temp;

	temp = first;

	bool exist = 0;

	//Полученные данные сериализуем
	char* new_seria = returnSeria(data);

	if (first != NULL) {

		temp = first;

		//Идём в конец
		while (temp->next != NULL) {
			temp = temp->next;
		}

		//Создаем "последний" узел заново и выделяем память
		struct Node* last;
		last = new Node();

		//Восстанавливаем связь
		temp->next = last;

		//Присваиваем последнему узлу данные
		temp->next->seria = new_seria;


		cout << "\nТовар записан!\n";


	}
	else {
		// В случае если мы создаём первый эл-т
		struct Node* temp;
		//Выделение памяти
		temp = new Node();

		temp->seria = new_seria;

		temp->next = first;
		first = temp;
		cout << "\nТовар записан!\n";

	}
	return 1;
};

char* returnSeria(struct Data data) {

	//Получаем размер нашей строки
	size_t s = data.name.size();

	//Задание байтных размеров всей серии по отдельным типам
	int n0 = sizeof(size_t);
	int n1 = s;
	int n2 = sizeof(int);
	int n3 = sizeof(bool);
	int n4 = sizeof(float);

	//Общий размер серии
	int n = n0 + n1 + n2 + n3 + n4;

	//Динамическое выделение новой памяти под нашу серию(удаляется потом в pop)
	char* new_seria = new char[n];

	//Преобразование наших данных в битовый вид
	char* d0 = reinterpret_cast<char*>(&s);
	char* d1 = const_cast<char*>(data.name.c_str());
	char* d2 = reinterpret_cast<char*>(&data.cost);
	char* d3 = reinterpret_cast<char*>(&data.av);
	char* d4 = reinterpret_cast<char*>(&data.weight);

	//Запись серии целиком
	for (int i = 0; i < n0; i++) new_seria[i] = d0[i];
	for (int i = 0; i < n1; i++) new_seria[i + n0] = d1[i];
	for (int i = 0; i < n2; i++) new_seria[i + n0 + n1] = d2[i];
	for (int i = 0; i < n3; i++) new_seria[i + n0 + n1 + n2] = d3[i];
	for (int i = 0; i < n4; i++) new_seria[i + n0 + n1 + n2 + n3] = d4[i];

	//Возврат серии
	return new_seria;
}

Data unSeria(char* seria) {

	//Вычисляем размер полученной серии
	int n0, n1, n2, n3, n4;
	n0 = sizeof(size_t);
	n2 = sizeof(int);
	n3 = sizeof(bool);
	n4 = sizeof(float);

	//Выясняем размер строки
	size_t p = *reinterpret_cast<size_t*>(seria);
	n1 = p;

	struct Data data;
	//Записываем строку
	string temp(seria + n0, p);

	//И переписываем в нашу структуру
	data.name = temp;

	//Получаем данные из серии
	data.cost = *reinterpret_cast<int*>(seria + n0 + n1);//<-Это смещение откуда читать данные
	data.av = *reinterpret_cast<bool*>(seria + n0 + n1 + n2);
	data.weight = *reinterpret_cast<float*>(seria + n0 + n1 + n2 + n3);

	//Возвращаем данные
	return data;

}

void print() {

	struct Node* temp;

	if (first == NULL) {
		cout << "\nКорзина пуста\n" << endl;
	}
	else {

		temp = first;

		cout << "\nТекущая корзина: \n";
		while (temp != NULL) {
			// печать данных узла
			Data data;
			data = unSeria(temp->seria);

			cout << "\nНазвание: " << data.name;
			cout << "\nЦена: " << data.cost << " рублей";
			cout << "\nНаличие: " << (data.av == true ? "Есть" : "Нет");
			cout << "\nВес: " << data.weight << " кг" << endl;

			// переходим к следующему узлу стека
			temp = temp->next;
		}

	}

};

bool pop() {

	struct Node* temp;

	if (first == NULL) {
		return 0;
	}
	else {
		// верхнее значение помещаем в temp
		temp = first;

		first = first->next;

		temp->next = NULL;

		//Удаляем поле данных
		delete[] temp->seria;

		// освобождаем память верхнего узла
		free(temp);
	}


	return 1;
};

bool pop_all() {
	if (first != NULL) {
		while (pop() != 0);
		cout << "\nКорзина очищена!\n";
	}
	else {
		cout << "\nКорзина пуста!\n";
	}
	return 1;
};

void fileInsert() {
	ifstream fin("Queue.dat", ios::binary);

	//Создаём место под серию, но память не выделяем
	char* new_seria;
	int n;
	while (!fin.eof()) {
		//Тут мы cчитаем сколько в целом символов в нашей серии
		if (fin.read((char*)&n, sizeof(int))) {
			//Выделяем память под серию
			char* seria = new char[n];

			//Считываем серию
			fin.read(seria, n);

			//Создаём структуру
			Data data;

			data = unSeria(seria);

			//Записываем
			push_back(data);

			//Освобождение памяти
			delete[]seria;
		}
	}

	//Закрываем файл
	fin.close();
}

void queueFileCreation() {

	bool exit = 0;

	ofstream fout("Queue.dat", ios::app | ios::binary);

	do {
		unsigned short int ch;
		cout << "\n1. Внести новый элемент\n";
		cout << "0. Выход\n";
		cin >> ch;

		if (ch == 0) exit = 1;
		if (ch == 1) {

			Data data;

			cout << "\nВведите название: "; cin >> data.name;
			cout << "\nВведите стоимость: "; cin >> data.cost;
			cout << "\nНаличие (1 - есть, 0 - нет): "; cin >> data.av;
			cout << "\nВведите вес: "; cin >> data.weight;

			char* seria = returnSeria(data);

			int n0, n1, n2, n3, n4, n;
			n0 = sizeof(size_t);
			n2 = sizeof(int);
			n3 = sizeof(bool);
			n4 = sizeof(float);

			size_t p = *reinterpret_cast<size_t*>(seria);
			n1 = p;

			n = n0 + n1 + n2 + n3 + n4;

			fout.write((char*)&n, sizeof(int));
			fout.write(seria, n);
			delete[] seria;

		}


	} while (exit != 1);

	fout.close();

}

void clearFile() {

	ofstream file("Queue.dat", ios::trunc);

	file.close();

}

void finding(string index) {

	if (first != NULL) {
		int index_int;
		float index_float;

		struct Node* temp;
		struct Node* temp1;
		temp1 = first;
		temp = first;

		index_int = atoi(index.c_str());
		index_float = atof(index.c_str());

		bool once = 0, check = 0;

		struct Data data;

		while (temp1 != NULL && temp != NULL) {

			data = unSeria(temp1->seria);
			if (index == data.name || index_float == data.weight || index_int == data.cost) {

				if (once == 0) {
					cout << "\nНайденые товары:\n";
					once = 1;
				}

				cout << "\nНазвание: " << data.name;
				cout << "\nСтоимость: " << data.cost << " рублей";
				cout << "\nВес: " << data.weight << " кг";
				cout << "\nНаличие: " << (data.av == true ? "Есть" : "Нет");
				cout << endl;

				if (temp1 != first) {
					temp->next = temp1->next;

					free(temp1);
					temp1 = temp->next;

				}
				else {
					temp1 = first->next;
					temp = first->next;
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
			cout << "\nТовары, подходящие по критерию поиска удалены\n";
		}

	}
	else {

		cout << "\nКорзина пуста\n";

	}




}
