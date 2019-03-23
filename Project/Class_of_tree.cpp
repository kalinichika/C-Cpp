#include "pch.h"
#include <iostream>

using namespace std;

struct Node {
	int data;
	Node *left, *right, *parent;
	Node() { }
};


struct Red_Black_Node : public Node {
	char color;
	Red_Black_Node() { }
	static Node NilNode;
};


class Tree {
public:
	Tree(int count_Branch1, int count1) {}
protected:	
	int count;
	void Add();
	void Remove(int value);
	bool Contains(int value);
	int Count();
	void Clear();
private:
	int count_Branch;

};


class Not_Binary_Tree : public Tree {
public:
	Not_Binary_Tree(int count_Branch1, int count1) : Tree (count_Branch1, count1) {}
private:
	int count_Branch;
	class Not_Binary_Tree** son;
};


class Binary_Tree : public Tree {
public:
	Binary_Tree(int count1) :Tree(2, count1) {}
protected:
	Node *root;
	int count_Branch = 2;
	void Add(int value);
	void Remove(int value);
	bool Contains(int value);
};

class Binary_Tree_Research : public Binary_Tree {
public:
	Binary_Tree_Research(int count1) : Binary_Tree(count1) {}
protected:
	void Left_Rotate();
	void Right_Rotate();
	void Property();
};

class Red_Black_Tree : public Binary_Tree {
	Red_Black_Tree(int count1) : Binary_Tree(count1) {}
protected:
	Red_Black_Node *root;
	void Left_Rotate();
	void Right_Rotate();
	void Property();
};


int main()
{
	return 0;
}

