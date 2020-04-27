#include <iostream>


class Phone {
public:
    Phone(const std::string& no) : _no(no) { }
    void call(const std::string no) const {
        std::cout << _no << "打电话给" << no << std::endl;
    }
    int foo(int x, int y) const {
        return x+y;
    }
    int ma;
private:
    std::string _no;
};

class Player {
public:
    Player(const std::string& media) : _media(media) {}
    void play(const std::string& clip) const {
        std::cout << _media << "播放器播放" << clip << std::endl;
    }
    int foo(int x, int y, int z) const {
        return x + y + z;
    }
    typedef int ma;
private:
    std::string _media;
};

class Computer {
public:
    Computer(const std::string& os) : _os(os) {}
    void run(const std::string& app) const {
        std::cout << "在"  << _os << "系统上运行" << app << std::endl;
    }
    void ma() {}
private:
    std::string _os;
};

// 内存布局按继承顺序由低到高排列
class SmartPhone : public Phone, public Player, public Computer {
public:
    SmartPhone(const std::string& no, const std::string& media, const std::string& os) : Phone(no), Player(media), Computer(os) {}

    int ma;
private:
};

int main() {
    SmartPhone sp("13910010072", "MP3", "windows");
    sp.call("01062332018");
    sp.play("小苹果");
    sp.run("LOL");

    Phone* phone = &sp;
    Player* player = &sp;
    Computer* computer = &sp;
    // 完成隐式类型转换时，做了偏移
    std::cout << &sp << " " << phone << " " << player << " " << computer << std::endl;
    phone->call("01062332018");
    player->play("小苹果");
    computer->run("LOL");

    SmartPhone* psp = static_cast<SmartPhone*>(player);
    std::cout << psp << std::endl;
    psp = static_cast<SmartPhone*>(computer);
    std::cout << psp << std::endl;

    // 子类隐藏基类，多个基类之间不是隐藏关系
    sp.Phone::ma = 20;
    SmartPhone::Player::ma i;
    sp.Computer::ma();
    sp.ma = 10;

    sp.Phone::foo(100, 200);
    sp.Player::foo(100, 200, 300);

    return 0;
}
