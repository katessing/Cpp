// NxN 크기의 흰 색 도화지에 1~9번 색 준비
// 9가지 색 중 하나를 골라서 직사각형 색칠
// 매번 다른 색 골라서 색칠, 덧칠 or 빈공간 칠하기
// 도화지 색은 0

// 좌표 (세로, 가로)

// 입력 형식
// 첫 줄은 도화지 크기 N 입력 (4<=N<=10)
// 두 번째 줄부터 N줄에 걸쳐 N개씩 색 정보가 공백없이 입력 (색 정보는 정수, 0<=색<=9)
// 도화지에 보이는 색 중 덧칠하지 않은 색의 개수 출력

// 입력 예시
//4
//1230
//1737
//1777
//0220

// 출력 예시
// 2

#include <iostream>
#include <fstream>
#include <string>
#include <istream>
#include <vector>
#include <tuple>

using namespace std;

int N;
int draw[10][10] = { 0 };

struct Point
{
	int y = 0;
	int x = 0;

	Point(int y = 0, int x = 0) : y(y), x(x) {};
	bool operator==(Point b) { return x == b.x && y == b.y; }
};

int ColorArray[9] = { 0 };

//string num = "01";
vector<tuple<int, Point, Point>> coord;
int CheckColorVector(int color);

void InputValue(istream& in)
{
	in >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			char ch;
			in >> ch;
			draw[i][j] = ch - '0';
		}
	}
}

void ExtractPoint()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (draw[i][j] == 0)
				continue;

			int index = CheckColorVector(draw[i][j]);
			if (index < 0)	// not in vector
			{
				coord.push_back(make_tuple(draw[i][j], Point{ i,j }, Point{}));
				ColorArray[draw[i][j] - 1] = 1;
			}
			else // in vector
			{
				if (get<1>(coord[index]).x > j)
				{
					get<1>(coord[index]).x = j;
				}
				
				if (get<2>(coord[index]).x < j)
				{
					get<2>(coord[index]).x = j;
				}

				if (get<1>(coord[index]).y > i)
				{
					get<1>(coord[index]).y = i;
				}

				if (get<2>(coord[index]).y < i)
				{
					get<2>(coord[index]).y = i;
				}

			}
		}
	}
}

int CheckColorVector(int color)
{
	if (coord.size())
	{
		for (auto it = coord.begin(); it != coord.end(); it++)
		{
			if (get<0>(*it) == color)
				return distance(coord.begin(), it);
		}
	}

	return -1;
}

vector<int> CheckCover(tuple<int, Point, Point> input)
{
	int start_x = get<1>(input).x;
	int start_y = get<1>(input).y;
	int end_x = get<2>(input).x;
	int end_y = get<2>(input).y;

	vector<int> return_color;

	for (int y = start_y; y <= end_y; y++)
	{
		for (int x = start_x; x <= end_x; x++)
		{
			if (draw[y][x] != get<0>(input))
			{
				return_color.push_back(draw[y][x]);
			}
		}
	}

	return return_color;
}

void CheckPure()
{
	for (auto it = coord.begin(); it != coord.end(); it++)
	{
		vector<int> color = CheckCover(*it);

		if (color.size() > 0)
		{
			for (auto i = color.begin(); i != color.end(); i++)
			{
				// color covered
				ColorArray[*i - 1] = -1;
			}
		}
	}
}

int ReturnPureColor()
{
	int sum = 0;

	for (auto i = begin(ColorArray); i != end(ColorArray); i++)
	{
		if (*i == 1)
		{
			sum++;
		}
	}

	return sum;
}

void Init()
{
	for (auto i = begin(ColorArray); i != end(ColorArray); i++)
	{
		*i = 0;
	}
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			draw[i][j] = 0;
		}
	}

	coord.clear();
}

int main()
{
	for (int i = 1; i < 11; i++)
	{
		Init();

		string num = to_string(i);
		if (num.length() == 1)
			num = "0" + num;

		string file_dir = "그림인식//in_" + num + ".txt";
		string out_dir = "그림인식//out_" + num + ".txt";
		ifstream input(file_dir);
		ifstream output(out_dir);

		int out;
		output >> out;

		InputValue(input);
		ExtractPoint();
		CheckPure();
		cout << num << endl;
		cout << "Calc: " << ReturnPureColor() << endl;
		cout << "Ans: " << out << endl;

	}
	
}