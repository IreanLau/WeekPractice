#pragma once


/*
������������һ���⣺

�ж�һ�������ַ����Ƿ�ƥ��һ�����ʽ�ַ���
, ���ʽ�ַ������*����Ƚ����⣬
*ƥ��������Ŀ�ַ�(��������ַ�)��
����aa1123ddefƥ�� aa*123*def��
bool isMatch(const char* regular,const char* dest);
����˵����regularΪ���ʽ�ַ�����destΪ�����ַ���������ֵ��
ƥ�䷵��ture����ƥ�䷵��false��

˼·�� ����KMP �㷨��
����� ����*���ָ�Ĳ��֣�����Ŀ�괮���ִ�
����
*/



/*KMP*/
void getNext(char* p, int *next)
{
	next[0] = -1;
	int slow = -1;
	int fast = 0;

	while (fast < strlen(p) - 1)		//�±�0�Ѿ�ʹ��
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


//aa1123ddef	ƥ��	aa*123*def��
/*
aa �� aa1123ddef��ƥ���
123 �� 1123ddefƥ��
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
	29.�����г���һ�����

	����ⷨ��
	���򣬷��������м����

	1 2 3 3 4 3 2 3 3 
	O��n�� ������ ��ͬ+1����ͬ-1  
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
	30.��С��k����
	O(n)�Ľⷨ�� ���ÿ��ŵ�partion�����ָ�
	����һ������	���Ҹı�ԭ������
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

	int part = partion(input,begin,end);			//���طָ����±�
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

/*		�ⷨ2 ���� ð�ݵ�˼�� O(n*k),�ı�����	*/

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
	�ⷨ3��
		���ѣ�O(nlg^n)	����ı�ԭ�����飬�ʺϺ������ݴ���
		�������� set������ set��ȥ�ظ���ʹ��multiset���
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
	31.��������������
	1��-2��3��10��-4��7��2��-5
*/
int GetSum(int *ar, int len)
{
	return 0;
}

/*

*/

/************** ���ֲ�������  **************************/
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