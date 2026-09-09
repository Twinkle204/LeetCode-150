#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

//方法一：把单词都提取出来再按照顺序输出
//时间O(N),空间O(N)
class Solution {
public:
    string reverseWords(string s) {
        vector<string> strs;
        string word = "";
        for(int i = 0;i < s.size();i++){
            while(s[i] == ' '){
                if(word != ""){
                    strs.push_back(word);
                    word = "";
                }
                i++;
            }
            if(i < s.size())
                word += s[i];
        }
        if(word != ""){
            strs.push_back(word);
        }
        
        s = "";
        for(int i = strs.size() - 1 ;i > -1;i--){
            s += strs[i];
            s += " ";
        }
        if (!s.empty()) {  
            s.pop_back();  // 移除最后一个字符 ' '
        }
        return s;
    }
};


//这个方法的时间和空间占比很低
//先把每个单词翻转，再把整个数组反转，就可以得到所得
//需要处理多余的' '
class Solution {
public:
    string reverseWords(string s) {
        int i = 0;
        //先拿到一个单词的开头和结尾下标
        int begin = -1;
        int end = -1;
        int offset = 0;//用来记录由多余a空格造成的位置偏移
        while(i < s.size()){
            //当遇到字符的时候，注意偏移
            if(s[i] != ' '){
                if(begin == -1){
                    s[i - offset] = s[i];
                    if (offset > 0) s[i] = ' ';  // 清空原位置
                    begin = i - offset;
                    end = i - offset;
                }else{
                    s[i - offset] = s[i];
                    if (offset > 0) s[i] = ' ';
                    end++;
                }
            }else if(s[i] == ' ' && begin != -1){
                //当给你遇见第一个空白字符的时候
                //调换顺序，并且不加偏移值
                reverse(s.begin() + begin, s.begin() + end + 1);//reverse的使用，后半部分需要把范围拉到末尾索引+1位置
                // 在压缩后的单词后面放置一个分隔空格
                s[end + 1] =' ' ;
                begin = -1;
                end = -1;
                
            }else{
                // 遇到多余空格（连续空格或前导空格），增加偏移
                offset++;
            }
            i++;
        } 
        // 处理最后一个单词（没有后续空格）
        if(begin != -1){
             reverse(s.begin() + begin, s.begin() + end + 1);
        }
        // 删除尾部所有多余空格（压缩后可能残留尾部空格）
        while (!s.empty() && s.back() == ' ') {
            s.pop_back();
        }
        // 最后翻转整个数组就好了
        reverse(s.begin(),s.end());
        return s;
    }
};

// 双指针
class Solution {
public:
    string reverseWords(string s) {
        // 使用双指针
        int m = s.size() - 1;
        string res;
        // 除去尾部空格
        while (s[m] == ' ' && m > 0) m--;
        int n = m; // n是另一个指针
        while (m >= 0) {
            while (m >= 0 && s[m] != ' ') m--;
            res += s.substr(m + 1, n - m) + " "; // 获取单词并加上空格
            while (m >= 0 && s[m] == ' ') m--;
            n = m;
        }
        return res.substr(0, res.size() - 1); // 忽略最后一位的空格
    }
};