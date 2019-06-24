// inTheString.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Два задания:
//1) Дана строка. Нужно удалить все повторы (дублирующиеся буквы).
//2) Дана строка big. Найди индекс, с которого начинается подстрока sub.

#include "pch.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::getline;

//1) Дана строка. Нужно удалить все повторы (дублирующиеся буквы).
string delRep(string str) {
	auto ii = str.cbegin();
	for (int i = 0; str[i + 1]; i++) {
		if (str[i] == str[i + 1]) {
			str.erase(ii + i);
			i--;
		}
	}
	return str;
}

//2) Дана строка big. Найди индекс, с которого начинается подстрока sub.
int findSubStr(const string big, const string sub) {
	if (sub.size() > big.size()) {
		cout << "This string is not a substring. (Size of the SUB > Size of the BIG)\n";
		return -1;
	}
	for (int i = 0; i<=(big.size()-sub.size()); i++) {
		int flag = 0;
		for (int j = 0; (big[i + j] == sub[j]) && (i + j < big.size()); j++) {
			flag++;
		}
		if (flag == sub.size()) return i;
	}
	cout << "This string is not a substring.\n";
	return -1;
}


int main()
{
	string one;
	string big;
	string sub;
	cout << "Task 1 :\n\n";

	cout << "Enter the string : ";
	cin >> one;
	one=delRep(one);
	cout << "The modified string : " << one;


	cout << "\n\nTask 2 :\n\n";

	cout << "Enter the BIG string : ";
	cin >> big;
	cout << "Size = " << big.size() << endl;
	cout << "Enter the SUB string : ";
	cin >> sub;
	cout << "Size = " << sub.size() << endl;
	cout << "Index SUB string in BIG string = " << findSubStr(big, sub) << endl;
}

