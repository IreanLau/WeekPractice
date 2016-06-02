#pragma once


/*
	51.�������ظ�����
	���� N�� ����������0~n-1�ķ�Χ��

	˼·��
	��ǰλ�õ����ֺ��±겻һ��
	������Ӧ�±��������

	ʱ��O(n) �ռ�O(1)
*/

bool duplicate(int num[], int len, int* duplication)
{
	if (num == NULL || len <= 0)
		return false;

	for (int i = 0; i < len; ++i)
	{
		if (num[i]<0 || num[i]>len - 1)
			return false;
	}

	for (int i = 0; i < len; ++i)
	{
		while (num[i] != i)				//������ѭ������ÿ������ཻ�����Ρ�����O��n��
		{
			if (num[i] == num[num[i]])
			{
				*duplication = num[i];
				return true;
			}

			std::swap(num[i],num[num[i]]);
		}
	}
	return false;
}

/*
	52.�˻�����
*/

void multiply(vector<double>& array1, vector<double>& array2)
{
	int len1 = array1.size();
	int len2 = array2.size();

	if (len1 == len2 && len2 > 1)
	{
		array2[0] = 1;
		for (int i = 1; i < len1; ++i)
			array2[i] = array2[i - 1] * array1[i - 1];

		double temp = 1;
		for (int i = len1 - 2; i >= 0; --i)
		{
			temp *= array1[i + 1];
			array2[i] *= temp;
		}
	}
}


/*
	53.������ʽƥ��
	'.'��������һ���ַ�
	'*'��ʾ��ǰ����ַ����Գ���һ�λ���

	���磺aaa �� a.a �� ab*ac*a ƥ��
*/

bool matchCore(char* str, char* pattern)
{
	if (*str == '\0' && *pattern == '\0')
		return true;
	if (*str != '\0' && *pattern == '\0')
		return false;

	// '*'
	if (*(pattern + 1) == '*')
	{
		if (*pattern == *str || (*pattern == '.' && *str != '\0'))
			return matchCore(str + 1, pattern + 2)   //����һ���ַ�ƥ��ʱ��ģʽ�����ƶ�������Ҳ���Բ���
			|| matchCore(str + 1, pattern)			//.����ǰһ���ַ���*������ֲ�ֹ1��
			|| matchCore(str, pattern + 2);

		else    //'*'����֮ǰ���ַ�����0��
			return matchCore(str, pattern + 2);
	}

	//ƥ�� �� '.'
	if (*str == *pattern || (*pattern == '.' && *str != '\0'))
		return matchCore(str + 1, pattern + 1);

	
	return false;
}

bool match(char* str, char* pattern)
{
	if (str == NULL || pattern == NULL)
		return false;
	return matchCore(str,pattern);
}


/*
	54.��ʾ��ֵ���ַ�
*/

//ͳ��0~9����λ
void scanDigits(char** string)
{
	while (**string != '\0' && **string >= '0' && **string <= '9')
		++(*string);
}

bool isExponential(char** string)
{
	if (**string != 'e' && **string != 'E')
		return false;

	++(*string);
	if (**string == '+' || *string == '-')
		++(*string);

	if (**string == '\0')
		return false;

	scanDigits(string);
	
	return (**string == '\0') ? true : false;
}


bool isNumeric(char* string)
{
	if (string == NULL)
		return false;

	if (*string == '+' || *string == '-')
		++string;
	if (*string == '\0')
		return false;

	bool numeric = true;

	scanDigits(&string);

	if (*string != '\0')
	{
		if (*string == '.')
		{
			++string;
			scanDigits(&string);
			if (*string == 'e' || *string == 'E')
				numeric = isExponential(&string);
		}
		else if (*string == 'e' || *string == 'E')
			numeric = isExponential(&string);
		else
			numeric = false;
	}
	return numeric && *string == '\0';
}

/*
	56.�����������ڽڵ�
*/

struct ListNode
{
	int val;
	struct ListNode* next;
	ListNode(int v = 0, ListNode* n = NULL)
		:val(v), next(n)
	{}
};

ListNode* findMeetingNode(ListNode* pHead)
{
	if (pHead == NULL)
		exit(1);

	ListNode *pSlow = pHead->next;
	if (pSlow == NULL)
		return NULL;

	ListNode* pFast = pSlow->next;
	while (pFast && pSlow)
	{
		if (pFast == pSlow)
			return pFast;

		pSlow = pSlow->next;

		pFast = pFast = next;
		if(pFast!=NULL)
			pFast = pFast = next;
	}
	return NULL;
}

//ͨ�������ڵ�����ڽڵ�
ListNode* EntryNode(ListNode* pHead)
{
	ListNode* meetingNode = findMeetingNode(pHead);
	if (meetingNode == NULL)
		return NULL;

	int Count = 1; //��¼����
	ListNode* pCount = meetingNode;
	while (pCount->next != meetingNode)
	{
		pCount = pCount->next;
		++Count;
	}

	pCount = pHead;
	for (int i = 0; i < Count; ++i)
		pCount = pCount->next;

	ListNode* pEntry = pHead;
	while (pCount != pEntry)
	{
		pCount = pCount->next;
		pEntry = pEntry->next;
	}
	return pEntry;
}

