#include <vector>
#include <deque>
#include "Call.h"
#include <unordered_map>
using namespace std;
int solution(vector<vector<int>> signals);

int main()
{
    auto st = solution({ 
        {1,1,4},
        {2, 1, 3}, 
        {3, 1, 2},
        {4, 1, 1}
        });
    cout << st << endl;
    return 0;
}


int solution(vector<vector<int>> signals) {
	const int signalCount = signals.size();
	vector<int> sizes(signalCount, 0);
    unordered_map<int, int> signalMap;

    int circleCount = 1;
    for (int i = 0; i < signalCount; i++)
    {
        for (const int term : signals[i])    sizes[i] += term;
		circleCount *= sizes[i];
    }


    int count = 0;
    while (circleCount > count) {
        for (size_t i = 0; i < signalCount; i++)
        {
			const auto& signal = signals[i];
            const int start = (signal.front()) + 1 + count * sizes[i];
            const int end = start + signal[1];

            for (size_t j = start; j < end ; j++)
            {
				auto it = signalMap.find(j);
                if (it == signalMap.end())
                {
                    signalMap.insert({j, 1});
                    continue;
                }

                (it->second)++;
                if (it->second == signalCount)
                    return it->first;
            }
        }
        count++;
    }
    return -1;
}