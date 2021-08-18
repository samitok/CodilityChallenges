#include <limits>       // std::numeric_limits

vector<int> GetRowColSums(vector<int> &A) {
    vector<int> row_col_sums(6,0);
    for(int i=0; i<3; i++) { //row
        for(int c=0; c<3; ++c) { //col
            row_col_sums[i] += A[3*i + c];
        }
    }
    for(int i=0; i<3; i++) { //row
        for(int r=0; r<3; ++r) { //row
            row_col_sums[3+i] += A[3*r + i];
        }
    }
    return row_col_sums;
}

vector<int> GetCrossSums(vector<int> &A) {
    vector<int> cross_sums(9,0);
    for(int i=0; i<3; i++) { //row
        for(int j=0; j<3; j++) { //col
            int index = 3*i+j;
            for(int c=0; c<3; ++c) { //col
                cross_sums[index] += A[3*i + c];
            }
            for(int r=0; r<3; ++r) { //row
                cross_sums[index] += A[3*r + j];
            }
        }
    }
    return cross_sums;
}

vector<int> solution(vector<int> &A) {
    //std::cout << "Question:" << std::endl;
    //for(int i=0; i<9; i++) {
    //    std::cout << A[i] << ", ";
    //}
    //std::cout << std::endl;
    while(true) {
        //Check final condition reached
        auto row_col_sums = GetRowColSums(A);
        int first_val = row_col_sums[0];
        bool all_same = true;
        for(int i=1; i<6; i++) {
            if(first_val != row_col_sums[i]) {
                all_same = false;
                break;
            }
        }
        // break on final condition
        if(all_same) {
            break;
        }

        //Get cross sums
        auto cross_sums = GetCrossSums(A);
        //Get min and next to min values
        int min_val = std::numeric_limits<int>::max();
        for(int i=0; i<9; i++) {
            if(min_val > cross_sums[i]) {
                min_val = cross_sums[i];
            }
        }
        int next_to_min_val = std::numeric_limits<int>::max();
        for(int i=0; i<9; i++) {
            if(cross_sums[i] != min_val) {
                if(next_to_min_val > cross_sums[i]) {
                    next_to_min_val = cross_sums[i];
                }
            }
        }

        //Add difference to reach next val
        for(int i=0; i<9; i++) {
            if(min_val == cross_sums[i]) {
                int increase = (next_to_min_val - min_val)/2;
                if(increase == 0)
                    increase = 1;
                A[i] += increase;
                //std::cout << "Setting :" << A[i] << " to " << i << std::endl;
                break;
            }
        }
    }

    //std::cout << "Answer:" << std::endl;
    //for(int i=0; i<9; i++) {
    //    std::cout << A[i] << ", ";
    //}
    //std::cout << std::endl;
    return A;
}
