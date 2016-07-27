#pragma once

struct Node
{
	int key;
	Node* next;
	Node(int nKey, Node* pNext)
		: key(nKey)
		, next(pNext)
	{}
};

void show(Node* pBeign)
{
	Node* cur = pBeign;
	while (cur)
	{
		cout << cur->key << " ";
		cur = cur->next;
	}
	cout << endl;
}

/*
15.链表的倒数第k个节点
*/

Node* _FindTailKpos(Node* pBegin, size_t K)
{
	if (pBegin == NULL || K == 0)
	{
		cout << "error argc! proc will exit" << endl;		//参数出错
		exit(1);
	}	

	Node* fast = pBegin;
	Node* slow = pBegin;

	size_t num = K;
	while (--num)
	{
		if (fast->next)
			fast = fast->next;
		else
		{
			cout << "K too big" << endl;
			exit(2);
		}
	}

	while (fast->next)
	{
		fast = fast->next;
		slow = slow->next;
	}
	return slow;
}


/*
	16.逆置单链表
*/

void Reverse(Node* &pBegin)
{
	if (pBegin == NULL || pBegin->next == NULL)
		return;

	Node* newHead = pBegin;
	Node* SubHead = pBegin->next;

	newHead->next = NULL;
	while (SubHead)
	{
		Node* Ins = SubHead;
		SubHead = SubHead->next;

		Ins->next = pBegin;
		pBegin = Ins;
	}
}


/*
	17.合并两个有序链表
*/

Node* MergeTwoList(Node* pBegin1, Node* pBegin2)
{
	if (pBegin1 == NULL || pBegin1 == NULL)
		return pBegin1 == NULL ? pBegin2 : pBegin1;

	Node* newHead = pBegin1;
	if (pBegin1->key > pBegin2->key)
	{
		newHead = pBegin2;
		newHead->next = MergeTwoList(pBegin1, pBegin2->next);
	}
	else
		newHead->next = MergeTwoList(pBegin1->next, pBegin2);
	return newHead;
}



struct BinTree
{
	int m_nValue;
	BinTree* m_pLeft;
	BinTree* m_pRight;
	BinTree(int x) :
		m_nValue(x), m_pLeft(NULL), m_pRight(NULL)
	{}
	BinTree(int x,BinTree* l,BinTree* r) :
		m_nValue(x), m_pLeft(l), m_pRight(r)
	{}
};

/*
	18.树的子结构
*/
bool DoseTree1HasTree2(BinTree* root1, BinTree* root2)
{
	if (root2 == NULL)
		return true;
	if (root1 == NULL)
		return false;
	if (root1->m_nValue != root2->m_nValue)
		return false;

	return DoseTree1HasTree2(root1->m_pLeft, root2->m_pLeft) 
		&& DoseTree1HasTree2(root1->m_pRight, root2->m_pRight);
}

bool HasSubTree(BinTree* root1, BinTree* root2)
{
	bool res = false;

	if (root1 != NULL && root2 != NULL)
	{
		if (root1->m_nValue == root2->m_nValue)
			res = DoseTree1HasTree2(root1, root2);			//如果值相等 先从当前结点判断
		if (!res)
			res = HasSubTree(root1->m_pLeft, root2);		//没有，递归判断 左树
		if (!res)
			res = HasSubTree(root1->m_pLeft, root2);		//右树
	}
	return res;
}

/*
	19.二叉树的镜像
*/
void MirrorTree(BinTree*& pNode)
{
	if (pNode == NULL)
		return;
	if (pNode->m_pLeft == NULL && pNode->m_pRight==NULL)
		return;

	BinTree* pTmp = pNode->m_pLeft;
	pNode->m_pLeft = pNode->m_pRight;
	pNode->m_pRight = pTmp;

	if (pNode->m_pLeft)
		MirrorTree(pNode->m_pLeft);
	if (pNode->m_pRight)
		MirrorTree(pNode->m_pRight);
}

