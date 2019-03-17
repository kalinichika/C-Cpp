// remoteTheNumber.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы. 
// Дан целочисленный вектор v. Необходимо удалить из вектора все элементы a. Число a вводится с клавиатуры.

#include "pch.h"
#include <iostream> 
#include <vector> 
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::getchar;


vector <int>& delNum(vector <int>& v, int a) {
	if (v.empty()) return v;
	int f = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == a) {
			v.erase(v.begin() + i);
			i--;
			f++;
		}
	}
	if (f == 0) cout << "This element is not in the vector.\n";
	return v;
}

vector <int>& init(vector <int>& v) {
	cout << "Enter the elements of the vector : \n";
	for (int i = 0; i < v.size(); i++) {
		cout << "v[" << i << "] = ";
		cin >> v[i];
	}
	return v;
}

void print(const vector <int>& v) {
	cout << "\nVector : ";
	for (const int i : v) cout << i << " ";
	if (v.size() == 0) cout << " is empty.\n";
	cout << endl;
	return;
}

int main()
{
	int N = 0;
	while ((N == 0) || (N < 0)) {
		cout << "Enter the number of elements of the vector : ";
		cin >> N;
	}
	vector <int> v(N);
	v = init(v);
	print(v);

	cout << "Enter the number to be deleted : ";
	int a;
	cin >> a;

	v = delNum(v, a);
	print(v);
	system("pause");
	return 0;
}
