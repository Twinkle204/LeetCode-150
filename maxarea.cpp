#include <iostream>
#include <vector>
#include <cstdlib>  // 整数 abs#include <cstdlib>  
using namespace std;


//暴力法，时间效率低
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0, right = 1;
        int max = 0;
        for(int i = 0;i < height.size()-1;i++){
            for(int j = i + 1;j < height.size();j++){
                if ((j - i) * min(height[j], height[i]) > max)
                {
                    right = j;
                    left = i;
                    max = (right - left) * min(height[right], height[left]);
                }
            }
        }        
        return max;
    }
};


// 对于左边界，如果往右扩展只能是比他高的点,但如果往左就既要考虑高度又要看下标
// 对于右边界，如果往左扩展也只能是比他高的点，如果往右就既要考虑又要看下标
// 从两端开始，往内寻找更优解，就只需要调整更矮的一边
// 一次只需要调整一步，如果有更大的则替换，最后只需要返回最大面积即可
// 这样只需要遍历一次，是标准的双指针贪心算法
class Solution {
public:
    int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1;
    int maxArea = 0;
    while (left < right) {
        int h = min(height[left], height[right]);
        maxArea = max(maxArea, (right - left) * h);
        if (height[left] < height[right]) left++;
        else right--;
    }
    return maxArea;
    }
};