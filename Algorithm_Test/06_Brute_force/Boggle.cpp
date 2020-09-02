// 06_Brute_force.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

ifstream& read_txt(ifstream& in, vector<char>& data);

int main()
{
    string input_file = "input1.txt";
    ifstream read_stream(input_file);

    vector<char> input_data;

    if (read_stream.is_open())
    {
        read_txt(read_stream, input_data);
    }

    size_t index = 0;
    size_t length = static_cast<size_t>(sqrt(input_data.size()));
    vector<vector<char> > data(length, vector<char>());
    for (int i = 0; i < input_data.size(); ++i)
    {
        int index = static_cast<int>(i / length);
        data[index].push_back(input_data[i]);
    }

}

ifstream& read_txt(ifstream& in, vector<char>& data)
{
    char temp;

    if (in)
    {
        while (in >> temp)
            data.push_back(temp);
    }

    return in;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
