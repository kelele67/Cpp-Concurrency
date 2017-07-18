//
//  3.7.cpp 避免死锁的进阶指导
//  1. 避免嵌套锁
//  2. 避免在持有锁时调用用户提供的代码
//  3. 使用固定顺序获取锁
//  4. 使用锁的层次结构
//
//  Cpp-Concurrency
//
//  Created by 刘启 on 2017/7/18.
//  Copyright © 2017年 kelele67. All rights reserved.
//  使用层次锁来避免死锁

#include <mutex>

class hierarchical_mutex {
public:
    explicit hierarchical_mutex(unsigned level) {}
    void lock() {}
    void unlock() {}
};

hierarchical_mutex high_level_mutex(1000);
hierarchical_mutex low_level_mutex(5000);

int do_low_level_stuff() {
    return 42;
}

int low_level_func() {
    std::lock_guard<hierarchical_mutex> lk(low_level_mutex);
    return do_low_level_stuff();
}

void high_level_stuff(int some_param) {
    
}

void high_level_func() {
    std::lock_guard<hierarchical_mutex> lk(high_level_mutex);
    high_level_stuff(low_level_func());
}

void thread_a() {
    high_level_func();
}

hierarchical_mutex other_mutex(100);
void do_other_stuff() {
    
}

void other_stuff() {
    high_level_func();
    do_other_stuff();
}

void thread_b() {
    std::lock_guard<hierarchical_mutex> lk(other_mutex);
    other_stuff();
}

int main() {
    
}
