//
//  receiver.cpp 消息传递框架与完整的ATM机示例
//  Cpp-Concurrency
//
//  Created by 刘启 on 2017/7/25.
//  Copyright © 2017年 kelele67. All rights reserved.
//  receiver 类

namespace messaging {
    class receiver {
        queue q;
    public:
        operator sender() {
            return sender(&q);
        }
        dispatcher wait() {
            return dispatcher(&q);
        }
    };
}

