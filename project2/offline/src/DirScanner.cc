#include "../include/Configuration.h"
#include "../include/DirScanner.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <iostream>
using std::cout;
using std::endl;

DirScanner::DirScanner(Configuration & conf)
: _conf(conf)
{}

void DirScanner::operator()()
{
    map<string, string> & confMap = _conf.getConfigMap();
    string dirName = confMap["yuliao"];
    traverse(dirName);
}

vector<string> & DirScanner::files()
{
    return _vecFiles;
}

void DirScanner::print()
{
    for(auto & c : _vecFiles)
        cout<<c<<endl;
}

void DirScanner::traverse(const string & dirName)
{
    DIR *dir;
    dir = opendir(dirName.c_str());
    if(!dir){
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    chdir(dirName.c_str());
    struct dirent *mydirent;
    struct stat mystat;

    while((mydirent = readdir(dir))){
        stat(mydirent->d_name, &mystat);
        if(S_ISDIR(mystat.st_mode)){    //判断该文件是不是目录
            if(!strcmp(mydirent->d_name, ".") || 
               !strcmp(mydirent->d_name, ".."))
                continue;
            else traverse(mydirent->d_name);    //如果是目录则进行递归遍历
        }else{
            string fileName;
            fileName.append(getcwd(NULL, 0))
                    .append("/")
                    .append(mydirent->d_name);
            _vecFiles.push_back(fileName);
        }
    }
    chdir("..");
    closedir(dir);
}
