#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <vector>

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

    bool Serialize(const  int fd) const{
        if (fd==-1)        {
            cout<<"文件获取失败"<<endl;
            return false;
        }
        

        if(write(fd,&i,sizeof(int))==-1){
            cout<<"序列化失败"<<endl;
            return false;
        }

         cout<<"序列化成功"<<endl;
         return true;
    }

    bool Deserialize(const int fd){
        int buf;
            cout<<"aaa"<<endl;
        if (fd==-1)        {
            cout<<"反序列化失败"<<endl;
            return false;
        }

        read(fd,&buf,sizeof(int));

        cout<< "反序列化结果：" <<buf<<endl;      
        i = buf;

        return  true;
    }

    void f(){
        cout<<"i的值为："<<i<<endl;
    }
};


class SerializerForAs
{
public:
    bool Serialize(const char* pFilePath,const std::vector<A>& v){
        int fd = open(pFilePath,  O_WRONLY | O_CREAT | O_TRUNC,  00700);

        if (fd==-1)        {
            cout<<"创建文件失败"<<endl;
            return false;
        }
        
        for (int i = 0; i < v.size(); i++)
        {
           v[i].Serialize(fd);
        }
        

        if( close(fd)==-1){
            return false;
        }

         return true;
    }
    bool Deserialize(const char *pFilePath, std::vector<A>& v){
        int fd = open(pFilePath,  O_RDWR );
        if (fd==-1){
            cout<<"反序列化失败"<<endl;
            return false;
        }


        for (int i = 0; i < v.size(); i++)
        {
           v[i].Deserialize(fd);
        }
        
        
         if( close(fd)==-1){
            return false;
        }

        return  true;
    }
};


int main()
{

    {
        vector<A>v;
        SerializerForAs sfa;
        A a(1); A b(2); A c(3);
        v.push_back(a);
        v.push_back(b);
        v.push_back(c);
        for (int i = 0; i < 3; i++)
        {
            v[i].f();
        }
        sfa.Serialize("data",v);
    }

    {
        vector<A>v(3);
        SerializerForAs sfa;
        sfa.Deserialize("data",v);
        for (int i = 0; i < 3; i++)
        {
            v[i].f();
        }
    }

    return 0;
}
