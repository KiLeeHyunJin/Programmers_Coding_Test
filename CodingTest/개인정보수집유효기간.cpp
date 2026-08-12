#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <iostream>

using namespace std;
vector<int> solution(string today, vector<string> terms, vector<string> privacies);

int main()
{
	vector<int> answer;
	int switcher = 0;
	if (switcher == 0)
	{
		answer = solution(
			"2020.12.17", {"A 12"},
			{"2010.01.01 A", "2019.12.17 A"}
		);
	}
	if (switcher == 1)
	{
		answer = solution(
			"2020.01.01",
			{ "Z 3", "D 5" },
			{ "2019.01.01 D", "2019.11.15 Z", "2019.08.02 D", "2019.07.01 D", "2018.12.28 Z" }
		);
	}
	for (const auto& result : answer)
		std::cout << result << " ";

    return 0;
}


struct date
{
	int year = 0;
	int month = 0;
	int day = 0;
	int line = 0;
};

vector<int> solution(string today, vector<string> terms, vector<string> privacies) {
    vector<int> answer;
	map<string, int> termMap;
	const int monthToDay = 28;
	for (const auto& term : terms)
	{
		const int pos = term.find(' ');
		termMap[term.substr(0, pos)] = stoi(term.substr(pos + 1));
	}
	vector<date> privacyData;
	privacies.reserve(privacies.size());
	
	date todayData;
	todayData.year = stoi(today.substr(0, 4));
	todayData.month = stoi(today.substr(5, 2));
	todayData.day = stoi(today.substr(8, 2));
	std::to_string(todayData.year) +  std::to_string(todayData.month) + std::to_string(todayData.day);
	todayData.line = stoi(std::to_string(todayData.year) + std::to_string(todayData.month / 10) + std::to_string(todayData.month % 10) + std::to_string(todayData.day / 10) + std::to_string(todayData.day % 10));

	for (size_t i = 0; i < privacies.size(); i++)
	{
		const auto& privacy = privacies[i];
		const int pos = privacy.find(' ');
		auto dateStr = privacy.substr(0, pos);
		
		date data;
		data.year = stoi(dateStr.substr(0, 4));
		data.month = stoi(dateStr.substr(5, 2)) + termMap[privacy.substr(pos + 1)];
		data.day = stoi(dateStr.substr(8, 2));

		if (data.day > monthToDay)
		{
			data.month += data.day / monthToDay;
			data.day %= monthToDay;
		}
		while (data.month / 12 != 0 && data.month - 12 > 0)
		{
			data.year++;
			data.month -= 12;
		}

		data.line = stoi(std::to_string(data.year) + std::to_string(data.month / 10) + std::to_string(data.month % 10) + std::to_string(data.day / 10) + std::to_string(data.day % 10));

		if (todayData.line >= data.line)
			answer.push_back(i + 1);

		cout << "todayData.line : " << todayData.line << ", data.line : " << data.line << endl;
		privacyData.push_back(data);
	}
	return answer;
}

