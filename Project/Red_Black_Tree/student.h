#ifndef STUDENT_H
#define STUDENT_H



namespace student{

    typedef enum {Black, Red} colorsNode;

    template <typename T>
    struct Node{
        Node *left;
        Node *right;
        Node *parent;
        T value;
        colorsNode color;
    };

    template <typename T>
    class RedBlackTree{
    public:
        RedBlackTree();
        ~RedBlackTree();
        void Clear();
        void Show();
        bool Find(T);
        void Insert(T);
        void Remove(T);
        unsigned int GetNodesCount();
    private:
        Node<T> *RBT_root;
        unsigned int countNodes;
        Node<T> *NewNode(T);
        void DeleteNode(Node<T>*);
        void Clear(Node<T>*);
        void Show(Node<T>*, int high, char dir);//high - высота, dir - значок
        Node<T> *RotateLeft(Node<T> *);
        Node<T> *RotateRight(Node<T> *);
        void BalanceInsert(Node<T>* );
        void BalanceRemove(Node<T> *);
    };

    struct _Test{
        void for_int();
        void for_double();
        void for_char();
        void for_string();
    };

}

#endif // STUDENT_H
