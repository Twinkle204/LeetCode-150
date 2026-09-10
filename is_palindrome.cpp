#include <iostream>
#include <vector>
using namespace std;

//算法时间与空间复杂度较大
class Solution {
public:
    bool isPalindrome(string s) {
        //先提取出我们需要的字符
        //利用自己的filterAndLower算法
        s = filterAndLower(s);
        int i = 0;
        int j = s.size() - 1;
        while(i < j){
            if(s[i] != s[j]) return false;
            i++;
            j--;
        }
        return true;

    }
    string filterAndLower(const string& s) {
        string res;
        for (unsigned char c : s) {
            if (isupper(c)) {
                c = tolower(c);
            }
            if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
                res += c;
            }
        }
        return res;
    }
};

//尝试不利用多余的字符串，同时在一次遍历中直接得到答案
class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0, j = s.size() - 1;
        while (i < j) {
            // 跳过非字母数字
            // // 跳过 i 处的非字母数字
            // while (i < j && !isalnum(s[i])) i++;
            // // 跳过 j 处的非字母数字
            // while (i < j && !isalnum(s[j])) j--;
            // // 统一转小写比较
            // if (tolower(s[i]) != tolower(s[j])) return false;
            // i++;
            // j--;
            while (i < j && !((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9'))) i++;
            while (i < j && !((s[j] >= 'a' && s[j] <= 'z') || (s[j] >= 'A' && s[j] <= 'Z') || (s[j] >= '0' && s[j] <= '9'))) j--;

            // 统一转小写
            char left = tolower(s[i]);
            char right = tolower(s[j]);
            if (left != right) return false;

            i++;
            j--;
        }
        return true;
    }
};

