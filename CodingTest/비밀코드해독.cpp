#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
#include <list>
#include <unordered_map>
using namespace std;

int solution(int n, vector<vector<int>> q, vector<int> ans);

int main()
{
    int switcher = 1;
    int answer = 0;
    if (switcher == 1)
    {
        answer = solution(10 ,{{1, 2, 3, 4, 5}, {6, 7, 8, 9, 10}, {3, 7, 8, 9, 10}, {2, 5, 7, 9, 10}, {3, 4, 5, 6, 7}}, {2, 3, 4, 3, 3});
    }
    if (switcher == 2)
    {
        answer = solution(15, {{2, 3, 9, 12, 13}, {1, 4, 6, 7, 9}, {1, 2, 8, 10, 12}, {6, 7, 11, 13, 15}, {1, 4, 10, 11, 14}}, {2, 1, 3, 0, 1});
    }
    cout << answer << endl;
}

int solution(int n, vector<vector<int>> q, vector<int> ans) 
{
    int answer = 0;



    return answer;
}