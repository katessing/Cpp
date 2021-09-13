// 건물은 일렬로 정렬, N개 있음 6<=N<=80000
// 건물 높이 H, 1<=H<=1,000,000,000
// 각 건물에서 동쪽만 바라봄, 건물 정보는 서쪽에서 동쪽 순으로 입력

// i위치 건물에서는 i+1, i+2, ..., N-1 건물만 볼수 있고
// 자기 건물보다 낮은 건물 옥상만 볼 수 있음
// 건물 높이가 같거나 높은 건물이 있으면 그 건물 옥상과 그 뒤의 모든 건물 옥상은 볼수 없음

#include <iostream>
#include <istream>
#include <fstream>
#include <vector>
#include <stack>
using namespace std;

int N; // 건물 수
int H[80010]; // 건물 높이

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
		while (st.size() > 0) // stack 순회
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
	ifstream fin("건물옥상정원//in_" + file_num + ".txt");
	ifstream fresult("건물옥상정원//out_" + file_num + ".txt");
	if (!fin)
	{
		return -1;
	}

	Input_Data(fin);		// 입력 함수

	// 코드 작성
	ans = RoofViewStack();
	long long result;
	fresult >> result;

	fin.close();
	fresult.close();
	cout << ans << endl; // 정답 출력
	cout << result << endl;
	return 0;
}