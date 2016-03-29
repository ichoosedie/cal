
#include <iostream>
#include <cstdlib>
#include <ctime>
#include<math.h>

using namespace std;

// class Of Arighm
class Arighm
{
public:
	// 构造函数
	Arighm();
	// 构造函数
	~Arighm();
	// 生成含有numOfNode个运算数字的随机表达式框架
	void CreateEx(int numOfNode);
	// 给生成的表达式框架填入符合条件的随机的数字
	int Count();
	// 输出所生成的表达式
	void Display();

private:
	// 比较运算符的优先级
	bool OperIsHigher();
	// 得到运算符的权值
	int GetPriOfOper(const char oper);

private:
	int iResult;
	// 表达式的结果
	char oper;
	// 表达式的运算符
	Arighm *lhs;
	// 表达式的左节点
	Arighm *rhs;
	// 表达式的右节点
	bool isRoot;
	// 该表达式是否为最终的表达式
	Arighm *Parent;
	// 表达式的父节点
	bool isLeft;
	// 是否为左节点(为了输出是加括号用)
};

Arighm::Arighm()
	: iResult(0)
	, oper('\0')
	, lhs(NULL)
	, rhs(NULL)
	, Parent(NULL)
	, isLeft(false)
{

}

Arighm::~Arighm()
{
	if (lhs != NULL)
	{
		delete lhs;
	}

	if (rhs != NULL)
	{
		delete rhs;
	}
}

void Arighm::CreateEx(int numOfNode)
{
	if (1 == numOfNode)
	{
		return;
	}
	else
	{
		int mode = rand() % 4;
		if (0 == mode)
		{
			oper = '+';
		}
		else if (1 == mode)
		{
			oper = '-';
		}
		else if (2 == mode)
		{
			oper = '*';
		}
		else
		{
			oper = '/';
		}

		lhs = new Arighm();
		rhs = new Arighm();
		lhs->Parent = this;
		lhs->isLeft = true;
		rhs->Parent = this;
		rhs->isLeft = false;

		int numOfNodeLeft = numOfNode - rand() % numOfNode;
		if (numOfNodeLeft == numOfNode)
		{
			numOfNodeLeft = 1;
		}

		lhs->CreateEx(numOfNodeLeft);
		rhs->CreateEx(numOfNode - numOfNodeLeft);
	}
}


int Arighm::Count()
{
	if (lhs != NULL && rhs != NULL)
	{
		int lResult = 0;
		int rResult = 0;

		lResult = lhs->Count();
		rResult = rhs->Count();

		while (lResult >= 5000 || lResult <= 0)
		{
			lResult = lhs->Count();
		}

		while (rResult >= 5000 || rResult <= 0)
		{
			rResult = rhs->Count();
		}

		if ('+' == oper)
		{
			iResult = lResult + rResult;
		}

		else if ('-' == oper)
		{
			iResult = lResult - rResult;
			if (iResult < 0)
			{
				Arighm *temp = lhs;
				lhs = rhs;
				lhs->isLeft = true;
				rhs = temp;
				rhs->isLeft = false;
				iResult = rResult - lResult;
			}
		}

		else if ('*' == oper)
		{
			int getNum = 0;
			iResult = lResult * rResult;
			while (iResult >= 3000)
			{
				lResult = lhs->Count();
				rResult = rhs->Count();
				getNum++;

				if (getNum > 3000)
				{
					int mode = rand() % 2;
					if (0 == mode)
					{
						oper = '+';
						iResult = lResult + rResult;
					}
					else if (1 == mode)
					{
						oper = '-';
						iResult = lResult - rResult;
						if (iResult < 0)
						{
							Arighm *temp = lhs;
							lhs = rhs;
							lhs->isLeft = true;
							rhs = temp;
							rhs->isLeft = false;
							iResult = rResult - lResult;
						}
					}

					return iResult;
				}

				iResult = lResult * rResult;
			}
		}

		else if ('/' == oper)
		{
			int getNum = 0;
			while (0 == lResult || 0 == rResult || lResult % rResult != 0)
			{
				lResult = lhs->Count();
				rResult = rhs->Count();
				getNum++;
				if (getNum > 2000)
				{
					int mode = rand() % 2;
					if (0 == mode)
					{
						oper = '+';
						iResult = lResult + rResult;
					}
					else if (1 == mode)
					{
						oper = '-';
						iResult = lResult - rResult;
						if (iResult < 0)
						{
							Arighm *temp = lhs;
							lhs = rhs;
							lhs->isLeft = true;
							rhs = temp;
							rhs->isLeft = false;
							iResult = rResult - lResult;
						}
					}

					return iResult;
				}
			}

			iResult = lResult / rResult;
		}
	}
	else
	{
		iResult = rand() % 5000;
		while (iResult == 0)
		{
			iResult = rand() % 5000;
		}
	}

	return iResult;
}

void Arighm::Display()
{
	if (lhs != NULL && rhs != NULL)
	{
		if (!OperIsHigher())
		{
			cout << '(';
		}
		lhs->Display();
		cout << " " << oper << " ";
		rhs->Display();
		if (!OperIsHigher())
		{
			cout << ')';
		}
	}
	else
	{
		cout << iResult;
	}
}

bool Arighm::OperIsHigher()
{
	if (NULL == Parent)
	{
		return true;
	}
	if (isLeft)
	{
		return GetPriOfOper(this->oper) >= GetPriOfOper(Parent->oper);
	}
	else
	{
		return GetPriOfOper(this->oper) > GetPriOfOper(Parent->oper);
	}
}

int Arighm::GetPriOfOper(const char oper)
{
	if ('\0' == oper)
	{
		return 3;
	}
	else if ('/' == oper || '*' == oper)
	{
		return 2;
	}
	else if ('+' == oper || '-' == oper)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int main()
{
	Arighm *pRoot = NULL;

	int numOfArighm = 0;

	int numOfNumber = 0;
	int size=0;

	cout << "请输入你要生成的题目个数" << endl;

	cin >> numOfArighm;
	cout <<"请输入你要生成的数值范围"<<endl;
	cin>>size;

	int iResult = 0;
	srand((int)time(0));

	for (int i = 0; i < numOfArighm; i++)
	{
		
		pRoot = new Arighm();
		numOfNumber = rand()%5;
		pRoot->CreateEx(numOfNumber);
		iResult = pRoot->Count();
		while (iResult >= 5000 || iResult <= 0)
		{
			iResult = pRoot->Count();
		}
		pRoot->Display();
		cout << " = " << iResult;
		cout << endl;
		delete pRoot;
	}
	getchar();
	getchar();
	return 0;
}