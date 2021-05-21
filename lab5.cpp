#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int col_el = 0;

struct Data {
	string name;
	int year;
	float cost;
	bool use;
};

struct list {
	struct Data data;

	struct list* next;
	struct list* prev;
};

struct list* first;
struct list* C;
struct list* last;



void push();
void showC();
void sort();
void fileCreate(int);
bool remove();
void clear();
void remove_forward();
void remove_next();
void remove_back();
void readFile();
bool push_next(struct Data);
bool push_back(struct Data);
bool push_forward(struct Data);
void print();
bool move_next();
bool move_prev();
int getN(int, int);


int main()
{
	setlocale(LC_ALL, "rus");

	bool exit = 0;

	do {

		cout << "\nВведите с клавиатуры выбранный пункт:\n\n";
		cout << "0. Напечатать список\n";
		cout << "1. Добавить элемент\n";
		cout << "2. Удалить элемент\n";
		cout << "3. Текущий элемент\n";
		cout << "4. Упорядочить элементы\n";
		cout << "5. Очистить список\n";
		cout << "6. Выгрузить в файл\n";
		cout << "7. Загрузить из файла\n";
		cout << "-1. Выход\n";
		cout << "Введите число-> ";

		int choice;

		cin >> choice;

		switch (choice) {

		case 0: {
			print();
			break;
		}

		case 1: {

			push();

			cout << "\nЭлемент добавлен!\n";
			print();

			break;
		}

		case 2: {
			if (remove() != 1) {
				print();
			}
			break;
		}

		case 3: {
			showC();
			break;
		}

		case 4: {
			sort();
			break;
		}

		case 5: {
			clear();
			break;
		}

		case 6: {
			cout << "\nВведите 1, если хотите перезаписать файл (иначе введите 0): "; int choice; cin >> choice;
			fileCreate(choice);
			break;
		}

		case 7: {
			readFile();
			print();
			break;
		}

		case -1: {
			exit = 1;
			break;
		}

		default: {
			cout << "\nТакого пункта нет, попробуйте снова!\n";
			break;
		}

		}

	} while (exit != 1);

	clear();
}



int getN(int left, int right) {

	float new_n;

	do {

		cin >> new_n;
		if (((int)new_n) - new_n != 0 || new_n < left || new_n > right) cout << "\nВведено неверное число! Повторите aпопытку\n";
	} while (((int)new_n) - new_n != 0 || new_n < left || new_n > right);


	return (int)new_n;
}

bool move_next() {

	if (first != NULL && last != NULL && C == NULL) C = first;

	if (first != NULL && last != NULL && C->next != NULL) {
		C = C->next;
		return 0;
	}
	else {
		return 1;
	}
};

bool move_prev() {

	if (first != NULL && last != NULL && C == NULL) C = first;

	if (first != NULL && last != NULL && C->prev != NULL) {
		C = C->prev;
		return 0;
	}
	else {
		return 1;
	}
};

void print() {

	if (first != NULL && last != NULL) {

		struct list* temp = first;

		while (temp != NULL) {
			cout << "\nНазвание: " << temp->data.name << endl;
			cout << "Стоимость: " << temp->data.cost << endl;
			cout << "Год производства: " << temp->data.year<< endl;
			cout << "Находится в использовании? (1 если да, иначе - не в использовании): " << (temp->data.use == 1 ? "В использовании" : "Не используется") << endl;
			temp = temp->next;
		}

	}
	else {
		cout << "\nСписок пуст!\n";
	}
}

bool push_next(struct Data new_data) {

	if (first != NULL && last != NULL) {
		//Если у нас не создан текущий элемент
		if (C == NULL) {
			C = first;
		}

		//Создаём два указателя, один под новый узел, другой для того чтобы сохранить связь
		list* temp = new list(); //создаём новый узел
		list* temp1 = C->next; //сохраняем связь

		//Записываем данные
		temp->data = new_data;

		if (C == last) last = temp; //В случае, если мы добавляем в конец, то нужно поменять указатель на last

		//восстанавливаем связь с прошлым
		C->next = temp;
		temp->prev = C;

		//Перемещаемся вперёд на добавленый
		move_next();

		//Восстанавливаем связь с прошлым
		C->next = temp1;
		temp->prev = C;

	}
	else {
		struct list* temp = new list();
		temp->data = new_data;
		temp->next = first;
		temp->prev = last;
		first = temp;
		last = temp;
	}
	col_el++;
	return 0;

}

