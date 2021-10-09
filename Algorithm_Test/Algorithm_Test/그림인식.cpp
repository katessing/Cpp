// NxN ũ���� �� �� ��ȭ���� 1~9�� �� �غ�
// 9���� �� �� �ϳ��� ��� ���簢�� ��ĥ
// �Ź� �ٸ� �� ��� ��ĥ, ��ĥ or ����� ĥ�ϱ�
// ��ȭ�� ���� 0

// ��ǥ (����, ����)

// �Է� ����
// ù ���� ��ȭ�� ũ�� N �Է� (4<=N<=10)
// �� ��° �ٺ��� N�ٿ� ���� N���� �� ������ ������� �Է� (�� ������ ����, 0<=��<=9)
// ��ȭ���� ���̴� �� �� ��ĥ���� ���� ���� ���� ���

// �Է� ����
//4
//1230
//1737
//1777
//0220

// ��� ����
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

		string file_dir = "�׸��ν�//in_" + num + ".txt";
		string out_dir = "�׸��ν�//out_" + num + ".txt";
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