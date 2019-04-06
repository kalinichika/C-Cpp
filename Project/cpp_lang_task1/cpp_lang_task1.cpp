#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "cpp_lang_task1.h"

using std::cout;
using std::endl;
using std::move;
using std::setw;
using std::ofstream;

using namespace student;

void print_number_table (short col, short row){
    ofstream fout;
    fout.open("Projects/cpp_lang_task1/table.log");
    srand(time(NULL));

    cout << " ";
    fout << " ";
    for(int j = 0; j < col*4-1; j++) {
        cout << "*";
        fout << "*";
    }
    cout << endl;
    fout << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            unsigned int x = rand() % 999 + 0;;
            cout << "|";
            cout << setw(3) << x;
            fout << "|";
            fout << setw(3) << x;
        }
        cout << "|\n";
        fout << "|\n";
        if (i<row-1) {
            cout << "|";
            fout << "|";
        }
        for (int j = 0; (j < col-1)&(i<row-1); j++) {
            cout << "---+";
            fout << "---+";
        }
        if (i<row-1) {
            cout << "---|\n";
            fout << "---|\n";
        }
    }
    cout << " ";
    fout << " ";
    for (int j = 0; j < col*4-1; j++) {
        cout << "*";
        fout << "*";
    }
    cout << "\n";
    fout << "\n";
    fout.close();
}

// S - T - R - I - N - G

string::~string() {
    if (_data) delete(_data);
}

string::string() : _data(nullptr), _size(0){}

string::string(unsigned int count, char ch) {
    if (count == 0) { _data = nullptr; _size = 0; }
    _size = count;
    _data = new char[_size+1];
    for (unsigned int i = 0; i < count-1; i++) {
        _data[i] = ch;
    }

    _data[_size] = '\0';
}

string::string(const char* other, unsigned int count) {
    if ((!other) || (count == 0)) { _data = nullptr; _size = 0;}
    unsigned other_size = 0;
    for (other_size = 0; other[other_size]; other_size++);
    _size = count;
    _data = new char[_size+1];
    for (unsigned int i = 0; (i < _size)&&(other[i]); i++) {
        _data[i] = other[i];
    }
    if(count > other_size){
        for (unsigned int i = count-other_size; (i < _size); i++) {
            _data[i] = '\0';
        }
    }

    _data[_size] = '\0';
}

string::string(const char* other) : _data(nullptr), _size(0){
    if (other) {
        unsigned int _size_other = 0;
        for (int i = 0; other[i]; i++) {
            _size_other++;
        }
        _size = _size_other;

        _data = new char[_size+1];
        for (unsigned int i = 0; other[i]; i++) {
            _data[i] = other[i];
        }
        _data[_size] = '\0';
    }
}

string::string(const string& other) : _data(), _size(other._size) {
    if (other._data) {
        _data = new char[_size+1];
        for (unsigned int i = 0; i<_size; i++) {
            _data[i] = other._data[i];
        }
        _data[_size] = '\0';
    }
}

string::string(string&& other) : _data(other._data), _size(other._size) {
    other._data = nullptr;
    other._size = 0;
    //cout<<"!!!конструктор перемещения!!!\n";
}

string& string::operator = (const string& other) {
    delete(_data);
    _size = other._size;
    if (!_size) {
        _data = 0;
        return *this;
    }
    _data = new char[_size+1];

    for (unsigned int i = 0; i<_size ; i++) {
        _data[i] = other._data[i];
    }
    _data[_size] = '\0';
    return *this;
}

string& string::operator = (string&& other) {
    delete(_data);
    _data = other._data;
    _size = other._size;
    other._data = nullptr;
    other._size = 0;
    //cout<<"!!!присваивание перемещением!!!\n";
    return *this;
}

string& string::operator= (const char* other) {
    delete(_data);
    unsigned int _size_other = 0;
    for (unsigned int i = 0; other[i]; i++) _size_other++;

    if (!_size_other) {
        _size = 0;
        _data = 0;
        return *this;
    }
    _size = _size_other;
    _data = new char[_size+1];

    for (int i = 0; other[i]; i++) {
        _data[i] = other[i];
    }
    _data[_size] = '\0';
    return *this;
}

