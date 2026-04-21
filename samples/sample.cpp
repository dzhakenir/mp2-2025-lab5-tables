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
	cout << "Êîëè÷åñòâî îïåðàöèé ó íåóïîðÿäî÷åííîé òàáëèöû: " << table.op_count << "\n";
	polynomial* p_ordered = ordered_table.find(name);
	cout << "Êîëè÷åñòâî îïåðàöèé ó óïîðÿäî÷åííîé òàáëèöû: " << ordered_table.op_count << "\n";
	polynomial* p_tree = tree.find(name);
	cout << "Êîëè÷åñòâî îïåðàöèé ó ÀÂË-äåðåâà: " << tree.op_count << "\n";
	polynomial* p_hash = hash_table.find(name);
	cout << "Êîëè÷åñòâî îïåðàöèé ó õåø-òàáëèöû: " << hash_table.op_count << "\n";
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
		cout << "Ïîëèíîì:\n" << p << "Âûáåðèòå îïåðàöèþ:\n0 - Âûõîä\n1 - Çàïèñàòü ïîëèíîì â ïàìÿòü\n2 - Ïðèáàâèòü ââåä¸ííûé ïîëèíîì\n3 - Ïðèáàâèòü ïîëèíîì èç ïàìÿòè\n4 - Âû÷åñòü ââåä¸ííûé ïîëèíîì\n5 - Âû÷åñòü ïîëèíîì èç ïàìÿòè\n6 - Óìíîæèòü íà êîíñòàíòó\n7 - Óìíîæèòü íà ââåä¸ííûé ïîëèíîì\n8 - Óìíîæèòü íà ïîëèíîì èç ïàìÿòè\n9 - Îáíóëèòü ïîëèíîì\n";
		cin >> op;
		switch (op) {
		case 0:
			return 0;
		case 1:
			cout << "Êàê íàçâàòü ïîëèíîì? Íå áîëüøå 80 ñèìâîëîâ.\n";
			cin >> name;
			table.add(name,p);
			cout << "Êîëè÷åñòâî îïåðàöèé ó íåóïîðÿäî÷åííîé òàáëèöû: " << table.op_count << "\n";
			ordered_table.add(name, p);
			cout << "Êîëè÷åñòâî îïåðàöèé ó óïîðÿäî÷åííîé òàáëèöû: " << ordered_table.op_count << "\n";
			tree.add(name, p);
			cout << "Êîëè÷åñòâî îïåðàöèé ó ÀÂË-äåðåâà: " << tree.op_count << "\n";
			hash_table.add(name, p);
			cout << "Êîëè÷åñòâî îïåðàöèé ó õåø-òàáëèöû: " << hash_table.op_count << "\n";
			break;
		case 2:
			cout << "Ââåäèòå êîëè÷åñòâî ìîíîìîâ:\n";
			cin >> n;
			for (int i = 0; i < n; i++) {
				cout << "Ââåäèòå êîýôôèöèåíò ìîíîìà:\n";
				double c;
				cin >> c;
				cout << "Ââåäèòå ñòåïåíè â ìîíîìå ïåðåä x, y è z ÷åðåç ïðîáåë:\n";
				int x, y, z;
				cin >> x >> y >> z;
				p += monomial(x * 100 + y * 10 + z, c);
			}
			break;
		case 3:
			cout << "Êàêîé ïîëèíîì èç ïàìÿòè âû õîòèòå ïðèáàâèòü?\n";
			cin >> name;
			q = get_poly(name);
			p += q;
			break;
		case 4:
			cout << "Ââåäèòå êîëè÷åñòâî ìîíîìîâ:\n";
			cin >> n;
			for (int i = 0; i < n; i++) {
				cout << "Ââåäèòå êîýôôèöèåíò ìîíîìà:\n";
				double c;
				cin >> c;
				cout << "Ââåäèòå ñòåïåíè â ìîíîìå ïåðåä x, y è z ÷åðåç ïðîáåë:\n";
				int x, y, z;
				cin >> x >> y >> z;
				p += monomial(x * 100 + y * 10 + z, -c);
			}
			break;
		case 5:
			cout << "Êàêîé ïîëèíîì èç ïàìÿòè âû õîòèòå âû÷åñòü?\n";
			cin >> name;
			q = get_poly(name);
			p -= q;
			break;
		case 6:
			cout << "Ââåäèòå ÷èñëî:\n";
			double c;
			cin >> c;
			p *= c;
			break;
		case 7:
			cout << "Ââåäèòå êîëè÷åñòâî ìîíîìîâ:\n";
			cin >> n;
			powers = new int[n];
			coefs = new double[n];
			for (int i = 0; i < n; i++) {
				cout << "Ââåäèòå êîýôôèöèåíò ìîíîìà:\n";
				cin >> coefs[i];
				cout << "Ââåäèòå ñòåïåíè â ìîíîìå ïåðåä x, y è z ÷åðåç ïðîáåë:\n";
				int x, y, z;
				cin >> x >> y >> z;
				powers[i] = x * 100 + y * 10 + z;
			}
			q = *(new polynomial(n, powers, coefs));
			p *= q;
			break;
		case 8:
			cout << "Íà êàêîé ïîëèíîì èç ïàìÿòè âû õîòèòå óìíîæèòü?\n";
			cin >> name;
			q = get_poly(name);
			p *= q;
			break;
		case 9:
			p.~polynomial();
			break;
		default:
			cout << "Íåèçâåñòíûé ââîä.\n";
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
	cout << "Ñêîëüêî äåéñòâèé ñ ïîëèíîìàìè íóæíî ñäåëàòü?\n";
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
		op = rand() % 4;
		if(op==3)op=0;
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
	cout << "Êîëè÷åñòâî îïåðàöèé ó íåóïîðÿäî÷åííîé òàáëèöû: " << table_op << "\n";
	cout << "Êîëè÷åñòâî îïåðàöèé ó óïîðÿäî÷åííîé òàáëèöû: " << ordered_op << "\n";
	cout << "Êîëè÷åñòâî îïåðàöèé ó ÀÂË-äåðåâà: " << tree_op << "\n";
	cout << "Êîëè÷åñòâî îïåðàöèé ó õåø-òàáëèöû: " << hash_op << "\n";
	cout << hash_table.conf << endl;

}
#endif
