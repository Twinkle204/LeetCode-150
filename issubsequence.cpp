#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    bool isSubsequence(string s, string t) {
        int ss = 0;
        int ts = 0;
        while(ss < s.size() + 1 && ts < t.size()){
            if(s[ss] == t[ts]){
                ss++;
            }
            ts++;
        }
        if(ss == s.size()){
            return true;
        }else{
            return false;
        }
    }
};