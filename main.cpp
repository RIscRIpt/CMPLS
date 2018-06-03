#include <iostream>
#include <algorithm>
#include <vector>

bool all_equal(std::vector<int> const &numbers) {
    if (numbers.size() <= 1)
        return true;
    return std::adjacent_find(numbers.begin(), numbers.end(), std::not_equal_to<int>()) == numbers.end();
}

std::vector<int> get_difference(std::vector<int> const &numbers) {
    if (numbers.size() <= 1)
        return {};
    std::vector<int> result(numbers.size() - 1);
    for (size_t i = 1; i < numbers.size(); i++) {
        result[i - 1] = numbers[i] - numbers[i - 1];
    }
    return result;
}

std::vector<int> get_next_numbers(std::vector<int> const &numbers, int to_get) {
    std::vector<std::vector<int>> differences;
    differences.push_back(numbers);
    while (!all_equal(differences.back())) {
        differences.emplace_back(get_difference(differences.back()));
    } 

    for (int i = 0; i < to_get; i++)
        differences.back().push_back(differences.back().front());

    for (int i = differences.size() - 2; i >= 0; i--) {
        auto &diff = differences[i];
        auto prev_size = diff.size();
        diff.resize(diff.size() + to_get);
        for (int j = 0; j < to_get; j++) {
            diff[prev_size + j] = diff[prev_size + j - 1] + differences[i + 1][prev_size + j - 1];
        }
    }

    return differences.front();
}

int main() {
    std::ios_base::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (int i = 0; i < T; i++) {
        int S, C;
        std::cin >> S >> C;
        std::vector<int> numbers(S);
        for (auto &n : numbers)
            std::cin >> n;
        numbers = get_next_numbers(numbers, C);
        for (int i = -C; i < 0; i++)
            std::cout << numbers[numbers.size() + i] << ' ';
        std::cout << '\n';
    }
    return 0;
}
