#pragma once

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
typedef int node_entry;

//Node Definition
struct Node
{
	Node();
	Node(node_entry);
	Node(Node*);
	node_entry entry;
	Node *rlink = NULL;
	Node *llink = NULL;
	Node* pushNode = NULL;
	node_entry bf;

};

//Tree Definition
class Tree
{
public:
	Tree();
	node_entry height(Node*);
	node_entry max(node_entry, node_entry);	
	Node* getRoot(){ return root; };
	Node* getSubRoot(node_entry);
	Node* getPreRoot(node_entry);
	Node* getTop(){ return top->pushNode; };
	bool isBalanced(Node*);
	bool empty();
	void balfactor(Node*);
	void insert(node_entry);
	void bfactor();
	void rightRotate(Node*&);
	void leftRotate(Node*&);
	void inOrderTraversal(Node*);
	void preOrderTraversal(Node*);
	void push(Node*);
	void pop();
	void testOrder(Node*);
	void treeDelete(Node*);
	void stackDelete();
	void setRootNULL();
protected:
	Node* root = NULL;
	Node* top = NULL;

};