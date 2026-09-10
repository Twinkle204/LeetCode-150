#include <iostream>
#include <vector>
using namespace std;

// 暴力求法就是一个个数对比，复杂度是O(n^2)较
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int start = 0;
        int end = numbers.size() - 1;
        int index1 = 0;
        int index2 = numbers.size() - 1;
        vector<int> v;
        for(int i = numbers.size() - 1; i >= 0;i--){

            while(numbers[index1] + numbers[index2] != target){
                // if(index1 == index2){
                //     index1 = ++start;
                //     index2 = --end;
                // }
                //这一步是多余的，因为不会再这种变化中漏掉值
                //数学证明：
                //使用双指针的实质是缩小查找范围。那么会不会把可能的解过滤掉？答案是不会。假设 numbers[i]+numbers[j]=target 是唯一解，
                // 其中 0≤i<j≤numbers.length−1。初始时两个指针分别指向下标 0 和下标 numbers.length−1，左指针指向的下标小于或等于 i，右指针指向的下标大于或等于 j。
                // 除非初始时左指针和右指针已经位于下标 i 和 j，否则一定是左指针先到达下标 i 的位置或者右指针先到达下标 j 的位置。
                // 如果左指针先到达下标 i 的位置，此时右指针还在下标 j 的右侧，sum>target，因此一定是右指针左移，左指针不可能移到 i 的右侧。
                // 如果右指针先到达下标 j 的位置，此时左指针还在下标 i 的左侧，sum<target，因此一定是左指针右移，右指针不可能移到 j 的左侧。


                if(numbers[index1] + numbers[index2] > target){
                    index2--;
                }else if (numbers[index1] + numbers[index2] < target)
                {
                    index1++;
                }else{
                    
                }
                
            }
        }
        v = {index1 +1 ,index2 + 1};
        return v;
    }
};

// 方法二：二分查找
//先固定一个数，再根据有序性找另外一个数
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        for (int i = 0; i < numbers.size(); ++i) {
            int low = i + 1, high = numbers.size() - 1;
            while (low <= high) {
                int mid = (high - low) / 2 + low;
                if (numbers[mid] == target - numbers[i]) {
                    return {i + 1, mid + 1};
                } else if (numbers[mid] > target - numbers[i]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
        }
        return {-1, -1};
    }
};

