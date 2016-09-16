#pragma once

/*
	22.栈的压入弹出顺序
	push: 1 2 3 4 5
	pop : 4 5 3 2 1 √
	pop	: 4 3 5 2 1 ×
*/

template<class T>
bool stackPopOrder(vector<T> push, vector<T> pop)
{
	if (push.empty() || pop.empty())
		exit(1);
	vector<T>_stack;
	_stack.clear();
	
	for (size_t i = 0, j = 0; i < push.size();)
	{
		_stack.push_back(push[i++]);
		while (j<pop.size() && _stack.back() == pop[j])
		{
			_stack.pop_back();
			++j;
		}
	}

	return _stack.empty();
}


/*
	23.层序遍历二叉树
*/
struct BinTree
{
	int _data;
	BinTree* _left;
	BinTree* _right;
	BinTree(int data=0, BinTree* l=NULL, BinTree* r=NULL)
		:_data(data)
		, _left(l)
		, _right(r)
	{}
};


void printTree(BinTree* &pRoot)
{
	if (pRoot == NULL)
		return;

	queue<BinTree*> myQueue;
	myQueue.push(pRoot);

	while (!myQueue.empty())
	{
		BinTree* cur = myQueue.front();
		cout << cur->_data << " ";
		myQueue.pop();

		if (cur->_left)
			myQueue.push(cur->_left);
		if (cur->_right)
			myQueue.push(cur->_right);
	}
}

/*
	24.二叉搜索树后序遍历
	输入一个数组判断是不是BST的后续遍历

	思路：
	若正确，该数组的最后一个元素是 root节点
	前面的元素被分为两部分，一部分小于root（左子树）
	另一部分大于root（右子树）
	
	递归判断左右
*/

bool lastOrderOfBST(int ar[], int len)
{
	if (ar == NULL || len <= 0)
		return false;

	int root = ar[len - 1];

	int leftEndIndex = 0;
	for (; leftEndIndex < len - 1; ++leftEndIndex)
		if (ar[leftEndIndex]>root)
			break;

	int rightEndIndex = leftEndIndex;
	for (; rightEndIndex < len - 1; ++rightEndIndex)	//右区间元素小于root非法
		if (ar[rightEndIndex] < root)
			return false;

	bool leftRes = true;
	bool rightRes = true;

	if (leftEndIndex > 0)
		leftRes = lastOrderOfBST(ar, leftEndIndex);
	if (leftEndIndex < len - 1)
		rightRes = lastOrderOfBST(ar+leftEndIndex,len-1-leftEndIndex);

	return leftRes && rightRes;
}

/*
	25.打印二叉树中和为指定值的路径

*/

vector<vector<int> >res;
vector<int> tmp;

void find(BinTree* node, int expectNumber)
{
	//如果是叶子节点，或差值等于当前结点值，push到二维数组
	tmp.push_back(node->_data);
	if (expectNumber - node->_data == 0 && !node->_left && !node->_right) 
		res.push_back(tmp);

	else 
	{
		if (node->_left)find(node->_left, expectNumber - node->_data);
		if (node->_right)find(node->_right, expectNumber - node->_data);
	}
	tmp.pop_back(); //不合法，将当前结点的值减去
}

vector<vector<int> > FindPath(BinTree* root, int expectNumber)
{
	if (root) find(root, expectNumber);
	return res;
}

/*
	26.
	复杂链表的复制
	每个节点有两人指针域：
	pNext指向下一个节点
	pSibling指向随机节点

	思路：
	1.在原节点后复制克隆节点（复制pNext）
	2.复制pSibling
	3.断开连接，返回新节点的头部
*/
struct ComplexListNode
{
	int			_data;
	ComplexListNode*	_pNext;
	ComplexListNode*	_pSlibling;

	ComplexListNode(int data = 0, ComplexListNode* n = NULL, ComplexListNode* s = NULL)
		:_data(data)
		, _pNext(n)
		, _pSlibling(s)
	{}
};


void cloneNext(ComplexListNode* &pHead)
{
	if (pHead == NULL)
		return;
	ComplexListNode* pCur = pHead;
	while (pCur)
	{
		ComplexListNode* pIns = new ComplexListNode(pCur->_data, pCur->_pNext, NULL);

		pCur->_pNext = pIns;
		pCur = pIns->_pNext;
	}
}


void cloneSlibling(ComplexListNode* &pHead)
{
	ComplexListNode* pCur = pHead;
	while (pCur)
	{
		ComplexListNode* pClone = pCur->_pNext;

		if (pCur->_pSlibling != NULL)
			pClone->_pSlibling = pClone->_pSlibling->_pNext;

		pCur = pClone->_pNext;
	}
}


