// 본사에서 공장까지 도로 건설하려함. 
// 토지 구입 비용을 최소화
// 지도 정보가 주어졌을 때, 토지 구입 비용 계산

// 지도는 정사각형 모양 크기 N (N = 자연수, 2<=N<=100)
// 토지는 1x1크기로 구분, 문자열로 각 토지 구입 가격 제공
// 구입 가격 0원은 이미 회사 소유 땅

// 도로는 상하좌우로 연결되어야함 (대각 연결 x)
// 본사 (0,0), 공장은 (N-1, N-1) 위치, (이 두 땅은 0원)

// 예제
// 3
// 041
// 253
// 620

#include <iostream>
#include <fstream>
#include <istream>
#include <ostream>
#include <string>
#include <limits>
#include <algorithm>
#include <queue>
#include <tuple>

using namespace std;

int map[100][100] = { 0 };
int cost[100][100] = { 0 };
int N;

int dir_x[] = {0, 0, -1, 1};
int dir_y[] = {-1, 1, 0, 0};

enum dir { UP = 0, DOWN, LEFT, RIGHT };

void InputData(istream& in)
{
	in >> N;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
		{
			char temp;
			in >> temp;
			map[y][x] = temp - '0';
		}
}

int Down(int (*data)[100], int y, int x)
{
	if (y + 1 >= N)
		return numeric_limits<int>::max();
	else
		return data[y + 1][x];
}

int Right(int(*data)[100], int y, int x)
{
	if (x + 1 >= N)
		return numeric_limits<int>::max();
	else
		return data[y][x + 1];
}

bool isValid(int y, int x)
{
	if (y < 0 || y >= N)
		return false;
	
	if (x < 0 || x >= N)
		return false;

	return true;
}

void bfs()
{
	queue<pair<int, int>> q_coord;

	q_coord.push(make_pair<int, int>(0, 0));

	cost[0][0] = map[0][0];

	while (!q_coord.empty())
	{
		int x, y;
		tie(x, y) = q_coord.front();

		for (int i = 0; i < 4; i++)
		{
			int new_x = x + dir_x[i];
			int new_y = y + dir_y[i];
			if (isValid(new_y, new_x)) // 재참조..
			{
				// 재참조는 cost 갱신때만..
				if (cost[new_y][new_x] > map[new_y][new_x] + cost[y][x])
				{
					cost[new_y][new_x] = map[new_y][new_x] + cost[y][x];
					q_coord.push(make_pair<int, int>(x + dir_x[i], y + dir_y[i]));
				}		
			}
		}

		q_coord.pop();
	}
}

void initMap()
{
	for (int y = 0; y < N; y++)
	{
		for (int x = 0; x < N; x++)
		{
			cost[y][x] = numeric_limits<int>::max();
		}
	}
}

int Calculation()
{
	initMap();
	bfs();

	int result = cost[N-1][N-1];
	return result;
}

int main()
{
	string num = "10"; //03, 07, 08
	string input_dir = "도로건설//in_" + num + ".txt";
	string output_dir = "도로건설//out_" + num + ".txt";
	fstream input(input_dir);
	InputData(input);
	
	fstream output(output_dir);
	int answer;
	output >> answer;
	
	cout << "Calc: " << Calculation() << ", Answer: " << answer << endl;
}
