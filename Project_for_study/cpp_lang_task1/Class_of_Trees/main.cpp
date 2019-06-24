#include <iostream>

using namespace std;



//хз нужен ли root в каждом классе

//++++++++++++++++++++++++++++++++++++++++++++++++++++

class Tree{
protected:
    /*Tree(){
        Data=0;
        CountData=0;
    }

    Tree(int value){
        Data=value;
        CountData=1;
        cout<<"Tree/";
    }*/


public:
    unsigned int CountData;
    int Data;
    virtual void Add()=0;      //добавляет элемент в дерево
    virtual void Remove()=0;   //удаляет элемент из дерева
    virtual bool Contains()=0; //проверяет вхождение элемента
    unsigned int getCount(){
        return CountData;
    }
    int getData(){
        return Data;
    }
    void Clear(){
        //реализация
    }
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++

class Not_Binary_Tree : virtual public Tree{
public:
    Not_Binary_Tree(){
        Data = 0;
        CountData = 0;
        CountSons = 0;
        Sons = 0;
        cout<<"NBT/";
    }
    Not_Binary_Tree(int value){
        Data = value;
        CountData = 1;
        CountSons = 0;
        Sons = 0;
        cout<<"NotBinaryTree/";
    }
    Not_Binary_Tree(int value, unsigned int c){
        cout<<"NotBinaryTree/";
        Data = value;
        CountData = 1;
        CountSons = c;
        Sons = new Not_Binary_Tree[c];

    }
    ~Not_Binary_Tree(){
        //if (Sons) delete Sons;
    }

    void Add(){      /*реализация*/    }
    void Remove(){   /*реализация*/    }
    bool Contains(){ return false;     }
private:
    unsigned int CountSons;
    Not_Binary_Tree* Sons;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++

class Binary_Tree : virtual public Tree{
public:
    Binary_Tree(){
        Data=0;
        CountData=0;
        Left = 0;
        Right = 0;
        cout<<"BinaryTree/";
    }
    Binary_Tree(int value){
        Data=value;
        CountData=1;
        Left = 0;
        Right = 0;
        cout<<"BinaryTree/";
    }
    ~Binary_Tree(){
        //if (Left!=0)        delete Left;
        //if (Right)       delete Right;
    }
    void Add(){      /*реализация*/    }
    void Remove(){/*реализация*/    }
    bool Contains(){ return false;     }
protected:
    const unsigned int CountSons = 2;
private:
    Binary_Tree* Left;
    Binary_Tree* Right;
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++

class Binary_Tree_Research : public Binary_Tree{
public:
    Binary_Tree_Research():Binary_Tree(){
        CountData = 0;
        Data = 0;
        Left = nullptr;
        Right = nullptr;
        cout<<"BinaryTreeResearch/";
    }
    ~Binary_Tree_Research(){
        //if(Left)        delete Left;
        //if(Right)       delete Right;
    }
    void Add(){      /*реализация*/    }
    void Remove(){   /*реализация*/    }
    bool Contains(){ return false;     }
private:
    Binary_Tree_Research* Left;
    Binary_Tree_Research* Right;
    void Left_Rotate();
    void Right_Rotate();
    void Property();
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef enum {Red, Black} nodeColor;


class Red_Black_Tree : public Binary_Tree{
public:
    Red_Black_Tree():Binary_Tree(){
        CountData = 0;
        Data = 0;
        Left = NIL;
        Right = NIL;
        Color = Red;
        cout<<"RedBlackTree/";
    }
    ~Red_Black_Tree(){
        //if(Left)        delete Left;
        //if(Right)       delete Right;
    }
    void Add(){      /*реализация*/    }
    void Remove(){   /*реализация*/    }
    bool Contains(){ return false;     }
private:
    Red_Black_Tree* Left;
    Red_Black_Tree* Right;
    Red_Black_Tree* NIL;
    nodeColor Color;
    void Left_Rotate();
    void Right_Rotate();
    void Property();
};

//++++++++++++++++++++++++++++++++++++++++++++++++++++

int main()
{
    cout<<endl;
    Not_Binary_Tree NBT(0,3);
    cout<<endl;
    Binary_Tree BT(0);
    cout<<endl;
    Binary_Tree_Research BTR;
    cout<<endl;
    Red_Black_Tree RBT;
    cout<<endl;

    return 0;
}