ComplexListNode* disConnection(ComplexListNode* &pHead)
{
	ComplexListNode* pCur = pHead;
	ComplexListNode* newHead = NULL;
	ComplexListNode* pClone = NULL;

	if(NULL != pCur)
	{
		newHead = pClone = pCur->_pNext;
		pCur->_pNext = pClone->_pNext;		//当前结点的next指向克隆节点的next
		pCur = pCur->_pNext;
	}

	while (pCur)
	{
		pClone->_pNext = pCur->_pNext;
		pClone = pClone->_pNext;
		pCur->_pNext = pClone->_pNext;
		pCur = pCur->_pNext;
	}
	return newHead;
}

/*
	27.BST转有序双向链表
	思路： 某节点的left作为前驱指针，指向左树中最大的节点
				   right作为后继指针，指向右树中最小的节点
	struct BinTree
	{
	int _data;
	BinTree* _left;
	BinTree* _right;
	}
*/

BinTree* IsSmall(BinTree* &pNode)
{
	if (pNode == NULL)
		exit(1);
	BinTree* pSmall = pNode;
	while (pSmall->_left)
		pSmall = pSmall->_left;

	return pSmall;
}

BinTree* IsBig(BinTree* &pNode)
{
	if (pNode == NULL)
		exit(1);
	BinTree* pBig = pNode;
	while (pBig->_right)
		pBig = pBig->_right;

	return pBig;
}

void ConverTree(BinTree* &pRoot)
{
	if (pRoot == NULL)
		return;
	BinTree* pL = pRoot->_left;
	BinTree* pR = pRoot->_right;
	if (pL && pL->_right != pRoot)
	{
		pRoot->_left = IsBig(pL);
		pRoot->_left->_right = pRoot;
		ConverTree(pL);
	}
	if (pR && pR->_left!=pRoot)
	{
		pRoot->_right = IsSmall(pR);
		pRoot->_right->_left = pRoot;
		ConverTree(pR);
	}
}

BinTree* Conver(BinTree* &pRoot)
{
	BinTree* ListHead = IsSmall(pRoot);
	ConverTree(pRoot);
	return ListHead;
}

/*
	28.字符串排列
	a b c:>
	abc acb bac bca cab cba
*/
void Permutation(char* pStr, char* pBegin)
{
	if (*pBegin == '\0')
		cout << pStr << endl;
	else
	{
		for (char* pCur = pBegin; *pCur != '\0'; ++pCur)
		{
			swap(*pCur, *pBegin);

			Permutation(pStr,pBegin+1);

			swap(*pCur, *pBegin);
		}
	}
}

void Permutation(char* str)
{
	if (str == NULL)
		return;
	Permutation(str, str);
}
/*********************** 部分测试用例 ******************************/

void Test()
{
	BinTree* root = new BinTree(8, NULL, NULL);

	root->_left = new BinTree(6, NULL, NULL);
	root->_right = new BinTree(10, NULL, NULL);

	root->_left->_left = new BinTree(5, NULL, NULL);
	root->_left->_right = new BinTree(7, NULL, NULL);

	root->_right->_left = new BinTree(9, NULL, NULL);
	root->_right->_right = new BinTree(11, NULL, NULL);

	vector<vector<int> > test = FindPath(root, 21);

	for (size_t i = 0; i < test.size(); ++i)
	{
		for (size_t j = 0; j < test[i].size(); ++j)
			cout << test[i][j] << " ";
		cout << endl;
	}
}

void TestPermutation()
{
	char ar[4] = { 'a','b','c' };
	Permutation(ar);
}

void TestConver()
{
	BinTree* root = new BinTree(8,NULL,NULL);

	root->_left = new BinTree(6, NULL, NULL);
	root->_right = new BinTree(10,NULL, NULL);

	root->_left->_left = new BinTree(5, NULL, NULL);
	root->_left->_right = new BinTree(7, NULL, NULL);

	root->_right->_left = new BinTree(9, NULL, NULL);
	root->_right->_right = new BinTree(11, NULL, NULL);

	BinTree* newHead = Conver(root);
	while (newHead)
	{
		cout << newHead->_data << " ";
		newHead = newHead->_right;
	}
	cout << endl;
}

void TeststackPopOrder()
{
	int ar[5] = { 1,2,3,4,5 };
	//int br[5] = { 4,5,3,2,1 };
	int br[5] = { 4,3,5,1,2 };
	

	vector<int>push(ar, ar + 5);
	vector<int>pop(br, br + 5);

	cout << stackPopOrder(push, pop) << endl;
}

void TestlastOrderOfBST()
{
	//int ar[7] = { 5,7,6,9,11,10,8 };
	int ar[7] = { 7,5,6,9,11,10,8 };
	cout << lastOrderOfBST(ar, 7) << endl;
}
