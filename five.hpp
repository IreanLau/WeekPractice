#pragma once


/*
面试中遇到的一道题：

判断一个正常字符串是否匹配一个表达式字符串
, 表达式字符串里的*含义比较特殊，
*匹配任意数目字符(包括零个字符)。
比如aa1123ddef匹配 aa*123*def。
bool isMatch(const char* regular,const char* dest);
参数说明：regular为表达式字符串，dest为正常字符串。返回值：
匹配返回ture，不匹配返回false。

思路： 借助KMP 算法，
如果： 被‘*’分割开的部分，都是目标串的字串
即可
*/



/*KMP*/
void getNext(char* p, int *next)
{
	next[0] = -1;
	int slow = -1;
	int fast = 0;

	while (fast < strlen(p) - 1)		//下标0已经使用
	{
		if (slow == -1 || p[slow] == p[fast])
		{
			++slow;
			++fast;

			next[fast] = slow;
		}
		else
			slow = next[slow];
	}
}

int KMP(char* s, char* p)
{
	if (s == NULL || p == NULL)
		return -1;
	if (s != NULL && *p == '\0')
		return 0;

	int next[100];
	int i = 0;
	int j = 0;
	getNext(p, next);

	while (i < strlen(s))
	{
		if (j == -1 || s[i] == p[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];

		if (j == strlen(p))
			return i - strlen(p);
	}
	return -1;
}


//aa1123ddef	匹配	aa*123*def。
/*
aa 在 aa1123ddef中匹配后
123 在 1123ddef匹配
*/
bool isMatch(const char* regular, const char* dest)
{
	char *pBeginOfDest = (char*)dest;
	char* pBegin = (char*)regular;
	char* pEnd = (char*)regular;

	int flag = 0;
	int subLen = 0;
	while (*pEnd != '\0')
	{
		char tmp[50];
		memset(tmp, '\0', sizeof(tmp));
		while (*pEnd != '*' && *pEnd != '\0')
			++pEnd;
		strncpy(tmp, pBegin, pEnd - pBegin);

		pBeginOfDest += (flag + subLen);
		flag = KMP(pBeginOfDest, tmp);
		subLen = pEnd - pBegin;

		if (flag == -1)
			return false;

		pBegin = ++pEnd;
	}
	return true;
}


/*
	29.数组中超过一半的数

	常规解法：
	排序，返回数组中间的数

	1 2 3 3 4 3 2 3 3 
	O（n） 计数： 相同+1，不同-1  
*/

bool check(int ar[], int len, int num)
{
	int count = 0;
	for (int i = 0; i < len; ++i)
	{
		if (ar[i] == num)
			count++;
	}
	return (count * 2) > len;
}

int MoreThanHalfNum(int ar[],int len)
{
	if (ar == NULL || len <= 0)
		exit(1);

	int count = 1;
	int cur = ar[0];

	for (int i = 0; i < len; ++i)
	{
		if (count == 0)
		{
			cur = ar[i];
			count = 1;
		}
		else if (ar[i] == cur)
			++count;
		else
			--count;
	}
	if (!check(ar, len, cur))
		exit(2);
	return cur;
}

/*
	30.最小的k个数
	O(n)的解法： 利用快排的partion函数分隔
	但不一定有序	而且改变原有数组
*/
int partion(int* ar,  int begin, int end)
{
	int target = ar[begin];
	while (begin<end)
	{
		while (begin<end && ar[end]>target)
			--end;
		if (begin < end)
		{
			ar[begin] = ar[end];
			++begin;
		}

		while (begin < end && ar[begin] < target)
			++begin;
		if (begin < end)
		{
			ar[end] = ar[begin];
			--end;
		}
	}
	ar[begin] = target;
	return begin;
}

void getLeastNum(int* input, int len, int* output, int k)
{
	if (input == NULL || output == NULL || len <= 0 || k <= 0 || k > len)
		return;

	int begin = 0;
	int end = len - 1;

	int part = partion(input,begin,end);			//返回分隔的下标
	while (part != k - 1)
	{
		if (part > k - 1)
		{
			end = part - 1;
			part = partion(input,begin,end);
		}
		else
		{
			begin = part + 1;
			part = partion(input,begin,end);
		}
	}
	for (int i = 0; i < k; ++i)
		output[i] = input[i];
}

/*		解法2 利用 冒泡的思想 O(n*k),改变数组	*/

vector<int> getLeastNumWithBubble(vector<int>input, int k)
{
	if (input.empty() || k>input.size())
		exit(1);

	vector<int>res;
	for (int i = 0; i < k; ++i)
	{
		for (int j = i + 1; j < input.size(); ++j)
			if (input[i] > input[j])
				std::swap(input[i],input[j]);

		res.push_back(input[i]);
	}
	return res;
}
/*
	解法3：
		最大堆：O(nlg^n)	不会改变原有数组，适合海量数据处理
		这里利用 set，但是 set会去重复，使用multiset解决
*/
vector<int> getLeastNumWithHeap(vector<int>input, int k)
{
	if (input.empty() || k>input.size())
		exit(1);

	multiset<int> Tree;
	vector<int> res;
	for (int i = 0; i < input.size(); ++i)
		Tree.insert(input[i]);

	multiset<int>::iterator it = Tree.begin();
	int i = 0;
	for (; i<k; ++i,++it)
		res.push_back(*it);

	return res;
}

/*
	31.连续子数组最大和
	1，-2，3，10，-4，7，2，-5
*/
int GetSum(int *ar, int len)
{
	return 0;
}

/*

*/

/************** 部分测试用例  **************************/
void TsetgetLeastNum()
{
	int ar[11] = {8,5,9,34,7,2,5,57,7,90,3};
	int br[10] = { 0 };

	//getLeastNum(ar, 11, br, 4);
	vector<int>arV(ar,ar+11);
	//vector<int>brV = getLeastNumWithHeap(arV, 4);
	vector<int>brV = getLeastNumWithBubble(arV, 4);
	for (int i = 0; i < brV.size(); ++i)
		cout << brV[i] << " ";
	cout << endl;
}

void TestMoreThanHalfNum()
{
	int _array[9] = { 1 ,2 ,3 ,3 ,4 ,3 ,2 ,3 ,3 };
	int res = MoreThanHalfNum(_array,9) ;
	cout << res << endl;
}

void TestIsMatch()
{
	//const char* regular = "aa*123*def";
	//const char* regular = "aa*23*def";
	//const char* regular = "aa*3*def";
	//const char* regular = "aa*def";

	//const char* regular = "aa*123*def";
	//const char* regular = "a*f";
	const char* regular = "a*";
	//const char* regular = "*";

	const char* dest = "aa12123ddef";

	cout << isMatch(regular, dest) << endl;
}