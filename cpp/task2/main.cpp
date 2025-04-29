#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>

using namespace std;

// генерация псевдослучайного числа в диапазоне min-max
int random_int(int min, int max) {
	ranlux48 gen(random_device{}());
	uniform_int_distribution<int> dist(min, max);
	return dist(gen);
}

void arrayPrint(int n, bool snake = false) {
	cout << "\n";
	int minVal = 100;

	vector<vector<int>> arr(n, vector<int>(6));

	// Заполнение массива
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < 6; ++j) {
			arr[i][j] = minVal++;
		}
	}

	// Вывод массива
	for (int i = 0; i < n; ++i) {
		if (snake && i % 2 == 0) {
			for (int j = 6 - 1; j >= 0; --j)
				cout << setw(4) << arr[i][j];
		} else {
			for (int j = 0; j < 6; ++j)
				cout << setw(4) << arr[i][j];
		}
		cout << '\n';
	}

}

int main() {
	cout << "Введите количество чисел (≥10): ";
    int n;
    cin >> n;
    vector<int> vec(n);
	cout << "Исходный массив: ";

	int posNumAmount = 0;
    for (int& num : vec) {
        num = random_int(-100, 100);
    	cout << num << " ";
    	if (num > 0) { posNumAmount+=1; }
    }
	cout << "\nПоложительных элементов: " << posNumAmount << endl;

	auto it = find(vec.rbegin(), vec.rend(), 0);
	if (it != vec.rend()) {
		int sumAftZero = accumulate(it.base(), vec.end(), 0);
		cout << sumAftZero << "\n";
	} else {
		cout << "В массиве нет нуля!\n";
	}

	std::vector<int> current;
	std::vector<int> longest;
	int prev = -101;

	for (int val : vec) {
		if (current.empty() || val > prev) {
			current.push_back(val);
		} else {
			if (current.size() > longest.size()) {
				longest = current;
			}
			current = {val};
		}
		prev = val;
	}

	if (current.size() > longest.size()) { longest = current; }

	cout << "Самая длинная возрастающая последовательность: ";
	for (int x : longest) {
		cout << x << " ";
	}

	arrayPrint(n, false);
	arrayPrint(n, true);

    return 0;
}