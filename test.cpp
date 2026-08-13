#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
using namespace std;

//解答此题过程中，我学会了利用打一些输出来验证自己到底是哪一步出了问题，不再是脑补，更快了解决了存在的各类bug
class Solution {
public:
    int hIndex(vector<int>& citations) {
    //首先想到的解法是从文章数量数n开始，反复验证是否有n篇文章引用数大于n
    //但这样的话时间复杂度为O（n^2）不是很合适
    //可以先对数组排序，选择升序
    //之后我们从第一个数组的下标开始，看他往后能否推到对应位置，可以的话就选他;
        sort(citations.begin(),citations.end());
        // cout << "排序完成" << endl;
        int h = 0;
        int currentindex = 0;
        while(currentindex < citations.size())
        {   
            //如果数组越界则这个点不可能是h值
            //或者当currentindex + citations[currentindex] - 1 为-1时数组越界
            if(citations.size() == 1 || citations[currentindex] == 0){
                if(citations.size() == 1 && citations[0] == 0)
                {
                    return 0;
                }else if(citations.size() == 1 && citations[0] != 0)
                {
                    return 1;
                }
                //若数组大小大于一，且第一个下标的值是0.为了避免后续citations[currentindex + citations[currentindex] - 1] 卡住，直接加一
                currentindex++;
                // cout<<h<<"1"<<endl;
                continue;
            }
            if(currentindex + citations[currentindex] - 1 >= citations.size())
            {//若当前大小超出了数组范围，则只需要数后续一共有多少数
                //并且这个数应该是要和之前所解答的h做比较的，谁多选谁
                h = max(int(citations.size() - currentindex),h);
                // cout<<h<<"4"<<endl;
                return h;
            }
            if(citations[currentindex + citations[currentindex] - 1] >= citations[currentindex])
            {
                h = citations[currentindex];
                // cout<<h<<"2"<<endl;
                currentindex++;
            }else
            {
                currentindex++;
                // cout<<h<<"3"<<endl;
            } 
        }

        return h;
    }
};



int main(){
    Solution s;
    vector<int> nums  = {0,0,2};
    s.hIndex(nums);
}