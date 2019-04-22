#include <iostream>
#include <student.h>

using namespace student;
using std::cout;
using std::endl;


template <typename T>
RedBlackTree<T>::RedBlackTree(){
        RBT_root = 0;
        countNodes = 0;
    }

template <typename T>
RedBlackTree<T>::~RedBlackTree(){
        Clear(RBT_root);
    }

template <typename T>
void RedBlackTree<T>::Clear(){
        Clear(RBT_root);
        countNodes = 0;
        RBT_root = 0;
    }

template <typename T>
void RedBlackTree<T>::Show()
    {
        printf("[tree]\n");
        Show(RBT_root,0,'*');
    }

template <typename T>
bool RedBlackTree<T>::Find(T value){
        Node<T> *node=RBT_root;
        while(node) {
            if(node->value==value) return true;
            if(node->value>value) node = node->left;
            else node = node->right;
        }
        return false;
    }

template <typename T>
void RedBlackTree<T>::Insert(T value){
        if(!RBT_root) RBT_root = NewNode(value);
        else{
            Node<T> *node = RBT_root;
            Node<T> *par = node;
            char flag = '\0';
            while(node){
                par = node;
                if(value < node->value){
                    node = node->left;
                    flag = 'L';
                }
                else if(value > node->value){
                    node = node->right;
                    flag = 'R';
                }
                else return;
            }
            node = NewNode(value);
            node->parent = par;
            if(flag == 'L') par->left = node;
            else par->right = node;
            if(par->color == Red) BalanceInsert(node);
        }
        RBT_root->color = Black;
    }

template <typename T>
void RedBlackTree<T>::Remove(T value){

        Node<T> *node = RBT_root;
        // Поиск вершины для удаления
        while(node->value != value) {
            if(node->value > value) node = node->left;
            else if(node->value < value) node = node->right;
            if (!node) return;
        }

        // СЛУЧАЙ 1
        // Если нет детей
        if(!node->left && !node->right){
            if(node == RBT_root){
                Clear();
                return;
            }
            if(node == node->parent->left) node->parent->left = 0;
            else node->parent->right = 0;
        }

        // СЛУЧАЙ 2
        // Если есть только один сын
        else if(node->left && !node->right){
            if(node == RBT_root){
                RBT_root = node->left;
                RBT_root->parent = 0;
                RBT_root->color = Black;
                countNodes--;
                delete node;
                return;
            }
            else if(node == node->parent->left) {
                node->parent->left = node->left;
                node->left->parent = node->parent;
            }
            else {
                node->parent->right = node->left;
                node->left->parent = node->parent;
            }
            //node->left->color=node->color;
        }
        else if(!node->left && node->right){
            if(node == RBT_root){
                RBT_root = node->right;
                RBT_root->parent = 0;
                RBT_root->color = Black;
                countNodes--;
                delete node;        //если указатели, то неправильно
                return;
            }
            else if(node == node->parent->left) {
                node->parent->left = node->right;
                node->right->parent = node->parent;
            }
            else {
                node->parent->right = node->right;
                node->right->parent = node->parent;
            }
            //node->right->color=node->color;
        }

        // СЛУЧАЙ 3
        // Если есть оба сына
        else{
            // Находим значение, которое заменит удаляемое
            Node<T> *sur = node->right;
            while(sur->left) sur = sur->left;
            node->value = sur->value;
            if(sur->right){
                sur->right->parent = sur->parent;
                if(sur == sur->parent->right)  sur->parent->right = sur->right;
                else if(sur == sur->parent->left) sur->parent->left = sur->right;
            }
            else if(sur == sur->parent->right) sur->parent->right = 0;
            else if(sur == sur->parent->left) sur->parent->left = 0;
            node = sur;
        }
        if(node->color == Black) BalanceRemove(node);
        delete node;
        countNodes--;
        return;
    }

template <typename T>
unsigned int RedBlackTree<T>::GetNodesCount(){
        return countNodes;
    }

template <typename T>
Node<T> *RedBlackTree<T>::NewNode(T val){
        countNodes++;
        Node<T> *node = new Node<T>;
        node->value = val;
        node->left = 0;
        node->right = 0;
        node->parent = 0;
        node->color = Red;
        return node;
    }

