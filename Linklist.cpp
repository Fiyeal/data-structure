#include <cstddef>
#include <iostream>
#include <new>

struct Node {
    int value;
    Node *next;
};

class Head {
private:
    int size;
    Node *next;

public:
    Head() : size(0), next(nullptr) {};
    inline bool empty() const { return size == 0; }
    inline int get_size() const { return size; }
    
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
    }

    void shift_left(int num)
    {
        if (num < 0) {
            std::cout << "所移位数不能为负" << std::endl;
            return;
        }
        num = num % size;
        int i = 0;
        auto p = this -> next;
        while (i < num) {
            p = p -> next;
            ++i;
        }
    }

};

using List = Head;


int main() {
    int a[] = {0, 1, 2, 3, 4, 5, 3};
    List l(a, sizeof(a)/sizeof(int));
    l.show();
    l.sort();
    // l.insert(0, 22);
    // std::cout << l.get_size() << std::endl;
    // l.show();
    // l.remove(0);
    // std::cout << l.get_size() << std::endl;
    l.show();
    return 0;
}