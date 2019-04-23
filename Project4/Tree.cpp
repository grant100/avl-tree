#include "Tree.h"
#include "stdafx.h"
#include <cmath>
#include <iomanip>

//Constructor definition for Tree 
Tree::Tree()
{
	root = NULL;
	top = NULL;
}

//node constructor
Node::Node(node_entry item)
{
	entry = item;
	bf = 0;
}

//node constructor
Node::Node(Node* p)
{
	pushNode = p;
}

// Function Name: insert(node_entry item)
// Purpose:	 insert Node into tree
// Parameters: node_entry
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: node inserted
void Tree::insert(node_entry item)
{
	
	Node *nNode = new Node(item);
	if (root == NULL)
	{
		root = nNode;
		cout << "\n" << item;
	
	}
	else 
	{
		Node *p, *q, *z;
		p = root; 
		q = NULL;
		while (p != NULL && p->entry != item) 
		{
			q = p; 
			if (item < p->entry)
			{
				p = p->llink;//go down left side
			}
				
			else 
			{
				p = p->rlink;//go down right side
			}
		} 
		if (p != NULL) //delete duplicate entry
		{
			cout << "\nDuplicate Data"<<" ("<<item<<")"<<" Deleted...";
			z = nNode;
			nNode = NULL;
			delete z;
		}
		else 
		{
			if (item < q->entry)
			{
				q->llink = nNode; //set link
				cout << "\n" << item;
				
			}
			else
			{
				q->rlink = nNode;//set link
				cout << "\n" << item;
				
			}
		}
	} 
	bfactor();//update balance factor after insertion
	if (isBalanced(root) != true)//check if unbalanced
	{
		Node *subRoot = getSubRoot(item);//get problem Node
		Node *preRoot = getPreRoot(item);//get parent of problem Node
		
		if (subRoot->bf > 1 && item < subRoot->llink->entry)//check for left left case
		{
			rightRotate(subRoot);//rotate root

			if (preRoot != NULL)
			{
				if (item > preRoot->entry) //link parent to rotated subRoot
				{
					preRoot->rlink = subRoot;
				}
				else
				{
					preRoot->llink = subRoot;//link parent to rotated subRoot
				}
			}
			else
			{
				root = subRoot; //reset root to rotated root
			}

		}
		if (subRoot->bf < -1 && item > subRoot->rlink->entry)//check for right right case
		{
			leftRotate(subRoot);
			if (preRoot != NULL)
			{
				if (item > preRoot->entry)
				{
					preRoot->rlink = subRoot;//link parent to rotated subRoot
				}
				else
				{
					preRoot->llink = subRoot;//link parent to rotated subRoot
				}
			}
			else
			{
				root = subRoot;//reset root to rotated root
			}

		}
		if (subRoot->bf > 1 && item > subRoot->llink->entry) //check for left right case
		{
			Node *p;
			p = subRoot->llink;
			leftRotate(p);//perform first rotation
			subRoot->llink = p;
			rightRotate(subRoot);//second rotation
			if (preRoot != NULL)
			{
				if (item > preRoot->entry)
				{
					preRoot->rlink = subRoot;//link parent to rotated subRoot
				}
				else
				{
					preRoot->llink = subRoot;//link parent to rotated subRoot
				}
			}
			else
			{
				root = subRoot;//reset root to rotated root
			}

		}
		if (subRoot->bf < -1 && item < subRoot->rlink->entry)//check for right left case
		{
			Node *p;
			p = subRoot->rlink;
			rightRotate(p);//perform first rotation
			subRoot->rlink = p;
			leftRotate(subRoot);//perform second rotation
			if (preRoot != NULL)
			{
				if (item > preRoot->entry)
				{
					preRoot->rlink = subRoot;//link parent to rotated subRoot
				}
				else
				{
					preRoot->llink = subRoot;//link parent to rotated subRoot
				}
			}
			else
			{
				root = subRoot;//reset root to rotated root
			}

		}
	
	}
}

