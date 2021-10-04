// B진법 (2<= B <= 36)의 수를 입력받아 곱셈, '0'~'9', 'A'~'Z'
// 테스트 케이스는 N (5<= N <= 100)
// 100자리 이하 B진법 정수 2개 입력 받고, 곱셈 출력

// 입력 정수, 연산 결과가 음수일때 '-'가 앞 붙음
// 

#include <iostream>
#include <istream>
#include <fstream>
#include <string>
#include <stack>
#include <vector>
#include <iterator>

using namespace std;

void ConvertToChar(int temp, int b, char& qu, char& re);
void Multiplier(vector<char>& result, int b, vector<char> vec_a, vector<char> vec_b);

int N = 0;
int B[100];
string S[100];
string D[100];

string file_name = "10";

string array_string = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void inputData(istream& in)
{
	in >> N;
	for (int i = 0; i < N; i++)
	{
		in >> B[i];
		in >> S[i];
		in >> D[i];
	}
}

bool InputStack(stack<char>& st, string data)
{
	bool negative_sign = false;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (i == 0 && data[i] == '-')
		{
			negative_sign = true;
		}
		else
		{
			st.push(data[i]);
		}
	}

	return negative_sign;
}

bool InputVector(vector<char>& vec, string data)
{
	bool negative_sign = false;
	for (size_t i = 0; i < data.size(); i++)
	{
		if (i == 0 && data[i] == '-')
		{
			negative_sign = true;
		}
		else
		{
			vec.push_back(data[i]);
		}
	}

	return negative_sign;
}

string Calculator(int num)
{
	vector<char> s_vec;
	vector<char> d_vec;

	bool s_sign = InputVector(s_vec, S[num]);
	bool d_sign = InputVector(d_vec, D[num]);
	
	vector<char> result;
	Multiplier(result, B[num], s_vec, d_vec);
	
	string a(result.rbegin(), result.rend());
	auto it = a.find_first_not_of('0');
	if (it != string::npos)
	{
		a.erase(a.begin(), a.begin() + it);
		if (s_sign ^ d_sign)
			a.insert(a.begin(), '-');
	}
	else
		a = "0";
	
	return a;
}

int ConvertToInt(char ch)
{
	return array_string.find(ch);
	//return distance(array_string.begin(), array_string.find(ch));
}

void Multiplier(vector<char>& result, int b, vector<char> vec_a, vector<char> vec_b)
{
	vector<char> temp_vec(vec_a.size() + vec_b.size(), '0');
	vector<int> temp_vec_int(vec_a.size() + vec_b.size(), 0);
	for (size_t i = 0; i < vec_a.size(); i++)
	{
		for (size_t j = 0; j < vec_b.size(); j++)
		{
			int temp = ConvertToInt(vec_a[vec_a.size()-i-1])* ConvertToInt(vec_b[vec_b.size()-j-1]);
			temp_vec_int[i + j] += temp;
		}
	}
	
	for (int i = 0; i < temp_vec_int.size(); i++)
	{
		//ConvertToChar(temp_vec_int[i], b, qu, re);

		int temp_qu = temp_vec_int[i] / b;
		int temp_re = temp_vec_int[i] % b;

		if (temp_qu != 0)
			temp_vec_int[i + 1] += temp_qu;
		temp_vec[i] = array_string[temp_re];
	}

	result = temp_vec;
}

void ConvertToChar(int temp, int b, char& qu, char& re)
{
	int temp_qu = temp / b;
	int temp_re = temp % b;

	qu = array_string[temp_qu];
	re = array_string[temp_re];
}

int main()
{
	string file_dir = "계산기//in_" + file_name + ".txt";
	string sol_dir = "계산기//out_" + file_name + ".txt";
	ifstream in(file_dir);
	ifstream solution(sol_dir);
	inputData(in);

	string ans;
	string sol;
	for (int i = 0; i < N; i++)
	{
		solution >> sol;
		ans = Calculator(i);
		cout << (ans == sol) << endl;
	}	
}