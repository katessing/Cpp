// �ǹ��� �Ϸķ� ����, N�� ���� 6<=N<=80000
// �ǹ� ���� H, 1<=H<=1,000,000,000
// �� �ǹ����� ���ʸ� �ٶ�, �ǹ� ������ ���ʿ��� ���� ������ �Է�

// i��ġ �ǹ������� i+1, i+2, ..., N-1 �ǹ��� ���� �ְ�
// �ڱ� �ǹ����� ���� �ǹ� ���� �� �� ����
// �ǹ� ���̰� ���ų� ���� �ǹ��� ������ �� �ǹ� ����� �� ���� ��� �ǹ� ������ ���� ����

#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

int N; // �ǹ� ��
int H[80010]; // �ǹ� ����

string file_num = "09";

void Input_Data(istream& in)
{
	in >> N;
	for (int i = 0; i < N; i++)
	{
		in >> H[i];
	}
}

long long RoofViewFor()
{
	vector<long long> view_vector(N);
	long long sum = 0;
	for (int i = 0; i < N; i++)
	{
		long long view = 0;

		for (int j = i + 1; j < N; j++)
		{
			if (H[i] > H[j])
			{
				view++;
			}
			else
			{
				break;
			}
		}

		view_vector[i] = view;
		sum += view;
	}
	return sum;
}

long long RoofViewReverse()
{
	vector<long long> building_vector(N);
	long long sum = 0;
	for (int i = N - 1; i > 0; i--)
	{
		long long building = 0;
		int max_height = H[i];
		for (int j = i - 1; j >= 0; j--)
		{
			if (H[j] <= max_height)
				continue;
			building++;
			max_height = H[j];
		}
		building_vector[i] = building;
		sum += building;
	}
	return sum;
}

long long RoofViewStack()
{
	stack<int> st;
	vector<long long> view_vector(N);
	long long sum = 0;

	for (int i = 0; i < N; i++)
	{
		while (st.size() > 0) // stack ��ȸ
		{
			if (st.top() > H[i])
			{
				break;
			}
			else
			{
				st.pop();
			}
		}
		view_vector[i] = st.size();
		sum += st.size();
		st.push(H[i]);
	}
	return sum;
}

int main()
{
	long long ans = -1;
	ifstream fin("�ǹ���������//in_" + file_num + ".txt");
	ifstream fresult("�ǹ���������//out_" + file_num + ".txt");
	if (!fin)
	{
		return -1;
	}

	Input_Data(fin);		// �Է� �Լ�

	// �ڵ� �ۼ�
	ans = RoofViewStack();
	long long result;
	fresult >> result;

	fin.close();
	fresult.close();
	cout << ans << endl; // ���� ���
	cout << result << endl;
	return 0;
}