bool push_back(struct Data new_data) {

	if (first != NULL && last != NULL) {

		list* temp = new list(); //создаём новый узел

		//Записываем данные
		temp->data = new_data;

		//делаем связь с последним
		temp->next = NULL;
		last->next = temp;
		temp->prev = last;

		last = temp; //В случае, если мы добавляем в конец, меняем указатель на last
	}
	else {
		struct list* temp = new list();
		temp->data = new_data;
		temp->next = first;
		temp->prev = last;
		first = temp;
		last = temp;
	}
	C = last;
	col_el++;
	return 0;

}

bool push_forward(struct Data new_data) {

	if (first != NULL && last != NULL) {

		list* temp = new list(); //создаём новый узел

		//Записываем данные
		temp->data = new_data;

		//делаем связь с первым
		temp->prev = NULL;
		temp->next = first;
		first->prev = temp;

		first = temp; //делаем эл-т первым
	}
	else {
		struct list* temp = new list();
		temp->data = new_data;
		temp->next = first;
		temp->prev = last;
		first = temp;
		last = temp;
	}
	C = first;
	col_el++;
	return 0;

}

void fileCreate(int choice) {

	if (first != NULL && last != NULL) {

		if (choice == 1) {

			ofstream fout("list.txt", ios::trunc);

			struct list* temp = first;

			while (temp != NULL) {
				fout << temp->data.name << " ";
				fout << temp->data.cost << " ";
				fout << temp->data.year<< " ";
				fout << temp->data.use << endl;
				temp = temp->next;
			}

			fout.close();
		}
		else {
			ofstream fout("list.txt", ios::app);

			struct list* temp = first;

			while (temp != NULL) {
				fout << temp->data.name << " ";
				fout << temp->data.cost << " ";
				fout << temp->data.year << " ";
				fout << temp->data.use << endl;
				temp = temp->next;
			}

			fout.close();
		}
	}
	else {
		cout << "\nСписок пуст!\n";
	}



}

void readFile() {

	ifstream fin("list.txt");

	if (!fin) {
		cout << "\nОШИБКА! Файла не существует!\n";
		return;
	}

	struct Data data;

	while (fin >> data.name >> data.cost >> data.year >> data.use) {
		push_back(data);
	}
	C = first;
	fin.close();
	cout << "\nФайл считан\n";
}

bool remove() {
	if (first != NULL) {
		cout << "\tЧто удалять?\n";
		cout << "\t1. В конце\n";
		cout << "\t2. В начале\n";
		cout << "\t3. На позиции k\n";
		cout << "\tВведите что удалять ->";

		int choice; cin >> choice;

		if (choice == 1) {
			remove_back();
			cout << "\nЭлемент удалён!\n";
		}
		else if (choice == 2) {
			remove_forward();
			cout << "\nЭлемент удалён!\n";
		}
		else if (choice == 3) {
			cout << "\t\tВведите k от 1 до " << col_el << " =";
			int k;
			k = getN(1, col_el);

			if (k == 1) {
				remove_forward();
				return 0;
			}
			if (k == col_el) {
				remove_back();
				return 0;
			}

			if (first != NULL) {
				struct list* temp = C;
				if (C != NULL) temp = C;
				C = first;

				for (int i = 1; i < k - 1; i++) {
					C = C->next;
				}

				remove_next();

				cout << "\nЭлемент удалён!\n";

				C = first;

			}




		}
		else {
			cout << "\nОшибка! Ничего не удалено!\n";
			return 1;
		}
	}
	else {
		cout << "\nОшибка! Список пуст!\n";
		return 1;
	}

	return 0;

}

