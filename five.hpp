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
		最大堆：O(nlg^k)	不会改变原有数组，适合海量数据处理
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
/*O(n)*/
int GetSum(int *ar, int len)
{
	if (ar == NULL || len <= 0)
		exit(1);

	int MaxSum = 0;
	int subSum = 0;
	for (int i = 0; i < len; ++i)
	{
		if (subSum < 0)
			subSum = ar[i];
		else
			subSum += ar[i];

		if (subSum > MaxSum)
			MaxSum = subSum;
	}
	return MaxSum;
}

/*
	32. 1~n中 '1'出现的次数
*/
/*穷举法 时间复杂度仅和数字的位数有关系， O(n*log^n)*/

int numOf1(int n)
{
	int count = 0;
	while (n)
	{
		if (n % 10 == 1)
			++count;
		n /= 10;
	}
	return count;
}

int numOf1ToN(int n)
{
	int count = 0;
	for (size_t i = 1; i <= n; ++i)
		count += numOf1(i);
	return count;
}


/*
	数学证明法
	https://leetcode.com/discuss/44281/4-lines-o-log-n-c-java-python
	例如： 3141592
	分成 a:3141  b:592，此时 m=1000
	以a的最低位取值讨论  
	最低位为 0, 1 和 >=2
	0,1时 (n / m % 10 == 1) * (n%m + 1) 
				当最低位0：  592取不到
				为1：		即 1000 ~ 1592 共 (592+1)
	否则： (n / m + 8) / 10 * m
				当 m==1000时, 重复计算 以'1000'作为模式 的 [a +(最低位>=2)]次  
*/
int NumberOf1Between1AndN(int n) 
{
	int count = 0;
	for (long long m = 1; m <= n; m *= 10)
		count += (n / m + 8) / 10 * m + (n / m % 10 == 1) * (n%m + 1);
	return count;

}

/*
	33. 数组排列成最小的数：
	{3,32,321}	->	321323

	思路：转成字符串，
	假设有两个数字字符串 a,b
	比较 ab,ba的大小
	
	将vector<int>{3,32,31}
	格式化打入 vector<string>中
	利用指定的compare函数进行sort
*/
const int g_maxSize = 10;

char* g_Str1 = new char[g_maxSize * 2 + 1];
char* g_Str2 = new char[g_maxSize * 2 + 1];

static bool compare(const string& num1, const string& num2)
{
	string s1 = num1 + num2;
	string s2 = num2 + num1;

	return s1<s2;
}

void printMin(vector<int> numbers)
{
	string res;
	if (numbers.size() <= 0)
		return;

	vector<string> strNum;							//把vector<int>转化为vector<string>
	for (int i = 0; i < numbers.size(); ++i)
	{
		char* Ins =new char[g_maxSize+1];
		sprintf(Ins, "%d", numbers[i]);
		strNum.push_back(string(Ins));
	}
	sort(strNum.begin(),strNum.end(),compare);	//

	for (int i = 0; i < strNum.size(); ++i)
		cout<<strNum[i];
	cout << endl;
}


/*
	34.输出第n个丑数
	丑数（包含2,3,5因子的数）
	O(n)的解法

	1 习惯被当作第一个丑数
*/
int Min(int a, int b, int c)
{
	int tmp = (a < b) ? a : b;
	return (tmp < c) ? tmp:c;
}

int GetUglyNumber(int index)
{
	if (index <= 0)
		return 0;
	int *uglyArray = new int[index];
	uglyArray[0] = 1;
	int nextUglyIndex = 1;

	int* pMul2 = uglyArray;
	int* pMul3 = uglyArray;
	int* pMul5 = uglyArray;

	while (nextUglyIndex < index)
	{
		int min = Min(*pMul2*2,*pMul3*3,*pMul5*5);
		uglyArray[nextUglyIndex] = min;

		while (*pMul2 * 2 <= uglyArray[nextUglyIndex])
			++pMul2;
		while (*pMul3 * 3 <= uglyArray[nextUglyIndex])
			++pMul3;
		while (*pMul5 * 5 <= uglyArray[nextUglyIndex])
			++pMul5;

		++nextUglyIndex;
	}
	int ugly = uglyArray[nextUglyIndex - 1];
	delete[]uglyArray;
	return ugly;
}

/*
	35.第一个只出现一个的字符
	abaccdeff  :-> b
*/
//	abbcad 找第一个不重复(重复)的
//*/
char findFirstNoRepeat(string A, int n)
{
	vector<int> array(256, 0);

	for (int i = 0; i < n; ++i)
		array[(int)(A[i] - '0')]++;
	for (int i = 0; i < 256; ++i)
		if (array[i] == 1)
			return (i + '0');
	return	'\0';
}

char findFirstReplace(string A, int n)
{
	vector<int> array(256,0);

	for (int i = 0; i < n; ++i)
		if (array[(int)(A[i] - '0')]++ == 1)
			return A[i];
	return '\0';
}

/*
	36.数组中的逆序对
*/
/*O(n^2)的解法（冒泡）： 一旦前面的大于后面的，则计数*/
int InversePairs(vector<int> d)
{
	int r = 0;
	for (int i = 0; i < d.size(); ++i) {
		for (int j = 0; j < i; ++j) 
			if (d[j] > d[j+1]) ++r;
	}
	return r;
}

/*O(nlg^n)的归并解法*/
int InversePairs(vector<int> data) 
{
	if (data.size() <= 0)
		return 0;
	vector<int> copy;
	for (int i = 0; i < data.size(); i++)
		copy.push_back(data[i]);
	int count = InversePairsCore(data, copy, 0, data.size() - 1);
	copy.clear();
	return count;
}

int InversePairsCore(vector<int> &data, vector<int>&copy, int start, int end)
{
	if (start == end)
	{
		copy[start] = data[start];
		return 0;
	}
	int length = (end - start) / 2;
	int left = InversePairsCore(copy, data, start, start + length);
	int right = InversePairsCore(copy, data, start + length + 1, end);

	int i = start + length;
	int j = end;
	int indexCopy = end;
	int count = 0;
	while (i >= start&&j >= start + length + 1)
	{
		if (data[i] > data[j])
		{
			copy[indexCopy--] = data[i--];
			count += j - start - length;
		}

		else
			copy[indexCopy--] = data[j--];
	}
	for (; i >= start; --i)
		copy[indexCopy--] = data[i];
	for (; j >= start + length + 1; --j)
		copy[indexCopy--] = data[j];
	return left + right + count;
}



/************** 部分测试用例  **************************/
void TestNum1ToN()
{
	cout << NumberOf1Between1AndN(20) << endl;
}


void  TestPrintMin()
{
	int ar[3] = {3,23,321};
	vector<int>arV(ar,ar+3);
	printMin(arV);
}

void TestUgly()
{
	cout << GetUglyNumber(1) << endl; 
	cout << GetUglyNumber(2) << endl;
	cout << GetUglyNumber(8) << endl;
	cout << GetUglyNumber(1500) << endl;
}

void TestGetSum()
{
	int ar[] = {1,-2,3,10,-4,7,2,-5 };
	cout << GetSum(ar, 8) << endl;
}

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
