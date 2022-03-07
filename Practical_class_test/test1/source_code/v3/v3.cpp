#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

using namespace std;

class A {
private:
    int i;
public:
    A(){
        i = 0;
    }

    explicit A(int j){
        i = j;
    }
    
    bool Serialize(const char* pFilePath) const{
        int fd = open(pFilePath,  O_WRONLY | O_CREAT | O_TRUNC,  00700);

        if (fd == -1)        {
            cout << "创建文件失败" << endl;
            return false;
        }
        

        if(write(fd, &i, sizeof(int)) == -1) {
            cout << "序列化失败" << endl;
            close(fd);
            return false;
        }

        if(close(fd) == -1){
            return false;
        }

         cout << "序列化成功" << endl;
         return true;
    }

    bool Deserialize(const char* pFilePath) {
        int fd = open(pFilePath,  O_RDWR );
        int buf;
        if (fd == -1)        {
            cout << "文件获取失败" << endl;
            return false;
        }

        read(fd, &buf, sizeof(int));

        cout << "反序列化结果：" << buf << endl;      
        i = buf;

        if(close(fd) == -1){
            return false;
        }

        return  true;
    }

    bool Serialize(const int fd) const {
        if (fd == -1)        {
            cout << "创建文件失败" << endl;
            return false;
        }
        

        if(write(fd, &i, sizeof(int)) == -1) {
            cout << "序列化失败" << endl;
            return false;
        }

         cout << "序列化成功" << endl;
         return true;
    }

    bool Deserialize(const int fd) { 
        int buf;

        if (fd == -1) {
            cout << "文件获取失败" << endl;
            return false;
        }

        read(fd, &buf, sizeof(int));

        cout << "反序列化结果：" << buf << endl;      
        i = buf;

        return  true;
    }

    void f(){
        cout << "A -> f()" << endl;
    }
};


class B {
private:
    int i;
    int j;
public:
    B(){
        i = 0;
        j = 1;
    }

    explicit B(int k) {
        i = k;
        j = k + 1;
    }
    
    bool Serialize(const char* pFilePath) const{
        int fd = open(pFilePath,  O_WRONLY | O_CREAT | O_TRUNC,  00700);

        if (fd == -1) {
            cout << "创建文件失败" << endl;
            return false;
        }
        

        if(write(fd, &i, sizeof(int)) == -1){
            cout << "序列化失败" << endl;
            close(fd);
            return false;
        }

        if (write(fd, &j, sizeof(int)) == -1) {
            cout << "序列化失败" << endl;
            close(fd);
            return false;
        }

        if(close(fd) == -1){
            return false;
        }

         cout << "序列化成功" << endl;
         return true;
    }

    bool Deserialize(const char* pFilePath) {
        int fd = open(pFilePath,  O_RDWR );
        int buf1, buf2, r;
        if (fd == -1)        {
            cout << "文件获取失败" << endl;
            return false;
        }

        r = read(fd, &buf1, sizeof(int));
        
        if (r == -1 || r == 0) {
            cout << "反序列化失败" << endl;
            return false;
        }

        r = read(fd, &buf2, sizeof(int));
        if (r == -1 || r == 0) {
            cout << "反序列化失败" << endl;
        }
        cout << "反序列化结果：" << buf1 << " , " << buf2 << endl;      
        i = buf1, j = buf2;

        if(close(fd) == -1){
            return false;
        }

        return  true;
    }

    bool Serialize(const  int fd) const {
        if (fd == -1) {
            cout << "文件获取失败" << endl;
            return false;
        }
        

        if(write(fd, &i, sizeof(int)) == -1) {
            cout << "序列化失败" << endl;
            return false;
        }

        if (write(fd, &j, sizeof(int)) == -1) {
            cout << "序列化失败" << endl;
            return false;
        }

         cout << "序列化成功" << endl;
         return true;
    }

    bool Deserialize(const int fd) { 
        int buf1, buf2, r;
        if (fd == -1) {
            cout << "文件获取失败" << endl;
            return false;
        }

        r = read(fd, &buf1, sizeof(int));
        if (r == -1 || r == 0) {
            cout << "反序列化失败" << endl;
            return false;
        }

        r = read(fd, &buf2, sizeof(int));
        if (r == -1 || r == 0) {
            cout << "反序列化失败" << endl;
            return false;
        }

        cout << "反序列化结果：" << buf1 << " , " << buf2 << endl;      
        i = buf1, j = buf2;
        
        return true;
    }

    void f() {
        cout << "B -> f()" << endl;
    }
};

// 手动多态
// 形成一个通用接口
struct Serialized {
    int nType;
    void* pObj;
    Serialized() {}
    Serialized(int _nType, void* _pObj): nType(_nType), pObj(_pObj) {}
};

class Serializer {
public:
    Serializer() {}

    explicit Serializer(int j) {}

    bool Serialize(const char* pFilePath, vector<Serialized>& v) const {
        int fd = open(pFilePath, O_WRONLY | O_CREAT | O_TRUNC,  00700);

        if (-1 == fd) {
            return false;
        }


        for (int i = 0; i < v.size(); ++i) {
            int r = write(fd, &v[i].nType, sizeof(int));
            if (r == -1 || r == 0) {
                return false;
            }
            if (v[i].nType == 0) {
                A *a = (A *)v[i].pObj;
                a->Serialize(fd);
            } else {
                B *b = (B *)v[i].pObj;
                b->Serialize(fd);
            }
        }


        if (close(fd) == -1) {
            return false;
        }

        return true;
    }

    bool DeSerialize(const char* pFilePath, vector<Serialized>& v) const {
        int fd = open(pFilePath,  O_RDWR );

        if (-1 == fd) {
            return false;
        }

        for (;;) {
            int Type;
            int r = read(fd, &Type, sizeof(int));
            Serialized serialized;
            if (r == -1 || r == 0) {
                return false;
            }
            if (Type == 0) {
                A *a = new A();     
                if (!a->Deserialize(fd)) {
                    return false;
                }
                serialized.nType = Type;
                serialized.pObj = (void *)a;
                v.push_back(serialized);
                delete a;           // 
            } else {
                B *b = new B();
                if (!b->Deserialize(fd)) {
                    return false;
                }
                serialized.nType = Type;
                serialized.pObj = (void *)b;
                v.push_back(serialized);
                delete b;    
            }
        }

        if (close(fd) == -1) {
            return false;
        }
        return true;
    }
};


int main () {
    {
        A a1(2), a2(4);
        B b1(5), b2(7);
        Serialized s1(0, &a1), s2(0, &a2),
                   s3(1, &b1), s4(1, &b2);
        vector<Serialized> pq;
        pq.push_back(s1);
        pq.push_back(s2);
        pq.push_back(s3);
        pq.push_back(s4);
        Serializer serializer;
        serializer.Serialize("data", pq);
    }

    {
        vector<Serialized> pq;
        Serializer serializer;
        serializer.DeSerialize("data", pq);
        for (int i = 0; i < pq.size(); ++i) {
            int nType = pq[i].nType;
            if (nType == 0) {
                cout << "A -> f()" << endl;
            } else {
                cout << "B -> f()" << endl;
            }
        }
    }
    return 0;
}