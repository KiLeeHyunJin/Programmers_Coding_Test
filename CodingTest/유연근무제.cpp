#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <string>
#include <iostream>

using namespace std;



int solution(vector<int> schedules, vector<vector<int>> timelogs, int startday);
void main()
{
    int answer = solution(
        { 730, 800, 1100 },
        {
        
        {710, 2359, 1050, 700, 650, 631, 659},{800, 801, 805, 800, 759, 810, 809},{1105, 1001, 1002, 600, 1059, 1001, 1100}

        },
        5
    );
    cout << answer << endl; 
}

int solution(vector<int> schedules, vector<vector<int>> timelogs, int startday) 
{
    int answer = schedules.size();
	int count = timelogs.size();
    for (size_t i = 0; i < schedules.size(); i++)
    {
		int limit = schedules[i] + 10;
        int other = limit % 100;
        if(other >= 60)
        {
            limit -= 60;
            limit += 100;
        }
        for (int j = 0; j < 7; j++)
        {
            int day = (startday - 1 + j) % 7 + 1;
			cout << i << " " << day << " " << timelogs[i][day] << " " << limit << endl;
            if (day <= 5)
                continue;

			if (timelogs[i][day] > limit)
            {
                answer -= 1;
                break;
            }
        }
    }
    return answer;
}