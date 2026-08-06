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

//方法二，数组翻转我们可以先将所有元素翻转，
//这样尾部的 k mod n 个元素就被移至数组头部，然后我们再翻转 [0,k mod n−1] 区间的元素
//和 [k mod n,n−1] 区间的元素即能得到最后的答案。

class Solution {
public:
    //反转方法  
    void reverse(vector<int>& nums, int start, int end) {
        while (start < end) {
            swap(nums[start], nums[end]);
            start += 1;
            end -= 1;
        }
    }

    void rotate(vector<int>& nums, int k) {
        k %= nums.size();
        //先反转整个数组
        reverse(nums, 0, nums.size() - 1);
        //再分段分解
        reverse(nums, 0, k - 1);
        reverse(nums, k, nums.size() - 1);
    }
};

//方法三 环状替换
//一个一个替换，这样空间复杂度就只有一了，但是只转一次会漏掉一些点，需要多转两轮，但多转几轮是一个需要计算的值
//简单一点的话可以直接计数
//思考过程
//容易发现，当回到初始位置 0 时，有些数字可能还没有遍历到，此时我们应该从下一个数字开始重复的过程，
//可是这个时候怎么才算遍历结束呢？我们不妨先考虑这样一个问题：从 0 开始不断遍历，最终回到起点 0 的过程中，我们遍历了多少个元素？
//an = bk
//b = 从起点出发，第一次回到起点时，总共走了多少步（即访问了多少个元素，包括起点）。
//每绕数组一圈（即累加一个 n），在实际数值累加中就会增加 n。
//一共走了 b 步，每一步都加了 k，所以实际数值累加总量是 b × k。
//所以说an一定是n和k的公倍数，又因为我们在第一次回到起点的时候就结束了，所以a要尽可能小，所以an是n和k的最小公倍数lcm(n,k)
//所以说 b 就为 lcm(n,k)/k。
//最大公约数x最小公倍数 = 两数之乘积
//所以nk/lcm（n,k）=gcd(n,k)(gcd是最大公约数)
//这样就可以求出n，那最后只需要设置循环次数为n就可以了


