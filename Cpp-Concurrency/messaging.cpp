//
//  messaging.cpp 消息传递框架与完整的ATM机示例
//  Cpp-Concurrency
//
//  Created by 刘启 on 2017/7/25.
//  Copyright © 2017年 kelele67. All rights reserved.
//  简单的消息队列

#include <mutex>
#include <condition_variable>
#include <queue>
#include <memory>

namespace messaging {
    struct message_base {
        virtual ~message_base() {}
    };
    
    template <typename Msg>
    struct wrapped_message: message_base {
        Msg contents;
        explicit wrapped_message(Msg const& contents_) : contents(contents_) {}
    };
    
    class queue {
        std::mutex mut;
        std::condition_variable cond;
        std::queue<std::shared_ptr<message_base> > msgq;
    public:
        template <typename T>
        void push(T const& msg) {
            std::lock_guard<std::mutex> lk(mut);
            msgq.push(std::make_shared<wrapped_message<T> >(msg));
            cond.notify_all();
        }
        std::shared_ptr<message_base> wait_and_pop() {
            std::unique_lock<std::mutex> lk(mut);
            cond.wait(lk, [&] { return !msgq.empty(); });
            auto res = msgq.front();
            msgq.pop();
            return res;
        }
    };
}
