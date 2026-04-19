#include <iostream>
#include "polynomial.h"
#include "tree.h"
#include "table.h"
#include "ordered_table.h"
#include "hash_table.h"
Table table;
OrderedTable ordered_table;
AvlTree tree;
HashTable hash_table;
#define gen
using namespace std;

polynomial get_poly(char* name) {
	polynomial* p = table.find(name);
	cout << "Количество операций у неупорядоченной таблицы: " << table.op_count << "\n";
	polynomial* p_ordered = ordered_table.find(name);
	cout << "Количество операций у упорядоченной таблицы: " << ordered_table.op_count << "\n";
	polynomial* p_tree = tree.find(name);
	cout << "Количество операций у АВЛ-дерева: " << tree.op_count << "\n";
	polynomial* p_hash = hash_table.find(name);
	cout << "Количество операций у хеш-таблицы: " << hash_table.op_count << "\n";
	if ((*p) != (*p_ordered) || (*p) != (*p_tree) || (*p) != (*p_hash))throw "polynomials are not equal";
	return *p;
}

polynomial random_poly() {
	int n = rand() % 20;
	polynomial p;
	for (int i = 0; i < n; i++) {
		p += monomial(rand() % 1000, rand() % 1000);
	}
	return p;
}
#ifndef gen
int main() {
	setlocale(LC_ALL, "Russian");
	polynomial p;
	polynomial q;
	char name[80];
	int op = 1;
	int n;
	int* powers;
	double* coefs;
	while (op != 0) {
		cout << "Полином:\n" << p << "Выберите операцию:\n0 - Выход\n1 - Записать полином в память\n2 - Прибавить введённый полином\n3 - Прибавить полином из памяти\n4 - Вычесть введённый полином\n5 - Вычесть полином из памяти\n6 - Умножить на константу\n7 - Умножить на введённый полином\n8 - Умножить на полином из памяти\n9 - Обнулить полином\n";
		cin >> op;
		switch (op) {
		case 0:
			return 0;
		case 1:
			cout << "Как назвать полином? Не больше 80 символов.\n";
			cin >> name;
			table.add(name,p);
			cout << "Количество операций у неупорядоченной таблицы: " << table.op_count << "\n";
			ordered_table.add(name, p);
			cout << "Количество операций у упорядоченной таблицы: " << ordered_table.op_count << "\n";
			tree.add(name, p);
			cout << "Количество операций у АВЛ-дерева: " << tree.op_count << "\n";
			hash_table.add(name, p);
			cout << "Количество операций у хеш-таблицы: " << hash_table.op_count << "\n";
			break;
		case 2:
			cout << "Введите количество мономов:\n";
			cin >> n;
			for (int i = 0; i < n; i++) {
				cout << "Введите коэффициент монома:\n";
				double c;
				cin >> c;
				cout << "Введите степени в мономе перед x, y и z через пробел:\n";
				int x, y, z;
				cin >> x >> y >> z;
				p += monomial(x * 100 + y * 10 + z, c);
			}
			break;
		case 3:
			cout << "Какой полином из памяти вы хотите прибавить?\n";
			cin >> name;
			q = get_poly(name);
			p += q;
			break;
		case 4:
			cout << "Введите количество мономов:\n";
			cin >> n;
			for (int i = 0; i < n; i++) {
				cout << "Введите коэффициент монома:\n";
				double c;
				cin >> c;
				cout << "Введите степени в мономе перед x, y и z через пробел:\n";
				int x, y, z;
				cin >> x >> y >> z;
				p += monomial(x * 100 + y * 10 + z, -c);
			}
			break;
		case 5:
			cout << "Какой полином из памяти вы хотите вычесть?\n";
			cin >> name;
			q = get_poly(name);
			p -= q;
			break;
		case 6:
			cout << "Введите число:\n";
			double c;
			cin >> c;
			p *= c;
			break;
		case 7:
			cout << "Введите количество мономов:\n";
			cin >> n;
			powers = new int[n];
			coefs = new double[n];
			for (int i = 0; i < n; i++) {
				cout << "Введите коэффициент монома:\n";
				cin >> coefs[i];
				cout << "Введите степени в мономе перед x, y и z через пробел:\n";
				int x, y, z;
				cin >> x >> y >> z;
				powers[i] = x * 100 + y * 10 + z;
			}
			q = *(new polynomial(n, powers, coefs));
			p *= q;
			break;
		case 8:
			cout << "На какой полином из памяти вы хотите умножить?\n";
			cin >> name;
			q = get_poly(name);
			p *= q;
			break;
		case 9:
			p.~polynomial();
			break;
		default:
			cout << "Неизвестный ввод.\n";
		}
	}
	return 0;
}
#endif

#ifdef gen
void main() {
	setlocale(LC_ALL, "Russian");
	srand(time(0));
	int n;
	int op;
	cout << "Сколько действий с полиномами нужно сделать?\n";
	cin >> n;
	polynomial p;
	auto names = new char[n][80];
	int n_names = 0;
	char name[80];
	int table_op = 0;
	int ordered_op = 0;
	int tree_op = 0;
	int hash_op = 0;
	int num = 0;
	for (int i = 0; i < n; i++) {
		op = rand() % 3;
		switch (op) {
		case 0:
			sprintf(name, "poly_%d", n_names);
			p = random_poly();
			table.add(name, p);
			ordered_table.add(name, p);
			tree.add(name, p);
			hash_table.add(name, p);
			n_names++;
			break;
		case 1:
			if (n_names == 0)break;
			num = rand() % n_names;
			strncpy(name, names[num],80);
			table.find(name);
			ordered_table.find(name);
			tree.find(name);
			hash_table.find(name);
			break;
		case 2:
			if (n_names == 0)break;
			num = rand() % n_names;
			strncpy(name, names[num],80);
			table.remove(name);
			ordered_table.remove(name);
			tree.remove(name);
			hash_table.remove(name);
			break;
		}
		table_op += table.op_count;
		ordered_op += ordered_table.op_count;
		tree_op += tree.op_count;
		hash_op += hash_table.op_count;
	}
	cout << "Количество операций у неупорядоченной таблицы: " << table_op << "\n";
	cout << "Количество операций у упорядоченной таблицы: " << ordered_op << "\n";
	cout << "Количество операций у АВЛ-дерева: " << tree_op << "\n";
	cout << "Количество операций у хеш-таблицы: " << hash_op << "\n";
	cout << hash_table.conf << endl;

}
#endif