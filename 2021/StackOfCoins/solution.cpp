int solution(vector<int> &A) {
    int len = A.size();
    vector<int> shifted(A.size());

    // Left Shift All
    int bag = 0;
    for(int i = len-1; i >= 0; --i) {
        bag = bag/2;
        shifted[i] = bag;
        bag += A[i];
    }

    int max_val = 0;

    // Right Shift All & check max val
    bag = 0;
    for(int i = 0; i < len; ++i) {
        bag = bag/2;
        shifted[i] += bag;
        bag += A[i];

        //check max val
        int sum = A[i] + shifted[i];
        if(sum > max_val) {
            max_val = sum;
        }
    }

    return max_val;
}
