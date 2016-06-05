#pragma once

/*
	60.�Ѷ�������ӡ�ɶ���

	˼·��
	�������б��� Ԫ��
	ͬʱ��Ҫ��¼��ǰ��û�д�ӡ�Ľڵ���
	��¼��һ��ڵ�Ľڵ���Ŀ

	pCur����������к�
	queue.pop
	ͬʱ ����������¼����
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
	61.֮��״ ��ӡ������
	˼·������ջ

	�����㣺 �ȱ����� �ٱ����ҵ���һ��ջ��
	ż���㣺 �ȱ����� �ڱ����󵽵ڶ���ջ��
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
	62.���л�������
	��NULL��������ַ�����
*/

//���л�
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

//�����л�

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
	63.�����������ĵ�k��ڵ�
	˼·��
	������������ ������� �������

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
	64.�������е���λ��
	���� ���� �� ��С��
	��λ�� ��ߵ��������ݲ�������
	�ұ� ������С�� 
	��Ҫ��֤�����ѵ����ݲ����1 ���������� ż��������С���У�
	��Ҫ��֤ �� ��ѵ���������С��С�ѵ��������ݣ�
	�� ���������ѵ����� ����С�ѵ�����һ����ʱ��
	�Ȳ����ѣ�����Ѷ�����ɾ��������С�ѡ�
*/

template<typename T>
class DynamicArray
{
public:
	void insert(T num)
	{
		if (((min.size() + max.size()) & 1) == 0)  //��ż��ʱ������С��
		{
			if (max.size() > 0 && num < max[0])	//������ "С�ѵ��� �� ����еĴ�"
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
	65.�������ڵ����ֵ
	{2,3,4,2,6,2,5,1}  һ������6���������ڣ����ڴ�С3
	��  ���ֵ	{4,4,6,6,6,5}

	˼·������ deque
	2����ʱ�򣬴�����У�
	3 ��2�� ������3 ɾ��2
	4 ͬ��

	2��4С����4�������� ��2 ���п��ܳ�Ϊ������� 2 ���β������4����ͷ��
	6 �� 2��4�� ɾ�� 2��4 ����6
	2 �� 6С�����β
	5 �� 2 �󣬱�6С��ɾ�� 2 ��5 ���β
	1 ����ʱ��Ӧ��ɾ��6 

	���֪�������Ƿ�Ӧ�ð���һ������
	���� Ӧ�ô��� �±꣬�������±�Ĳ�ֵ���ڴ��ڴ�С��ɾ��֮ǰ���±�

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



/**************** ���ֲ������� **********************/



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

	Print(root);		//���ӡ
	Print_(root);		//֮ ��״��ӡ

	size_t k = 4;
	cout << KthNodeCore(root, k)->_data << endl; //������������k��
}