#include <iostream>
using namespace std;

// 不满足开闭原则    对扩展开放   继承（虚函数覆盖）
// 扩展功能：继承 （虚函数覆盖） 组合
class ZooShow {
public:
    void Show() {
        if (Show0()) PlayGame();
        Show1();
        Show2();
        Show3();
    }

private:
    void PlayGame() {
        cout << "after Show0, then play game" << endl;
    }

protected: // 用户调用父类的show0, 此处需要改为protected，以便于子类方法的覆盖
    virtual bool Show0() {  // 类比：抽象方法
        cout << "show0" << endl;
        return true;
    }
    virtual void Show1() {

    }
    virtual void Show2() {
        cout << "show2" << endl;
    }
    virtual void Show3() {

    }
};

class ZooShowEx1: public ZooShow {
protected:
    virtual bool Show0() {
        cout << "ZooShowEx1 - show0" << endl;
        return true;
    }
    virtual void Show2() {
        cout << "ZooShowEx1 - show2" << endl;
    }
};

class ZooShowEx2: public ZooShow {
protected:
    virtual void Show1() {
        cout << "ZooShowEx2 - show1" << endl;
    }
    virtual void Show2() {
        cout << "ZooShowEx2 - show2" << endl;
    }
};

class ZooShowEx3: public ZooShow {
protected:
    virtual void Show1() {
        cout << "ZooShowEx3 - show1" << endl;
    }
    virtual void Show3() {
        cout << "ZooShowEx3 - show3" << endl;
    }
    virtual void Show4() {
        //
    }
};
/*
*/
int main() {
    ZooShow* zs = new ZooShowEx3;
    zs->Show();
    cout << "------------" << endl;
    ZooShow* zs1 = new ZooShowEx1;
    zs1->Show();
    cout << "------------" << endl;
    ZooShow* zs2 = new ZooShowEx2;
    zs2->Show();
    return 0;
}

