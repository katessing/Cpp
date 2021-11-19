// 필터에는 반사 정도 R, 투과 정도 P가 있음
// 반사 정도와 투과 정도가 최대한 가까울수록 좋음

// 필터개수
// 반사정도 투과정도

//4
//2 10
//2 8
//3 4
//4 12

// 1번 필터 제거하면
// 반사정도 = 2*3*4 = 24
// 투과정도 = 8+4+12 = 24

// 최고 성능을 위해 제거해야할 필터 개수는?

// 필터 개수 N (2<=N<=10)
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
	string str_in = "디스플레이필터//in_" + number + ".txt";
	string str_out = "디스플레이필터//out_" + number + ".txt";
	fstream input(str_in);
	fstream output(str_out);

	int solution;
	inputData(input);
	output >> solution;

	cout << "Answer: " << Calculate() << ", Solution: " << solution << endl;
}