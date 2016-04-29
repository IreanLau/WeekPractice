#pragma once
#include <assert.h>

#include <stack>
#include <vector>


/*
	����ջʵ��һ�����У�
	appendTail
	deleteHead
*/

template<class T>
class QueMadeOfStack
{
public:
	void appendTail(const T& val) 
	{
		_stack1.push(val);
	}

	void deleteHead()
	{
		if (_stack2.empty())
		{
			while (!_stack1.empty())
			{
				T& tmp = _stack1.top();
				_stack1.pop();
				_stack2.push(tmp);
			}
		}
		if (_stack2.empty())
		{
			cout << "QueQue empty!" << endl;
			return;
		}

		_stack2.pop();
	}
public:
	stack<T> _stack1;		//�����Ƚ���_stack1
	stack<T> _stack2;		//_stack2��Ϊ�����ռ�ʹ��	
};

void TestQueMadeOfStack()
{
	QueMadeOfStack<int> _queue;

	//_queue.deleteHead();    //���Կյ�ʱ��ͷ��ɾ��
	_queue.appendTail(1);
	_queue.appendTail(2);
	_queue.appendTail(3);

	_queue.deleteHead();
}

/*
	CMyString�࣬��Ӹ�ֵ�����
*/

class CMyString
{
public:
	CMyString(const char *data = "")
		:_ptr(new char[strlen(data) + 1])
	{
		strcpy(_ptr, data);
	}

	~CMyString()
	{
		if (_ptr)
			delete[]_ptr;
	}

	//�����ռ�Ŀ������� �� ��ֵ�����
	CMyString(const CMyString& rhs)  
		:_ptr(NULL)						 //û����֮ǰ��ptr��ֵΪ���ֵ�� ������,�������ֵ�ǲ������
	{
		CMyString tmp(rhs._ptr);
		std::swap(tmp._ptr,_ptr);
	}

	CMyString& operator=(CMyString rhs)	//��������ֵ�����������ã���ӵ��ÿ�������
	{
		std::swap(_ptr, rhs._ptr);
		return *this;
	}

	friend ostream& operator<<(ostream& out, const CMyString& s)
	{
		assert(s._ptr);
		out << s._ptr;
		return out;
	}
	
private:
	char* _ptr;
};

void TestCMyString()
{
	CMyString S1;

	CMyString S3("SSSSS");
	CMyString S2(S3);
	CMyString S4 = S1;

	cout << S1 << endl;
	cout << S2 << endl;
	cout << S3 << endl;
	cout << S4 << endl;
}


/*
	����̰߳�ȫ�ĵ�����
*/

//����ģʽ �����Ƿ�ʹ���ڳ���ʼ����һ��ʵ���������Ժ󷵻�
//��̬ʵ����ʼ�� �ڽ���������֮ǰ���Ѿ���ɳ�ʼ��

class Singleton
{
private:
	static const Singleton* m_instance;
	Singleton() {}								
public:
	static const Singleton* GetInstance()
	{
		return m_instance;
	}
};
const Singleton*Singleton::m_instance = new Singleton;

void TestSingleTon()
{
	const Singleton* obj1=Singleton::GetInstance();
	const Singleton* obj2=Singleton::GetInstance();

	if (obj1 == obj2)
		cout << "OK" << endl;
}


/*
	��ά���� �����ҵ���
	���ϵ��� ����
	������ֵ  �ж��Ƿ����
*/
bool FindInMatrix(vector<vector<int> > array, int target)
{
	bool found = false;
	int rows = array.size();
	int cols = array[0].size();
	if (rows > 0 && cols > 0)
	{
		int row = 0;//��
		int col = cols - 1;//��
		while (row < rows && col >= 0)
		{
			if (array[row][col] == target)
			{
				found = true;
				break;
			}
			else if (array[row][col] > target)
				--col;
			else
				++row;
		}
	}
	return found;
}

void TestFindInMatrix()
{
	vector<vector<int> > array;
	int ar1[4] = { 1,2,3,4 };
	int ar2[4] = { 2,3,4,5 };
	int ar3[4] = { 3,4,5,6 };
	int ar4[4] = { 4,5,6,7 };


	vector<int>element1(ar1,ar1+4);
	array.push_back(element1);
	vector<int>element2(ar2, ar2 + 4);
	array.push_back(element2);
	vector<int>element3(ar3, ar3 + 4);
	array.push_back(element3);
	vector<int>element4(ar4, ar4 + 4);
	array.push_back(element4);


	cout << FindInMatrix(array, 6) << endl;
	cout << FindInMatrix(array, 10) << endl;
}

