#pragma once


struct ListNode
{
	int m_nKey;
	ListNode* m_pNext;
	ListNode(int val, ListNode* pNode)
		:m_nKey(val), m_pNext(pNode)
	{}
};
/*
37：>两个链表公共节点

首先 获取两个链表长度，差值为x，长的先走x步；两个同时走，第一个公共节点即是

O(m+n)
*/



int GetLength(ListNode* pHead)
{
	if (pHead == NULL)
		exit(1);
	int count = 0;
	ListNode* tmp = pHead;
	while (tmp)
	{
		++count;
		tmp = tmp->m_pNext;
	}
	return count;
}

ListNode* FindCommNode(ListNode* pHead1, ListNode* pHead2)
{
	int len1 = GetLength(pHead1);
	int len2 = GetLength(pHead2);

	int Dif = len1 - len2;

	ListNode* pLong = pHead1;
	ListNode* pShort = pHead2;

	if (len2 > len1)
	{
		Dif = len2 - len1;
		pLong = pHead2;
		pShort = pHead1;
	}

	for (int i = 0; i < Dif; ++i)
		pLong = pLong->m_pNext;

	while (pLong && pShort && pLong != pShort)
	{
		pLong = pLong->m_pNext;
		pShort = pShort->m_pNext;
	}

	ListNode* pComm = pLong;
	return pLong;
}

/*
38  :>数字（重复且连续）在排序数组中出现的次数
{1,2,3,3,3,3,4,5}   3出现4次

遍历一遍O(n)
更优解：
归并查找第一个3，位置first；最后一个3，位置last
个数 last-first+1
O(lg^n)
*/

int GetNumFirstPos(int* ar, int len, int start, int end, int k);
int GetNumlastPos(int* ar, int len, int start, int end, int k);

int GetNumTimes(int* ar, int len, int k)
{
	if (ar == NULL || k <= 0)
		return 0;

	int times = 0;

	int first = GetNumFirstPos(ar, len, 0, len - 1, k);
	int last = GetNumlastPos(ar, len, 0, len - 1, k);

	if (first > -1 && last > -1)
		times = last - first + 1;
	return times;
}

int GetNumFirstPos(int* ar, int len, int start, int end, int k)
{
	if (start > end)
		return -1;
	int midPos = (end + start) / 2;
	int midData = ar[midPos];

	if (midData == k)
	{
		if ((midPos>0 && ar[midPos - 1] != k) || midPos == 0)
			return midPos;
		else
			end = midPos - 1;
	}
	else if (midData > k)
		end = midPos - 1;
	else
		start = midPos + 1;

	return  GetNumFirstPos(ar, len, start, end, k);
}

int  GetNumlastPos(int* ar, int len, int start, int end, int k)
{
	if (start > end)
		return -1;
	int midPos = (end + start) / 2;
	int midData = ar[midPos];

	if (midData == k)
	{
		if ((midPos < len - 1 && ar[midPos + 1] != k) || midPos == len - 1)
			return midPos;
		else
			start = midPos + 1;
	}
	else if (midData < k)
		start = midPos + 1;
	else
		end = midPos - 1;

	return  GetNumlastPos(ar, len, start, end, k);
}

/*
39:> 二叉树的深度
*/
struct BinTree
{
	int val;
	BinTree* m_pLeft;
	BinTree* m_pRight;

};

int Depth(BinTree* pRoot)
{
	if (pRoot == NULL)
		return 0;
	int nLeft = Depth(pRoot->m_pLeft);
	int nRight = Depth(pRoot->m_pRight);

	return (nLeft > nRight) ? (nLeft + 1) : (nRight + 1);
}
/*
判断是不是平衡二叉树
（每个节点遍历一遍的解法）
即，遍历当前结点前，其左右子树已经遍历并确定了深度
*/

bool IsBalanced(BinTree* pRoot, int *depth);