template <typename T>
void RedBlackTree<T>::DeleteNode(Node<T>* node){
        countNodes--;
        delete node;
    }

template <typename T>
void RedBlackTree<T>::Clear(Node<T>* node){
        if(!node) return;
        if(node->left) Clear(node->left);
        if(node->right) Clear(node->right);
        countNodes--;
        delete node;
    }

template <typename T>
void RedBlackTree<T>::Show(Node<T>* node, int high, char dir)//high - высота, dir - значок
    {
        int n;
        if(!node) return;
        for(n=0; n < high; n++) putchar(' ');
        if(node->color == Red)
            cout << dir << '[' << node->value << ']' << " (Red)" << endl;
        else
            cout << dir << '[' << node->value << ']' << " (Black)" << endl;
        Show(node->left, high + 2, '-');
        Show(node->right, high + 2, '+');
    }

    /*      X                Y
           / \              / \
          a   Y     -->    X   c
             / \          / \
            b   c        a   b      */

template <typename T>
Node<T> *RedBlackTree<T>::RotateLeft(Node<T> *X){
        Node<T> *Y = X->right;
        X->right = Y->left;
        if (Y->left) Y->left->parent = X;
        Y->parent = X->parent;
        if (X->parent){
            if (X->parent->left == X) X->parent->left = Y;
            else X->parent->right = Y;
        }
        Y->left = X;
        X->parent = Y;
        if(X == RBT_root) RBT_root = Y;
        return Y;
    }

    /*      X                Y
           / \              / \
          Y  a       -->   b   X
         / \                  / \
        b   c                c   a      */

template <typename T>
Node<T> *RedBlackTree<T>::RotateRight(Node<T> *X){
        Node<T> *Y = X->left;
        X->left = Y->right;
        if (Y->right) Y->right->parent = X;
        Y->parent = X->parent;
        if (X->parent){
            if (X->parent->right == X) X->parent->right = Y;
            else X->parent->left = Y;
        }
        Y->right = X;
        X->parent = Y;
        if(X == RBT_root) RBT_root = Y;
        return Y;
    }

template <typename T>
void RedBlackTree<T>::BalanceInsert(Node<T>* node){
        Node<T> *par = node->parent;
        while((node != RBT_root) && (par->color == Red)){
            int flag = 0;
            if(par->parent->left && par->parent->right && (par->parent->left->color == Red) && (par->parent->right->color == Red)){
                par->parent->left->color = Black;
                par->parent->right->color = Black;
                par->parent->color = Red;
                node = par->parent;
                par = par->parent->parent;
            }
            if((node == RBT_root) || (par == RBT_root)) return;
            if(!(par->parent->left) || (par->parent->left->color == Black)){  //если par - правый сын своего отца, а левый сын черный
                if(node == par->left) par = RotateRight(par);
                par->color = Black;
                par->parent->color = Red;
                RotateLeft(par->parent);
                flag = 1;
            }
            if(!flag && (!(par->parent->right) || (par->parent->right->color == Black))){ //если par - левый сын своего отца, а правый сын черный
                if(node == par->right) par = RotateLeft(par);
                par->color = Black;
                par->parent->color = Red;
                par = RotateRight(par->parent);
            }
        }
    }

