#include <iostream>
#include <vector>
using namespace std;

//知识补充
//对于原生数组：迭代器就是指针
//对于 std::vector 等容器：迭代器是“行为像指针”的一个被封装过的类对象；
//迭代器是一种“概念”，指针是满足这种概念的一种原始形式；而容器的迭代器是“穿上了盔甲的指针”，它们重载了运算符，提供更安全、更统一的访问方式
//用pair可以同时返回两值

//也可以使用输出参数（引用/指针）

//题目分析：其实本质上是找一个数组中差值最大的两个数，并给出两个数所处位置的下标
//解题思路：
//最简单的方法就是遍历整个数组，但是时间复杂度应该为O(n!),空间复杂度为O（n）
//暴力算法在数组过大的时候，时间复杂度过高
class Solution {
public:
    int maxProfit(vector<int>& prices) {
      int indexmin = 0;
      int indexmax = 0;
      int max = 0;
      for(int i = 0;i < prices.size();i++){
        for(int j = i + 1; j < prices.size();j++){
            if(prices[j] - prices[i] > max ){
                indexmin = i;
                indexmax = j;
                max = prices[j] - prices[i] ;
            }
        }
      }
        return max;
    }
};
//这题不妨使用动态规划算法来尝试解决问题
//先考虑数组只含两个元素的情况。
//然后每添加一个数，就看这个数与上个数组最小的数的差值是否比上个数组中最小的差值大。
//那么我们就需要一个是保存差值前一个数组的差值，以及他们最小的数
//思路可以那么说
// “我维护了两个状态变量：minPrice（历史最低价）和 maxProfit（历史最大利润）。然后进行一次遍历，不断更新这两个状态，最后 maxProfit 就是答案。这本质上是将DP数组压缩到了常数空间。”
// 与标准的dp写法相比，我没有使用一个dp数组来存储第i天卖出时候的最高价格

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        //验证合法性
        if(prices.size() <= 1){
            return 0 ;
        }
        vector<int> nums = {prices[0],prices[1]};
        int max = (prices[0] - prices[1] > 0)? 0 : prices[1] - prices[0] ;
        int min = (prices[0] - prices[1] < 0)? prices[0] : prices[1];
        for(int i = 2;i < prices.size(); i++){
            max = (prices[i] - min > max) ? prices[i] - min : max;
            min = (prices[i] - min > 0) ? min : prices[i];
        }
        return max;
    }
};
