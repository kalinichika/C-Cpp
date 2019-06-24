// ConsoleApplication1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// Вводится число [0 : 255]. Вывести количество единиц в его битовом представлении.

#include "pch.h"
#include <iostream>
#include <stdlib.h>
using std::cin;
using std::cout;
using std::endl;

typedef unsigned char byte;

void printBits(const byte b) {
	cout << ((b >> 7) & 1);
	cout << ((b >> 6) & 1);
	cout << ((b >> 5) & 1);
	cout << ((b >> 4) & 1);
	cout << ((b >> 3) & 1);
	cout << ((b >> 2) & 1);
	cout << ((b >> 1) & 1);
	cout << ((b >> 0) & 1) << endl;
}

int getCountBits1_1(const byte b) {
	return ((b >> 0) & 1) + ((b >> 1) & 1) + ((b >> 2) & 1) + ((b >> 3) & 1) + ((b >> 4) & 1) + ((b >> 5) & 1) + ((b >> 6) & 1) + ((b >> 7) & 1);
}

int getCountBits1_2(const byte b) {
	int table[256] = { 0 };
	table[0] = 0; 
	table[1] = 1; 
	table[2] = 1; 
	table[3] = 2; 
	int i = 0;
	int stepen[] = { 1, 2, 4, 8, 16, 32 };
 	for (int j = 4 * stepen[i]; (j < 256)&(j < stepen[i] * 8); j++) {
		table[j] = table[j - 4 * stepen[i]] + 1;
		//cout << table[j] << " ";
		if ((i < 5) && (j == stepen[i] * 8 - 1) && (j<255))	
			i++;
		if (j == 255) 
			return table[b];
	}
	return table[b];
}

int main()
{
	int b;
	cout << "b = ";
	cin >> b;
	cout << "\nCountBits1 for 'b' = " << getCountBits1_1(b) << endl;
	cout << "Bitovoe predstavlenie = ";
	printBits(b);
	cout << "\nCountBits2 for 'b' = " << getCountBits1_2(b) << endl;
	//printTable();
	/* РАБОТАЕТ С ОШИБКОЙ
	byte b;
	cout << "b = ";
	cin >> b;
	cout << "CountBits1 for 'b' = " << getCountBits1_1(b) << endl;
	*/
}


