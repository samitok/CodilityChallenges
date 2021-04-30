// you can use includes, for example:
#include <algorithm>
#include <unordered_set>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

bool exists(std::unordered_set<int> &argSet, int item)
{
    auto it = argSet.find(item);
    return it != argSet.end();
}

void freeup(std::unordered_set<std::unordered_set<int>*> &argSet)
{
    for (auto item : argSet) {
        delete item;
    }
}

bool solution(vector<int> &P, vector<int> &T, vector<int> &A, vector<int> &B) {
    // write your code in C++14 (g++ 6.2.0)
    std::unordered_set<int> nc_problems;
    int N = P.size();
    for(int i = 0; i <N; ++i)
    {
        if(P[i] != T[i])
        {
            nc_problems.insert(i);
        }
    }

    std::unordered_set<std::unordered_set<int>*> connected_groups; 
    int M = A.size();
    for (int i = 0; i < M; ++i) {
        nc_problems.erase(A[i]);
        nc_problems.erase(B[i]);

        std::vector<std::unordered_set<int>*> matched_groups;
        for (auto cont : connected_groups) {
            if(exists(*cont, A[i]))
            {
                cont->insert(B[i]);
                matched_groups.push_back(cont);
            }
            else if(exists(*cont, B[i]))
            {
                cont->insert(A[i]);
                matched_groups.push_back(cont);
            }
        }
        if(matched_groups.size() == 0)
        {
            auto new_group = new std::unordered_set<int>();
            new_group->insert(A[i]);
            new_group->insert(B[i]);
            connected_groups.insert(new_group);
        }
        else if(matched_groups.size() > 1)
        {
            auto first_group = matched_groups[0];
            auto second_group = matched_groups[1];

            for (int item : *second_group) {
                first_group->insert(item);
            }

            delete second_group;
            connected_groups.erase(second_group);
        }
    }

    if(nc_problems.size() > 0)
    {
        freeup(connected_groups);
        return false;
    }

    bool success = true;
    for (auto group : connected_groups) {
        int dog_persons = 0;
        int dog_toys = 0;
        for(int index : *group)
        {
            if(P[index] == 1)
            {
                ++dog_persons;
            }
            if(T[index] == 1)
            {
                ++dog_toys;
            }
        }
        if(dog_persons != dog_toys)
        {
            success = false;
            break;
        }
    }

    freeup(connected_groups);
    return success;
}
