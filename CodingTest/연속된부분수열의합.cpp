#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

//비내림차순으로 정렬
//시간 복잡도 2N
using namespace std;
vector<int> solution(vector<int> sequence, int k) {
    vector<int> answer(2, 0);
    int size = sequence.size();
    int sum = 0;
    int start = 0;
    int end = 0;
    int min = size + 2;
    //N회 반복 순회로 연속합 계산
    for (size_t i = 0; i < size; i++)
    {
        sum += sequence[i];
        //뒷부분 피봇 이동
        end = i + 1;
        
        if (sum < k)
            continue;

        if (sum == k)
        {
            //사용된 조합 수가 적다면 시작점과 끝점 저장 
            if (min > (end - start) + 1)
            {
                min = (end - start) + 1;
                answer[0] = start;
                answer[1] = end - 1;
           }
            continue;
        }

        //N회 반복해서 앞 부분 제거
        while (sum > k)
        {
            sum -= sequence[start];
            start++; //앞 부분 피봇 이동
        }
        if (sum == k)
        {
            //사용된 조합 수가 적다면 시작점과 끝점 저장 
            if (min > (end - start) + 1)
            {
                min = (end - start) + 1;
                answer[0] = start;
                answer[1] = end - 1;
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