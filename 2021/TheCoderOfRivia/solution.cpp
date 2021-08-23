#include <limits>       // std::numeric_limits
#include <algorithm>    // std::min_element

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

        int max_sum = *std::max_element(row_col_sums.begin(), row_col_sums.end());

        //Get cross sums
        auto cross_sums = GetCrossSums(A);
        auto min_cross_sum_it = std::min_element(cross_sums.begin(), cross_sums.end());
        int min_cross_index = min_cross_sum_it - cross_sums.begin();

        int row_sum = row_col_sums[min_cross_index / 3];
        int col_sum = row_col_sums[3 + (min_cross_index % 3)];

        int bigger_sum = row_sum < col_sum ? col_sum : row_sum;

        A[min_cross_index] += max_sum - bigger_sum;
    }

    return A;
}
