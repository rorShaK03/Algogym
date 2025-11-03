#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>
#include <cstdlib>

// https://coderun.yandex.ru/problem/avto/description

// Core idea: greedy remove the car that will be used the furthest in the future

// Nice improvement: memorize next positions for each positions

// Nice optimization: dont't use arrays of stacks, because stack implemented through deque
// and even empty deque allocates about 4096 B (https://en.cppreference.com/w/cpp/container/deque.html)

void remove_farest(std::set<std::pair<int, int>>& elem_dist, std::set<std::pair<int, int>>& dist_elem) {
    auto it = dist_elem.end();
    it--;

    auto elem_dist_it = elem_dist.lower_bound({it->second, -1});
    elem_dist.erase(elem_dist_it);

    dist_elem.erase(it);
}


int main() {
    int n, k, p;
    std::cin >> n >> k >> p;
    std::vector<int> order;
    for (int i = 0; i < p; i++) {
        int num;
        std::cin >> num;
        order.push_back(num);
    }

    // Vector of consequent positions of each car in the list
    std::vector<std::vector<int>> pos_st(n + 1);
    for (int i = 1; i <= n; i++) {
        pos_st[i].push_back(p);
    }
    for (int i = p - 1; i >= 0; i--) {
        pos_st[order[i]].push_back(i);
    }
    
    // Calc next position of element on position i that is greater than i
    std::vector<int> next_pos(p);
    for (int i = 0; i < p; i++) {
        pos_st[order[i]].pop_back();
        next_pos[i] = pos_st[order[i]].back();
    }


    int ans = 0;
    std::set<std::pair<int, int>> elem_dist;
    std::set<std::pair<int, int>> dist_elem;

    for (int i = 0; i < p; i++) {
        auto elem_it = elem_dist.lower_bound({order[i], -1});
        if (elem_it == elem_dist.end() || elem_it->first != order[i]) {
            // For new car, add position to sets

            // If there're too many cars already, remove the one which won't be used for the longest time
            if (elem_dist.size() == k) {
                remove_farest(elem_dist, dist_elem);
            }

            dist_elem.insert({next_pos[i], order[i]});
            elem_dist.insert({order[i], next_pos[i]});
            ans++;
        } else {
            // For existing car, update its position in sets
            dist_elem.erase({elem_it->second, elem_it->first});
            elem_dist.erase(elem_it);

            elem_dist.insert({order[i], next_pos[i]});
            dist_elem.insert({next_pos[i], order[i]});
        }
    }
    std::cout << ans;
    return 0;
}
