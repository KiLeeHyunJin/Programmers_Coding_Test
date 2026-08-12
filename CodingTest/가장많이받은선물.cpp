#include <string>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;
int solution(vector<string> friends, vector<string> gifts);


int main()
{

	int switcher = 2;
	int answer = 0;
	if(0 == switcher)
	{
		answer = solution(
			{ "muzi", "ryan", "frodo", "neo" },
			{ "muzi frodo", "muzi frodo", "ryan muzi", "ryan muzi", "ryan muzi", "frodo muzi", "frodo ryan", "neo muzi" }
		);
	}
	if( 1 == switcher)
	{
		answer = solution(
			{ "joy", "brad", "alessandro", "conan", "david" },
			{ "alessandro brad", "alessandro joy", "alessandro conan", "david alessandro", "alessandro david" }
		);
	}	

	if( 2 == switcher)
	{
		answer = solution(
			{ "a", "b", "c" },
			{ "a b", "b a", "c a", "a c", "a c", "c a" }
		);
	}

	cout << answer << endl;
	return 0;
}


struct Entity
{
	string name = {};
	int giveCount = 0;
	int receiveCount = 0;
	int index = 0;

	vector<int> receiveFrom;
};
unordered_map<string, Entity> matrix;
int GetIndex(const string& name) {
	return matrix[name].index;
}
int solution(vector<string> friends, vector<string> gifts) {
	int idx = 0;
	map<int, string> indexToName;
	for (auto& name : friends)
	{
		matrix[name] = { name, {} };
		indexToName[idx] = name;
		auto& ref = matrix[name];
		ref.name = name;
		ref.index = idx++;
		ref.giveCount = 0;
		ref.receiveCount = 0;
		ref.receiveFrom = vector<int>(friends.size(), 0);
	}

	for (auto& data : gifts)
	{
		int pos = data.find(' ');
		if (pos != string::npos)
		{
			string from = data.substr(0, pos);
			string to = data.substr(pos + 1);
			matrix[from].giveCount++;
			matrix[to].receiveFrom[GetIndex(from)]++;
			matrix[to].receiveCount++;
		}
	}
	map<int, list<string>> sorted;
	set<int> visited;
	map<string, int> nextReceiveCount;
	int answer = 0;
	for (auto& entity : matrix)
	{
		const auto& value = entity.second;
		const int id = GetIndex(value.name);
		sorted[value.giveCount - value.receiveCount].push_back(value.name);

		for (int j = 0; j < value.receiveFrom.size(); j++)
		{
			const int high = (id > j) ? id : j;
			const int low = (id < j) ? id : j;
			const int visitedId = (high * 1000) + low;
			if (visited.find(visitedId) != visited.end())
				continue;

			visited.insert(visitedId);
			
			const string* addTarget = nullptr;
			const auto& target = matrix[indexToName[j]];
			if (value.receiveFrom[j] != target.receiveFrom[id])
			{
				addTarget = value.receiveFrom[j] < target.receiveFrom[id] ? 
					&value.name : &indexToName[j];
			}
			else if (value.receiveCount - value.giveCount != target.receiveCount - target.giveCount)
			{
				addTarget = (value.receiveCount - value.giveCount) < (target.receiveCount - target.giveCount) ? 
					&value.name : &indexToName[j];
			}
			if(addTarget != nullptr)
			{
				nextReceiveCount[*addTarget]++;
				if(answer < nextReceiveCount[*addTarget])
				{
					answer = nextReceiveCount[*addTarget];
				}
			}
		}
	}

    return answer;
}