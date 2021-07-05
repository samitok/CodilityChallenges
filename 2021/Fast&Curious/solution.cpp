#include <cstdint>
#include <vector>

int solution(vector<int> &A) {
    int city_cnt = A.size();
    vector<uint64_t> until_autobahn_dist(city_cnt-1, 0);
    vector<uint64_t> from_autobahn_dist(city_cnt-1, 0);

    uint64_t cumulative = 0;
    for(int i = 1; i < city_cnt-1; ++i){
        uint64_t travelled_dist = A[i] - A[i-1];
        cumulative += i * travelled_dist;
        until_autobahn_dist[i] = cumulative;
    }

    cumulative = 0;
    int last_city = A[city_cnt-1];
    for(int i = city_cnt-3; i >= 0; --i){
        cumulative += last_city - A[i+1];
        from_autobahn_dist[i] = cumulative;
    }

    uint64_t min_val = until_autobahn_dist[0] + from_autobahn_dist[0];
    for(int i=0; i < city_cnt-1; ++i){
        uint64_t cur_val = until_autobahn_dist[i] + from_autobahn_dist[i];
        if(cur_val < min_val){
            min_val = cur_val;
        }
    }

    const uint64_t divider = 1000000007;
    return min_val % divider;
}
