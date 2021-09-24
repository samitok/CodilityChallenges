string solution(string &S) {
    int total = S.size();
    int f = 0; //fixed
    while(f < total) {
        if(S.substr(f,3) == "abb") {
            S[f] = 'b';
            S[f+1] = 'a';
            S[f+2] = 'a';
            f -= 2;
        }
        else {
            f++;
        }

        if(f<0) {
            f = 0;
        }
    }
    return S;
}