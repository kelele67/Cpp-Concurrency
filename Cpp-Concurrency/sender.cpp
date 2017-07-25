//
//  sender.cpp 消息传递框架与完整的ATM机示例
//  Cpp-Concurrency
//
//  Created by 刘启 on 2017/7/25.
//  Copyright © 2017年 kelele67. All rights reserved.
//  sender类

namespace messaging {
    class sender {
        queue *q;
    public:
        sender() : q(nullptr) {}
        explicit sender(queue* q_) : q(q_) {}
        template <typename Message>
        void send(Message const& msg) {
            if (q) {
                q->push(msg);
            }
        }
    };
}

