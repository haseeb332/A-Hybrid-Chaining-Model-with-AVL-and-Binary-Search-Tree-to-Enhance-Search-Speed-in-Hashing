#include "graphics.h"
#include<iostream>
using namespace std;
class TreeNode {
public:
	int val;
	TreeNode* left, * right;
};

class BST {
public:
	TreeNode* bstRoot;
	int SpacesDefined;
	BST() {
		bstRoot = NULL;
		SpacesDefined = 0;
	}

	void bstinsert(int data)
	{
		TreeNode* n = new TreeNode;
		n->val = data;
		n->left = n->right = NULL;
		if (bstRoot == NULL) { bstRoot = n; }
		else {
			TreeNode* curr = bstRoot;
			while (1) {
				if (data < curr->val) {
					if (curr->left != NULL) { curr = curr->left; }
					else { curr->left = n; break; }
				}
				else  (data > curr->val) {
					if (curr->right != NULL) { curr = curr->right; }
					else { curr->right = n; break; }
				}
				
			}
		}
	}

	TreeNode* search(int key)
	{
		TreeNode* cr = bstRoot;

		while (cr != NULL && cr->val != key) {
			if (key == cr->val)
			{
				return cr;
			}
			else if (key > cr->val) {
				cr = cr->right;
			}
			else {
				cr = cr->left;
			}
		}
		return NULL;
	}

	void Display(TreeNode* p)
	{
		if (p != NULL) {
			cout << " " << p->val;
			Display(p->left);
			Display(p->right);
		}
	}

	int Height(TreeNode* p)
	{
		int left, right;
		if (p == NULL) {
			return -1;
		}
		else {
			left = Height(p->left);
			right = Height(p->right);

			if (left > right) {
				return left + 1;
			}
			else { return right + 1; }
		}

	}
	int total_leaf(TreeNode* temp)
	{

		if (temp == NULL) {
			return 0;
		}
		if (temp->left == NULL && temp->right == NULL) {
			return 1;
		}
		else {
			return total_leaf(temp->left) + total_leaf(temp->right);
		}
	}



	void findMax()
	{
		TreeNode* temp = bstRoot;
		while (temp->right != NULL) {
			temp = temp->right;
		}
		cout << "Max: " << temp->val;
	}
	void findMin()
	{
		TreeNode* temp = bstRoot;
		while (temp->left != NULL) {
			temp = temp->left;
		}
		cout << "Min: " << temp->val;
	}
};
class Node
{
public:
	int data;
	Node* left, * right;
	BST BT;
};

class AVL
{
public:
	Node* root;
	int count;
	AVL()
	{
		root = NULL;
		count = 0;
	}

	void insert(int data)
	{
		Node* NewNode = new Node();
		NewNode->data = data % 10;
		if (!root)
		{
			root = NewNode;
			root->BT.bstinsert(data);
		}
		else
		{
			Node* CurrentNode = root;
			while (true)
			{
				if (NewNode->data < CurrentNode->data)
				{
					if (CurrentNode->left)
					{
						CurrentNode = CurrentNode->left;
					}
					else
					{
						CurrentNode->left = NewNode;
						CurrentNode->left->BT.bstinsert(data);
						break;
					}
				}
				else if (NewNode->data > CurrentNode->data)
				{
					if (CurrentNode->right)
					{
						CurrentNode = CurrentNode->right;
					}
					else
					{
						CurrentNode->right = NewNode;
						CurrentNode->right->BT.bstinsert(data);
						break;
					}
				}
				else
				{
					CurrentNode->BT.bstinsert(data);
					break;
				}
			}
		}
		doing_AVL(root);
	}

	TreeNode* search(int key)
	{
		Node* CurrentNode = root;
		int CurrentKey = key % 10;
		if (!CurrentNode)
		{
			return NULL;
		}
		while (CurrentNode)
		{
			if (CurrentNode->data == CurrentKey)
			{
				return CurrentNode->BT.bstRoot;

			}
			else if (CurrentNode->data < CurrentKey)
			{
				CurrentNode = CurrentNode->right;
			}
			else
			{
				CurrentNode = CurrentNode->left;
			}
		}
		return NULL;
	}




	void leftRotate(Node*& p)
	{
		Node* T1 = p->right;
		Node* T2 = T1->left;

		//Perform rotation
		T1->left = p;
		p->right = T2;

		p = T1;
	}
	void rightRotate(Node*& p)
	{
		Node* T1 = p->left;
		Node* T2 = T1->right;

		//Perform rotation
		T1->right = p;
		p->left = T2;

		p = T1;
	}
	int Height(Node* p) {
		int left, right;
		if (p == NULL) {
			return -1;
		}
		else {
			left = Height(p->left);
			right = Height(p->right);

			if (left > right) {
				return left + 1;
			}
			else { return right + 1; }
		}

	}

	int BalanceFactor(Node* p)
	{
		if (p == NULL) { return 0; }
		return Height(p->left) - Height(p->right);
	}
	void doing_AVL(Node*& p)
	{

		int balance_factr;
		if (p != NULL) {
			doing_AVL(p->left);
			doing_AVL(p->right);
			balance_factr = BalanceFactor(p);

			if (balance_factr > 1) {
				if (BalanceFactor(p->left) > 0) {
					rightRotate(p);
				}
				else {
					leftRotate(p->left);
					rightRotate(p);
				}
			}

			else if (balance_factr < -1) {
				if (BalanceFactor(p->right) < 0) {
					leftRotate(p);
				}
				else {
					rightRotate(p->right);
					leftRotate(p);
				}
			}
		}
	}
};

