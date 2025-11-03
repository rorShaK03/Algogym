#include <iostream>
#include <vector>
#include <algorithm>

// https://coderun.yandex.ru/problem/cafe

int main() {
    int n;
    std::cin >> n;
    std::vector<int> prices;
    for (int i = 0; i < n; i++) {
        int price;
        std::cin >> price;
        prices.push_back(price);
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(300 * n + 1, -1));
    for (int j = 0; j <= 300 * n; j++) {
        dp[0][j] = 0;
    }

    for (int day = 1; day <= n; day++) {
        for (int sum = 0; sum <= 300 * n; sum++) {
            if (dp[day - 1][sum] >= 1) {
                dp[day][sum] = std::max(dp[day][sum], dp[day - 1][sum] - 1);
            }
            if (sum - prices[day -1] >= 0 && dp[day - 1][sum - prices[day - 1]] != -1) {
                if (prices[day - 1] > 100) {
                    dp[day][sum] = std::max(dp[day][sum], dp[day - 1][sum - prices[day - 1]] + 1);
                } else {
                    dp[day][sum] = std::max(dp[day][sum], dp[day - 1][sum - prices[day - 1]]);
                }
            }
        }
    }

    int sum = -1, k1 = -1;
    for (int j = 0; j <= 300 * n; j++) {
        if (dp[n][j] != -1) {
            sum = j;
            k1 = dp[n][j];
            break;
        }
    }

    int k2 = 0;
    std::vector<int> ans;

    int i = n, j = sum;
    while(i > 0) {
        if (i >= 1 && dp[i - 1][j] >= 1 && dp[i][j] == dp[i - 1][j] - 1) {
            ans.push_back(i);
            k2++;

            i--;
        } else {
            j -= prices[i - 1];
            i--;
        }
    }

    std::reverse(ans.begin(), ans.end());
    std::cout << sum << '\n';
    std::cout << k1 << ' ' << k2 << '\n';
    for (int num : ans) {
        std::cout << num << ' ';
    }
    return 0;
}
