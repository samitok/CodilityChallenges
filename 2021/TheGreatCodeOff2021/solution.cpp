// you can use includes, for example:
// #include <algorithm>
// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(int N, int K, vector<int> &A, vector<int> &B, vector<int> &C) {
    // write your code in C++14 (g++ 6.2.0)
    int M = A.size();
    if(K > M)
        return 0;

    std::vector<int> cakes(N+1, 0);//-1 bad or last layer

    cakes[0] = -1;
    for (int i=0; i<M; ++i) 
    {
        int new_layer = C[i];
        for (int j=A[i]; j<=B[i]; ++j) 
        {
            int current_layer = cakes[j];
            if(current_layer != -1)
            {
                if(current_layer+1 == new_layer)
                {
                    cakes[j] = new_layer;
                }
                else
                {
                    cakes[j] = -1;
                }
            }
        }
    }

    int good_cake_cnt = 0;
    for(int i=1; i<N+1; ++i)
    {
        if(cakes[i] == K)
        {
            good_cake_cnt++;
        }
    }
    
    return good_cake_cnt;
}