void Drawing_AVL(Node* root,
	int a, int b,
	int noderatio)
{

	setcolor(15);
	circle(a, b, 25);
	setcolor(14);
	setfillstyle(SOLID_FILL, 14);
	floodfill(a, b, WHITE);

	char arr[5];
	itoa(root->data, arr, 10);
	outtextxy(a, b, arr);

	if (root->left != NULL) {
		setcolor(15);
		line(a, b, a - 20 * noderatio, b + 70);
		Drawing_AVL(root->left, a - 20 * noderatio, b + 70,
			noderatio - 2);
	}
	if (root->right != NULL) {
		setcolor(15);
		line(a, b, a + 20 * noderatio, b + 70);
		Drawing_AVL(root->right, a + 20 * noderatio, b + 70,
			noderatio - 2);
	}
}
void Drawing_BST(TreeNode* root,
	int c, int d,
	int noderatio)
{

	setcolor(15);
	circle(c, d, 25);
	setcolor(14);
	setfillstyle(SOLID_FILL, 14);
	floodfill(c, d, WHITE);

	char arr[5];
	itoa(root->val, arr, 10);
	outtextxy(c, d, arr);

	if (root->left != NULL) {
		setcolor(15);
		line(c, d, c - 20 * noderatio, d + 70);
		Drawing_BST(root->left, c - 20 * noderatio, d + 70,
			noderatio - 2);
	}
	if (root->right != NULL) {
		setcolor(15);
		line(c, d, c + 20 * noderatio, d + 70);
		Drawing_BST(root->right, c + 20 * noderatio, d + 70,
			noderatio - 2);
	}
}
void function_of_menu()
{
	setcolor(14);
	outtextxy(10, 10, "ADD");
	rectangle(50, 10, 200, 30);
	outtextxy(220, 10, "Find");
	rectangle(270, 10, 420, 30);
	outtextxy(500, 10, "Stop");
	rectangle(490, 10, 540, 30);

}

int main(void)

{
	AVL obj;
	initwindow(950, 650, "HAshingTable");
	function_of_menu();
	while (1)
	{
		while (!ismouseclick(WM_LBUTTONDOWN)) {}
		int x, y;
		char a;
		char arr[2];
		getmouseclick(WM_LBUTTONDOWN, x, y);
		if (x >= 50 && x <= 200 && y >= 10 && y <= 30)
		{
			outtextxy(53, 12, "_");
			string s;
			int variable = 51, data;
			setcolor(14);
			while (1)
			{
				a = getch();

				if (a >= '0' && a <= '9')
				{
					s.push_back(a);
					arr[0] = a;
					arr[1] = NULL;
					outtextxy(variable, 11, arr);
					variable = variable + 8;
				}
				else if (a == 8)
				{
					s.pop_back();
					variable = variable - 8;
					outtextxy(variable, 11, "  ");
				}
				else if (a == 13)
				{
					outtextxy(51, 11, "                                     ");
					data = stoi(s);
					obj.insert(data);
					setcolor(14);
					outtextxy(80, 60, "AVL:");
					Drawing_AVL(obj.root, 500, 100, 8);
					delay(500);
					cleardevice();
					function_of_menu();
					TreeNode* BT = obj.search(data);
					setcolor(14);
					outtextxy(80, 60, "BST:");
					Drawing_BST(obj.search(data), 500, 100, 8);
					delay(500);
					cleardevice();
					function_of_menu();
					setcolor(14);
					outtextxy(80, 60, "AVL:");
					Drawing_AVL(obj.root, 500, 100, 8);
					break;

				}
			}
		}
		else if (x >= 270 && x <= 420 && y >= 10 && y <= 30)
		{
			outtextxy(273, 12, "_");
			string s_1;
			int variable_1 = 271, data_1;
			setcolor(14);
			while (1)
			{

				a = getch();
				if (a >= '0' && a <= '9')
				{
					s_1.push_back(a);
					arr[0] = a;
					arr[1] = NULL;
					outtextxy(variable_1, 11, arr);
					variable_1 = variable_1 + 8;
				}
				else if (a == 8)
				{
					s_1.pop_back();
					variable_1 = variable_1 - 8;
					outtextxy(variable_1, 11, "  ");
				}
				else if (a == 13)
				{
					outtextxy(271, 11, "                                     ");
					data_1 = stoi(s_1);
					if (obj.search(data_1) != NULL)
					{
						Drawing_AVL(obj.root, 500, 100, 8);
						TreeNode* BT = obj.search(data_1);
						delay(500);
						cleardevice();
						function_of_menu();
						Drawing_BST(obj.search(data_1), 500, 100, 8);
						outtextxy(500, 400, "Value Founded");
						getch();
						cleardevice();
						function_of_menu();
					}
					else
					{
						outtextxy(500, 400, "Value Not Founded");
					}



					break;

				}
			}
		}
		else if (x >= 490 && x <= 540 && y >= 10 && y <= 30)
		{
			closegraph();
			break;
		}


	}
	return 0;
}
