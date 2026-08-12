#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <string>
#include <iostream>

using namespace std;
int solution(int n, int w, int num);
void main()
{

    int answer = 0;
    if(false)
    {
        answer = solution(
            22, 6, 9
        );
    }
    else
    {
        answer = solution(
            13, 3, 13
        );
    }
	cout << answer << endl;
    return;
}

/// 택배 상자의 개수를 나타내는 정수 n, 
/// 가로로 놓는 상자의 개수를 나타내는 정수 w
/// 꺼내려는 택배 상자의 번호를 나타내는 정수 num
/// 
int solution(int n, int w, int num) {
    int answer = 0;
    
	vector<vector<bool>> matrix((n / w) + 1, vector<bool>(w, true));
    const bool isOther = ((n % w) != 0 ? true : false);
	const int floor = (n / w) + (isOther ? 1 : 0);
    const bool goLeft =  floor % 2 == 0;
    if(goLeft)
    {
        auto it = matrix.back().rbegin() + n % w;
        for (size_t i = n % w; i < w; i++, it++)
            (*it) = false;
    }
    else
    {
        auto it = matrix.back().begin() + n % w;
        for (size_t i = n % w; i < w; i++, it++)
            (*it) = false;
    }

    const int level = (((num % w) == 0) ? (num / w) : (num / w) + 1) - 1;
    const bool isLeft = ((level + 1) % 2 == 0);
    int moveCount = (num - (level * w));
    if (isLeft)
        moveCount = w - moveCount;
    else
        moveCount -= 1;
	int boxCount = 0;
	//cout << "level : " << level << ", moveCount : " << moveCount << endl;
    for (size_t i = level; i < matrix.size(); i++)
    {
        if(matrix[i][moveCount ])
            boxCount++;
    }

    /*for (int i = matrix.size() - 1; i >= 0 ; i--)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
			bool isLeft = ((i + 1) % 2 == 0);
            if (i == level && j == moveCount) {
                cout << "m";
                continue;
            }
            if (matrix[i][j])
            {
                cout << "o";
            }
            else
            {
                cout << " ";
            }
        }
        cout << endl;
    }*/
    return boxCount;
}



