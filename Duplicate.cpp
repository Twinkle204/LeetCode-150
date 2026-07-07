#include <iostream>
#include <vector>
using namespace std;
//删除有序数组中重复的数||
int removeDuplicates(vector<int>& nums) {
    int slow,fast;
    slow = nums[0];
    fast = 0;
    vector<int> Newnums;// 直接创建对象，不用 new
    Newnums.push_back(nums[fast++]); // 或者 Newnums[slow] = nums[fast]，但需要先 resize
    //快指针往前走，问题关键在于如何判断，是否已经有两个数字了
    bool duplicate = false;
    //判断向量大小要用.size ,sizeof 返回的是字节数
    while(fast < nums.size()){
        if(nums[fast] != slow){
        //如果说数字和当前数字不同
            slow = nums[fast];
            Newnums.push_back(nums[fast++]);;
            duplicate = false;
        }else if(!duplicate){
            duplicate = true;
            Newnums.push_back(nums[fast++]);
        }else{
            fast++;
        }
    }
    nums = Newnums;
    return nums.size();
}
//“利用空间位置（索引差）来代替状态变量”的编程思想
//最简单的写法
//可以扩展到k个元素的情况
// class Solution {
//     public int removeDuplicates(int[] nums) {
//         // 数组中的一号和二号元素肯定不用删除
//         int count = 2;
//         for(int i = 2 ; i < nums.length ; i++) {
//             if(nums[i] != nums[count-2]) {
//                 nums[count++] = nums[i];
//             }
//         }
//         return count;
//     }
// }