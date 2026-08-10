#include <iostream>
#include <vector>
#include <stack>
using namespace std;

//需要计算最短路径的话，那我们问题一的贪心算法就不可用了
//目前想到两种思路，一种是从开头开始推，然后把步数入栈，每往后走一步加一，首先尽可能跳得最远
//然后如果走到最后没走通，就会回退一步，尝试少走一步，直到所有情况尝试完，就应该是最短的路径
class Solution {
public:
    int jump(vector<int>& nums) {
        stack<int> route;
        int lastindex = 0;
        //用一个额外的数组来存储当前的点已经走过几种对应路径
        vector<int>storeage (nums.size(),0);
        while(lastindex < nums.size())
        {
            if(storeage[lastindex] < nums[lastindex] )
            {
                //当前位置的下标还能跳的时候，我们优先跳最远,在减去他已经试过的路
                route.push(lastindex);
                lastindex = lastindex + nums[lastindex] - storeage[lastindex]++;
            }else{
                if (!route.empty()) 
                {
                    lastindex = route.top();
                } else 
                {
                    // 处理栈为空的情况（比如跳出循环）
                    break;
                }
            }
        }
        //当lastindex大于尾部下标时候，说明已经是最短的路径了将最后一个下标入栈后，看栈中元素个数即可；
        route.push(nums.size() - 1);
        return route.size();
            
    }
};
//测试之后，这种逻辑，会忽略中间有更快路径的方法。应该在每次跳跃的时候选择跳到数值最大的路径
//下面的代码总是能通过部分测试，但是因为一些逻辑没有写好，所以只能重写，以求通过全部案例
class Solution {
public:
    int jump(vector<int>& nums) {
        stack<int> route;
        int lastindex = 0;
        //用一个额外的数组来存储当前的点是否被走过
        //在当前lastindex能走的步数中，我们考差这一段数组，遍历寻找其中能走到的地方最远的点，前没有被走过的步数
        vector<int>storage (nums.size(),0);
        storage[0] = 1;
        route.push(0);
        //用于辅助最后一步，最后一步不能够直接算，数组会越界
        bool find = false;
        //我发现下面的代码无法处理一步或直接走到终点的情况，所以我单独写一种方法来处理
        //因为第一步没有去判定他能否直接到达终点，后面的点都是判定了的
        if(nums[0] >= nums.size() - 1)
        {
            if(nums.size() == 1)
            {
                return 0;
            }
            return 1;
        }
        while (lastindex < nums.size() - 1 && !find)
        {
            int max = -1;
            for(int i = lastindex +1;i <= min(lastindex + nums[lastindex], int(nums.size()-1));i++)
            {
                if(nums[i - 1] + i  - 1 >= nums.size() - 1)
                {//如果直接能走到
                    route.push(nums.size() - 1);
                    find = true;
                    break;
                }
                if(nums[i] + i >= max && storage[i] == 0)
                {   //如果存在两数相同，取最远的
                    //这里弄错了。既想用max来表达最远距离又想表示下标
                    lastindex = i;
                    max = nums[i] + i;
                }
                //将选择出来的最快路径入栈
            }
            if(max == -1)
            {//max ==  -1 说明目前已经不存在没走过的点了，这条路走不通
                if(route.size() <= 1) {   // 无法回溯，避免崩溃
                    return 0;
                }
                route.pop();
                lastindex = route.top();
            }else
            {
                storage[lastindex] = 1;
                route.push(lastindex);
            }
        }
        //当lastindex大于尾部下标时候，说明已经是最短的路径了将最后一个下标入栈后，看栈中元素个数即可；
        return route.size();
    }
};

//第三版
class Solution {
public:
    int jump(vector<int>& nums) {
        stack<int> route;
        int lastindex = 0;
        //用一个额外的数组来存储当前的点是否被走过
        //在当前lastindex能走的步数中，我们考差这一段数组，遍历寻找其中能走到的地方最远的点，前没有被走过的步数
        vector<int>storage (nums.size(),0);
        storage[0] = 1;
        route.push(0);
        //我发现下面的代码无法处理一步或直接走到终点的情况，所以我单独写一种方法来处理
         if(nums[0] >= nums.size() - 1)
        {
            if(nums.size() == 1)
            {
                return 0;
            }
            return 1;
        }
        while (lastindex < nums.size() - 1) {
            int max = -1;
            int bestIndex = -1;

            if (lastindex + nums[lastindex] >= nums.size() - 1) {
                route.push(nums.size() - 1);
                break;
            }
            //不能再循环内部修改循环条件，会导致bug
            int reach = min(lastindex + nums[lastindex], int(nums.size() - 1));
            for (int i = lastindex + 1; i <= reach; i++) {
                if (nums[i] + i >= max && storage[i] == 0) {
                    bestIndex = i;
                    max = nums[i] + i;
                }
            }

            if (bestIndex == -1) {
                if (route.size() <= 1) {
                    return 0;
                }
                route.pop();
                lastindex = route.top();
            } else {
                lastindex = bestIndex;
                storage[lastindex] = 1;
                route.push(lastindex);
            }
        }

        print(route);
        return (int)route.size() - 1;
    }   
    void print(stack<int>& nums){
        stack<int> temp = nums;
        while (!temp.empty()) {
            cout << temp.top() << endl;
            temp.pop();
        }
    }
};


//最佳贪心解法
//这个算法中需要维护两个值，一个是该点的右边界，另一个是该点所能跳的点所能跳到的最远距离
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        int jumps = 0;
        int curEnd = 0;    // 当前这一跳能到达的右边界
        int farthest = 0;  // 已经扫过的位置中能到达的最远下标

        for (int i = 0; i < n - 1; ++i) {
            farthest = max(farthest, i + nums[i]);

            // 已经走完当前这一跳的所有可达位置，必须再跳一次
            if (i == curEnd) {
                ++jumps;
                curEnd = farthest;
            }
        }

        return jumps;
    }
};