bool IsBalanced(BinTree* pRoot)
{
	int depth = 0;
	return IsBalanced(pRoot, &depth);
}

bool IsBalanced(BinTree* pRoot, int *depth)
{
	if (pRoot == NULL)
	{
		*depth = 0;
		return true;
	}

	int left = 0;
	int right = 0;

	if (IsBalanced(pRoot->m_pLeft, &left)
		&& IsBalanced(pRoot->m_pRight, &right))
	{
		int dif = left - right;
		if (dif <= 1 || dif >= -1)
		{
			*depth = left > right ? (left + 1) : (right + 1);
			return true;
		}
	}
	return false;
}

/*
40:>    数组中只出现一次的数（2个）（其他都出现2次）  时间：O(n)，空间O(1)
异或
{2,4,3,6,3,2,5,5}
第一次异或 即4^6->0010
用0010把数组分成两部分{2,3,6,2,3},{4,5,5}
	找到0010最小不为0的比特位，是第二位。
	利用 ar[i]的第二位 == 0x1? 来分隔数组
*/

//获取两个出现一次数的异或结果
int _res(int ar[], int len)
{
	int res = 0;
	for (int i = 0; i < len; ++i)
		res ^= ar[i];
	return res;
}

void FindOnlyAppearOnce(int ar[], int len, int* num1, int* num2)
{
	if (ar == NULL || len < 2)
		return;
	int res = _res(ar, len);

	int countBit = 0;
	while ((res & 0x1) == 0)
	{
		res >>= 1;
		++countBit;
	}

	*num1 = 0;
	*num2 = 0;
	for (int i = 0; i < len; ++i)
	{
		int tmp = ar[i];
		if (((tmp >>= countBit) & 1) == 1)
			*num1 ^= ar[i];
		else
			*num2 ^= ar[i];
	}

	cout << *num1 << endl;
	cout << *num2 << endl;
}


/*
41：和为s的两个数 ； 和为s的连续正整数序列
{1，2，4，7，11，15}  求和为15的两个数(头尾指针)
*/
bool FindTwoNumOfSum(int ar[], int len, int sum, int *num1, int *num2)
{
	bool flag = false;

	if (ar == NULL || len <= 0 || num1 == NULL || num2 == NULL)
		return flag;

	int head = 0;
	int tail = len - 1;
	while (head < tail)
	{
		int curSum = ar[head] + ar[tail];
		if (curSum == sum)
		{
			*num1 = ar[head];
			*num2 = ar[tail];
			flag = true;
			break;
		}
		else if (curSum>sum)
			tail--;
		else
			head++;
	}
	return flag;
}

/*
打印和为n的序列
1+2+3+4+5=4+5+6=7+8=15
打印 1~5，4~6，7~8
*/
void printSeq(int small, int big)
{
	for (int i = small; i <= big; ++i)
		cout << i << " ";
	cout << endl;
}

void FindSeqOfSum(int sum)
{
	if (sum < 3)
		return;

	int small = 1;
	int big = 2;
	int times = (sum + 1) / 2; //small big两个数  只用增加到sum的一半
	int curSum = small + big;

	while (small < times)
	{
		if (curSum == sum)
			printSeq(small, big);
		while (curSum > sum && small < times)
		{
			curSum -= small;
			small++;

			if (curSum == sum)
				printSeq(small, big);
		}

		big++;
		curSum += big;
	}
}

/*
42:> 翻转句子 ； 左旋字符串
i am student -> student am i (整体翻转，局部翻转)
*/


void Reserve(char* pBegin, char* pEnd)
{
	if (pBegin == NULL || pEnd == NULL || pBegin + 1 == pEnd)
		return;
	while (pBegin < pEnd)
	{
		std::swap(*pBegin, *pEnd);
		pBegin++;
		pEnd--;
	}
}

