//
//  7.15.cpp 无锁数据结构的例子->写一个无锁的线程安全队列
//  Cpp-Concurrency
//
//  Created by 刘启 on 2017/7/21.
//  Copyright © 2017年 kelele67. All rights reserved.
//  无锁队列中的线程互助
//  无锁队列中简单的帮助性push()的实现

#include <atomic>
#include <memory>

template <typename T>
class lock_free_queue {
private:
    void set_new_tail(counted_node_ptr &old_tail,
                      counted_node_ptr const &new_tail) {
        node* const current_tail_ptr = old_tail.ptr;
        while (!tail.compare_exchange_weak(old_tail, new_tail) && old_tail.ptr == current_tail_ptr);
        if (old_tail.ptr == current_tail_ptr) {
            free_external_counter(old_tail);
        }
        else {
            current_tail_ptr->release_ref();
        }
    }
public:
    void push(T new_value) {
        std::unique_ptr<T> new_data(new T(new_value));
        counted_node_ptr new_next;
        new_next.ptr new_next;
        new_next.ptr = new node;
        new_next.external_count = 1;
        counted_node_ptr old_tail = tail.load();
        for ( ; ; ) {
            increase_external_count(tail, old_tail);
            T* old_data = nullptr;
            if (old_tail.ptr->data.compare_exchange_strong(old_data, new_data.get())) {
                counted_node_ptr old_next = {0};
            }
        }
    }
};
