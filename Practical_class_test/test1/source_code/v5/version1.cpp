#include <iostream>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

class A
{
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

        if (fd==-1)        {
            cout<<"创建文件失败"<<endl;
            return false;
        }
        

        if(write(fd,&i,sizeof(int))==-1){
            cout<<"序列化失败"<<endl;
            close(fd);
            return false;
        }

        if( close(fd)==-1){
            return false;
        }

         cout<<"序列化成功"<<endl;
         return true;
    }

    bool Deserialize(const char* pFilePath){
        int fd = open(pFilePath,  O_RDWR );
        int buf;
        if (fd==-1)        {
            cout<<"反序列化失败"<<endl;
            return false;
        }

        read(fd,&buf,sizeof(int));

        cout<< "反序列化结果：" <<buf<<endl;      
        i = buf;

         if( close(fd)==-1){
            return false;
        }

        return  true;
    }

    void f(){
        cout<<"i的值为："<<i<<endl;
    }

};



using namespace std;

int main()
{

    {
        A a(31);
        a.Serialize("data");
        a.f();
    }

    {
        A a(31);
        a.Deserialize("data");
        a.f();
    }

    return 0;
}
