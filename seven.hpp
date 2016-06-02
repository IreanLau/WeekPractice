#pragma once


/*
	51.数组中重复的数
	长度 N， 所有数都在0~n-1的范围内

	思路：
	当前位置的数字和下标不一样
	则，与相应下标的数交换

	时间O(n) 空间O(1)
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
		while (num[i] != i)				//有两重循环，但每个数最多交换两次。总体O（n）
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
	52.乘积数组
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
	53.正则表达式匹配
	'.'代表任意一个字符
	'*'表示它前面的字符可以出现一次或多次

	例如：aaa 与 a.a 和 ab*ac*a 匹配
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
			return matchCore(str + 1, pattern + 2)   //当第一个字符匹配时，模式可以移动两个，也可以不变
			|| matchCore(str + 1, pattern)			//.代表前一个字符，*代表出现不止1次
			|| matchCore(str, pattern + 2);

		else    //'*'代表之前的字符出现0次
			return matchCore(str, pattern + 2);
	}

	//匹配 或 '.'
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
	54.表示数值的字符
*/

//统计0~9的数位
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
	56.带环链表的入口节点
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

//通过相遇节点找入口节点
ListNode* EntryNode(ListNode* pHead)
{
	ListNode* meetingNode = findMeetingNode(pHead);
	if (meetingNode == NULL)
		return NULL;

	int Count = 1; //记录环长
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
	57.删除链表中重复的节点（指相邻两个节点的值相同）
*/
void deleteDuplication(ListNode** pHead)	//头节点也可能被删除
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

		if (!needDelete)		//不需要删除，则向后遍历
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
	58.二叉树的下一个节点
	包含 父节点
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
	分3种情况：
	cur是父节点且有右子树，后继是右子树的最左节点

	cur是left时，后继是它的父节点
	cur没有右树	（例如：cur是左数的最右边，后继是root）
	则从cur向上遍历，while(cur==dad->right)
	循环结束找到
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
	59.二叉树的对称（左右）
	思路：
	指定新的遍历方式：
	右->中->左
	与常规的中序相同 则对称
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

/**************** 部分测试用例 **********************/

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