template <typename T>
void RedBlackTree<T>::BalanceRemove(Node<T> *node){

        // X-ребенок удаленной вершины
        Node<T> *X = node;
        if(!node->right){
            if(node->left) X = node->left;
            else{
                X->value = T();
                X->color = Black;
            }
        }
        else X = node->right;
        Node<T> *par = X->parent;

        // Выполняем, пока Х - не корень и Х - черная
        while((X != RBT_root) && (X->color == Black)){

            // ЕСЛИ Х - Л.Е.В.Ы.Й СЫН
            if((X == par->left)||(par->left==0 && X->value==T())){
                // Если у Х есть красный брат
                if((par->right) && (par->right->color == Red)){
                    par->color = Red;
                    par->right->color = Black;
                    RotateLeft(par);
                }
                else {
                    // Если у брата черные дети
                    // Мы не используем NIL-узлы, поэтому много условий
                    if((!par->right->right && !par->right->left) ||
                            (!par->right->right && (par->right->left->color == Black)) ||
                            (!par->right->left && (par->right->right->color == Black)) ||
                            ((par->right->left) && (par->right->right) &&
                             (par->right->left->color == Black) &&
                             (par->right->right->color == Black)))
                    {
                        par->right->color = Red;
                        X = par;
                        par = X->parent;
                    }
                    // Если у брата одинаковый ребенок - черный
                    else if(par->right->right && (par->right->right->color == Black)){
                        par->right->color = Red;
                        if (par->right->left) par->right->left->color = Black;
                        RotateRight(par->right);
                    }
                    // В других случаях
                    else{
                        if ((par->right->left && par->right->left->color && !par->right->right)||
                            (par->right->left && par->right->left->color && !par->right->right->color)) {
                            par->right->left->color = Black;
                            par->right->color = Red;
                            RotateRight(par->right);
                        }
                        par->right->color = par->color;
                        par->color = Black;
                        if (par->right->right) par->right->right->color = Black;

                        RotateLeft(par);
                        return;
                    }
                }
            }

            // ЕСЛИ Х - П.Р.А.В.Ы.Й СЫН
            else if((X == par->right)||(par->right==0 && X->value==T())){
                // Если у Х есть красный брат
                if((par->left) && (par->left->color == Red)){
                    par->color = Red;
                    par->left->color = Black;
                    RotateRight(par); //!
                }
                else{
                    // Если у брата черные дети
                    // Мы не используем NIL-узлы, поэтому много условий
                    if((!par->left->right && !par->left->left) ||
                            (!par->left->right && !par->left->left->color) ||
                            (!par->left->left && !par->left->right->color) ||
                            ((par->left->left) && (par->left->right) &&
                             !par->left->left->color &&
                             !par->left->right->color))
                    {
                        par->left->color = Red;
                        X = par;
                        par = X->parent;
                    }
                    // Если у брата одинаковый ребенок - черный
                    else if(par->left->left && !par->left->left->color){
                        par->left->color = Red;
                        RotateLeft(par->left);
                    }
                    // В других случаях
                    else{
                        if ((par->left->left && !par->left->left->color && par->left->right->color)||
                            (!par->left->left && par->left->right->color)) {
                            par->left->right->color = Black;
                            par->left->color = Red;
                            RotateLeft(par->left);
                        }
                        par->left->color = par->color;
                        par->color = Black;
                        if (par->left->left) par->left->left->color = Black;

                        RotateRight(par);
                        return;
                    }
                }
            }
        }
        if((X!=RBT_root) && (X->color ==Red))
            X->color=Black;
    }


void _Test::for_int(){
        cout<<"\n**************************************************\n"
              "\n*            T E S T         I N T               *\n"
              "\n**************************************************\n";
        RedBlackTree<int> tree;
        tree.Insert(7);
        tree.Insert(-1);
        tree.Insert(2);
        tree.Insert(28);
        tree.Insert(0);
        tree.Insert(10);
        tree.Insert(5);
        tree.Insert(-4);
        tree.Insert(15);
        tree.Insert(3);
        tree.Insert(17);
        tree.Insert(8);
        tree.Insert(9);
        tree.Insert(6);
        cout << endl;
        tree.Show();

        cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;

        cout << "\nFind(1) = " << tree.Find(1) << endl;
        cout << "Find(8) = " << tree.Find(8) << endl;

        cout << "\nAfter Remove(3) : " << endl;
        tree.Remove(3);
        tree.Show();
        cout << "\nAfter Remove(-4) : " << endl;
        tree.Remove(-4);
        tree.Show();
        cout << "\nAfter Remove(-1) : " << endl;
        tree.Remove(-1);
        tree.Show();
        cout << "\nAfter Remove(2) : " << endl;
        tree.Remove(2);
        tree.Show();
        cout << "\nAfter Remove(8) : " << endl;
        tree.Remove(8);
        tree.Show();
        cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;
        cout << "\nAfter Remove(17) : " << endl;
        tree.Remove(17);
        tree.Show();
        cout << "\nAfter Remove(10) : " << endl;
        tree.Remove(10);
        tree.Show();
        cout << "\nAfter Remove(15) : " << endl;
        tree.Remove(15);
        tree.Show();
        cout << "\nAfter Remove(28) : " << endl;
        tree.Remove(28);
        tree.Show();
        cout << "\nAfter Remove(0) : " << endl;
        tree.Remove(0);
        tree.Show();
        cout << "\nAfter Remove(7) : " << endl;
        tree.Remove(9);
        tree.Show();

        cout << "\nAfter Clear : " << endl;
        tree.Clear();
        tree.Show();
    }
