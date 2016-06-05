#pragma once

/*
	60.把二叉树打印成多行

	思路：
	借助队列保存 元素
	同时还要记录当前层没有打印的节点数
	记录下一层节点的节点数目

	pCur的左右入队列后
	queue.pop
	同时 更新两个记录变量
*/
struct BinTree
{
	int _data;
	BinTree* _left;
	BinTree* _right;
	BinTree(int data = 0, BinTree* l = NULL, BinTree* r = NULL)
		:_data(data)
		, _left(l)
		, _right(r)
	{}
};

void Print(BinTree* pRoot)
{
	if (pRoot == NULL)
		return;

	queue<BinTree*> nodes;
	nodes.push(pRoot);
	int nextLevel = 0;
	int toBePrint = 1;
	while (!nodes.empty())
	{
		BinTree* pNode = nodes.front();
		cout << pNode->_data << " ";

		if (pNode->_left)
		{
			nodes.push(pNode->_left);
			++nextLevel;
		}
		if (pNode->_right)
		{
			nodes.push(pNode->_right);
			++nextLevel;
		}

		nodes.pop();
		--toBePrint;

		if (toBePrint == 0)
		{
			cout << endl;
			toBePrint = nextLevel;
			nextLevel = 0;
		}

	}
}

/*
	61.之形状 打印二叉树
	思路：两个栈

	奇数层： 先保存左 再保存右到第一个栈里
	偶数层： 先保存右 在保存左到第二个栈里
*/
void Print_(BinTree* pRoot)
{
	if (pRoot == NULL)
		return;

	stack<BinTree*> levels[2];
	int cur = 0;
	int next = 1;
	
	levels[cur].push(pRoot);
	while (!levels[0].empty() || !levels[1].empty())
	{
		BinTree* pCur = levels[cur].top();
		levels[cur].pop();

		cout << pCur->_data << " ";

		if (cur == 0)
		{
			if (pCur->_left != NULL)
				levels[next].push(pCur->_left);
			if (pCur->_right != NULL)
				levels[next].push(pCur->_right);
		}
		else
		{
			if(pCur->_right!=NULL)
				levels[next].push(pCur->_right);
			if (pCur->_left != NULL)
				levels[next].push(pCur->_left);
		}
		if (levels[cur].empty())
		{
			cout << endl;
			cur = 1 - cur;
			next = 1 - next;
		}
	}
}


/*
	62.序列化二叉树
	将NULL用特殊的字符代替
*/

//序列化
void Serialize(BinTree* pRoot, ostream& stream)
{
	if (pRoot == NULL)
	{
		stream << "$,";
		return;
	}
	stream << pRoot->_data << ',';
	Serialize(pRoot->_left, stream);
	Serialize(pRoot->_right, stream);
}

//反序列化

bool ReadStream(istream& stream, int* number)
{
	if (stream.eof())
		return false;

	char buffer[32];
	buffer[0] = '\0';

	char ch;
	stream >> ch;
	int i = 0;
	while (!stream.eof() && ch != ',')
	{
		buffer[i++] = ch;
		stream >> ch;
	}

	bool isNumeric = false;
	if (i > 0 && buffer[0] != '$')
	{
		*number = atoi(buffer);
		isNumeric = true;
	}

	return isNumeric;
}

void Deserialize(BinTree** pRoot, istream& stream)
{
	int num=0;
	if (ReadStream(stream, &num))
	{
		*pRoot = new BinTree();
		(*pRoot)->_data = num;
		(*pRoot)->_left = NULL;
		(*pRoot)->_right = NULL;

		Deserialize(&((*pRoot)->_left), stream);
		Deserialize(&((*pRoot)->_right), stream);
	}


}

/*
	63.二叉搜索树的第k大节点
	思路：
	二叉搜索树的 中序遍历 是有序的

*/
BinTree* KthNodeCore(BinTree* pRoot, size_t& k);


BinTree* KthNode(BinTree* pRoot, size_t k)
{
	if (pRoot == NULL || k == 0)
		return NULL;

	return KthNodeCore(pRoot, k);
}

BinTree* KthNodeCore(BinTree* pRoot, size_t& k)
{
	BinTree* target = NULL;
	if (pRoot->_left != NULL)
		target = KthNodeCore(pRoot->_left, k);

	if (target == NULL)
	{
		if (k == 1)
			target = pRoot;
		--k;
	}
	if (target == NULL && pRoot->_left != NULL)
		target = KthNodeCore(pRoot->_right, k);
	return target;
}

