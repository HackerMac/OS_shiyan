#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <algorithm>


using namespace std;

class ILSerializable {
public:
    virtual bool Serialize(int fd) = 0;
    virtual ILSerializable *Deserialize(int fd) = 0;
    virtual bool GetType(int &nType) = 0;

public:
    ILSerializable(){

    }

    virtual ~ILSerializable() {

    }
  
};


class A : public ILSerializable {
private:
    int i;

public:
    A() {}
    A(int k) {
        i = k;
    }
    virtual ~A() {}

    void f() {
        cout << "f() -> A: " << i << endl;
    }

    virtual bool GetType(int &nType) {
        nType = 1;
        return true;
    }

    virtual bool Serialize(int fd) {
        if (fd == -1) {
            return false;
        }
        int w = write(fd, &i, sizeof(int));
        if (w == -1 || w == 0) {
            return false;
        }
        cout << "Serialize succ" << endl;
        return true;
    }


    virtual ILSerializable* Deserialize (int fd) {
        if (fd == -1) {
            cout << "open file faild" << endl;
            return NULL;
        }
        A *p = new A();
        int w = read(fd, &(p->i), sizeof(int));
        if (w == 0 || w == -1) {
            return NULL;
        }
        return p;
    }

};


class B : public ILSerializable {
private:
    int i, j;

public:
    B() {}
    B(int k) {
        i = k;
        j = k + 1;
    }
    void f() {
        cout << "f() -> B: " << i << " " << j << endl;
    }
    virtual ~B() {

    }

    virtual bool GetType(int &nType) {
        nType = 0;
        return true;
    }

    virtual bool Serialize(int fd) {
        if (fd == -1) {
            return false;
        }
        int w = write(fd, &i, sizeof(int));
        if (w == -1 || w == 0) {
            return false;
        }
        w = write(fd, &j, sizeof(int));
        if (w == 0 || -1 == w) {
            return false;
        }
        cout << "Serialize succ" << endl;
        return true;
    }


    virtual ILSerializable* Deserialize (int fd) {
        if (fd == -1) {
            cout << "open file faild" << endl;
            return NULL;
        }
        B *p = new B();
        int w = read(fd, &(p->i), sizeof(int));
        if (w == 0 || w == -1) {
            return NULL;
        }
        w = read(fd, &(p->j), sizeof(int));
        if (w == 0 || w == -1) {
            return NULL;
        }
        return p;
    }

};

// 添加宏 防止魔数 magic_number 
class CLSerializer {
public:
    bool Serialize(const char* filename, vector<ILSerializable*> &v) const {
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00700);
        if (fd == -1) {
            cout << "open file faild" << endl;
            return false;
        }
        for (int i = 0; i < v.size(); ++i) {
            int type;
            v[i]->GetType(type);      
            if (write(fd, &type, sizeof(int)) == -1) {
                close(fd);
                return false;
            }
            v[i]->Serialize(fd);
        }
        if (close(fd) == -1) {
            cout << "close file faild" << endl;
            return false;
        }
        return true;
    }

    bool DeSerialize(const char* filename, vector<ILSerializable*> &v) const {
        int fd = open(filename, O_RDWR, 00700);
        if (fd == -1) {
            cout << "open file faild" << endl;
            return false;
        }

        while(true) {
            int nType;
            int r = read(fd, &nType, sizeof(int));
            if (-1 == r || r == 0) {
                break;
            }
            int type;
            for (int i = 0; i < m_vSerialized.size(); ++i) {
                m_vSerialized[i]->GetType(type);
                if (type == nType) {
                    ILSerializable *p = m_vSerialized[i]->Deserialize(fd);
                    if (p != NULL)
                        v.push_back(p);
                }
            }
        }

        if (close(fd) == -1) 
            return false;
        return true;
    }


    void reagister(ILSerializable* pSerialized) {
        m_vSerialized.push_back(pSerialized);
        // ? 
    }  

private:
    vector<ILSerializable*> m_vSerialized;

};
// 小记
// dynamic_cast 转换类型失败会返回NULL

int main () {
    {
        A *a1 = new A(1);
        A *a2 = new A(2);
        B *b1 = new B(1);
        B *b2 = new B(2);
        vector<ILSerializable*> v;
        v.push_back(a1);
        v.push_back(a2);
        v.push_back(b1);
        v.push_back(b2);
        CLSerializer s;
        s.Serialize("data", v);
        delete a1;
        delete a2;
        delete b1;
        delete b2;
    }

    {
        CLSerializer s;
        A a;
        B b;
        s.reagister(&a);
        s.reagister(&b);
        vector<ILSerializable*> v;
        s.DeSerialize("data", v);

        for (int i = 0; i < v.size(); ++i) {
            A *p = dynamic_cast<A *>(v[i]);
            if (p != nullptr) 
                p->f();
            B *c = dynamic_cast<B *>(v[i]);
            if (c != nullptr) 
                c->f();
        }
    }
}
