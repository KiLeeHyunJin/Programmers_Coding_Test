#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <iostream>

using namespace std;

int solution(vector<int> players, int m, int k) {
    int answer = 0;
    int serverLimit = m;
    int duration = k;

    int curServer = 0;
    vector<int> serverOperation(players.size(), 0);
    for (int i = 0; i < players.size(); i++)
    {
        int user = players[i];
        int needServer = user / m;
        curServer += serverOperation[i];

        if (needServer > curServer)
        {
            int addServer = needServer - curServer;
            serverOperation[i] += addServer;
            curServer += addServer;
            answer += addServer;
            if(i + k < 24)
                serverOperation[i + k] -= addServer;
        }
    }
    return answer;
}


int main()
{
    int answer = 0;
    answer = solution({ 0, 2, 3, 3, 1, 2, 0, 0, 0, 0, 4, 2, 0, 6, 0, 4, 2, 13, 3, 5, 10, 0, 1, 5 }, 3,	5); // 7
    cout << answer << " " << " : " << 7 << endl;

    answer = solution({ 7, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }, 3, 1); // 7
    cout << answer << " " << " : " << 3 << endl;

    answer = solution({0, 0, 0, 10, 0, 12, 0, 15, 0, 1, 0, 1, 0, 0, 0, 5, 0, 0, 11, 0, 8, 0, 0, 0}, 5, 1);  // 11
    cout << answer << " " << " : " << 11 << endl;

    answer = solution({0, 0, 0, 0, 0, 2, 0, 0, 0, 1, 0, 5, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1}, 1, 1 );     //12
    cout << answer << " " << " : " << 12 << endl;

    return 0;
}