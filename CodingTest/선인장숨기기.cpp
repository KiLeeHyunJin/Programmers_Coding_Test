#include <vector>
#include <deque>
#include "Call.h"
using namespace std;
vector<int> solution(int m, int n, int h, int w, vector<vector<int>> drops);

int main()
{
    auto st = solution(4, 6, 1, 2, { {0, 1}, {0, 3}, {0, 5}, {1, 1}, {1, 3}, {1, 5}, {2, 1}, {2, 3}, {2, 5}, {3, 1}, {3, 3}, {3, 5} });
    cout << st[0] << ", " << st[1];
    return 0;
}

vector<int> solution(int m, int n, int h, int w, vector<vector<int>> drops)
{
    vector<int> answer(2);

    vector<vector<int>> worldMat(m, vector<int>(n, 0));

    int dropCount = drops.size();

    for (int i = 0; i < drops.size(); i++)
    {
        worldMat[drops[i][0]][drops[i][1]] = dropCount--;
    }


    // 가로 방향 최대값
    vector<vector<int>> rowMax(
        m,
        vector<int>(n - w + 1, 0)
    );

    for (int row = 0; row < m; row++)
    {
        deque<int> dq;

        for (int col = 0; col < n; col++)
        {
            // 현재 값이 0이면 빗방울 없음
            if (worldMat[row][col] != 0)
            {
                while (!dq.empty() &&
                    worldMat[row][dq.back()] <= worldMat[row][col])
                {
                    dq.pop_back();
                }

                dq.push_back(col);
            }

            while (!dq.empty() &&
                dq.front() <= col - w)
            {
                dq.pop_front();
            }

            if (col >= w - 1)
            {
                rowMax[row][col - w + 1] =
                    dq.empty() ? 0 : worldMat[row][dq.front()];
            }
        }
    }


    // 세로 방향 최대값
    vector<vector<int>> result(
        m - h + 1,
        vector<int>(n - w + 1, 0)
    );

    for (int col = 0; col < n - w + 1; col++)
    {
        deque<int> dq;

        for (int row = 0; row < m; row++)
        {
            if (rowMax[row][col] != 0)
            {
                while (!dq.empty() &&
                    rowMax[dq.back()][col] <= rowMax[row][col])
                {
                    dq.pop_back();
                }

                dq.push_back(row);
            }

            while (!dq.empty() &&
                dq.front() <= row - h)
            {
                dq.pop_front();
            }

            if (row >= h - 1)
            {
                result[row - h + 1][col] =
                    dq.empty() ? 0 : rowMax[dq.front()][col];
            }
        }
    }


    // 가장 먼저 떨어지는 시간이 가장 작은 영역 선택
    int bestTime = INT_MAX;

    for (int i = 0; i < m - h + 1; i++)
    {
        for (int j = 0; j < n - w + 1; j++)
        {
            int time = result[i][j];

            // 빗방울이 하나도 없는 영역
            if (time == 0)
            {
                answer[0] = i;
                answer[1] = j;
                return answer;
            }

            if (time < bestTime)
            {
                bestTime = time;
                answer[0] = i;
                answer[1] = j;
            }
        }
    }

    return answer;
}