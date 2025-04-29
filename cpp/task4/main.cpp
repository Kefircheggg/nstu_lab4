#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

string findBorda(const vector<string>& candidates, const vector<vector<string>>& votes) {
    map<string, int> scores;

    for (const auto& vote : votes) {
        for (int i = 0; i < vote.size(); ++i) {
            scores[vote[i]] += (candidates.size() - 1 - i);
        }
    }

    // Находим максимальный балл
    int maxScore = max_element(
        scores.begin(), scores.end(),
        [](const auto& a, const auto& b) {
            return a.second < b.second;
        }
    )->second;

    // Собираем всех кандидатов с этим баллом
    vector<string> winners;
    for (const auto& [candidate, score] : scores) {
        if (score == maxScore) {
            winners.push_back(candidate);
        }
    }

    return winners.size() == 1 ? winners[0] : "Ничья между несколькими кандидатами";
}

string findCondorce(const vector<string>& candidates, const vector<vector<string>>& votes) {
    map<string, map<string, int>> pairwise;

    // заполнение матрицы сравнений 
    for (const auto& vote : votes) {
        for (int i = 0; i < vote.size(); ++i) {
            for (int j = i + 1; j < vote.size(); ++j) {
                pairwise[vote[i]][vote[j]]++;
            }
        }
    }

    // Поиск на победителя Кондорсе
    for (const auto& candidate : candidates) {
        bool isWinner = true;

        for (const auto& opponent : candidates) {
            if (candidate == opponent) continue;

            if (pairwise[candidate][opponent] <= pairwise[opponent][candidate]) {
                isWinner = false;
                break;
            }
        }

        if (isWinner) return candidate;
    }

    return "Победитель Кондорсе не найден";
}

int main() {
    vector<string> candidates = {"a", "b", "c"};
    vector<vector<string>> votes = {
        {"a", "c", "b"},
        {"a", "c", "b"},
        {"c", "b", "a"},
    };

    string winBorda = findBorda(candidates, votes);
    string winConrorce = findCondorce(candidates, votes);

    cout << "Победитель по Борда: " << winBorda << "\n";
    cout << "Победитель по Кондорсе: " << winConrorce;
    if (winBorda != winConrorce)
        cout << "\nРазные алгоритмы могут давать разные результаты в зависимости от специфики голосования";

    return 0;
}