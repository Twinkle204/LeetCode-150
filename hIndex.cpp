#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

class Solution {
public:
    int hIndex(vector<int>& citations) {
    //首先想到的解法是从文章数量数n开始，反复验证是否有n篇文章引用数大于n
    //但这样的话时间复杂度为O（n^2）不是很合适
    //可以先对数组排序，选择升序
    //之后我们从第一个数组的下标开始，看他往后能否推到对应位置，可以的话就选他;
        sort(citations.begin(),citations.end());
        int h = 0;
        int currenth = 0;
        int currentindex = 0;
        //这种算法适用于数组长度满足条件的时候,但例如[99,100]这种就判断不了
        // while(currentindex < citations.size())
        // {   
        //     //如果数组越界则这个点不可能是h值
        //     //或者当currentindex + citations[currentindex] - 1 为-1时数组越界
        //     if(currentindex + citations[currentindex] - 1 > citations.size() ||
        //         currentindex + citations[currentindex] - 1 < 0)
        //     {
        //         currentindex++;
        //         continue;
        //     }
        //     if(citations[currentindex + citations[currentindex] - 1] >= citations[currentindex])
        //     {
        //         h = citations[currentindex];
        //         currentindex++;
        //     }else
        //     {
        //         currentindex++;
        //     } 
        // }
        //经过思考后，需要修改为
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
                cout<<h<<endl;
                continue;
            }
            if(currentindex + citations[currentindex] - 1 > citations.size())
            {//若当前大小超出了数组范围，则只需要数后续一共有多少数
                h = citations.size() - currentindex;
                return h;
            }
            if(citations[currentindex + citations[currentindex] - 1] >= citations[currentindex])
            {
                h = citations[currentindex];
                cout<<h<<endl;
                currentindex++;
            }else
            {
                currentindex++;
                cout<<h<<endl;;
            } 
        }


        return h;
    }
};

//题解一：排序
//时间复杂度：O(nlogn)，其中 n 为数组 citations 的长度。即为排序的时间复杂度。
//空间复杂度：O(logn)，其中 n 为数组 citations 的长度。即为排序的空间复杂度。
//思考：同样是排序算法，但是我的算法很复杂，因为我是从小的部分开始排序，需要考虑一些诸如越界的特殊情况
//而从尾部开始算，只用考虑比不比h大即可
class Solution {
public:
    int hIndex(vector<int>& citations) {
        sort(citations.begin(), citations.end());
        int h = 0, i = citations.size() - 1;
        while (i >= 0 && citations[i] > h) {
            h++;
            i--;
        }
        return h;
    }
};

//题解二:计数排序
//时间复杂度：O(n)，其中 n 为数组 citations 的长度。需要遍历数组 citations 一次，以及遍历长度为 n+1 的数组 counter 一次。
//空间复杂度：O(n)，其中 n 为数组 citations 的长度。需要创建长度为 n+1 的数组 counter。
//这种解法，在于对数据进行了预处理，减少了后续处理的复杂度
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size(), tot = 0;
        vector<int> counter(n + 1);
        for (int i = 0; i < n; i++) {
            if (citations[i] >= n) {
                counter[n]++;
            } else {
                counter[citations[i]]++;
            }
        }
        for (int i = n; i >= 0; i--) {
            tot += counter[i];
            if (tot >= i) {
                return i;
            }
        }
        return 0;
    }
};

//方法三：二分搜索
//时间复杂度：O(nlogn)，其中 n 为数组 citations 的长度。需要进行 logn 次二分搜索，每次二分搜索需要遍历数组 citations 一次。
//空间复杂度：O(1)，只需要常数个变量来进行二分搜索。
//二分搜索解法之所以在 H 指数问题中可行，其根本原因在于判定条件具有“单调性”（即逻辑上的二段性）。
//这种单调性保证了我们可以在答案区间上进行二分查找，而不会遗漏正确答案。
//注意这里的mid是下标mid，如果mid可行，那比他大的数可能可行，如果mid不可行，那比他大的数一定不可行
class Solution {
public:
    int hIndex(vector<int>& citations) {
        int left=0,right=citations.size();
        int mid=0,cnt=0;
        while(left<right){
            // +1 防止死循环
            mid=(left+right+1)>>1;
            cnt=0;
            for(int i=0;i<citations.size();i++){
                if(citations[i]>=mid){
                    cnt++;
                }
            }
            if(cnt>=mid){
                // 要找的答案在 [mid,right] 区间内
                left=mid;
            }else{
                // 要找的答案在 [0,mid) 区间内
                right=mid-1;
            }
        }
        return left;
    }
};