void ReserveSentense(char* pData)
{
	if (pData == NULL)
		return;
	char* pBegin = pData;
	char* pEnd = pBegin;
	while (*pEnd != '\0')
		pEnd++;
	pEnd--;  //指向尾

	Reserve(pBegin, pEnd);//整体翻转

	pEnd = pBegin = pData;
	while (*pBegin != '\0')
	{
		if (*pBegin == ' ')
		{
			pBegin++;
			pEnd++;
		}
		else if (*pEnd == ' ' || *pEnd == '\0')
		{
			Reserve(pBegin, --pEnd);
			pBegin = ++pEnd;
		}
		else
			++pEnd;
	}
}


/*
左旋单词
abcdefg ->2 -> cdefgab
分两部分 ab cdefg
整体翻转 部分翻转
*/
void LeftRotateStr(char*pStr, int n)
{
	if (pStr == NULL || n <= 0)
		return;
	int len = strlen(pStr);
	n %= len;//大于长度会指向非法内存

	char* pFirstStart = pStr;
	char* pFirstEnd = pStr + n - 1;
	char* pSecondStart = pStr + n;
	char* pSecondEnd = pStr + len - 1;

	Reserve(pFirstStart, pFirstEnd);
	Reserve(pSecondStart, pSecondEnd);
	Reserve(pFirstStart, pSecondEnd);
}


/*
45:> 约瑟夫环
*/

//数学解法
int LastLive(size_t total, size_t key)
{
	if (total < 1 || key < 1)
		return -1;

	int last = 0;
	for (int i = 2; i <= total; ++i)
		last = (last + key) % i;

	return last;
}



/*
	46.	1~n求和	
	不能使用 * / for while if else switch case 以及三目运算符 

	思路：利用虚函数的特性
	让 n==0 和 n!=0时，有不同的调用
*/
class A;
A* Array[2];

class A
{
public:
	virtual size_t sum(size_t n)
	{
		return 0;
	}
};

class B:public A
{
public:
	virtual size_t sum(size_t n)
	{
		return Array[!!n]->sum(n - 1) + n;
	}
};

int SumRes(size_t n)
{
	A a;
	B b;
	Array[0] = &a;
	Array[1] = &b;

	size_t res = Array[1]->sum(n);

	return res;
}

/*
	47.不用 + - * / 做加法
	位运算：
*/

int Add(int num1, int num2)
{
	int sum, cur;
	do 
	{
		if (num1 == 0)
		{
			num1 = num2;
			break;
		}
		sum = num1^num2;		//异或 找出对应位置不同
		cur = (num1&num2) << 1;		//对应位置相同且为一，说明要进位

		num1 = sum;
		num2 = cur;
	} while (num2 != 0);

		return num1;
}

/*
	48.不能被继承的类
*/

template<class T>
class MakeSealed
{
	friend T;			//实例化后，友元身份，访问不会出错
private:
	MakeSealed() {};
	~MakeSealed() {};
};

class SealedClass :virtual public MakeSealed<SealedClass>	//该类不能被继承
{
public:
	SealedClass() {}
	~SealedClass() {}
};

class Try :public SealedClass
{
public:
	Try() {};
	~Try() {};
};

/********** 部分测试用例 ******************/
void TestAdd()
{
	cout << Add(6, 2) << endl;
}

void TestLastLive()
{
  cout <<"live is:> "<< LastLive(10, 3) << endl;
}

void TestReserveSentense()
{
  //char ar[] = "i am a student";
  char ar[] = "                                i am a student";
  ReserveSentense(ar);
  cout << ar /*<< endl*/;
}

void TestLeftRotateStr()
{
  char ar[] = "i am a student";
  
  LeftRotateStr(ar,15);
  cout << ar << endl;
}

void TestFindSeqOfSum()
{
  FindSeqOfSum(15);
}

void TestFindOnlyAppearOnce()
{
  int ar[8] = { 2,4,3,6,3,2,5,5 };
  int num1;
  int num2;
  FindOnlyAppearOnce(ar, 8,&num1,&num2);
}
