#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <queue>
#include <array>
using namespace std;

int solution(int n, int infection, vector<vector<int>> edges, int k);

int main()
{
    int answer = 0;
	int switcher = 1;
    if(switcher == 1)
    {
		answer = solution(10, 1 ,{{1, 2, 1}, {1, 3, 1}, {1, 4, 3}, {1, 5, 2}, {5, 6, 1}, {5, 7, 1}, {2, 8, 3}, {2, 9, 2}, {9, 10, 1}}, 2);
    }
    if(switcher == 2)
    {
        answer = solution ( 7, 6,{{1, 2, 3}, {1, 4, 3}, {4, 5, 1}, {5, 6, 1}, {3, 6, 2}, {3, 7, 2}},
            3);
    }

    return answer;
}

const static int weight = 100 + 1;
int BackTracking(const array<array<int, weight>, weight>& graph, 
    int hierachy,  int remainCount, 
    const set<int>& virus);


int solution(int n, int infection, vector<vector<int>> edges, int k) 
{
	array<array<int, weight>, weight> graph;
    for (auto& row : graph)
        row.fill(-1);
    
	int  typeCount = 0;
    for (const auto& pair : edges)
    {
        if(pair[2] > typeCount)
			typeCount = pair[2];
        graph[pair[0]][pair[1]] = pair[2];
        graph[pair[1]][pair[0]] = pair[2];
    }
    int answer = 0;
	
    for (size_t i = 0; i < k; i++)
    {
        int size = BackTracking(graph, typeCount, k, {infection});
		answer = max(answer, size);
    }

    return answer;
}
    
int BackTracking(const array<array<int, weight>, weight>& graph,int hierachy, int remainCount,const set<int>& viruses)
{
    if (remainCount <= 0)
    {
        return viruses.size();
    }

    
    int value = 0;
    for (size_t type = 0; type <= hierachy; type++)
    {
		queue<int> que;
		set<int> virusesValue = viruses;
        for (auto virus : virusesValue)
        {
            que.push(virus);
        }

        while(!que.empty())
        {
            int current = que.front();
            que.pop();

            for (size_t neighbor = 0; neighbor < weight; neighbor++)
            {
                if(graph[current][neighbor] == -1)
                    continue;
                if (graph[current][neighbor] != type ||
                    graph[neighbor][current] != type)
                    continue;
                if (virusesValue.find(neighbor) != virusesValue.end())
                    continue;

                que.push(neighbor);
                virusesValue.insert(neighbor);
            }
        }
        value = max(value, BackTracking(graph, hierachy, remainCount - 1, virusesValue));
    }
    return value;
}