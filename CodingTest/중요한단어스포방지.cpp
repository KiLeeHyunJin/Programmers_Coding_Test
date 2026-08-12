#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <string>
#include <iostream>

using namespace std;
int solution(string message, vector<vector<int>> spoiler_ranges);

int main()
{
    auto st = solution(
        "my phone number is 01012345678 and may i have your phone number", 
        { {5, 5} ,{25, 28},{34, 40},{53, 59} }
    );
    cout << st << endl;
    return 0;
}

int solution(string message, vector<vector<int>> spoiler_ranges) {
    vector<int> spoiler_positions(message.size(), -1);
    vector<string> spoiler_words({ message.size(), "" });
    map<string, set<int>> spoiler_word_indices;
	string temp = "";
	int idx = -1;
    int count = 0;
    for (auto ch : message)
    {
        idx++;
        if (ch == ' ')
        {
            if (!temp.empty())
            {
                spoiler_word_indices[temp].insert(count);
                spoiler_words[count] = temp;
                temp.clear();
                count++;
            }
            continue;
        }
		temp.push_back(ch);
        spoiler_positions[idx] = count;
    }
    if (!temp.empty()) {
        spoiler_word_indices[temp].insert(count);
        spoiler_words[count] = temp;
    }



	set<int> spoiler_word_set;
    for (const auto& range : spoiler_ranges)
    {
        for (size_t i = range.front(); i <= range.back(); i++)
        {
			int word_idx = spoiler_positions[i];
            if(word_idx == -1)
                continue;
			spoiler_word_set.insert({ word_idx });
        }
    }


    map<string, set<int>> checked_spoiler_words;
	int i = 0;
    int answer = 0;

    for (const auto idx : spoiler_word_set)
    {
        const string& word = spoiler_words[idx];

        if(checked_spoiler_words.find(word) == checked_spoiler_words.end())
        {
            auto& indices = spoiler_word_indices[word];
            checked_spoiler_words[word].swap(indices);
        }
        checked_spoiler_words[word].erase(idx);
        if (checked_spoiler_words[word].empty())
        {
            checked_spoiler_words.erase(word);
            answer++;
        }
        i++;
    }

    return answer;
}