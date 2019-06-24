#include "rss.h"
#include <regex>
#define FILEPATH "coolshell.xml"

RssReader::RssReader()
{
   // _rss.reserve(1024);
    cout<<"RssReader()"<<endl;
}

void RssReader::parseRss()
{
    XMLDocument doc;
    doc.LoadFile(FILEPATH);
    if(0!=doc.Error()){
        cout<<"load file error"<<endl;
        return;
    }

    XMLElement * root = doc.RootElement();
    XMLElement * channel = root->FirstChildElement("channel");
    if(NULL==channel){
        cout<<"get first child element error"<<endl;
        return;
    }
    
    std::regex pattern("<.*?>");
    struct RssItem rss;
    XMLElement * title = channel->FirstChildElement("title");
    rss.title = title->GetText();
    //cout<<"title: "<<title->GetText()<<endl;
    XMLElement * link = channel->FirstChildElement("link");
    rss.link = link->GetText();
    //cout<<"link: "<<link->GetText()<<endl;
    XMLElement * description = channel->FirstChildElement("description");
    rss.description = description->GetText();
    //cout<<"description: "<<description->GetText()<<endl;
    XMLElement * content = channel->FirstChildElement("content:encoded");
    if(NULL==content) rss.content = "";
    else{
        rss.content = content->GetText();
        cout<<"content: "<<content->GetText()<<endl;
    }
    _rss.push_back(rss);

    XMLElement * item = channel->FirstChildElement("item");
    
    while(item)
    {
        XMLElement *item_child = item->FirstChildElement();
        struct RssItem Rss;
        while(item_child)
        {
            if(!strcmp(item_child->Name(),"title")){
                if(!item_child->GetText()) Rss.title = "";
                else{
                    Rss.title = item_child->GetText();
                    //cout<<"title: "<<item_child->GetText()<<endl;
                }
            }else if(!strcmp(item_child->Name(),"link")){
                if(!item_child->GetText()) Rss.link = "";
                else{
                    Rss.link = item_child->GetText();
                    //cout<<"link: "<<item_child->GetText()<<endl;
                }
            }else if(!strcmp(item_child->Name(),"description")){
                if(!item_child->GetText()) Rss.description = "";
                else{
                    Rss.description = item_child->GetText();
                    //cout<<"description: "<<item_child->GetText()<<endl;
                }
            }else if(!strcmp(item_child->Name(),"content:encoded")){
                if(!item_child->GetText()) Rss.content = "";
                else{
                    Rss.content = item_child->GetText();
                    Rss.content = std::regex_replace(Rss.content,pattern,"");
                    //cout<<"content: "<<item_child->GetText()<<endl;
                }
            }
            item_child = item_child->NextSiblingElement();
        }
        _rss.push_back(Rss);
        item = item->NextSiblingElement();
    }
}

void RssReader::dump(const string & filename)
{
    int cnt=0;
    ofstream ofs(filename);
    if(!ofs){
        cout<<"open file error!"<<endl;
        return ;
    }
    for(auto & c : _rss)
    {
        ofs<<"<doc>"<<endl;
        ofs<<"    "<<"<docid>"<<cnt++<<"</docid>"<<endl;
        ofs<<"    "<<"<title>"<<c.title<<"</title>"<<endl;
        ofs<<"    "<<"<link>"<<c.link<<"</link>"<<endl;
        ofs<<"    "<<"<description>"<<c.description<<"</description>"<<endl;
        ofs<<"    "<<"<content>"<<c.content<<"</content>"<<endl;
        ofs<<"</doc>"<<endl;
    }
}
