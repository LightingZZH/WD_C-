#include "DictProducer.h"
#include "SplitTool.h"
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

size_t DictProducer::nBytesCode(const char ch)
{
    if(ch & (1<<7)){
        size_t nBytes = 1;
        for(int idx = 0; idx!=6; ++idx){
            if(ch & (1<<(6-idx))){
                ++nBytes;
            }
            else break;
        }
        return nBytes;
    }
    return 1;
}

void DictProducer::build_dict()
{
    for(auto & c : _enfiles){
        ifstream ifs(c.c_str());
        if(!ifs){
            cout<<"open file "<<c<<" error "<<endl;
            return;
        }
        string line;
        while(std::getline(ifs, line)){
            for(auto & c : line){
                if(ispunct(c) ||isdigit(c)) c = ' ';
                if(c>='A' && c<='Z') c += 32;
            }
            istringstream iss(line);
            string word;
            while(iss >> word){
                ++_dict[word];
            }
        }
    }
}

void DictProducer::build_cn_dict()
{
    for(auto & c : _cnfiles){
        ifstream ifs(c.c_str());
        if(!ifs){
            cout<<"open file "<<c<<" error "<<endl;
            return;
        }
        string line;
        while(std::getline(ifs, line)){
            for(auto & c : line){
                if(c>='A' && c<='Z') c += 32;
                if(ispunct(c) ||isdigit(c)) c = ' ';
            }
            vector<string> words = _splitTool->cut(line);
            for(auto & c : words){
                if(c == " ") continue;
                ++_dict[c];
            }
        }
    }
}

void DictProducer::store_dict(const char * filepath)
{
    ofstream ofs(filepath);
    if(!ofs){
        cout<<"ofstream open file error!"<<endl;
        return;
    }
    for(auto & c : _dict){
        ofs<<c.first<<" "<<c.second<<"\n";
    }
    ofs.close();
}

void DictProducer::store_index(const char * filepath)
{
    ofstream ofs(filepath);
    if(!ofs){
        cout<<"ofstream open file error!"<<endl;
        return ;
    }
    int cnt = 0;
    for(auto & dict : _dict){
        for(size_t idx = 0; idx!=dict.first.size(); ++idx){
            size_t nBytes = nBytesCode(dict.first[idx]);
            string c = dict.first.substr(idx, nBytes);
            _index[c].insert(cnt);
            idx += (nBytes - 1);
        }
        ++cnt;
    }
    for(auto & index : _index){
        ofs<<index.first;
        for(auto & c : index.second){
            ofs<<" "<<c;
        }
        ofs<<"\n";
    }
    ofs.close();
}

void DictProducer::show_files() const
{
    for(auto & c : _enfiles){
        cout<<c<<endl;
    }
    cout<<"------------"<<endl;
    for(auto & c : _cnfiles){
        cout<<c<<endl;
    }
}

void DictProducer::show_dict() const
{
    for(auto & c : _dict){
        cout<<c.first<<" "<<c.second<<endl;
    }
}

void DictProducer::push_dict(const string & word)
{
    ++_dict[word];
}

void DictProducer::get_files()
{
    char name[512] = {0};
    char lan_path[512] = {0};
    char end_path[512] = {0};
    DIR *dir;
    dir = opendir(_dir.c_str());
    if(!dir) cout<<"opendir error"<<endl;

    int ret = chdir(_dir.c_str());
    if(ret==-1) cout<<"chdir error"<<endl;

    getcwd(name, sizeof(name));

    struct dirent *p;
    while((p = readdir(dir))){
        if(!strcmp(p->d_name, "en")){
            memset(lan_path, 0, 512);
            sprintf(lan_path,"%s%s",name,"/en");
            DIR *dir1 = opendir(lan_path);
            if(!dir1) cout<<"opendir error"<<endl;
            struct dirent *p1;
            while((p1 = readdir(dir1))){
                if(!strcmp(p1->d_name, ".") || !strcmp(p1->d_name, "..")) continue;
                memset(end_path, 0 ,512);
                sprintf(end_path, "%s%s%s", lan_path, "/", p1->d_name);
                string endpath(end_path);
                _enfiles.push_back(endpath);
            }
            closedir(dir1);
        }else if(!strcmp(p->d_name, "cn")){
            memset(lan_path, 0, 512);
            sprintf(lan_path,"%s%s",name,"/cn");
            DIR *dir1 = opendir(lan_path);
            if(!dir1) cout<<"opendir error"<<endl;
            struct dirent *p1;
            while((p1 = readdir(dir1))){
                if(!strcmp(p1->d_name, ".") || !strcmp(p1->d_name, "..")) continue;
                memset(end_path, 0 ,512);
                sprintf(end_path, "%s%s%s", lan_path, "/", p1->d_name);
                string endpath(end_path);
                _cnfiles.push_back(endpath);
            }
            closedir(dir1);
        }
    }
    closedir(dir);
}