// Function Name: bfactor()
// Purpose:	 calculate balance factor of each node in Tree
// Parameters: void
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: updated BF in each node
void Tree::bfactor()
{
	if (root != NULL)
	{
		root->bf = height(root->llink) - height(root->rlink);
		balfactor(root->llink);
		balfactor(root->rlink);
	}
}

// Function Name: isBalanced(Node* root)
// Purpose:	 check if tree is imbalanced anywhere
// Parameters: Node*
// Returns:	  bool
// Pre-conditions: none	
// Post-conditions: none
bool Tree::isBalanced(Node* root)
{
	int leftHeight; 
	int rightHeight; 
	Node* p = root;
	
	if (root == NULL)
	{
		return true;
	}
	
	leftHeight = height(root->llink);
	rightHeight = height(root->rlink);

	if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->llink) && isBalanced(root->rlink))//recursively check each links height if greater than |1| then out of balance
	{
		return true;
	}
		
	return false;

}

// Function Name: getSubRoot(node_entry item)
// Purpose:	 find the lowest out of balance node in tree (on same path as inserted item)
// Parameters: node_entry
// Returns:	  Node*
// Pre-conditions: none	
// Post-conditions: none
Node* Tree::getSubRoot(node_entry item)

{
	bfactor();//update balance factor of each node after insertion
	Node *trace,*p, *q;
	p = root;
	q = NULL;
	trace = NULL;
	while (p != NULL && p->entry != item)
		{
			q = p;

			if (p->bf < -1 || p->bf > 1)//if balance factor > 1 set trace pointer to node
			{
				
				trace = p;
			}
			if (item < p->entry)
			{
				p = p->llink;//go left
			}

			else 
			{
				p = p->rlink;//go right
			}	
		}
	return trace;
}

// Function Name: getPreRoot(node_entry item)
// Purpose:	 find parent of the lowest out of balance node in tree (on same path as inserted item)
// Parameters: node_entry
// Returns:	  Node*
// Pre-conditions: none	
// Post-conditions: none
Node* Tree::getPreRoot(node_entry item)

{
	bfactor();
	Node *trace, *p, *q, *follower;
	int leftHeight, rightHeight;
	leftHeight = height(root->llink);
	rightHeight = height(root->rlink);
	p = root;
	q = NULL;
	follower = NULL;
	trace = NULL;
	while (p != NULL && p->entry != item)
	{
		
		if (p->bf < -1 || p->bf > 1)
		{
			follower = q;
			trace = p;
		}
		if (item < p->entry)
		{
			q = p;
			p = p->llink;//go left
		}

		else
		{
			q = p;
			p = p->rlink;//go right
		}

	}
	if (follower == root && (max(leftHeight,rightHeight) < 3))//if height of longest branch < 3 and follower is same as root, then follower has to be NULL (main root needs to be adjusted)
	{
		follower = NULL;
	}
	return follower;
}

// Function Name: height(Node * p)
// Purpose:	 find height
// Parameters: Node*
// Returns:	  node_entry
// Pre-conditions: none	
// Post-conditions: none
node_entry Tree::height(Node * p)
{
	if (p == NULL)
	{
		return 0;
	}
	if ((p->llink == NULL) && (p->rlink == NULL))
	{
		return 1;
	}
	return 1 + max(height(p->llink), height(p->rlink));
}

// Function Name: balfactor(Node * p)
// Purpose:	 update balance factor of each node
// Parameters: Node*
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: each Node BF is updated
void Tree::balfactor(Node * p)
{
	if (p != NULL)
	{
		p->bf = height(p->llink) - height(p->rlink);
		balfactor(p->llink); 
		balfactor(p->rlink);
	
	}
}

// Function Name: max(node_entry a, node_entry b)
// Purpose:	 find greatest value
// Parameters: node_entry
// Returns:	  node_entry
// Pre-conditions: none	
// Post-conditions: none
node_entry Tree::max(node_entry a, node_entry b)
{
	int m = a; 
	if (b > a) m = b; 
	return m;
}

