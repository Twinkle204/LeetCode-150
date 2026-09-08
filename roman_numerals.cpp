#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

//解法一：哈希表求解
class Solution {
public:
    int romanToInt(string s) {
        //用哈希表来存储对应关系
        int number = 0;
        unordered_map<char, int> map = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
        {'C', 100},
        {'D', 500},
        {'M', 1000}
    };
    //unordered_map 底层是哈希表，每次查找需要进行哈希计算和桶寻址，对于只有 7 个键值对的场景，开销相对较大。
    for (int i = 0; i < s.size(); i++) {
        // 如果当前字符比后一个小，则减去当前值（如 IV）
        if (i + 1 < s.size() && map[s[i]] < map[s[i + 1]]) {
            number -= map[s[i]];
        } else {
            number += map[s[i]];
        }
    }
    return number;
    }
};

// 优化解法
// 优化点一：用数组替代 unordered_map
// 优化点二：减少重复的数组/哈希查找
// 优化点三：缓存字符串长度

class Solution {
public:
    int romanToInt(string s) {
        // 1. 使用栈上分配的数组（256个int，仅1KB），比哈希表快得多
        int map[256] = {};
        map['I'] = 1; map['V'] = 5; map['X'] = 10;
        map['L'] = 50; map['C'] = 100; map['D'] = 500; map['M'] = 1000;

        int result = 0;      // 【修复】必须为局部变量
        int n = s.size();    // 【优化】缓存长度

        for (int i = 0; i < n; ++i) {
            int cur = map[s[i]];      // 只查一次表
            // 判断减法规则：当前值小于下一位的值（如 IV, XC）
            if (i + 1 < n && cur < map[s[i + 1]]) {
                result -= cur;
            } else {
                result += cur;
            }
        }
        return result;
    }
};


//或者不想维护256大小数组，用switch
class Solution {
public:
    int romanToInt(string s) {
        int result = 0;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            int cur = getVal(s[i]);
            if (i + 1 < n && cur < getVal(s[i + 1])) result -= cur;
            else result += cur;
        }
        return result;
    }
private:
    // 定义为静态内联，无函数调用开销（编译器自动内联）
    static inline int getVal(char c) {
        switch(c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default: return 0;
        }
    }
};