// you can use includes, for example:
// #include <algorithm>
#include <unordered_map>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int> &A, int L, int R) {
    std::unordered_map<int, int> disks;
    for (auto disk : A) {
        auto it = disks.find(disk);
        if(it == disks.end()) {
            disks[disk] = 1;
        }
        else {
            it->second = it->second + 1;
        }
    }
    int placed_cnt = 0;
    for (auto item : disks) {
        int slots = 0;
        if(item.first < L) {
            slots++;
        }
        if(item.first > R) {
            slots++;
        }
        int disk_cnt = item.second;
        if(disk_cnt > slots) {
            disk_cnt = slots;
        }
        placed_cnt += disk_cnt;
    }
    return placed_cnt;
}
