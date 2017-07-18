//
//  5.3.cpp 同步操作和强制排序->先行发生
//  Cpp-Concurrency
//
//  Created by 刘启 on 2017/7/18.
//  Copyright © 2017年 kelele67. All rights reserved.
//  对于参数中的函数调用顺序是非指定顺序的

#include <iostream>

void foo(int a, int b) {
    std::cout << a << "," << b << std::endl;
}

int get_num() {
    static int i = 0;
    return ++i;
}

int main() {
    foo(get_num(), get_num()); // 无序调用get_num() 结果为1,2 或 2,1
}
