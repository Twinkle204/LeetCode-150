#include <iostream>
#include <vector>
using namespace std;

//方法一
//暴力法，直接从第一个数开始走，限制走的步数，如果在限制之前就走完了，就输出true，否则输出false
//这种解法在遇到[2,0]的时候通过失败了，因为没有他走较少步数的可能性
//最大的问题在于这个方法无法解决前面的问题对于后续问题产生的影响，比如[2,5,0,0]他直接跳到0的位置，却不再考虑5的情况了
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int stepnumber = nums.size();
        int step = 0; 
        int index = 0;
        while(step < stepnumber){
            if(index >= nums.size() - 1){
                return true;
            }
            index += nums[index];
            step++;
        } 
        return false;
    }
};

//方法二：尝试逆推
//可以用一个方法来计算，从最后一个数组倒退，看哪些下标位置有到达它的能力，看最后能否推回下标0 找到完整路径
//但这样计算需要多次遍历，并且需要一个nxn的额外数组空间，使用栈，只要能找到一条路径就是可行的
//但是性能极差


//官方题解一
// 如果某一个作为 起跳点 的格子可以跳跃的距离是 3，那么表示后面 3 个格子都可以作为 起跳点
// 可以对每一个能作为 起跳点 的格子都尝试跳一次，把 能跳到最远的距离 不断更新
// 如果可以一直跳到最后，就成功了
// 实时维护最远可以到达的位置。
class Solution {
public:
    bool canJump(vector<int>& nums) {
        //最开始从零开始跳
        int k = 0;
        //每一个都跳一次，如果可以跳的更远就覆盖掉
        for (int i = 0; i < nums.size(); i++) {
            if (i > k) return false;
            k = max(k, i + nums[i]);
        }
        return true;
    }
};
