#include <cmath>

#include <vector>
#include <algorithm>

using namespace std;

//Segmented Tree Node
struct SGNode {
	char ch;
	int index;
	int valid_count;
};

class SegmentedTree {
private:
	int max_size;
	int height;
	string& S;
	vector<SGNode> tree;

private:
	// A utility function to get the middle index from corner indexes.
	int getMid(int s, int e) { return s + (e - s) / 2; }

	SGNode constructST(int start, int end, int index) {
		// If there is one element in array, store it in current node of
		// segment tree and return
		if (start == end)
		{
			tree[index] = { S[start], start, 1 };
			return tree[index];
		}

		// If there are more than one elements, then recur for left and
		// right subtrees and store the sum of values in this node
		int mid = getMid(start, end);
		auto left = constructST(start, mid, index * 2 + 1);
		auto right = constructST(mid + 1, end, index * 2 + 2);

		if (left.ch <= right.ch) {
			tree[index] = left;
		}
		else {
			tree[index] = right;
		}

		tree[index].valid_count = left.valid_count + right.valid_count;
		return tree[index];
	}

	char GetSmallestChar(int index, int& moves, bool& not_enough_moves) {
		// If leaf node
		if (tree[index].valid_count == 1)
		{
			tree[index].index = max_size;
			tree[index].valid_count = 0;
			return tree[index].ch;
		}

		char ret_val = tree[index].ch;
		if (tree[index].index == tree[index * 2 + 1].index) {
			// remove from left
			GetSmallestChar(index * 2 + 1, moves, not_enough_moves);
		}
		else if (moves >= tree[index * 2 + 1].valid_count) {
			// remove from right, enough moves
			moves -= tree[index * 2 + 1].valid_count;
			GetSmallestChar(index * 2 + 2, moves, not_enough_moves);
		}
		else {
			not_enough_moves = true;
			return ret_val;
		}

		auto& left = tree[index * 2 + 1];
		auto& right = tree[index * 2 + 2];

		if (left.valid_count == 0) {
			tree[index] = right;
		}
		else if (right.valid_count == 0) {
			tree[index] = left;
		}
		else if (left.ch <= right.ch) {
			tree[index] = left;
		}
		else {
			tree[index] = right;
		}

		tree[index].valid_count = left.valid_count + right.valid_count;
		return ret_val;
	}

	string GetString(int index) {
		// If leaf node
		if (tree[index].valid_count == 0) {
			return "";
		}
		else if (tree[index].valid_count == 1)
		{
			return string(1, tree[index].ch);
		}

		return GetString(index * 2 + 1) + GetString(index * 2 + 2);
	}

public:
	SegmentedTree(string& S_arg) : S(S_arg) {
		//Height of segment tree
		height = (int)(ceil(log2(S.size())));

		//Maximum size of segment tree
		max_size = 2 * (int)(0x1 << height) - 1;

		tree.resize(max_size, { 'z', max_size, 0 });

		constructST(0, S.size() - 1, 0);
	}

	int Size() {
		return tree[0].valid_count;
	}

	char GetSmallestChar(int& moves, bool& not_enough_moves) {
		return GetSmallestChar(0, moves, not_enough_moves);
	}

	string Remaining() {
		return GetString(0);
	}
};

string single_move_func(string& S, int moves) {
	string ans;
	int N = S.size();

	for (int j = 0; j < N; ++j) {
		// find minimum char
		char min_ch = 'z' + 1;
		int idx = 0;
		for (int i = 0; i < min(int(S.size()), moves+1); ++i) {
			if (S[i] < min_ch) {
				min_ch = S[i];
				idx = i;
			}
		}
		ans += min_ch;
		S.erase(S.begin() + idx);
		moves -= idx;
	}
	return ans;
}

string solution(string& S, int K) {
	string sorted_prefix;
	SegmentedTree st(S);

	while ((K > 0) && (st.Size() > 0)) {
		bool not_enough_moves = false;
		int test_K = K;
		char val = st.GetSmallestChar(test_K, not_enough_moves);
		if (!not_enough_moves) {
			sorted_prefix += val;
			K = test_K;
		}
		else {
			break;
		}
	}

	string rem = st.Remaining();
	if (K > 0 && rem.size() > 0) {
		rem = single_move_func(rem, K);
	}

	return sorted_prefix + rem;
}