char& string::operator[](unsigned int pos) {
    return _data[pos];
}

const char& string::operator[](unsigned int pos) const {
    return _data[pos];
}

const char* string::data() const {
    return _data;
}

unsigned int string::size() const {
    return _size;
}

bool string::empty() {
    if (_data==nullptr) return true;
    if (_data){
        for(unsigned int i = 0; (i<_size); i++){
            if (_data[i]!='\0') return false;
        }
    }
    return true;
}

void string::clear() {
    if (!_data) return;
    _data = nullptr;
    _size = 0;
}

void string::push_back(char ch) {
    _size++;
    _data = (char*)realloc(_data, sizeof(char)*(_size+1));
    _data[_size - 1] = ch;
    _data[_size] = '\0';
}

void string::pop_back() {
    if (!_data) return;
    _size--;
    _data = (char*)realloc(_data, sizeof(char)*(_size+1));
    _data[_size] = '\0';
}

string& string::append(unsigned int count, const char& ch) {
    if (count == 0) return *this;

    _data = (char*)realloc(_data, sizeof(char)*(_size + count));
    for (unsigned int i = _size - 1; i < _size + count; i++) {
        _data[i] = ch;
    }
    _size = _size + count;
    _data[_size] = '\0';

    return *this;
}

string& string::append(const string& other) {
    _size = _size + other._size;
    _data = (char*)realloc(_data, sizeof(char)*(_size + 1));
    int j = 0;
    for (unsigned int i = _size - other._size - 1; i < _size; i++) {
        _data[i] = other[j];
        j++;
    }
    _data[_size] = '\0';
    return *this;
}

string& string::append(const char* other, unsigned int count) {
    if (count == 0) return *this;
    unsigned int other_size = 1;
    for( other_size = 1; other[other_size]; other_size++ );
    if (other_size < count) count = other_size;

    _size = _size + count;
    _data = (char*)realloc(_data, sizeof(char)*(_size+1));
    int j = 0;
    for (unsigned int i = _size - count - 1; i < _size; i++) {
        _data[i] = other[j++];
    }
    _data[_size] = '\0';
    return *this;
}

string string::substr(unsigned int pos, unsigned int count) {
    if (_data == nullptr) return nullptr;
    if (pos + count > _size) count = _size - pos;
    char* result = new char[count + 1];

    for (unsigned int i = 0; i < count; i++) {
        result[i] = _data[pos + i];
    }
    result[count] = '\0';
    return result;
}

void string::print() {
    if (_data)
        for (unsigned int i = 0; i<_size; i++)
            cout << _data[i];
}

// V - E - C - T - O - R

template <typename T>
vector<T>::~vector(){
    if (_data) delete(_data);
}

template <typename T>
vector<T>::vector() : _data(nullptr), _size(0) {}

template <typename T>
vector<T>::vector(const vector& other): _data(nullptr), _size(0){
    if(other._data){
        _size = other._size;
        _data = new T [_size];
        for (unsigned int i = 0; i < _size ; i++) {
            _data[i] = other._data[i];
        }
    }
}

template <typename T>
vector<T>::vector(vector&& other) : _data(other._data), _size(other._size){
    if(other._data){
        other._data = nullptr;
        other._size = 0;
    }
}

template <typename T>
vector<T>::vector(int count): _size(count) {
    if (count < 0) {
        _data = nullptr;
        _size = 0;
    }
    if (count != 0){
        T val = T();
        _data = new T[_size];
        for (unsigned int i = 0; i<_size; i++){
            _data[i] = val;
        }
    }
    _data = nullptr;
}

template <typename T>
vector<T>::vector(unsigned int count, const T& val) : _data(nullptr), _size(count) {
    if(_size!=0){
        _data = new T[_size];
        for (unsigned int i = 0; i<_size; i++){
            _data[i] = val;
        }
    }
}

template <typename T>
T& vector<T>::operator[] (int pos){
   return _data[pos];
}

template <typename T>
const T& vector<T>::operator[] (int pos) const{
    return _data[pos];

}

template <typename T>
unsigned int vector<T>::size(){
    return _size;
}

template <typename T>
T* vector<T>::data(){
    if (_data) return _data;
    return nullptr;
}

