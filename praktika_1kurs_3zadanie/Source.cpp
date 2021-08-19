#include<iostream>
#include<string>
#include<regex>
#include<fstream>

using namespace std;

const int MAX = 10;
const char fName[] = "file.txt";

regex regular1("(\\d)");// ����� ��������
regex regular2("([�-�]{1,4}\-\\d\\d\\d\\d)");//�������� �����
regex regular3("(\\d\\d\\d\\d)");//����� �����
regex regular4("([�-�][�-�]\-\\d\\d\\d[�-�])");//����� ��

struct AirPlan//��������� ������
{
	string point;
	string Mark;
	string BortNumb;
	string NumRei;
};
struct ID//�������
{
	int index;
	string key;
};
void FileRaed(AirPlan* pst, int& N);//�������� �����
void PrintTabl(AirPlan* pSt, int N);//������ �������� ������
void ReisSortMax(ID* pSt, int N);//���������� �� ������ �����

int main()
{
	setlocale(LC_ALL, "ru");
	system("color F0");
	AirPlan Table[MAX];
	ID IndexArr[MAX];
	int N = 0;
	FileRaed(Table, N);
	PrintTabl(Table, N);
	int k = 0;
	for (int i = 0; i < N; i++)
	{
		IndexArr[k].index = i;
		IndexArr[k].key = Table[i].NumRei;
		k++;
	}
	if (k != 0)
	{
		ReisSortMax(IndexArr, k);
		cout << "  ------------------------------" << endl;
		for (int i = 0; i < N; i++)
		{
			cout << " | " << Table[IndexArr[i].index].NumRei
				<< " | " << Table[IndexArr[i].index].Mark
				<< " | " << Table[IndexArr[i].index].BortNumb
				<< " | " << Table[IndexArr[i].index].point << " |" << endl;
			cout << "  ------------------------------" << endl;
		}
	}
	return 0;
}

void FileRaed(AirPlan* pst, int& N)
{
	ifstream fin(fName);
	if (!fin)
	{
		cout << "���� �� ������" << endl;
		exit(1);
	}
	int i = 0;
	int k = 0;
	while (!fin.eof())
	{
		fin >> pst[i].NumRei >> pst[i].Mark >> pst[i].BortNumb >> pst[i].point;
		if (!regex_match(pst[i].NumRei, regular3))
		{
			cout << "� ������ " << k + 1 << " ������������ ����� �����, ��� ����� ���������\n";
			i--;
			N--;
		}
		else if (!regex_match(pst[i].BortNumb, regular2))
		{
			cout << "� ������ " << k + 1 << " ������������ �������� �����, ��� ����� ���������\n";
			i--;
			N--;
		}
		else if (!regex_match(pst[i].point, regular1))
		{
			cout << "� ������ " << k + 1 << " ������������ ����� ��������, ��� ����� ���������\n";
			i--;
			N--;
		}
		else if (!regex_match(pst[i].Mark, regular4))
		{
			cout << "� ������ " << k + 1 << " ������������ ����� ��, ��� ����� ���������\n";
			i--;
			N--;
		}
		i++;
		N++;
		k++;
	}
	if (N == 0)
	{
		cout << "����������� ������ ������, ��������� ������������\n";
		exit(2);
	}
	else cout << "���������� ���������� �������:" << N << endl;
	fin.close();
}
void ReisSortMax(ID* pSt, int N)
{
	if (N != 0)
	{
		cout << "���������� ������� \"��������\"�� ����������� ������� ������:\n";
		for (int i = 0; i < N; i++)
		{
			for (int j = 1; j < N - i; j++)
			{
				if (pSt[j - 1].key > pSt[j].key)
				{
					string swap = pSt[j - 1].key;
					pSt[j - 1].key = pSt[j].key;
					pSt[j].key = swap;
					int change = pSt[j - 1].index;
					pSt[j - 1].index = pSt[j].index;
					pSt[j].index = change;
				}
			}
		}
	}
}

void PrintTabl(AirPlan* pSt, int N)
{
	int i;
	cout << "\t�������� ������:\n";
	cout << "  ------------------------------" << endl;
	for (i = 0; i < N; i++)
	{
		cout << "  ";
		cout << "| " << pSt->NumRei << " | " << pSt->Mark << " | " << pSt->BortNumb << " | " << pSt->point << " | " << endl;
		pSt++;
		cout << "  ------------------------------" << endl;
	}
}