/*
	57.ɾ���������ظ��Ľڵ㣨ָ���������ڵ��ֵ��ͬ��
*/
void deleteDuplication(ListNode** pHead)	//ͷ�ڵ�Ҳ���ܱ�ɾ��
{
	if (pHead == NULL || *pHead == NULL)
		return;

	ListNode* pPreNode = NULL;
	ListNode* pNode = *pHead;
	while (pNode != NULL)
	{
		ListNode* pNext = pNode->next;
		bool needDelete = false;

		if (pNext != NULL && pNext->val == pNode->val)
			needDelete = true;

		if (!needDelete)		//����Ҫɾ������������
		{
			pPreNode = pNode;
			pNode = pNode->next;
		}
		else
		{
			int value = pNode->val;
			ListNode* pToBeDel = pNode;
			while (pToBeDel != NULL && pToBeDel->val == value)
			{
				pNext = pToBeDel->val;

				delete pToBeDel;
				pToBeDel = NULL;

				pToBeDel = pNext;
			}

			if (pPreNode == NULL)
				*pHead = pNext;
			else
				pPreNode->next = pNext;
			pNode = pNext;
		}
	}
}


/*
	58.����������һ���ڵ�
	���� ���ڵ�
*/
struct BinTree
{
	int _data;
	BinTree* _left;
	BinTree* _right;
	BinTree* _parent;
	BinTree(int data = 0, BinTree* l = NULL, BinTree* r = NULL, BinTree* p = NULL)
		:_data(data)
		, _left(l)
		, _right(r)
		,_parent(p)
	{}
};

/*
	��3�������
	cur�Ǹ��ڵ������������������������������ڵ�

	cur��leftʱ����������ĸ��ڵ�
	curû������	�����磺cur�����������ұߣ������root��
	���cur���ϱ�����while(cur==dad->right)
	ѭ�������ҵ�
*/

BinTree* GetNextOfInOrder(BinTree* pNode)
{
	if (pNode == NULL)
		return NULL;

	BinTree* pNext = NULL;
	if (pNode->_right != NULL)
	{
		BinTree* pRright = pNode->_right;
		while (pRright->_left)
			pRright = pRright->_left;

		pNext = pRright;
	}
	else if (pNode->_parent != NULL)
	{
		BinTree* pCur = pNode;
		BinTree* pParent = pNode->_parent;
		while (pParent != NULL && pCur == pParent->_right)
		{
			pCur = pParent;
			pParent = pParent->_parent;
		}
		pNext = pParent;
	}
	return pNext;
}


/*
	59.�������ĶԳƣ����ң�
	˼·��
	ָ���µı�����ʽ��
	��->��->��
	�볣���������ͬ ��Գ�
*/
bool isSymmetrical(BinTree* pRoot)
{
	return isSymmetrical(pRoot, pRoot);
}

bool isSymmetrical(BinTree* pRoot1, BinTree* pRoot2)
{
	if (pRoot1 == NULL && pRoot2 == NULL)
		return true;
	if (pRoot1 == NULL || pRoot2 == NULL)
		return false;
	if (pRoot1->val != pRoot2->val)
		return false;

	return isSymmetrical(pRoot1->_left, pRoot2->_right)
		&& isSymmetrical(pRoot1->_right, pRoot2->_left);
}

/**************** ���ֲ������� **********************/

void Test(char* testName, char* string, char* pattern, bool expected)
{
	if (testName != NULL)
		printf("%s begins: ", testName);

	if (match(string, pattern) == expected)
		cout<<"Passed."<<endl;
	else
		cout << "FAILED." << endl;
}

void TestMatch()
{
	Test("Test01", "", "", true);
	Test("Test02", "", ".*", true);
	Test("Test03", "", ".", false);
	Test("Test04", "", "c*", true);
	Test("Test05", "a", ".*", true);
	Test("Test06", "a", "a.", false);
	Test("Test07", "a", "", false);
	Test("Test08", "a", ".", true);
	Test("Test09", "a", "ab*", true);
	Test("Test10", "a", "ab*a", false);
	Test("Test11", "aa", "aa", true);
	Test("Test12", "aa", "a*", true);
	Test("Test13", "aa", ".*", true);
	Test("Test14", "aa", ".", false);
	Test("Test15", "ab", ".*", true);
	Test("Test16", "ab", ".*", true);
	Test("Test17", "aaa", "aa*", true);
	Test("Test18", "aaa", "aa.a", false);
	Test("Test19", "aaa", "a.a", true);
	Test("Test20", "aaa", ".a", false);
	Test("Test21", "aaa", "a*a", true);
	Test("Test22", "aaa", "ab*a", false);
	Test("Test23", "aaa", "ab*ac*a", true);
	Test("Test24", "aaa", "ab*a*c*a", true);
	Test("Test25", "aaa", ".*", true);
	Test("Test26", "aab", "c*a*b", true);
	Test("Test27", "aaca", "ab*a*c*a", true);
	Test("Test28", "aaba", "ab*a*c*a", false);
	Test("Test29", "bbbba", ".*a*a", true);
	Test("Test30", "bcbbabab", ".*a*a", false);

}

