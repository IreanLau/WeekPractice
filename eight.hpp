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

void Deserialize(BinTree* pRoot, ostream& stream)
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

/**************** ���ֲ������� **********************/


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
}