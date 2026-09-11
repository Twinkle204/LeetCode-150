class Solution {
public:
    bool isSubsequence(string s, string t) {
        
    }
};

//ai解答
//标准纵向扫描
//以第一个字符串为标准，从第一个字母开始往后推，这样就只用遍历一次字符串数组
class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()) return "";
        for (int i = 0; i < strs[0].size(); ++i) {
            char c = strs[0][i];
            for (int j = 1; j < strs.size(); ++j) {
                if (i >= strs[j].size() || strs[j][i] != c) {
                    return strs[0].substr(0, i);
                }
            }
        }
        return strs[0];
    }
};


