#include <iostream>
#include <vector>
using namespace std;

//从末尾开始算，注意循环的越界问题即可
class Solution {
public:
    int lengthOfLastWord(string s) {
        int n = s.size()- 1;
        while( n != -1 && s[n] == ' '){
            n--;
        }
        int number = 0;
        while( n != -1 && s[n] != ' '){
            n--;
            number++;
        }
        return number;
    }
};