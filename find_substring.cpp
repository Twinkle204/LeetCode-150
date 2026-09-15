#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

//自己思考的解法，但是时间复杂度高
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        // 先计算一个串联子串的长度
        if(words.empty()){ 
            return {};
        }
        int wordLength = words[0].size();
        int slidingLength = words.size() * wordLength;
        int left = 0,right = wordLength - 1;
        vector<int> startindex;
        // 分析一下情况：
        // 运用滑动窗口，则有一个左右边界[left,rigth],关键在于窗口如何滑动
        // 简化问题，本体首先得能判断，一段字符串是否是串联子串，
        // 因为words中每个词长度一致，我们可以考虑运用哈希表来存储word
        // 每次滑动对应的长度，然后判断对应范围内单词是否属于构成串联数组需要的词
        unordered_map<string, int> wordsMap;
        unordered_map<string, int> originWordsMap;
        for(int i = 0;i < words.size();i++){    
            originWordsMap[words[i]]++;
        }
        //此时对应的数字就是剩余使用次数
        wordsMap = originWordsMap;
        while(right < s.size()){
            // 如果right往后退字符长度后满足条件，那就可以把right往后移动字符长度的大小
            if(wordsMap[s.substr(right - wordLength + 1,wordLength)]){
                right += wordLength;
                wordsMap[s.substr(right - 2 * wordLength + 1,wordLength)]--;
            }else{
                // 如果发现当前字符不匹配，则把left往前一位并且重置哈希表
                left++;
                right = left + wordLength - 1;
                wordsMap = originWordsMap;
            }
            // 当长度相等时就是已经找到了一个完整的字符串
            if(right - left - wordLength == slidingLength - 1){
                startindex.push_back(left);
                left++;                              // 只挪 1 位
                right = left + wordLength - 1;       // 窗口重置
                wordsMap = originWordsMap;           // 哈希表重置
            }
            
        }
        return startindex;
    }
};
// 标准解法是按偏移量分组 + 滑动窗口。核心思想：因为每个单词长度都是 wordLength，
// 所有可能的起始位置可以按 offset = 0, 1, ..., wordLength-1 分成 wordLength 组，每组内以 wordLength 为步长滑动，组内用双指针维护窗口。
// O(n · L)
// 因为 L 是单词长度（通常很小，比如 3、5），所以 O(n · L) 远小于 O(n²)。
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        if (words.empty() || s.empty()) return res;

        int wordLength = words[0].size();
        int m = words.size();
        int n = s.size();
        int slidingLength = m * wordLength;

        if (n < slidingLength) return res;

        // 目标词频
        unordered_map<string, int> target;
        for (const string& w : words) target[w]++;

        // 对每个偏移量分别滑窗
        for (int offset = 0; offset < wordLength; ++offset) {
            unordered_map<string, int> window;
            int left = offset;
            int right = offset;
            int count = 0;  // 当前窗口内已匹配的有效单词数

            while (right + wordLength <= n) {
                string w = s.substr(right, wordLength);
                right += wordLength;

                if (target.count(w)) {
                    window[w]++;
                    count++;

                    // 该单词超量，从左边收缩
                    while (window[w] > target[w]) {
                        string lw = s.substr(left, wordLength);
                        window[lw]--;
                        left += wordLength;
                        count--;
                    }

                    // 窗口内单词数正好等于 m，找到一个答案
                    if (count == m) {
                        res.push_back(left);
                        // 左移一个单词，继续找下一个
                        string lw = s.substr(left, wordLength);
                        window[lw]--;
                        left += wordLength;
                        count--;
                    }
                } else {
                    // 遇到不在 words 中的单词，窗口彻底断开
                    window.clear();
                    count = 0;
                    left = right;
                }
            }
        }

        return res;
    }
};