template <typename T>
const T* vector<T>::data() const{
    if (_data) return _data;
    return nullptr;
}

template <typename T>
bool vector<T>::empty() const{
    if (_data==nullptr) return true;
    if (_data){
        T val = T();
        for(unsigned int i = 0; (i<_size); i++){
            if (_data[i]!=val) return false;
        }
    }
    return true;
}

template <typename T>
void vector<T>::clear(){
    if (_data) {
        T val = T();
        for(unsigned int i=0; i<_size; i++) _data[i]=val;
    }
}

template <typename T>
void vector<T>::push_back(const T& value){
    _size++;
    _data = (T*)realloc(_data, sizeof(T)*(_size));
    _data[_size - 1] = value;
}

template <typename T>
void vector<T>::push_back(T&& value){
    _size++;
    _data = (T*)realloc(_data, sizeof(T)*(_size));
    _data[_size - 1] = value;
}

template <typename T>
void vector<T>::pop_back(){
    if (!_data) return;
    _size--;
    _data = (T*)realloc(_data, sizeof(T)*(_size));
}

template <typename T>
void vector<T>::insert( unsigned int pos, unsigned int count, const T& value){
    if(pos > _size) {
        unsigned int new_size = pos + count;
        _data = (T*)realloc(_data, sizeof(T)*(new_size));
        for(unsigned int i = _size; i < pos; i++)
            _data[i]=T();
        for (unsigned int i = pos; i < pos + count; i++)
            _data[i]=value;
        _size = new_size;
    }
    else {
        unsigned int new_size = _size + count;
        _data = (T*)realloc(_data, sizeof(T)*(new_size));
        for(unsigned int i = new_size-1; i >= pos + count; i--)
            _data[i]=_data[i-count];
        for (unsigned int i = pos; i < pos + count; i++)
            _data[i]=value;
        _size = new_size;
    }
}

template <typename T>
void vector<T>::print() {
    if (_data!=nullptr)
        for (unsigned int i = 0; i<_size; i++){
            cout << _data[i];
            if (i<_size-1) cout << ", ";
        }
}

void Test0_table(){
    cout << "\n***********************************************\n";
    cout <<   "*               TEST 0 _ TABLE                *\n";
    cout <<   "***********************************************\n\n";

    print_number_table(3,6);
    print_number_table(5,2);
    print_number_table(1,1);
}

void Test1_string() {
    cout << "\n***********************************************\n";
    cout <<   "*               TEST 1 _ STRING               *\n";
    cout <<   "***********************************************\n\n";

    cout << "\n...Конструктор по умолчанию (string mystr)...\n";
    string mystr;
    cout << "My string = \"";
    mystr.print();
    cout << "\", size = " << mystr.size() << endl;

    cout << "\n...Конструктор 1 (string mystr1 (8,'8'))...\n";
    string mystr1(8, '8');
    cout << "My string = \"";
    mystr1.print();
    cout << "\", size = " << mystr1.size() << endl;

    cout << "\n...Конструктор 2 (string mystr2 (\"Kalinichika@gmail.com\",11) и (\"Kalinichika@gmail.com\",30))...\n";
    string mystr2("Kalinichika@gmail.com", 11);
    cout << "My string = \"";
    mystr2.print();
    cout << "\", size = " << mystr2.size() << endl;
    string mystr21("Kalinichika@gmail.com", 30);
    cout << "My string = \"";
    mystr21.print();
    cout << "\", size = " << mystr21.size() << endl;

    cout << "\n...Конструктор 3 (string mystr3 (\"Vika Kalinina\"))...\n";
    string mystr3("Vika Kalinina");
    cout << "My string = \"";
    mystr3.print();
    cout << "\", size = " << mystr3.size() << endl;


    string copy = "Hello, World!";
    cout << "\n...Конструктор копирования (string mystr4(copy))...\n";
    string mystr4(copy);
    cout << "My string = \"";
    mystr4.print();
    cout << "\", size = " << mystr4.size() << endl;
    cout << "...Откуда копировали:...\n";
    cout << "My string = \"";
    copy.print();
    cout << "\", size = " << copy.size() << endl;


    cout << "\n...Конструктор переноса (string mystr5(move(copy)))...\n";
    string mystr5(move(copy));
    cout << "My string = \"";
    mystr5.print();
    cout << "\", size = " << mystr5.size() << endl;
    cout << "...Откуда переносили:...\n";
    cout << "My string = \"";
    copy.print();
    cout << "\", size = " << copy.size() << endl;

    cout << "\n...Операторы присваивания (mystr=mystr1) и (mystr=\"KTSO-01-16\")...\n";
    mystr = mystr1;
    cout << "My string = \"";
    mystr.print();
    cout << "\", size = " << mystr.size() << endl;
    mystr = "KTSO-01-16";
    cout << "My string = \"";
    mystr.print();
    cout << "\", size = " << mystr.size() << endl;

    cout << "\n...Оператор [ ]...\n";
    cout << "My string = \"";
    mystr.print();
    cout << "\"\n";
    char ch;
    ch = mystr[1];
    cout << "mystr[1] = \"" << mystr[1] << "\"";
    ch = mystr[20];
    cout << "\nmystr[20] = \"" << ch << "\"";
    ch = mystr[mystr.size()];
    cout << "\nmystr[mystr.size()] = \"" << ch << "\"";
    cout << endl;
    cout << "\nmystr[1] = 'A' \nMy string = \"";
    mystr[1] = 'A';
    mystr.print();
    cout << "\"" << endl;

}

