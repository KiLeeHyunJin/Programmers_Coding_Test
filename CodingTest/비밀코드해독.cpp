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

int BackTracking(vector<int>& q, vector<int>& ans,int range, int passSize, int index, vector<int>* out)
{
    if (index > range)
        return 0;

    int stackCount = 0;
    for (size_t i = index; i <= range; i++)
    {
        bool isJump = false;
        vector<int> removePasswordIndex;
        removePasswordIndex.reserve(ans.size());

        int clearCheck = 0;
        for (size_t j = 0; j < q.size(); j++)
        {
            if (0 != (q[j] & (1 << i)))
            {
                q[j] &= ~(1 << i);
                ans[j]--;
                removePasswordIndex.push_back(j);

                if (isJump = (ans[j]) < 0)
                    break;
            }

            if (ans[j] == 0)
                clearCheck++;
        }
       
        out->push_back(i);
        if (isJump == false)
        {
            int curSize = out->size();
            if (clearCheck == q.size() && curSize == passSize)
                stackCount++;
            else if(curSize < passSize)
                stackCount += BackTracking(q, ans, range, passSize, i + 1, out);
        }

        out->pop_back();
        
        for (auto removeAns : removePasswordIndex)
        {
            ans[removeAns]++;
            q[removeAns] |= 1 << i;
        }
    }
    return stackCount;
}

int solution(int n, vector<vector<int>> q, vector<int> ans) 
{
    
    const int keySize = q.front().size();
    set<int> usedNum;
    unsigned int flags = 0;
    for (const auto& inputNums : q)
        for (int num : inputNums)
            usedNum.insert(num).second;

    vector<int> nums;
    nums.reserve(usedNum.size());
    for (auto num : usedNum)
        nums.push_back(num);
    usedNum.clear();

    vector<int> inputPass(q.size(), 0);
    for (size_t i = 0; i < q.size(); i++)
        for (size_t j = 0; j < keySize; j++)
            inputPass[i] |= 1 << q[i][j];


    vector<int> selectNums;
    selectNums.reserve(keySize);


    return BackTracking(inputPass, ans,n, keySize,
        1 , & selectNums);
}