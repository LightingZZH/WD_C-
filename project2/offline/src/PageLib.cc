#include "../include/Configuration.h"
#include "../include/DirScanner.h"
#include "../include/rss.h"
#include "../include/PageLib.h"
#include <iostream>
#include <fstream>
using std::ofstream;
using std::cout;
using std::endl;

PageLib::PageLib(Configuration & conf, DirScanner & dirScanner)
: _conf(conf)
, _dirScanner(dirScanner)
{}

void PageLib::create()
{
    vector<string> & vecFiles = _dirScanner.files();
    RssReader rssReader(vecFiles);
    rssReader.loadFiles();
    cout<<"rssReader loadFiles over!"<<endl;
    rssReader.makePages(_vecPages);
    cout<<"rssReader makePages over!"<<endl;
}

void PageLib::store()
{
    map<string, string> & confMap = _conf.getConfigMap();
    string pageLibPath = confMap["ripepage"];
    string offsetLibPath = confMap["offset"];

    ofstream ofsPage(pageLibPath.c_str());
    ofstream ofsOffset(offsetLibPath.c_str());
    if(!ofsPage && !ofsOffset){
        cout<<"ofstream open error!"<<endl;
        return ;
    }
    
    for(size_t idx = 0; idx!=_vecPages.size(); ++idx){
        ofstream::pos_type offset = ofsPage.tellp();
        ofsPage << _vecPages[idx];
        ofsOffset << (idx+1) << '\t' << offset << '\t' << _vecPages[idx].size() << '\n';
    }

    ofsPage.close();
    ofsOffset.close();
}
