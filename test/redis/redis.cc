#include "redis.h"

int main()
{
    Redis *redis = new Redis();
    if(!redis->connect("127.0.0.1", 6379)){
        printf("connect error!\n");
        return 0;
    }
    //redis->set("name", "Andy");
    string ret = redis->get("name");
    if(!ret.size()) cout<<"缓存未命中"<<endl;
    else cout<<ret<<endl;
    delete redis;
    return 0;
}

