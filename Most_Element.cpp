#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//多数元素

 int majorityElement(vector<int>& nums) {
    //暴力求解
    int i = 0;
    sort(nums.begin(),nums.end());
    int number = nums[0];
    int max = 0;
    int mostelement = nums[0];
    int now = 0;
    while(i < nums.size()){
        if(nums[i] == number){
            now++;
        }
        else{
            if(now > max){
                max = now;
                mostelement = nums[i-1];
            }
            now = 1;
            number = nums[i];
        }
        i++;
    }
    //处理边界
    if (now > max) {
        max = now;
        mostelement = number;   // 或 nums[nums.size()-1]
    }
    return mostelement;   
}

//使用Boyer-Moore投票算法找到多数元素
// 算法原理：
// 1. 候选人(candidate)初始化为None，票数count初始化为0
// 2. 遍历数组：
// - 如果count为0，将当前元素设为候选人
// - 如果当前元素等于候选人，count加1
// - 如果当前元素不等于候选人，count减1
// 3. 遍历结束后，候选人即为多数元素
// 如果候选元素不是多数元素，那么多数元素会与其他元素一起"抵消"候选元素的票数
// 由于多数元素的数量超过一半，最终剩下的候选元素一定是多数元素
// 即使过程中候选元素可能变化，但多数元素的票数最终会占优

//     int majorityElement(vector<int>& nums) {
//     int count = 0;
//     int candidate = nums[0];

//     for (int num : nums) {
//         if (count == 0) {
//             candidate = num;
//         }
//         count += (num == candidate) ? 1 : -1;
//     }

//     return candidate;
// }



