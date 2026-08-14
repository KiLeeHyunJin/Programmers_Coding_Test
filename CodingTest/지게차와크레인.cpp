#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

int solution(vector<string> storage, vector<string> requests) {
    int height = storage.size();
    int width = storage[0].size();

    int dy[] = { -1, 1, 0, 0 };
    int dx[] = { 0, 0, -1, 1 };

    for (const string& req : requests) {
        char target = req[0];
        bool isAll = (req.size() == 2);

        vector<vector<bool>> accessible(height, vector<bool>(width, false));
        queue<pair<int, int>> q;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (i == 0 || i == height - 1 || j == 0 || j == width - 1) {
                    accessible[i][j] = true;
                    q.push({ i, j });
                }
            }
        }
        while (!q.empty()) {
            auto [y, x] = q.front();
            q.pop();

            if (storage[y][x] != '0') continue;

            for (int i = 0; i < 4; ++i) {
                int ny = y + dy[i];
                int nx = x + dx[i];

                if (ny >= 0 && ny < height && nx >= 0 && nx < width) {
                    if (!accessible[ny][nx]) {
                        accessible[ny][nx] = true;
                        q.push({ ny, nx });
                    }
                }
            }
        }

        vector<pair<int, int>> toRemove;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (storage[i][j] == target) {
                    if (isAll || accessible[i][j]) {
                        toRemove.push_back({ i, j });
                    }
                }
            }
        }

        for (auto& p : toRemove) {
            storage[p.first][p.second] = '0';
        }
    }

    int remainingCount = 0;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (storage[i][j] != '0') {
                remainingCount++;
            }
        }
    }

    return remainingCount;
}

int main() {
    // 테스트 케이스 1 실행 (기대값: 11)
    cout << "Test 1: " << solution({ "AZWQY", "CAABX", "BBDDA", "ACACA" }, { "A", "BB", "A" }) << endl;
    // 테스트 케이스 2 실행 (기대값: 4)
    cout << "Test 2: " << solution({ "HAH", "HBH", "HHH", "HAH", "HBH" }, { "C", "B", "B", "B", "B", "H" }) << endl;
    return 0;
}
