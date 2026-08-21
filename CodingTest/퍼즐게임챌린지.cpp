#include <string>
#include <vector>
#include <set>
#include <map>
#include <list>
#include <iostream>

using namespace std;

int solution(vector<int> diffs, vector<int> times, long long limit) {
    for (int level = 1; level < 10000000; level++)
    {
        unsigned long long totalTime = 0;
        int prev_Time = 0;
        bool isFind = true;
        for (int i = 0; i < diffs.size(); i++)
        {
            const int remain =  diffs[i] - level;
            const int curTime = times[i];
            totalTime += (remain <= 0) ? 
                curTime : 
                ((prev_Time + curTime) * remain) + curTime;

            prev_Time = times[i];
            if ((isFind = totalTime <= limit) == false)
                break;
        }

        if (isFind)
            return level;

    }
    return -1;
}


int main()
{
    int answer = 0;

    answer = solution({ 1, 5, 3 }, { 2, 4, 7 }, 30);
    cout << "3" << '\t' << answer << endl;

    answer = solution(
        { 1, 4, 4, 2 }, 
        { 6, 3, 8, 2 }, 
        59);
    cout << "2" << '\t' << answer << endl;

    answer = solution(
        { 1, 328, 467, 209, 54 }, 
        { 2, 7, 1, 4, 3 }, 
        1723);
    cout << "294" << '\t' << answer << endl;

    answer = solution(
        { 1, 99999, 100000, 99995 }, 
        { 9999, 9001, 9999, 9001 }, 
        
        
        3456789012);
    cout << "39354" << '\t' << answer << endl;

    return 0;
}