void _Test::for_double(){
        cout<<"\n**************************************************\n"
              "\n*            T E S T      D O U B L E            *\n"
              "\n**************************************************\n";
        RedBlackTree<double> tree;
        tree.Insert(1.0);
        tree.Insert(5.54);
        tree.Insert(5.53);
        tree.Insert(5.8);
        tree.Insert(6.66);
        tree.Insert(0.13);
        tree.Insert(9.99);cout << "\nAfter Remove(5.8) : " << endl;
        tree.Remove(5.8);
        tree.Show();
        tree.Insert(6.455);
        tree.Insert(3.3);
        tree.Insert(2.15);
        tree.Insert(0);
        tree.Insert(8);
        cout << endl;
        tree.Show();
        cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;

        cout << "\nFind(1.1) = " << tree.Find(1.1) << endl;
        cout << "Find(6.66) = " << tree.Find(6.66) << endl;

        cout << "\nAfter Remove(5.8) : " << endl;
        tree.Remove(5.8);
        tree.Show();
        cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;
        cout << "\nAfter Remove(3.3) : " << endl;
        tree.Remove(3.3);
        tree.Show();
        cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;

        cout << "\nAfter Clear : " << endl;
        tree.Clear();
        tree.Show();
    }
void _Test::for_char(){
        cout<<"\n**************************************************\n"
              "\n*            T E S T          C H A R            *\n"
              "\n**************************************************\n";
        RedBlackTree<char> tree;
        tree.Insert('a');
        tree.Insert('b');
        tree.Insert('c');
        tree.Insert('d');
        tree.Insert('e');
        tree.Insert('f');
        tree.Insert('g');
        tree.Insert('h');
        tree.Insert('i');
        tree.Insert('j');
        cout << endl;
        tree.Show();
        cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;
        cout << "\nFind('i') = " << tree.Find('i') << endl;
        cout << "Find('t') = " << tree.Find('t') << endl;
        cout << "\nAfter Clear : " << endl;

        cout << "\nAfter Remove('e') : " << endl;
        tree.Remove('e');
        tree.Show();
        cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;
        cout << "\nAfter Remove('d') : " << endl;
        tree.Remove('d');
        tree.Show();
        cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;

        tree.Clear();
        tree.Show();
    }
void _Test::for_string(){
        cout<<"\n**************************************************\n"
              "\n*            T E S T      S T R I N G            *\n"
              "\n**************************************************\n";
        #include <string>
        RedBlackTree<std::string> tree;
        tree.Insert("Vika");
        tree.Insert("Roma");
        tree.Insert("Oleg");
        tree.Insert("Kate");
        tree.Insert("Olga");
        tree.Insert("Uliana");
        tree.Insert("Artem");
        tree.Insert("Vladislav");
        tree.Insert("Galina");
        tree.Insert("Pavel");
        cout << endl;
        tree.Show();
        cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;
        cout << "\nFind(\"Svetlana\") = " << tree.Find("Svetlana") << endl;
        cout << "Find(\"Uliana\") = " << tree.Find("Uliana") << endl;

        cout << "\nAfter Remove(\"Olga\"): " << endl;
        tree.Remove("Olga");
        tree.Show();
        cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;
        cout << "\nAfter Remove(\"Roma\"): " << endl;
        tree.Remove("Roma");
        tree.Show();
        cout << "\nCount of Nodes = " << tree.GetNodesCount() << endl;

        cout << "\nAfter Clear : " << endl;
        tree.Clear();
        tree.Show();
    }
