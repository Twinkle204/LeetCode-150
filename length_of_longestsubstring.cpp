#include <iostream>
#include <vector>
#include <numeric>
#include <unordered_map>
using namespace std;

// 滑动窗口法常常用于解决子串问题
// （left,right）满足状态（存在重复字符），则（left，right +1....end）也满足状态
// （left,right）满足状态（不存在重复字符），则（left+1....right，right）也满足状态
// 伪代码
// for(int left = 0,right = 0;right < 上限;right++){
//      第一次进入for循环是空子串，不满足状态；
//      while（满足状态）{
//          根据情况收集答案
//          left移出窗口
//          left++;
//      }
//      不满足状态(根据情况收集答案)
// }
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        // （left,right）满足状态（存在重复字符），则（left，right +1....end）也满足状态
        // （left,right）满足状态（不存在重复字符），则（left+1....right，right）也满足状态
        int ans = 0;
        unordered_map<char, int> charCnt;
        for(int left = 0,right = 0;right < s.size();right++){
            charCnt[s[right]]++;
            while (charCnt[s[right]] > 1){
                charCnt[s[left]]--;
                left++;
            }
            ans = max(ans,right - left + 1);
        }
        return ans;
    }
};