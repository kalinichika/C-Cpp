#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

// ПОИСК МЕСТА "РАЗРЫВА"
template <typename T>
int search_break(vector<T>& v){
    if(v[0] < v[v.size()-1]) return v.size()-1;

    int a = 0;
    int b = v.size()-1;

    int count = b/2;
    int middle = count;

    while ((a!=middle)&&(b!=middle)) {

        if ( v[a] > v[middle] ) {
            b = middle;
            count = static_cast<int>((b-a)/ 2);
            middle = middle - count;
        }
        else{
            a = middle;
            count = static_cast<int>((b-a)/ 2);
            middle = middle + count;
        }
    }
    return middle + 1;
}

// ПОИСК ЗНАЧЕНИЯ В ЧАСТИ ВЕКТОРА
template< typename It, typename T >
int search_in_part(It begin, It end, const T& value ){
    It a = begin;
    It b = end-1;
    int size = end - begin;
    It middle = begin+size/2;

    if( *middle == value ) {
        while(*(middle-1) == value)
            middle--;
        return middle-begin;
    }

    while((*middle!=value)&&((a!=middle)&&(b!=middle))){

        if( value < *middle ) {
            b = middle;
            middle = middle - ((b-a)/ 2);
        }
        else{
            a = middle;
            middle = middle + ((b-a)/ 2);
        }
    }

    It result;
    if( *a == value ) result = a;
    else if( *b == value ) result = b;
    else if( *middle == value ) result = middle;
    else return -1;

    while(*(result-1)==value)
        result--;
    return result-begin;
}

// ФУНКЦИЯ SEARCH - ВЫЗЫВАЕТ ВСПОМОГАТЕЛЬНЫЕ
// Ф-ИИ, ОПИСАННЫЕ ВЫШЕ
template <typename T>
int search(vector<T>& v, const T value){
    int pos = search_break(v);
    int result=-1;

    result = search_in_part(v.begin(), v.begin()+pos, value);
    if (result>=0) return result;

    result = search_in_part(v.begin()+pos, v.end(), value);
    if (result>=0) return pos+result;

    return -1;
}


int main()
{
    // СОЗДАЮ ВЕКТОР
    //           0, 1, 2, 3,  4,  5,  6, 7, 8, 9,10,11
    int arr[] = {7, 8, 9, 9, 12, 12, 17, 0, 3, 3, 4, 4,};
    vector<int> v(arr, arr+12);
    // ПЕЧАТЬ ВЕКТОРА
    cout << " num = 0, 1, 2, 3,  4,  5,  6, 7, 8, 9,10,11\n vec = ";
    for (auto i:v) cout << i << ", ";
    cout << endl;
    // ПОИСК ЭЛЕМЕНТОВ 0-19
    for (int i = 0; i<20; i++){
        cout << "position of value \"" << i << "\" = " << search(v,i) << endl;
    }
}
