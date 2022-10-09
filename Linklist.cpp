#include <iostream>
#include <new>

struct Node {
    int value;
    Node *next = nullptr;
};

class Head {
private:
    int size; // 链表长度
    Node *next; // 指向下一节点

public:
    Head() : size(0), next(nullptr) { };
    
    // 头插法以数组构造链表
    Head(int a[], int len) : size(0), next(nullptr)
    {
        for (int i = 0; i < len; ++i) {
            auto p = new Node();
            p -> value = a[len - 1 - i];
            p -> next = this -> next;
            this -> next = p;
            ++size;
        }
    }

    ~Head()
    {
        auto p = this -> next;
        while (p != nullptr) {
            auto tmp = p;
            p = p -> next;
            delete tmp;
        }
    }

    // 判空
    inline bool empty() const { return size == 0; }
    
    // 获取链表长度
    inline int get_size() const { return size; }

    // 在pos位置插入值val
    void insert(int pos, int val)
    {
        if (pos < 0 || pos > size) {
            std::cout << "越界插入" << std::endl;
            return;
        }
        auto node = new Node();
        node -> value = val;
        if (pos == 0) {
            node -> next = this -> next;
            this -> next = node;
        }
        else {
            int i = 1;
            auto p = this -> next;
            while (i < pos) {
                p = p -> next;
                ++i;
            }
            node -> next = p -> next;
            p -> next = node;
        }
        ++size;
        return;
    }

    // 移除某位置的节点
    void remove(int pos)
    {
        if (pos < 0 || pos >= size) {
            std::cout << "越界移除" << std::endl;
            return;
        }
        if (pos == 0) {
            auto des = this -> next;
            this -> next = des -> next;
            delete des;
        }
        else {
            auto p = this -> next;
            int i = 1;
            while (i < pos) {
                p = p -> next;
                ++i;
            }
            auto des = p -> next;
            p -> next = des -> next;
            delete des;
        }
        --size;
        return;
    }

    // 输出链表元素到标准输出流
    void show() {
        if (this -> empty()) {
            std::cout << "Empty list" << std::endl;
            return;
        }
        auto p = this -> next;
        while (p != nullptr) {
            std::cout << p -> value << " ";
            p = p -> next;
        }
        std::cout << std::endl;
        return;
    }

    // 排序，冒泡排序法，复杂度O(n^2)
    void sort()
    {
        if (this -> empty())
            return;
        bool flag = true;
        while (flag) {
            flag = false;
            for (auto p = this -> next; p -> next != nullptr; p = p -> next) {
                if (p -> value > p -> next -> value) {
                    flag = true;
                    std::swap(p -> value, p -> next -> value);
                }
            }
        }
        return;
    }

    // 左右移位，dir为方向，l表示左移位，r表示右移位
    void shift(int num, char dir)
    {
        if (!(dir == 'r' || dir == 'l')) {
            std::cout << "请输入正确的方向指示(l/r)" << std::endl;
            return;
        }
        if (num < 0) {
            std::cout << "所移位数不能为负" << std::endl;
            return;
        }
        num = num % size;
        if (num == 0 || this -> empty())
            return;
        if (dir == 'r')
            num = size - num;
        int i = 1;
        auto p = this -> next;
        while (i < num) { // 找到截断部分的左侧节点
            p = p -> next;
            ++i;
        }
        auto trail = this -> next;
        while (trail -> next != nullptr) // 找到链表尾节点
            trail = trail -> next;
        trail -> next = this -> next;
        this -> next = p -> next;
        p -> next = nullptr;
        return;
    }


    // 先排序，再去重
    void remove_duplicates()
    {
        if (this -> empty())
            return;
        this -> sort();
        auto pre = this -> next;
        auto p = pre -> next;
        while (p != nullptr) {
            if (pre -> value == p -> value) {
                auto tmp = p;
                p = p -> next;
                delete tmp;
                --size;
            }
            else {
                pre -> next = p;
                pre = p;
                p = pre -> next;
            }
        }
        pre -> next = nullptr;
        return;
    }
    

    // 利用头插法进行reverse
    void reverse()
    {
        if (this -> empty() || size == 1)
            return;
        auto p = this -> next;
        this -> next = nullptr;
        while (p != nullptr) {
            auto tmp = p;
            p = p -> next;
            tmp -> next = this -> next;
            this -> next = tmp;
        }
        return;
    }

    // 两个有序列表合并，结果保持为一个有序列表
    void combine(Head &h)
    {
        this -> sort();
        h.sort();
        if (h.empty())
            return;
        Node a{0, this -> next}, b{0, h.next};
        Node *pa = &a, *pb = &b;
        while (pa -> next && pb -> next) {
            if (pa -> next -> value > pb -> next -> value) {
                auto p = new Node();
                p -> value = pb -> next -> value;
                p -> next = pa -> next;
                pa -> next = p;
                pb = pb -> next;
            }
            pa = pa -> next;
        }
        if (pa -> next == nullptr && pb -> next != nullptr) {
            while (pb -> next != nullptr) {
                auto p = new Node();
                p -> value = pb -> next -> value;
                p -> next = pa -> next;
                pa -> next = p;
                pa = pa -> next;
                pb = pb -> next;
            }
        }
        this -> next = a.next;
        return;
    }
};

using List = Head;


int main() {
    int a[] = {0, 1, 2, 3};
    int b[] = {1, 3, 3, 4, 5};
    List l1(a, sizeof(a)/sizeof(int));
    List l2(b, sizeof(b)/sizeof(int));

    l1.show();
    l2.show();
    l1.combine(l2);
    l1.show();
    return 0;
}