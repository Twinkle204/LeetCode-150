#include <iostream>
#include <vector>
#include <stack>
using namespace std;

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



int main(){
    vector<int> nums = {1,1,1,1};
    Solution A;
    int a = A.jump(nums); 
    cout << a;
}