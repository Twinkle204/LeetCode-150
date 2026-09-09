#include <iostream>
#include <vector>
using namespace std;

//以二维数组来解
//性能较差
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;  // 特殊处理

        int n = s.size();
        int cycle = 2 * numRows - 2;      // 正确周期
        int numCols = (n / cycle) * (numRows - 1) + (n % cycle > 0 ? 1 : 0) 
                    + (n % cycle > numRows ? (n % cycle - numRows) : 0); // 精确列数（可简化）
        // 更简单：直接用足够大的列数，如 n，避免计算复杂
        vector<vector<char>> zarr(numRows, vector<char>(n, '\0')); // 列数直接设为 n，绝对够用

        int row = 0, col = 0;
        bool goingDown = true;

        for (char c : s) {
            zarr[row][col] = c;
            if (goingDown) {
                if (row == numRows - 1) {  // 到达底部
                    goingDown = false;
                    row--;
                    col++;
                } else {
                    row++;
                }
            } else {
                if (row == 0) {           // 到达顶部
                    goingDown = true;
                    row++;
                } else {
                    row--;
                    col++;
                }
            }
        }

        string result;
        for (int r = 0; r < numRows; r++) {
            for (int c = 0; c < n; c++) {
                if (zarr[r][c] != '\0') result += zarr[r][c];
            }
        }
        return result;
    }
};

//方法二：压缩二维数组空间
//只需要将对应的char填入对应行，并不需要二维数组
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows < 2)
            return s;
        vector<string> rows(numRows);
        int i = 0, flag = -1;
        for (char c : s) {
            rows[i].push_back(c);
            if (i == 0 || i == numRows -1)
                flag = - flag;
            i += flag;
        }
        string res;
        for (const string &row : rows)
            res += row;
        return res;
    }
};

//方法三：直接构造
// 我们来研究方法一中矩阵的每个非空字符会对应到 s 的哪个下标（记作 idx），从而直接构造出答案。
// 由于 Z 字形变换的周期为 t=2r−2，因此对于矩阵第一行的非空字符，其对应的 idx 均为 t 的倍数，即 idx≡0(modt)；同理，对于矩阵最后一行的非空字符，应满足 idx≡r−1(modt)。
// 对于矩阵的其余行（行号设为 i），每个周期内有两个字符，第一个字符满足 idx≡i(modt)，第二个字符满足 idx≡t−i(modt)。

class Solution {
public:
    string convert(string s, int numRows) {
        int n = s.length(), r = numRows;
        if (r == 1 || r >= n) {
            return s;
        }
        string ans;
        int t = r * 2 - 2;
        for (int i = 0; i < r; ++i) { // 枚举矩阵的行
            for (int j = 0; j + i < n; j += t) { // 枚举每个周期的起始下标
                ans += s[j + i]; // 当前周期的第一个字符
                if (0 < i && i < r - 1 && j + t - i < n) {
                    ans += s[j + t - i]; // 当前周期的第二个字符
                }
            }
        }
        return ans;
    }
};
