#include <iostream>
#include <vector>
using namespace std;


//自己的思路：
//从第一个车站开始往后试，开始的时候维护一个变量nowgas,来看当前剩余燃油量。
//解法的时间复杂度是o（n^2）对于大规模的输入会导致超时
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
    {
        int i = 0;
        int nowgas = 0;


        while(i < gas.size())
        {
            nowgas = gas[i];//判断当前剩余燃油量
            int j = i;//j表示要到达的下一站
            while(true)  
            {
                nowgas -= cost[j];
                if(nowgas < 0){//不能够到达下一个点
                    break;
                }
                j = (j + 1) % gas.size();
                nowgas += gas[j];//补充燃油
                if (i == j){//如果下一站是起点
                    return i;
                } 
            }
            i++;
        }
        return -1;
    }
};

//标准解法是贪心解法
// 先检查总油量是否 ≥ 总消耗，若不满足则直接返回 -1。
// 如果满足，则一定存在唯一起点。从 0 开始遍历，维护当前油箱油量 tank，如果 tank < 0，则说明从当前起点到当前位置无法继续，那么起点应该设为 i+1，并重置 tank = 0。
// 遍历结束后，start 就是答案。

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total = 0, tank = 0, start = 0;
        for (int i = 0; i < gas.size(); ++i) {
            int diff = gas[i] - cost[i];
            total += diff;
            tank += diff;
            if (tank < 0) {
                start = i + 1;
                // # 从当前 start 出发，到 i 已经出现油量不足，
                // # 那么 start 到 i 之间都不可能作为起点
                tank = 0;
            }
        }
        // # 总油量都不够总消耗，一定无法跑完一圈
        return total >= 0 ? start : -1;
    }
};

//另一种写法
//看不太懂
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int i = 0;
        while (i < n) {
            int sumOfGas = 0, sumOfCost = 0;
            int cnt = 0;
            while (cnt < n) {
                int j = (i + cnt) % n;
                sumOfGas += gas[j];
                sumOfCost += cost[j];
                if (sumOfCost > sumOfGas) {
                    break;
                }
                cnt++;
            }
            if (cnt == n) {
                return i;
            } else {
                i = i + cnt + 1;
            }
        }
        return -1;
    }
};
