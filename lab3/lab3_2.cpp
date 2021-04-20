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
		cout << "\n����:\n";
		cout << "1. ����������� ������\n";
		cout << "2. ������� ������ �� �����\n";
		cout << "3. ������� ������\n";
		cout << "4. �������� ����� �������\n";
		cout << "5. ����������� �����\n";
		cout << "6. �����\n";
		cout << "0. �����\n";

		cin >> ch;

		switch (ch) {
		case 1: {
			struct data data;
			cout << "\n������� �������� ������ ������: "; cin >> data.groupname;
			cout << "�������� ������: "; cin >> data.name;
			cout << "���������� ���������: "; cin >> data.startprice;
			cout << "���������� ������: "; cin >> data.quantity;
			cout << "���� �������: "; cin >> data.sellprice;

			while (data.sellprice < data.startprice) {
				cout << "��������� ������� �� ����� ���� ������ ����������! ���������� �����.\n"; cin >> data.sellprice;
			}

			push_end(data);
			break;
		}
		case 2: {
			cout << "���������� �� �����..." << endl;
			cout << "���������� ���������\n";
			fileinsert();
			break;
		}

		case 3: {
			struct data data;

			cout << "��� ������?\n";
			cout << "�������� ��������: "; cin >> data.name;
			cout << "���������� ������: "; cin >> data.quantity;


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


	// ���� ������� ����� - ������� ������ �������
	if (first == NULL)
	{
		first = new Node();
		first->next = NULL;
		first->data = data;
	}
	// ����� ��������� ������� � ����� �������
	else
	{
		// ������� ����� ���� temp � �������� ������
		struct Node* temp;

		temp = first;
		// ���� � ����� �������
		while (temp->next != NULL)
		{
			temp = temp->next;
		}

		// �������� ������
		temp->next = new Node;


		// �������������� ������ � ���� ������
		temp->next->data = data;

		// �������� � next ������� ���������
		temp->next->next = NULL; //

	}

	cout << "New element " << data.name << " is added" << endl;
}

// �������� ������� ��������
void pop()
{
	// �������� �� ������ �������
	if (first == NULL) {
		cout << "\nQueue is empty" << endl;

		exit(1);
	}
	else {
		struct Node* temp;

		// �������� ������ ������� � temp
		temp = first->next;

		cout << "Element " << first->data.name << " is deleted" << endl;

		// ����������� ������ ������� ����
		free(first);

		// ������ ������� ���������� ����� ������
		first = temp;
	}
}

// ������ ���� ���������
void display()

{
	// �������� �� ������ �������
	if (first == NULL) {
		cout << "\n�����...\n" << endl;
	}
	else {
		struct Node* temp;

		temp = first;

		cout << "Current queue: \n";
		while (temp != NULL)
		{
			// ������ ������ ����
			cout << "������ ������: " << temp->data.groupname << endl;
			cout << "������������: " << temp->data.name << endl;
			cout << "���������� ����: " << temp->data.startprice << " ";
			cout << "����������: " << temp->data.quantity << endl;
			cout << "���� �������: " << temp->data.sellprice << endl << endl;

			// ��������� � ���������� ���� �������
			temp = temp->next;
		}

		cout << endl;
	}
}

bool pop_all() {

	while (first != NULL) {
		pop();
	}

	cout << "\n������� �����\n";

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
		cout << "\n1. ����� �������\n";
		cout << "\n0. �����\n";
		cin >> ch;

		if (ch == 0) exit = 1;
		if (ch == 1) {

			struct data data;

			cout << "�������� ������: "; cin >> data.groupname;
			cout << "������������ ������: "; cin >> data.name;

			do {
				cout << "������� ���������� ��������� ������:"; cin >> data.startprice;
				if (data.startprice <= 0) cout << "\n�� ����� �������� ���������� ���������";
			} while (data.startprice <= 0);
			do {
				cout << "������� ���������� ������:"; cin >> data.quantity;
				if (data.quantity <= 0) cout << "\n�� ����� �������� ���������� ������";
			} while (data.quantity <= 0);
			do {
				cout << "������� ���� ������� ������:"; cin >> data.sellprice;
				if (data.startprice > data.sellprice) cout << "\n�� ����� �������� ���� �������\n";
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
					cout << "\n������������ ������ �� ������\n";
					cout << "\n������� �������? (1 - ��) ";

					short int ch;
					cin >> ch;

					if (ch == 1) {


						total += temp->data.quantity * temp->data.sellprice;
						profit += temp->data.quantity * (temp->data.sellprice - temp->data.startprice);
						sold_quantity += temp->data.quantity;
						temp->data.quantity = 0;
						cout << "\n������� ������" << data.name << " �������\n";
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
			cout << "\n����� " << data.name << " ������ � ���������� " << sold_quantity << endl;
		}
		else {
			cout << "\n������ ������ �� ������ ���\n";
		}

	}
	else {

		cout << "\n������� �����\n";

	}

}

void report() {
	int counting = 0;
	int cost_all = 0;

	if (first == NULL) {
		cout << "\n����� ����\n" << endl;
	}
	else {
		struct Node* temp;

		temp = first;

		while (temp != NULL) {
			counting += temp->data.quantity;
			cost_all += temp->data.quantity * temp->data.startprice;

			// ��������� � ���������� ���� �������
			if (temp != NULL) temp = temp->next;
		}

	}

	cout << endl;

	cout << "���������� ������ �� ������: " << counting;
	cout << "\n����� ��������� ������� �� ������: " << cost_all << endl;

	cout << "���������� �������: " << profit;

}