void Test2_string() {
    cout << "\n***********************************************\n";
    cout <<   "*               TEST 2 _ STRING               *\n";
    cout <<   "***********************************************\n\n";

    string str = "Viktoriya Vladislavovna Kalinina";
    cout << "\n...Функция substr...\n";
    cout << "My string = \"";
    str.print();
    cout << "\"";

    cout << "\n1) substr(5,5) = \"";
    string substring = str.substr(5, 5);
    substring.print();
    cout << "\"";
    cout << ", size = " << substring.size();

    cout << "\n2) substr(10,30) = \"";
    substring = str.substr(10, 30);
    substring.print();
    cout << "\"";
    cout << ", size = " << substring.size() << endl;

    string str1("MIREA!");

    cout << "\n...Функция append...\n";
    cout << "My string = \"";
    str1.print();
    cout << "\"\n";

    cout << "1) append(2,'!') = \"";
    str1.append(2, '!');
    str1.print();
    cout << "\"";
    cout << ", size = " << str1.size() << "\n";

    cout << "2) append(My string) = \"";
    str1.append(str1);
    str1.print();
    cout << "\"";
    cout << ", size = " << str1.size() << "\n";

    cout << "3) append(\" GO!!!\",8) = \"";
    str1.append(" GO!!!", 8);
    str1.print();
    cout << "\"";
    cout << ", size = " << str1.size() << "\n";

    cout << "\n...Проверка empty и clear...\n";
    cout << "\"MIREA!!!MIREA!!! GO!!!\" is empty? = " << str1.empty() << ", size = " << str1.size() << endl;
    str1.clear();
    cout << "\"\" is empty? = " << str1.empty() << ", size = " << str1.size() << endl;

    str1 = "Information";

    cout << "\n...Проверка pop_back...\n";
    cout << "My string = \"Information\", применим pop_back = \"";
    str1.pop_back();
    str1.print();
    cout << "\", size = " << str1.size() << endl;

    cout << "\n...Проверка push_back...\n";
    cout << "My string = \"Informatio\", применим push_back('N') = \"";
    str1.push_back('N');
    str1.print();
    cout << "\", size = " << str1.size() << endl;
}

