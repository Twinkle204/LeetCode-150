#include <iostream>
#include <vector>
using namespace std;
// //第一版代码，写了一个方法调换，尝试迭代解决
// //结果：超时
// class Solution {
// public:
//     void rotate(vector<int>& nums, int k) {
//         int times = k;
//         while(k > 0){
//             this -> rotateTool(nums);
//             k--;
//         }
//     }

//     void rotateTool(vector<int>& nums){
//         //做单次的调换
//         //保存最后一个数字
//         //首先检验非空
//         if (nums.empty()) return;
//         int temp = nums[nums.size() - 1];//    int temp = nums.back();
//         for(int i = nums.size() - 1;i >= 1;i--){
//             nums[i] = nums[i-1];
//         }
//         nums[0] = temp;
//         return;
//     }
// };

//方法1：我们可以使用额外的数组来将每个元素放至正确的位置。
// 用 n 表示数组的长度，我们遍历原数组，
// 将原数组下标为 i 的元素放至新数组下标为 (i+k)modn 的位置，
// 最后将新数组拷贝至原数组即可。
//这个方法使用了额外的数组
// 时间复杂度： O(n)，其中 n 为数组的长度。
// 空间复杂度： O(n)
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> newArr(n);
        for (int i = 0; i < n; ++i) {
            newArr[(i + k) % n] = nums[i];
        }
        nums.assign(newArr.begin(), newArr.end());
        //nums = newArr;效果一样，都是深拷贝
    }
};


