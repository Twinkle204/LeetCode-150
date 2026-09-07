#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

//要以常数级的时间复杂度，插入、删除和获取随机元素
//变长数组可以在 O(1) 的时间内完成获取随机元素操作，但是由于无法在 O(1) 的时间内判断元素是否存在，
//因此不能在 O(1) 的时间内完成插入和删除操作。
//哈希表可以在 O(1) 的时间内完成插入和删除操作，但是由于无法根据下标定位到特定元素，
//因此不能在 O(1) 的时间内完成获取随机元素操作。为了满足插入、删除和获取随机元素操作的时间复杂度都是 O(1)，
//需要将变长数组和哈希表结合，变长数组中存储元素，哈希表中存储每个元素在变长数组中的下标。

class RandomizedSet {
public:
    RandomizedSet() {
        srand((unsigned)time(NULL));
        //每次实例化时，以当前时间作为种子，确保 rand() 产生的随机序列每次运行都不一样。
    }
    
    bool insert(int val) {
        if (indices.count(val)) {// 查哈希表，判断是否存在
            return false;
        }
        int index = nums.size();//新元素将放在数组末尾，下标即当前长度
        nums.emplace_back(val);//将值加入数组尾部
        indices[val] = index;//在哈希表中记录该值对应的下标
        return true;
    }
    //删除交换的方法避免了后续再查找随机数组的时候由于对应位置没元素报错
    bool remove(int val) {
        if (!indices.count(val)) { // 查哈希表，判断是否存在
            return false;
        }
        int index = indices[val];// 获取待删除值的下标（假设删除 20，index = 1）
        int last = nums.back();// 获取数组最后一个元素（last = 30）
        nums[index] = last;// 【覆盖】用 30 覆盖掉 index=1 的位置 -> nums 变为 [10, 30, 30]
        indices[last] = index;// 【更新哈希】将 30 的下标从 2 改为 1 -> indices[30] = 1
        nums.pop_back(); // 【删除末尾】移除末尾元素 -> nums 变为 [10, 30]
        indices.erase(val); //【擦除旧键】从哈希表中删除 20 的条目
        return true;
    }
    
    int getRandom() {
        int randomIndex = rand()%nums.size();// 随机生成 [0, size-1] 的下标
        return nums[randomIndex];// 直接通过数组下标取值
    }
private:
    vector<int> nums;
    unordered_map<int, int> indices;//unordered_map<key,value>
};

// cpp中的hash table
// std::unordered_map 并非一个完全独立的实现，它建立在一个通用的哈希表（_Hashtable） 之上。
// 这个通用哈希表只负责管理数据存储、冲突解决和扩容等核心机制，而 unordered_map 和 unordered_set 只是对它的不同封装
// std::unordered_map 的底层核心是一个 “哈希桶”（Hash Bucket） 数组
// 节点（Node）：每个节点都包含键值对数据和一个指向下一个节点的指针，用来形成链表
// 哈希函数：从键到索引的映射
// 当你插入一个键值对时，需要三步来确定它该放进哪个“桶”。
// 计算哈希值：哈希表会调用一个哈希函数（std::hash<Key>），将你的键（Key）转换成一个 size_t 类型的整数，即哈希值（Hash Value）。
// 对于 int 等整数类型，哈希值通常就是它本身。
// 对于 std::string，则会通过一个算法（如乘以31或131）来计算。
// 扰动计算：为了减少碰撞，实现可能会对原始哈希值进行一些位运算（扰动），让结果更随机。
// 映射到桶：最后，用处理过的哈希值对桶数组的总数（bucket_count()）取模，得到桶的索引。在 GCC 和 MSVC 的实现中，桶的数量通常是 2 的幂，因此可以用更快的位运算（& (bucket_count - 1)）来代替取模（%）。