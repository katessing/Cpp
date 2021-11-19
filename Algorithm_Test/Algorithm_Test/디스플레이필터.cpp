// ���Ϳ��� �ݻ� ���� R, ���� ���� P�� ����
// �ݻ� ������ ���� ������ �ִ��� �������� ����

// ���Ͱ���
// �ݻ����� ��������

//4
//2 10
//2 8
//3 4
//4 12

// 1�� ���� �����ϸ�
// �ݻ����� = 2*3*4 = 24
// �������� = 8+4+12 = 24

// �ְ� ������ ���� �����ؾ��� ���� ������?

// ���� ���� N (2<=N<=10)
// 1<=R<=20
// 1<=P<=1'000'000

#include <iostream>
#include <vector>
#include <istream>
#include <fstream>
#include <string>

using namespace std;

int N;

vector<int> R;
vector<int> P;
vector<vector<int>> comb;

void inputData(istream& in)
{
	in >> N;
	int temp;
	for (int i = 0; i < N; i++)
	{
		in >> temp;
		R.push_back(temp);
		in >> temp;
		P.push_back(temp);
	}
}

void Combination(vector<int>& list,int start, int n, int r)
{
	if (r == 0)
	{
		comb.push_back(list);
		return;
	}
	
	vector<int> copy_vec(list);
	
	for (int i = start; i < n; i++)
	{
		list.push_back(i);
		Combination(list, i + 1, n, r - 1);
		list = copy_vec;
	}
}

int Calculate()
{
	long long multi = 1;
	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		multi *= R[i];
		sum += P[i];
	}

	long long diff = abs(multi - sum);
	
	int solution = 0;

	vector<int> visit(N, 0);
	for (int i = 1; i < N; i++)
	{
		//int combination_num = CombinationNumber(N, i);
		//vector<int> temp(combination_num);
		vector<int> temp;
		//comb.push_back(temp);
		Combination(temp, 0, N, i);
	}

	for (auto it = begin(comb); it != end(comb); it++)
	{
		long long temp_multi = multi;
		int temp_sum = sum;
		for (auto it2 = begin(*it); it2 != end(*it); it2++)
		{
			temp_multi /= R[*it2];
			temp_sum -= P[*it2];
		}
		
		long long temp_diff = abs(temp_multi - temp_sum);

		if (temp_diff <= diff)
		{
			diff = temp_diff;
			solution = it->size();
		}
	}

	return solution;
}

int main()
{
	string number = "11";
	string str_in = "���÷�������//in_" + number + ".txt";
	string str_out = "���÷�������//out_" + number + ".txt";
	fstream input(str_in);
	fstream output(str_out);

	int solution;
	inputData(input);
	output >> solution;

	cout << "Answer: " << Calculate() << ", Solution: " << solution << endl;
}