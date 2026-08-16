#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

//비내림차순으로 정렬
using namespace std;
vector<int> solution(vector<int> sequence, int k) {
    vector<int> sums(sequence.size(), 0);
    vector<int> answer(2, 0);
    int size = sequence.size();
    for (int i = 0; i < sequence.size(); i++)
    {
        int value = 0;
        int curSize = 0;
        for (int j = i; j < sequence.size(); j++)
        {
            curSize++;
            value += sequence[j];
            if (value > k)
                break;
            if (value == k)
            {
                if (size > curSize)
                {
                    size = curSize;
                    answer[0] = i;
                    answer[1] = j;
                }
                break;
            }
        }
    }
    return answer;
}


int main()
{
    vector<int> answer;
    answer = solution({ 1,2,3,4,5 }, 7);
    cout << answer[0] << ' ' << answer[1] << endl;
    
    answer = solution({ 1,1,1,2,3,4,5 }, 5);
    cout << answer[0] << ' ' << answer[1] << endl;

    answer = solution({ 2,2,2,2,2 }, 6);
    cout << answer[0] << ' ' << answer[1] << endl;
    
    return 0;
}