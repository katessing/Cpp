// ������ ��Ģ�� �°� �Ծ Ű�� Ű��� ����
// ���� Ű�� ���� Ű��� ��

// ���� ���� N�� �ڿ���, 1<=N<=150'000
// ������ �Ϸķ� �þ��������� 0������ N-1������
// ������ ���ִ� ���� P=�ڿ���, 1<=P<=500

// ������ 0������ ������� ������ ���� �����ؾ���
// Ȧ�� ��° ���� ���� ���ڸ�ŭ Ŀ���� ¦������� ���� ���ڸ�ŭ �۾���

// �Է� ��
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
	string str_in = "����������//in_" + num + ".txt";
	string str_out = "����������//out_" + num + ".txt";

	fstream input(str_in);
	fstream output(str_out);
	
	int ans;
	output >> ans;

	InputData(input);

	cout << "Calculation: " << Calculate() << ", Answer: " << ans << endl;
}



