// 버섯을 규칙에 맞게 먹어서 키를 키우는 게임
// 가장 키를 많이 키우면 됨

// 버섯 개수 N는 자연수, 1<=N<=150'000
// 버섯은 일렬로 늘어져있으며 0번부터 N-1번까지
// 버섯에 써있는 숫자 P=자연수, 1<=P<=500

// 버섯은 0번부터 순서대로 먹을지 말지 결정해야함
// 홀수 번째 먹은 버섯 숫자만큼 커지고 짝수번재로 먹은 숫자만큼 작아짐

// 입력 예
// 8
// 7 2 1 8 4 3 5 6

#include <iostream>
#include <string>
#include <fstream>
#include <istream>

using namespace std;

int N;
int P[150'000] = { 0 };

void InputData(istream& in)
{
	in >> N;
	for (int i = 0; i < N; i++)
	{
		in >> P[i];
	}
}

int Calculate()
{
	int sum = P[0];
	for (int i = 1; i < N; i++)
	{
		if (P[i - 1] < P[i])
			sum = sum - P[i - 1] + P[i];
	}
	return sum;
}

int main()
{
	string num = "01";
	string str_in = "마리오게임//in_" + num + ".txt";
	string str_out = "마리오게임//out_" + num + ".txt";

	fstream input(str_in);
	fstream output(str_out);
	
	int ans;
	output >> ans;

	InputData(input);

	cout << "Calculation: " << Calculate() << ", Answer: " << ans << endl;
}