/*
	64.数据流中的中位数
	利用 最大堆 和 最小堆
	中位数 左边的所有数据插入最大堆
	右边 插入最小堆 
	（要保证两个堆的数据差不大于1 数据总量是 偶数，插入小堆中，
	还要保证 ： 大堆的所有数据小于小堆的所有数据）
	当 即将插入大堆的数据 大于小堆的任意一个数时：
	先插入大堆，将大堆顶的数删除并插入小堆。
*/

template<typename T>
class DynamicArray
{
public:
	void insert(T num)
	{
		if (((min.size() + max.size()) & 1) == 0)  //当偶数时，插入小堆
		{
			if (max.size() > 0 && num < max[0])	//不满足 "小堆的数 比 大堆中的大"
			{
				max.push_back(num);
				push_heap(max.begin(),max.end(),less<T>());

				num = max[0];

				pop_heap(max.begin(), max.end(), less<T>());
				max.pop_back();
			}
			min.push_back(num);
			pop_heap(min.begin(), min.end(), greater<T>());
		}
		else
		{
			if (min.size() > 0 && num > min[0])
			{
				min.push_back(num);
				push_heap(min.begin(), min.end(), greater<T>());

				num = min[0];
				pop_heap(min.begin(), min.end(), greater<T>());
				min.pop_back();
			}
			max.push_back(num);
			pop_heap(max.begin(), max.end(), less<T>());
		}
	}

	T GetMedian()
	{
		int size = min.size() + max.size();
		if (size == 0)
		{
			cout << "no numbers,will exit" << endl;
			exit(1);
		}

		T median = 0;
		if ((size & 1) == 1)
			median = min[0];
		else
			median = (min[0] + max[0]) / 2;

		return median;
	}
private:
	vector<T> min;
	vector<T> max;
};


/*
	65.滑动窗口的最大值
	{2,3,4,2,6,2,5,1}  一共存在6个滑动窗口，窗口大小3
	则  最大值	{4,4,6,6,6,5}

	思路：利用 deque
	2来的时候，存入队列，
	3 比2大 ，存入3 删除2
	4 同上

	2比4小，当4滑出窗口 ，2 还有可能成为最大，所以 2 存队尾，最大的4还在头部
	6 比 2，4大 删除 2和4 存入6
	2 比 6小，存队尾
	5 比 2 大，比6小。删除 2 ，5 存队尾
	1 来的时候，应该删除6 

	如何知道窗口是否应该包含一个数，
	队列 应该存入 下标，当两个下标的差值大于窗口大小，删除之前的下标

*/


vector<int> maxInWindows(vector<int>& num, size_t sizeOfWindows)
{
	vector<int> maxInWindows;

	if (num.size() >= sizeOfWindows && sizeOfWindows >= 1)
	{
		deque<int> index;
		for (size_t i = 0; i < sizeOfWindows; ++i)
		{
			while (!index.empty() && num[i] >= num[index.back()])
				index.pop_back();

			index.push_back(i);
		}

		for (size_t i = sizeOfWindows; i < num.size(); ++i)
		{
			maxInWindows.push_back(num[index.front()]);

			while (!index.empty() && num[i] >= num[index.back()])
				index.pop_back();
			if (!index.empty() && index.front() <= (int)(i - sizeOfWindows))
				index.pop_front();

			index.push_back(i);
		}
		maxInWindows.push_back(num[index.front()]);
	}
	return maxInWindows;
}



/**************** 部分测试用例 **********************/



void TestMaxInWindows()
{
	int ar[8] = { 2,3,4,2,6,2,5,1 };
	vector<int>input(ar,ar+8);

	vector<int>res = maxInWindows(input, 3);
	for (vector<int>::iterator it = res.begin(); it != res.end(); ++it)
		cout << *it << " ";
	cout << endl;
}

void TestPrint()
{
	BinTree* root = new BinTree(8, NULL, NULL);

	root->_left = new BinTree(6, NULL, NULL);
	root->_right = new BinTree(10, NULL, NULL);

	root->_left->_left = new BinTree(5, NULL, NULL);
	root->_left->_right = new BinTree(7, NULL, NULL);

	root->_right->_left = new BinTree(9, NULL, NULL);
	root->_right->_right = new BinTree(11, NULL, NULL);

	Print(root);		//层打印
	Print_(root);		//之 形状打印

	size_t k = 4;
	cout << KthNodeCore(root, k)->_data << endl; //二叉搜索树第k大
}