#include <iostream>
#include <vector>
using namespace std;

//直接解法消耗最少，但是不美观
class Solution {
public:
    string intToRoman(int num) {
        //对数据进行分析
        //测试案例范围是1 <= n <= 3999
        //说明我们在写的时候需要注意分几个阶段从千位到个位的来看
        //先处理千位情况：
        string s = "";
        while(num >= 1000){
            num -= 1000;
            s += "M";
        }
        //再处理百位情况
        //如果是4或者9开头
        while(num >= 100){
            if(num / 100 == 4){
                s += "CD";
                num -= 400;
            }else if(num / 100 == 9){
                s += "CM";
                num -= 900;
            }else if(num >= 500){
                s += "D";
                num -= 500;
            }else{
                s += "C";
                num -= 100;
            }
        }
        //十位
        while(num >= 10){
            if(num / 10 == 4){
                s += "XL";
                num -= 40;
            }else if(num / 10 == 9){
                s += "XC";
                num -= 90;
            }else if(num >= 50){
                s += "L";
                num -= 50;
            }else{
                s += "X";
                num -= 10;
            }
        }
        //个位
        while(num >= 1){
            if(num / 1 == 4){
                s += "IV";
                num -= 4;
            }else if(num / 1 == 9){
                s += "IX";
                num -= 9;
            }else if(num >= 5){
                s += "V";
                num -= 5;
            }else{
                s += "I";
                num -= 1;
            }
        }
        return s;
    }
};

//官方解法
// 编程时，可以建立一个数值-符号对的列表 valueSymbols，按数值从大到小排列。
// 遍历 valueSymbols 中的每个数值-符号对，若当前数值 value 不超过 num，
// 则从 num 中不断减去 value，直至 num 小于 value，然后遍历下一个数值-符号对。
// 若遍历中 num 为 0 则跳出循环。


const pair<int, string> valueSymbols[] = {
    {1000, "M"},
    {900,  "CM"},
    {500,  "D"},
    {400,  "CD"},
    {100,  "C"},
    {90,   "XC"},
    {50,   "L"},
    {40,   "XL"},
    {10,   "X"},
    {9,    "IX"},
    {5,    "V"},
    {4,    "IV"},
    {1,    "I"},
};

class Solution {
public:
    string intToRoman(int num) {
        string roman;
        for (const auto &[value, symbol] : valueSymbols) {
            //const auto & + 结构化绑定是目前 C++17 中最优雅、最高效的迭代遍历写法
            //// 你的写法（C++17）
            // for (const auto &[value, symbol] : valueSymbols) { 
            //     // 循环体 
            // }

            // // 编译器在底层实际展开的样子（伪代码）
            // {
            //     // 1. 获取迭代器（begin 和 end）
            //     auto begin = valueSymbols.begin(); 
            //     auto end = valueSymbols.end();   
                
            //     // 2. 传统的迭代器 for 循环
            //     for (; begin != end; ++begin) {  
            //         // 3. 解引用迭代器，拿到容器中的元素（这里是 pair 对象）
            //         const auto& element = *begin; 
                    
            //         // 4. 结构化绑定：把 element.first 映射给 value，element.second 映射给 symbol
            //         const auto& value = element.first;   
            //         const auto& symbol = element.second; 
                    
            //         // 5. 执行你的循环体代码
            //     }
            // }
            while (num >= value) {
                num -= value;
                roman += symbol;
            }
            if (num == 0) {
                break;
            }
        }
        return roman;
    }
};


//硬编码
const string thousands[] = {"", "M", "MM", "MMM"};
const string hundreds[]  = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
const string tens[]      = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
const string ones[]      = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

class Solution {
public:
    string intToRoman(int num) {
        return thousands[num / 1000] + hundreds[num % 1000 / 100] + tens[num % 100 / 10] + ones[num % 10];
    }
};