void Test3_vector_int(){
    cout << "\n***********************************************\n";
    cout <<   "*          TEST 3 _ VECTOR (for int)          *\n";
    cout <<   "***********************************************\n\n";

    cout << "...Конструктор (vector<int> i)...\nMy vector = \t";
    vector<int> i;
    i.print();
    cout << ", size = " << i.size();
    cout << endl;
    cout << "\n...Конструктор 1 (vector<int> i1 (5, 10))...\nMy vector = \t";
    vector<int> i1(5,10);
    i1.print();
    cout << ", size = " << i1.size();
    cout << endl;
    cout << "\n...Конструктор 2 (vector<int> i2(7))...\nMy vector = \t";
    vector<int> i2(7);
    i2.print();
    cout << ", size = " << i2.size();
    cout << endl;
    cout << "\n...Конструктор 2_1 (vector<int> i2_1(-7))...\nMy vector = \t";
    vector<int> i2_1(-7);
    i2_1.print();
    cout << ", size = " << i2_1.size();
    cout << endl;
    cout << "\n...Конструктор 3 копирования (vector<int> i3(i1))...\nMy vector = \t";
    vector<int> i3(i1);
    i3.print();
    cout << ", size = " << i3.size();
    cout << endl;
    cout << "\n...Конструктор 4 перемещения (vector<int> i4(move(i3)))...\nMy vector = \t";
    vector<int> i4(std::move(i3));
    i4.print();
    cout << ", size = " << i4.size();
    cout << endl;
    cout << "\n...Оператор = (vector<int> i5 = i4)...\nMy vector = \t";
    vector<int> i5 = i4;
    i5.print();
    cout << ", size = " << i5.size();
    cout << endl;

    cout << "\n...Оператор [ ] (i[5] = ?)...\nMy vector = \t";
    i5.print();
    cout << ", size = " << i5.size() << "\n";
    cout << "i5[2] = " << i5[2] ;
    cout << endl;
    cout << "\n...Оператор [ ] (i5[2] = 3; i5[10] = 44)...\nMy vector = \t";
    i5[2] = 3;
    i5[10] = 44;
    i5.print();
    cout << ", size = " << i5.size();
    cout << endl;

    cout << "\n...Функция emty...\nMy vector = \t";
    i5.print();
    cout << "\nMy vector is empty? - " << i5.empty() << ", size = " << i5.size();
    cout << endl;

    cout << "\n...Функция clear (i5.clear())...\nMy vector = \t";
    i5.print();
    cout << ", \nAfter clear = \t";
    i5.clear();
    i5.print();
    cout << ", size = " << i5.size();
    cout << endl;
    cout << "My vector is empty? - " << i5.empty() << ", size = " << i5.size();
    cout << endl;

    i5[0]=0; i5[1]=1; i5[2]=-2; i5[3]=3; i5[4]=4;
    cout << "\n...Функция pop_back...\nMy vector = \t";
    i5.print();
    cout << ", size = " << i5.size() << endl;
    cout << "After pop_back = \t";
    i5.pop_back();
    i5.print();
    cout << ", size = " << i5.size() << endl;

    cout << "\n...Функция push_back...\nMy vector = \t";
    i5.print();
    cout << ", size = " << i5.size() << endl;
    cout << "After push_back(4) = \t";
    i5.push_back(4);
    i5.print();
    cout << ", size = " << i5.size() << endl;


    cout << "\n...Функция insert(pos, count, value)...\nMy vector = \t";
    i5.print();
    cout << ", size = " << i5.size() << endl;

    vector<int> i6(i5);
    cout << "After insert(2,4,7) = \t";
    i6.insert(2, 4, 7);
    i6.print();
    cout << ", size = " << i6.size() << endl;

    vector<int> i6_1(i5);
    cout << "After insert(0,3,9) = \t";
    i6_1.insert(0, 3, 9);
    i6_1.print();
    cout << ", size = " << i6_1.size() << endl;

    vector<int> i6_2 = i5;
    cout << "After insert(16,5,1) =\t";
    i6_2.insert(16, 5, 1);
    i6_2.print();
    cout << ", size = " << i6_2.size() << endl;

    vector<int> i6_3 = i5;
    cout << "After insert(5,5,1) =\t";
    i6_3.insert(5, 5, 1);
    i6_3.print();
    cout << ", size = " << i6_3.size() << endl;
}