void clear() {
	if (first != NULL && last != NULL) {
		while (first != NULL) {
			remove_forward();
		}
		cout << "\nСписок очищен\n";
	}
	else {
		cout << "\nСписок пуст!\n";
	}
}

void showC() {


	if (first != NULL) {
		if (C == NULL) C = first;

		cout << "\nИмя: " << C->data.name << endl;
		cout << "Стоимость: " << C->data.cost << endl;
		cout << "Год производства: " << C->data.year << endl;
		cout << "В использовании? (1 - если да) " << (C->data.use == 1 ? "В использовании" : "Не используется") << endl;
	}
	else {
		cout << "\nСписок пуст!\n";
	}


}

void remove_next() {

	list* temp = C->next;

	C->next = temp->next;
	temp->next->prev = C;

	temp->next = NULL;
	temp->prev = NULL;

	free(temp);
	col_el--;

}

void remove_forward() {


	list* temp = first;

	if (temp == last) {
		temp->next = NULL;
		temp->prev = NULL;
		free(temp);
		first = NULL;
		last = NULL;
		return;
	}

	first = first->next;
	first->prev = NULL;
	temp->next = NULL;
	temp->prev = NULL;

	free(temp);
	col_el--;
}

void remove_back() {

	list* temp = last;

	if (temp == first) {
		temp->next = NULL;
		temp->prev = NULL;
		free(temp);
		first = NULL;
		last = NULL;
		return;
	}

	last = last->prev;
	last->next = NULL;
	temp->prev = NULL;
	temp->next = NULL;

	free(temp);
	col_el--;
}

void push() {
	struct Data data;
	cout << "\n\tВведите новые данные:\n";
	cout << "\tИмя: "; cin >> data.name;
	cout << "\tСтоимость: "; cin >> data.cost;
	cout << "\tГод производства: "; cin >> data.year;
	cout << "\tВ использовании? (1 если да): "; cin >> data.use;

	cout << "\n\tКуда добавить?\n";
	cout << "\t1. В конец\n";
	cout << "\t2. В начало\n";
	cout << "\t3. На позицию k\n";
	cout << "\tВведите куда добавить ->";

	int choice; cin >> choice;

	if (choice == 1) {
		push_back(data);
	}
	else if (choice == 2) {
		push_forward(data);
	}
	else if (choice == 3) {
		cout << "\t\tВведите k от 1 до " << col_el + 1 << " =";
		int k;
		k = getN(1, col_el + 1);

		if (k == 1) {
			push_forward(data);
			return;
		}

		if (first != NULL) {
			C = first;

			for (int i = 1; i < k - 1; i++) {
				C = C->next;
			}

			push_next(data);

		}
		else {
			push_back(data);
		}



	}
	else {
		cout << "\nОшибка, добавляю в конец!\n";
		push_back(data);
	}

}

void sort() {

	if (first != NULL) {
		cout << "\nВыберите поле, по какому сортировать:\n";
		cout << "\n1. Имя\n";
		cout << "\n2. Год производства\n";
		cout << "\nВведите цифру -> ";
		int choice; cin >> choice;

		switch (choice) {

		case 1: {

			C = first;
			list* temp = first;

			for (int i = 0; i < col_el; i++) {
				for (int j = 0; j < col_el; j++) {
					if (C == temp) continue;
					if (strcmp(temp->data.name.c_str(), C->data.name.c_str()) > 0) {
						swap(temp->data, C->data);
					}
					if (temp->next != NULL) temp = temp->next;

				}
				temp = first;
				C = C->next;

			}


			C = first;
			break;
		}

		case 2: {
			C = first;
			list* temp = first;

			for (int i = 0; i < col_el; i++) {
				for (int j = 0; j < col_el; j++) {
					if (C == temp) continue;
					if (temp->data.year > C->data.year) {
						swap(temp->data, C->data);
					}
					if (temp->next != NULL) temp = temp->next;

				}
				temp = first;
				C = C->next;

			}


			C = first;


			break;
		}

		default: {
			cout << "\nОшибка, выбран неправильный пункт!\n";
			break;
		}

		}



	}
	else {
		cout << "\nСписок пустой!\n";
	}


}