/*
	�ַ�����ָ���ַ��滻
	We are happy   => We%20are%20happy
*/

//�Ȼ�ȡ��Ҫ����
//�Ӻ���ǰ�ƶ� O��n��������
void BlankReplace(char _str[],int len)
{
	if (_str==NULL && len<=0)
		return;

	
	int StringLen = 0;		//	��ȡ�ַ�����Ч����
	int BlankNum = 0;
	for (int i = 0; _str[i] != '\0';++i)
	{
		++StringLen;
		if (_str[i] == ' ')
			++BlankNum;
	}

	int LenAfterReplace = StringLen + BlankNum * 2;
	if (LenAfterReplace > len)   //������Χ
		return;

	int indexOfOriginal = StringLen;
	int indexOfnew = LenAfterReplace;
	while (indexOfOriginal >= 0 && indexOfnew > indexOfOriginal)
	{
		if (_str[indexOfOriginal] == ' ')
		{
			_str[indexOfnew--] = '0';
			_str[indexOfnew--] = '2';
			_str[indexOfnew--] = '%';
		}
		else
			_str[indexOfnew--] = _str[indexOfOriginal];

		--indexOfOriginal;
	}
}

void TestBlankReplace()
{
	//char ar[20] = "We are happy";
	//char ar[20] = "";
	char ar[20] = " ";

	BlankReplace(ar, 20);
	cout << ar << endl;
}

/*
	��β��ͷ��ӡ����
*/
struct Node
{
	int key;
	Node* next;
	Node(int nKey, Node* pNext)
		: key(nKey)
		, next(pNext)
	{}
};

void ResPrint(Node* pBegin)
{
	if (pBegin == NULL)
		return;
	else
	{
		ResPrint(pBegin->next);
		cout << pBegin->key << " ";
	}
}


//��������ʱ�򣬱���ʹ�õݹ�
void _ResPrint(Node* pBegin)
{
	stack<Node*> _st;

	Node* pCur = pBegin;
	while (pCur != NULL)
	{
		_st.push(pCur);
		pCur = pCur->next;
	}

	while (!_st.empty())
	{
		pCur = _st.top();
		cout << pCur->key << " ";
		_st.pop();
	}
	cout << endl;
}


/*
	�ؽ�������
	pre  1,2,4,7,3,5,6,8
	in   4,7,2,1,5,3,8,6
*/


struct BinTree
{
	int m_nValue;
	BinTree* m_pLeft;
	BinTree* m_pRight;
	BinTree(int x) :
		m_nValue(x), m_pLeft(NULL), m_pRight(NULL)
	{}
	BinTree(int x, BinTree* l, BinTree* r) :
		m_nValue(x), m_pLeft(l), m_pRight(r)
	{}
};


/***********************************************************/
BinTree* ConstructWithPreAndIn(int* headpre, int *tailpre, int* headin, int* tailin)
{
	int rootvalue = headpre[0];
	BinTree* root = new BinTree(rootvalue);

	//�߽�
	if (headpre == tailpre)
	{
		if (headin == tailin && *headpre == *headin)	//ֻ��һ����
			return root;
		else
			throw std::exception("invalid input");
	}

	//����:> �ҵ�����λ��
	int *rootIn = headin;
	while (rootIn <= tailin && *rootIn != rootvalue)
		++rootIn;

	//�ߵ���βû�ҵ�
	if (rootIn == tailin && *rootIn != rootvalue)
		throw std::exception("invalid input");

	//�޸ĳ��ȣ�β�߽�
	int LeftLength = rootIn - headin;
	int* LeftPreorderEnd = headpre + LeftLength;

	if (LeftLength > 0)
	{
		root->m_pLeft = ConstructWithPreAndIn(headpre + 1, LeftPreorderEnd, headin, rootIn - 1);
	}
	if (LeftLength < tailpre - headpre)
	{
		root->m_pRight = ConstructWithPreAndIn(LeftPreorderEnd + 1, tailpre, rootIn + 1, tailin);
	}
	return root;
}

BinTree* Construct(int* pre, int* in, int length)
{
	if (pre == NULL || in == NULL || length <= 0)
		return NULL;

	return ConstructWithPreAndIn(pre, pre + length - 1, in, in + length - 1);
}


void TestConstruct()
{
	int pre[8] = { 1,2,4,7,3,5,6,8 };
	int in[8] = { 4,7,2,1,5,3,8,6 };

	BinTree* root = Construct(pre, in, 8);
}