void Test4_vector_double(){
    cout << "\n***********************************************\n";
    cout <<   "*       TEST 3 _ VECTOR (for double)          *\n";
    cout <<   "***********************************************\n\n";

    cout << "...Конструктор (vector<double> d)...\nMy vector = \t";
    vector<double> d;
    d.print();
    cout << ", size = " << d.size();
    cout << endl;
    cout << "\n...Конструктор 1 (vector<double> d1(4, 7.6))...\nMy vector = \t";
    vector<double> d1(4,7.6);
    d1.print();
    cout << ", size = " << d1.size();
    cout << endl;
    cout << "\n...Конструктор 2 (vector<double> d2(3))...\nMy vector = \t";
    vector<double> d2(3);
    d2.print();
    cout << ", size = " << d2.size();
    cout << endl;
    cout<<"...Конструктор 2 (vector<double> d2_1(-3))...\nMy vector = \t";
    vector<double> d2_1(-3);
    d2_1.print();
    cout << ", size = " << d2_1.size();
    cout << endl;
    cout << "\n...Конструктор 3 копирования (vector<double> d3(d1))...\nMy vector = \t";
    vector<double> d3(d1);
    d3.print();
    cout << ", size = " << d3.size();
    cout << endl;
    cout << "\n...Конструктор 4 перемещения (vector<double> d4(move(d3)))...\nMy vector = \t";
    vector<double> d4(move(d3));
    d4.print();
    cout << ", size = " << d4.size();
    cout << endl;
    cout << "\n...Оператор = (vector<double> d5 = d4)...\nMy vector = \t";
    vector<double> d5 = d4;
    d5.print();
    cout << ", size = " << d5.size();
    cout << endl;

    cout << "\n...Оператор [ ] (d5[2] = ?)...\nMy vector = \t";
    d5.print();
    cout << ", size = " << d5.size();
    cout << "\nd5[2] = " << d5[2];
    cout << endl;

    cout << "\n...Оператор [ ] (d5[2] = 3.3; d5[7] = 4.4)...\nMy vector = \t";
    d5[2] = 3.3;
    d5[7] = 4.4;
    d5.print();
    cout << ", size = " << d5.size();
    cout << endl;

    cout << "\n...Функция emty...\nMy vector = \t";
    d5.print();
    cout << "\nMy vector is empty? - " << d5.empty() << ", size = " << d5.size();
    cout << endl;

    cout << "\n...Функция clear (d5.clear())...\nMy vector = \t";
    d5.print();
    cout << ", \nAfter clear = \t";
    d5.clear();
    d5.print();
    cout << ", size = " << d5.size();
    cout << endl;
    cout << "My vector is empty? - " << d5.empty() << ", size = " << d5.size();
    cout << endl;

    d5[0]=0.11; d5[1]=3.2; d5[2]=-3.7; d5[3]=5; d5[4]=2.3;
    cout << "\n...Функция pop_back...\nMy vector = \t";
    d5.print();
    cout << ", size = " << d5.size() << endl;
    cout << "After pop_back = \t";
    d5.pop_back();
    d5.print();
    cout << ", size = " << d5.size() << endl;

    cout << "\n...Функция push_back...\nMy vector = \t";
    d5.print();
    cout << ", size = " << d5.size() << endl;
    cout << "After push_back(55.45) = \t";
    d5.push_back(55.45);
    d5.print();
    cout << ", size = " << d5.size() << endl;

    cout << "\n...Функция insert(pos, count, value)...\nMy vector = \t";
    d5.print();
    cout << ", size = " << d5.size() << endl;

    vector<double> d6(d5);
    cout << "After insert(2,4,7.2) = \t";
    d6.insert(2, 4, 7.2);
    d6.print();
    cout << ", size = " << d6.size() << endl;

    vector<double> d6_1(d5);
    cout << "After insert(0,3,99/99) = \t";
    d6_1.insert(0, 3, 99.99);
    d6_1.print();
    cout << ", size = " << d6_1.size() << endl;

    vector<double> d6_2 = d5;
    cout << "After insert(13,4,0.91) =\t";
    d6_2.insert(13, 4, 0.91);
    d6_2.print();
    cout << ", size = " << d6_2.size() << endl;

    vector<double> d6_3 = d5;
    cout << "After insert(4,5,1.01) =\t";
    d6_3.insert(4, 5, 1.01);
    d6_3.print();
    cout << ", size = " << d6_3.size() << endl;
}

int main()
{
    //setlocale(LC_ALL, "Russian");
    Test0_table();
    Test1_string();
    Test2_string();
    Test3_vector_int();
    Test4_vector_double();

    return 0;
}
