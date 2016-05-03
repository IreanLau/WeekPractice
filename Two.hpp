#pragma once

/*
	8.
	��ת�������Сֵ  O(logn)

	{3,4,5,2,1}  :> 1
	{1,0,1,1,1}  :>	0
*/


int FindMinInRetationArray(int _array[], int len)
{
	if (_array == NULL || len <= 0)
	{
		cout << "invalid input" << endl;
		exit(1);
	}

	int left = 0;
	int right = len - 1;
	int mid = left;

	//left > right ˵�� ���龭����ת�󣬲�����ȫ���� ��1,2,3,4,5��
	while (_array[left] >= _array[right])
	{
		if (left + 1 == right)
		{
			mid = right;
			break;
		}

		mid = left + (right - left) / 2;

		if (_array[left] == _array[mid] && _array[mid] == _array[right])	//������־λ��ͬ��˳�����
		{
			int res = _array[left];
			for (int i = left + 1; i <= right; ++i)
			{
				if (_array[i] < res)
					res = _array[i];
			}
			return res;
		}

		if (_array[mid] >= _array[left])
			left = mid;
		else if (_array[mid] <= _array[right])
			right = mid;
	}
	return _array[mid];
}

void TestFindMinInRetationArray()
{
	int array[] = { 3,4,5,1,2 };
	//int array[] = { 1,0,1,1,1 };
	//int *array = NULL;

	cout << FindMinInRetationArray(array, 5)<<endl;
}


/*
	9.
	쳲���������
*/

//�ݹ�

long long Fibonacci(size_t n)
{
	if (n <= 0)
		return 0;
	if (n == 1)
		return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}


//�ǵݹ�  �������ε���
long long _Fibonacci(size_t n)
{
	int res[2] = { 0,1 };
	int index1 = res[0];
	int index2 = res[1];
	int index3 = 0;

	if (n < 2)
		return res[n];

	for (size_t i = 2; i <= n; ++i)
	{
		index3 = index1 + index2;
		index1 = index2;
		index2 = index3;
	}
	return index3;
}


void TestFibonacci()
{
	cout << _Fibonacci(1) << endl;
	cout << _Fibonacci(2) << endl;
	cout << _Fibonacci(3) << endl;
	cout << _Fibonacci(6) << endl;
	cout << _Fibonacci(8) << endl;
}


/*
	10.
	�������� 1 �ĸ���
*/
int CountOfBinary(int val)
{
	int count = 0;
	while (val)
	{
		val &= (val-1);
		++count;
	}
	return count;
}



/* 
	11.��ֵ�������η� O(logn)
*/
/*
	base^n	=	base^(n/2) * base^(n/2)			nż��
	base^n	=	base^(n/2) * base^(n/2) * base	n����
*/
double Power(double base, int exponent)
{
	if (0 == exponent)
		return 1;
	if (1 == exponent)
		return base;
	bool flag = true;					//��־λ���б�����
	if (exponent < 0)
	{
		exponent *= -1;
		flag = false;
	}

	double res = Power(base, exponent >> 1);
	res *= res;
	if ( (exponent & 0x1) == 1)				//�������������ٳ�base
		res *= base;

	if (!flag)				
		return 1 / res;  
	return res;
}

void TestPower()
{
	cout << Power(2,3) << endl;
	cout << Power(-2,3) << endl;
	cout << Power(2, -3) << endl;
	cout << Power(-2, -3) << endl;
}


/*
	12.
	��ӡ 1������nλ��
	����3 ����ӡ 1��2��3 ���� 999
*/
//�ݹ��дȫ���� ����

void PrintMaxNum(char* number,size_t n, size_t index);

void PrintMaxNum(size_t n)
{
	char* number = new char[n + 1];
	number[n] = '\0';

	for (size_t i = 0; i < 10;++i)
	{
		number[0] = i + '0';
		PrintMaxNum(number, n, 0);
	}
	delete []number;
}

//���� �� ȫ��������ǰ�� ���õ�'0'
void printNum(char* num)
{
	bool flag = false;			//Ĭ�ϣ���'0',�ǺϷ����
	int len = strlen(num);

	for (int i = 0; i < len; ++i)
	{
		if (!flag && num[i] != '0')
			flag = true;

		if (flag)
			cout << num[i];
	}
	cout << endl;
}

void PrintMaxNum(char* number, size_t n, size_t index)
{
	if (index == n - 1)
	{
		printNum(number);
		return;
	}

	for (size_t i = 0; i < 10;++i)
	{
		number[index+1] = i + '0';
		PrintMaxNum(number, n, index + 1);
	}
}


void TestPrintMaxNum()
{
	//PrintMaxNum(1);
	//PrintMaxNum(2);
	PrintMaxNum(3);
}



/*
	13.
	O(1)��ɾ���ڵ�����
*/
struct ListNode
{
	int			m_nValue;
	ListNode*	m_pNext;
	ListNode(int val = 0, ListNode* next = NULL)
		:m_nValue(val)
		, m_pNext(next)
	{}
};

//	ʱ�临�Ӷ�	=[(n-1)+n]/n=O(1)

void DeleteNode(ListNode* &pHead, ListNode* pDel)
{
	assert(pDel&&pHead);

	if (pDel->m_pNext != NULL)					//��β�ڵ�
	{
		ListNode* _Pnext = pDel->m_pNext;
		pDel->m_nValue = _Pnext->m_nValue;
		pDel->m_pNext = _Pnext->m_pNext;

		delete(_Pnext);
		_Pnext = NULL;
	}
	else if (pHead == pDel)						//ͷ�ڵ�
	{
		delete pDel;
		pHead = NULL;
		pDel = NULL;
	}
	else										//β�ڵ�
	{	
		ListNode* pCur = pHead;
		while (pCur->m_pNext != pDel)
			pCur = pCur->m_pNext;

		pCur->m_pNext = NULL;
		delete pDel;
		pDel = NULL;
	}
}


void ListPrint(ListNode* pHead)
{
	ListNode* pCur = pHead;
	while (pCur)
	{
		cout << pCur->m_nValue << " ";
		pCur = pCur->m_pNext;
	}
	cout << endl;
}

void TestDeleteNode()
{
	/*4 2 3 5 7 9 0 1*/
	ListNode *h = new ListNode(1, NULL);
	ListNode *g = new ListNode(0, h);
	ListNode *f = new ListNode(9, g);
	ListNode *e = new ListNode(7, f);

	ListNode *d = new ListNode(5, e);
	ListNode *c = new ListNode(3, d);
	ListNode *b = new ListNode(2, c);
	ListNode *a = new ListNode(4, b);


	//DeleteNode(a,NULL);


	//DeleteNode(a,g);
	//DeleteNode(a,h);
	DeleteNode(a, a);

	ListPrint(a);
}



/*
	14.
	�������飬������λ��ż��ǰ��
*/

void changeOrder(int* array, size_t len)
{
	if (array == NULL || len <= 0)
		return;

	int* left = array;
	int* right = array + len - 1;

	while (left < right)
	{
		while (left < right && (*left & 0x1) == 1)
			++left;
		while (left < right && (*right & 0x1) == 0)
			--right;
		if (left < right)
			std::swap(*left,*right);
	}
}


void TestchangeOrder()
{
	int array[5] = {1,2,3,4,5};

	changeOrder(array, 5);
	for (int i = 0; i < 5; ++i)
		cout << array[i]<<" ";
	cout << endl;
}