/*
	20.顺序打印矩阵
*/
void printMatrix(vector<vector<int> > matrix)
{
	vector<int>res;
	res.clear();

	int row = matrix.size();		//行数
	int col = matrix[0].size();		//列数

	int circle = ((row < col ? row : col) - 1) / 2 + 1;//圈数
	cout << "circle:>	" <<circle <<endl;
	for (int start = 0; start <= circle; ++start)
	{
		//左->右
		for (int i = start; i < col-start; ++i)
			res.push_back(matrix[start][i]);
		//上->下
		for (int i = start + 1; i < row - start; ++i)
			res.push_back(matrix[i][col -start-1]);
		//右->左
		for (int i = col - start - 2; (i >= start) && (start * 2 + 1 < row); --i)
			res.push_back(matrix[row - start - 1][i]);
		//下->上
		for (int i = row - start - 2; (i > start) && (start * 2 + 1 < col); --i)
			res.push_back(matrix[i][start]);
	}
	for (size_t i = 0; i < res.size(); ++i)
		cout << res[i] << " ";
	cout << endl;
}


/*
	包含min的栈
*/

template<class T>
class MinStack
{
public:
	T& Min()
	{
		if (_min.empty() || _stack.empty())
			exit(1);
		return _min.top();
	}
	void Pop()
	{
		if (_stack.empty() || _min.empty())
			return;

		_stack.pop();
		_min.pop();
	}

	void Push(const T& val)
	{
		if (_stack.empty() || val<=_min.top())
			_min.push(val);
		else
			_min.push(_min.top());
		_stack.push(val);
	}
private:
	stack<T> _stack;
	stack<T> _min;
};

/************************************************************************/
/* 部分测试用例如下                                                     */
/************************************************************************/
void TestFindTailKpos()
{
	/*4 2 3 5 7 9 0 1*/
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);

	show(a);
	cout << endl;


	Node*cur = _FindTailKpos(a, 4);
	//cout << "倒数第4个：》 " << cur->key << endl;

	//cur = _FindTailKpos(a, 1);
	//cout << "倒数第1个：》 " << cur->key << endl;

	//cur = _FindTailKpos(a, 0);
	//cout << "倒数第0个：》 " << cur->key << endl;

	cur = _FindTailKpos(a, 8);
	cout << "倒数第8个：》 " << cur->key << endl;

	cur = _FindTailKpos(a, 9);
	cout << "倒数第9个：》 " << cur->key << endl;
	cout << endl;
}

void TestReverse()
{
	/*4 2 3 5 7 9 0 1*/
	Node *h = new Node(1, NULL);
	Node *g = new Node(0, h);
	Node *f = new Node(9, g);
	Node *e = new Node(7, f);

	Node *d = new Node(5, e);
	Node *c = new Node(3, d);
	Node *b = new Node(2, c);
	Node *a = new Node(4, b);

	show(a);
	Reverse(a);
	show(a);

}

void TestMergeTwoList()
{
	Node *i = new Node(9, NULL);
	Node *h = new Node(7, i);
	Node *g = new Node(5, h);
	Node *f = new Node(3, g);
	Node *e = new Node(1, f);

	Node *d = new Node(6, NULL);
	Node *c = new Node(4, d);
	Node *b = new Node(2, c);
	Node *a = new Node(0, b);

	show(a);
	cout << endl;

	show(e);
	cout << endl;

	Node*NewHead = MergeTwoList(a, e);
	show(NewHead);
	cout << endl;
}

void TestPrintMatrix()
{
	vector<vector<int> >matrix;

	int ar1[4] = { 1,2,3,4 };
	vector<int>temp1(ar1,ar1+4);

	int ar2[4] = { 5,6,7,8 };
	vector<int>temp2(ar2, ar2 + 4);

	int ar3[4] = { 9,10,11,12 };
	vector<int>temp3(ar3, ar3 + 4);

	int ar4[4] = { 13,14,15,16 };
	vector<int>temp4(ar4, ar4 + 4);

	int ar5[4] = { 17,18,19,20 };
	vector<int>temp5(ar5, ar5 + 4);

	matrix.push_back(temp1);
	matrix.push_back(temp2);
	matrix.push_back(temp3);
	matrix.push_back(temp4);
	matrix.push_back(temp5);

	printMatrix(matrix);
	
}