// Function Name: inOrderTraversal(Node * p)
// Purpose:	traverse tree and output data in order
// Parameters: Node*
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: none
void Tree::inOrderTraversal(Node * p)
{
	if (p != NULL)
	{			
		inOrderTraversal(p->llink);
		cout << "\n" << p->entry;
		inOrderTraversal(p->rlink);
		
	}
}

// Function Name: rightRotate(Node *&root)
// Purpose: perform right rotation on node
// Parameters: Node*&
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: updated root with correct node, updated balance factor
void Tree::rightRotate(Node *&root)
{
	Node *node1 = root->llink;
	Node *temp = node1->rlink;
	node1->rlink = root;//begin rotation
	root->llink = temp;
	root = node1;
	bfactor();
}

// Function Name: leftRotate(Node *&root)
// Purpose: perform left rotation on node
// Parameters: Node*&
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: updated root with correct node, updated balance factor
void Tree::leftRotate(Node *&root)
{
	Node *node1 = root->rlink;
	Node *temp = node1->llink;
	node1->llink = root;
	root->rlink = temp;
	root = node1;
	bfactor();
}

// Function Name: push(Node* p)
// Purpose: push node onto stack
// Parameters: Node*
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: node is pushed on stack
void Tree::push(Node* p)
{
	Node* nNode = new Node(p);
	if (top == NULL)
	{
		top = nNode;
	}
	else
	{
		nNode->rlink = top;
		top = nNode;
	}
}

// Function Name: pop()
// Purpose: remove top node from stack
// Parameters: void
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: node on top of stack is removed
void Tree::pop()
{
	if (top != NULL)
	{
	
		Node *p;
		p = top;
		top = top->rlink;
		delete p;

	}
}

// Function Name: preOrderTraversal(Node* root)
// Purpose: display value of nodes of tree in pre-order format
// Parameters: Node*
// Returns:	  void
// Pre-conditions: none	
// Post-conditions: display value of nodes of tree in pre-order format
void Tree::preOrderTraversal(Node* root)
{
	Node *p = root;
  loop:while(p != NULL)
	{
		 cout <<"\n"<< p->entry;
		 push(p);//push on stack
		 p = p->llink;
	}

	   if(!empty())
	   {
		   p = getTop();
		   pop();
		   p = p->rlink;
		   goto loop;
	   }
}

// Function Name: empty()
// Purpose: check if stack is empty
// Parameters: void
// Returns:	  bool
// Pre-conditions: none	
// Post-conditions:none
bool Tree::empty()
{
	if (top == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Function Name: empty()
// Purpose: check if stack is empty
// Parameters: void
// Returns:	  bool
// Pre-conditions: none	
// Post-conditions:none
void Tree::testOrder(Node* p)
{
	if (p != NULL)
	{
		cout << "\n" << p->entry;
		testOrder(p->llink);
		
		testOrder(p->rlink);

	}
}

// Function Name: treeDelete(Node* root)
// Purpose: delete all nodes in tree
// Parameters: Node*
// Returns:	  void
// Pre-conditions: none	
// Post-conditions:all nodes in tree are deleted
void Tree::treeDelete(Node* root)
{
	if (root != NULL)
	{
		treeDelete(root->llink);
		treeDelete(root->rlink);
		delete root;
	}
	root = NULL;
}

// Function Name: stackDelete()
// Purpose: delete all nodes in stack
// Parameters: void
// Returns:	  void
// Pre-conditions: none	
// Post-conditions:all nodes in stack are deleted
void Tree::stackDelete()
{
	
		while (top != NULL)
		{
			Node *p;
			p = top;
			top = top->rlink;
			delete p;
		}
}

// Function Name: setRootNULL()
// Purpose: set root to NULL
// Parameters: void
// Returns:	  void
// Pre-conditions: none	
// Post-conditions:root is NULL
void Tree::setRootNULL()
{
	root = NULL;
}
