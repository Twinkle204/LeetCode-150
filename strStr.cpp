#include <iostream>
#include <vector>
using namespace std;



//暴力解法
//时间O((n-m) *m) 空间O（1）
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;

        int n = haystack.size();
        int m = needle.size();

        for (int i = 0; i + m <= n; ++i) {
            int j = 0;
            while (j < m && haystack[i + j] == needle[j]) {
                ++j;
            }
            if (j == m) return i;
        }

        return -1;
    }
};

//KMP算法
//时间O（m+n）
//KMP 算法是一个快速查找匹配串的算法，它的作用其实就是本题问题：如何快速在「原字符串」中找到「匹配字符串」
//KMP 利用已匹配部分中相同的「前缀」和「后缀」来加速下一次的匹配。
//关键在于推导next数组
class Solution {
public:
    int strStr(string s, string p) {
        int n = s.size(), m = p.size();
        if(m == 0) return 0;
        //设置哨兵
        // 目的是让 j 下标从 0 开始，省去 j 从 -1 开始的麻烦。
        s.insert(s.begin(),' ');
        p.insert(p.begin(),' ');
        vector<int> next(m + 1);
        //预处理next数组
        // next[j] 的定义是：子串 p[1..j] 的最长相等真前缀和真后缀的长度
        for(int i = 2, j = 0; i <= m; i++){
            //因为对于字符串他的前缀的后缀其实和后缀的后缀是一样的，通过这个方式可以更快得到next数组的值
            while(j and p[i] != p[j + 1]) j = next[j];
            if(p[i] == p[j + 1]) j++;
            next[i] = j;
        }
        //匹配过程
        // j 表示的是“已经匹配成功的长度”
        for(int i = 1, j = 0; i <= n; i++){
            while(j and s[i] != p[j + 1]) j = next[j];
            if(s[i] == p[j + 1]) j++;
            if(j == m) return i - m;
        }
        return -1;
    }
};



















