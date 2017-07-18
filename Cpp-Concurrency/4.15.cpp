//
//  4.15.cpp 使用同步操作简化代码->使用消息传递的同步操作
//  Cpp-Concurrency
//
//  Created by 刘启 on 2017/7/18.
//  Copyright © 2017年 kelele67. All rights reserved.
//  ATM逻辑类的简单实现

#include <string>

struct card_inserted {
    std::string account;
};

class atm {
    messaging::receiver incoming;
    messaging::sender bank;
    messaging::sender inerface_hardware;
    void (atm::*state);
    std::string account;
    std::string pin;
    void waiting_for_card() {
        inerface_hardware.send(display_enter_card());
        incoming.wait().handle<card_inserted> ([&](card_inserted const& msg) {
            account = msg.account;
            pin = "";
            inerface_hardware.send(display_enter_pin());
            state = &atm::getting_pin;
        });
    }
    void getting_pin();
public:
    void run() {
        state = &atm::waiting_for_card;
        try {
            for (; ;) {
                (this->*state)();
            }
        }
        catch(messaging::close_queue const&) {
            
        }
    }
};
