#include <iostream>
#include <vector>
#include <numeric>
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
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        // 维护一个sum变量动态调整数组和
        int left = 0, sum = 0;
        int minLen = INT_MAX;
        for (int right = 0; right < n; ++right) {
            sum += nums[right];
            while (sum >= target) {
                minLen = min(minLen, right - left + 1);
                sum -= nums[left];
                ++left;
            }
        }
        return minLen == INT_MAX ? 0 : minLen;
    }
};