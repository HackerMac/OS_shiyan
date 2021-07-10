#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
#include <algorithm>


using namespace std;

// 手动多态
// 形成一个通用接口
// struct Serialized {
//     int nType;
//     void* pObj;
//     Serialized() {}
//     Serialized(int _nType, void* _pObj): nType(_nType), pObj(_pObj) {}
// };

class Serialized {
public:
    virtual void f() = 0;
    virtual bool Serialize(const char* filename) = 0;
    virtual bool Deserialize(const char* filename, const Serialized obj) = 0;
};

class A : public Serialized {
private:
    int i;
public:
    A () {}
    A (int k) {
        i = k;
    }

    virtual void f() {
        cout << "f() -> A" << endl;
        return;
    }


    virtual bool Serialize(const char* filename) {
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | 07000);

        if (-1 == fd) {
            return false;
        }

        int r = write(fd, &i, sizeof(int));
        if (r == 0 || r == -1) {
            cout << "Serialize faild" << endl;
            return false;
        }

        if (close(fd) == -1) {
            cout << "close file faild" << endl;
            return false;
        }
        return true;
    }

    virtual bool Deserialize(const char* filename, const Serialized obj) {
        int fd = open(filename, O_RDWR);

        if (-1 == fd) {
            cout << "open file faild" << endl;
            return false;
        }

        int r = read(fd, &i, sizeof(int));
        if (r == 0 || -1 == r) {
            cout << "Deserialize faild" << endl;
            return false;
        }

        if (close(fd) == -1) {
            cout << "close file faild" << endl;
            return false;
        }

        return true;
    }

};

class B : public Serialized {
private:
    int i, j;

public:  
    B () {}
    B (int k) {
        i = k;
        j = k + 1;
    }

    virtual void f() {
        cout << "f() -> B" << endl;
    }

    virtual bool Serialize(const char* filename) {
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | 07000);

        if (-1 == fd) {
            return false;
        }

        int r = write(fd, &i, sizeof(int));
        if (r == 0 || r == -1) {
            cout << "Serialize faild" << endl;
            return false;
        }

        if (close(fd) == -1) {
            cout << "close file faild" << endl;
            return false;
        }
        return true;
    }

    virtual bool Deserialize(const char* filename, const Serialized obj) {
        int fd = open(filename, O_RDWR);

        if (-1 == fd) {
            cout << "open file faild" << endl;
            return false;
        }

        int r = read(fd, &i, sizeof(int));
        if (r == 0 || -1 == r) {
            cout << "Deserialize faild" << endl;
            return false;
        }

        if (close(fd) == -1) {
            cout << "close file faild" << endl;
            return false;
        }

        return true;
    }

};


class C : public Serialized {
private:
    int i;
public:
    C () {}
    C (int k) {
        k = i;
    }

    virtual void f() {
        cout << "f() -> C" << endl;
    }

    virtual bool Serialize(const char* filename) {
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | 07000);

        if (-1 == fd) {
            return false;
        }

        int r = write(fd, &i, sizeof(int));
        if (r == 0 || r == -1) {
            cout << "Serialize faild" << endl;
            return false;
        }

        if (close(fd) == -1) {
            cout << "close file faild" << endl;
            return false;
        }
        return true;
    }

    virtual bool Deserialize(const char* filename, const Serialized obj) {
        int fd = open(filename, O_RDWR);

        if (-1 == fd) {
            cout << "open file faild" << endl;
            return false;
        }

        int r = read(fd, &i, sizeof(int));
        if (r == 0 || -1 == r) {
            cout << "Deserialize faild" << endl;
            return false;
        }

        if (close(fd) == -1) {
            cout << "close file faild" << endl;
            return false;
        }

        return true;
    }
};

class D : public Serialized {

private:
    int i;

public: 
    
    D() {}
    D(int k) {
        i = k;
    }


    virtual void f() {
        cout << "f() -> D" << endl;
    }

    virtual bool Serialize(const char* filename) {
        int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC | 07000);

        if (-1 == fd) {
            return false;
        }

        int r = write(fd, &i, sizeof(int));
        if (r == 0 || r == -1) {
            cout << "Serialize faild" << endl;
            return false;
        }

        if (close(fd) == -1) {
            cout << "close file faild" << endl;
            return false;
        }
        return true;
    }

    virtual bool Deserialize(const char* filename, const Serialized obj) {
        int fd = open(filename, O_RDWR);

        if (-1 == fd) {
            cout << "open file faild" << endl;
            return false;
        }

        int r = read(fd, &i, sizeof(int));
        if (r == 0 || -1 == r) {
            cout << "Deserialize faild" << endl;
            return false;
        }

        if (close(fd) == -1) {
            cout << "close file faild" << endl;
            return false;
        }

        return true;
    }

};

class Serializeor : public Serialized {
public:
    virtual void Serialize() {

    }

    virtual void Deserialize() {

    }

    virtual void Deserialize() {

    }
};


int main () {
    {
        A a(1);
        B b(2);
        C c(2);
        D d(2);
        vector<Serialized> pq;
        pq.push_back(a);
        pq.push_back(b);
        pq.push_back(c);
        pq.push_back(d);
        for (int i = 0; i < pq.size(); ++i) {
            pq[i].Serialize("data");
        }
    }

    {
        Serialized 
    }
}