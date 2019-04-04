#include <iostream>
#include "cpp_lang_task1.h"

using std::cout;
using std::endl;
using std::move;

using namespace student;

string::~string() {
    if (_data) delete(_data);
}

string::string() : _data(nullptr), _size(0), _lenght(0) {}

string::string(unsigned int count, char ch) {
    if (count == 0) { _data = nullptr; _size = 0; _lenght = 0; }
    _size = count + 1;
    _lenght = count;
    _data = new char[_size];
    for (unsigned int i = 0; i < count; i++) {
        _data[i] = ch;
    }

    _data[_size - 1] = '\0';
}

string::string(const char* other, unsigned int count) {
    if ((!other) || (count == 0)) { _data = nullptr; _size = 0; _lenght = 0; }

    _size = count + 1;
    _lenght = count;
    _data = new char[_size];
    for (unsigned int i = 0; i < _size - 1; i++) {
        _data[i] = other[i];
    }
    _data[_size - 1] = '\0';
}

string::string(const char* other) : _data(nullptr), _size(0), _lenght(0) {
    if (other) {
        unsigned int _size_other = 0;
        for (int i = 0; other[i]; i++) {
            _size_other++;
        }
        _size = _size_other + 1;
        _lenght = _size_other;

        _data = new char[_size];
        for (unsigned int i = 0; other[i]; i++) {
            _data[i] = other[i];
        }
        _data[_size - 1] = '\0';
    }
}

string::string(const string& other) : _data(), _size(other._size), _lenght(other._lenght) {
    if (other._data) {
        _data = new char[_size];
        for (unsigned int i = 0; other._data[i]; i++) {
            _data[i] = other._data[i];
        }
        _data[_size - 1] = '\0';
    }
}

string::string(string&& other) : _data(other._data), _size(other._size), _lenght(other._lenght) {
    other._data = nullptr;
    other._size = 0;
    other._lenght = 0;
    //cout<<"!!!конструктор перемещения!!!\n";
}

string& string::operator = (const string& other) {
    delete(_data);
    _size = other._size;
    _lenght = other._lenght;
    if (!_size) {
        _data = 0;
        return *this;
    }
    _data = new char[_size];

    for (unsigned int i = 0; other._data[i]; i++) {
        _data[i] = other._data[i];
    }
    _data[_size - 1] = '\0';
    return *this;
}

string& string::operator = (string&& other) {
    delete(_data);
    _data = other._data;
    _size = other._size;
    _lenght = other._lenght;
    other._data = nullptr;
    other._size = 0;
    other._lenght = 0;
    //cout<<"!!!присваивание перемещением!!!\n";
    return *this;
}

string& string::operator= (const char* other) {
    delete(_data);
    unsigned int _size_other = 0;
    for (unsigned int i = 0; other[i]; i++) _size_other++;

    if (!_size_other) {
        _size = 0;
        _lenght = 0;
        _data = 0;
        return *this;
    }
    _size = _size_other + 1;
    _lenght = _size_other;

    _data = new char[_size];

    for (int i = 0; other[i]; i++) {
        _data[i] = other[i];
    }
    _data[_size - 1] = '\0';
    return *this;
}


char& string::operator[](unsigned int pos) {
    //char ch = '\0';
    //if (pos > _size) return ch;
    return _data[pos - 1];
}

const char& string::operator[](unsigned int pos) const {
    //char ch = '\0';
    //if (pos > _size) return ch;
    return _data[pos - 1];
}

const char* string::data() const {
    return _data;
}

unsigned int string::size() const {
    return _size;
}

unsigned int string::length() const {
    return _lenght;
}

bool string::empty() {
    if (!_data) return true;
    else return false;
}

void string::clear() {
    if (!_data) return;
    _data = nullptr;
    _size = 0;
    _lenght = 0;
}

void string::push_back(char ch) {
    _size++;
    _lenght++;
    _data = (char*)realloc(_data, sizeof(char)*(_size));
    _data[_size - 2] = ch;
    _data[_size - 1] = '\0';
}

void string::pop_back() {
    if (!_data) return;
    _size--;
    _lenght--;
    _data = (char*)realloc(_data, sizeof(char)*(_size));
    _data[_size - 1] = '\0';
}

string& string::append(unsigned int count, const char& ch) {
    if (count == 0) return *this;

    _data = (char*)realloc(_data, sizeof(char)*(_size + count));
    for (unsigned int i = _size - 1; i < _size + count - 1; i++) {
        _data[i] = ch;
    }

    _size = _size + count;
    _lenght = _size - 1;
    _data[_size - 1] = '\0';

    return *this;
}

string& string::append(const string& other) {
    _data = (char*)realloc(_data, sizeof(char)*(_size + other._size - 1));

    _data[_size + other._size - 1] = '\0';
    _size = _size + other._size - 1;
    _lenght = _size - 1;

    return *this;
}

string& string::append(const char* other, unsigned int count) {
    _data = (char*)realloc(_data, sizeof(char)*(_size + count));
    int j = 0;
    for (unsigned int i = _size - 1; i < _size + count; i++) {
        _data[i] = other[j++];
    }
    _data[_size + count - 1] = '\0';
    _size = _size + count;
    _lenght = _size - 1;

    return *this;
}

string string::substr(unsigned int pos, unsigned int count) {
    if (_data == nullptr) return nullptr;
    if (pos + count > _size) count = _size - pos;
    char* result = new char[count];
    //char* result = (char*)malloc(sizeof(char)*count);
    for (unsigned int i = 0; i < count; i++) {
        result[i] = _data[pos + i];
    }
    result[count] = '\0';
    return result;
}

void string::print() {
    if (_data)
        for (unsigned int i = 0; _data[i]; i++)
            cout << _data[i];
}


void Test1() {
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
    cout << "mystr[1] = \"" << ch << "\"";
    ch = mystr[20];
    cout << "\nmystr[20] = \"" << ch << "\"";
    ch = mystr[mystr.size()];
    cout << "\nmystr[mystr.size()] = \"" << ch << "\"";
    cout << endl;
}

void Test2() {
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


int main()
{
    //setlocale(LC_ALL, "Russian");
    Test1();
    Test2();
    return 0;
}
