#include "../include/rss.h"
#include <regex>
#include <sstream>
#include <iostream>
using std::cout;
using std::endl;
using std::ostringstream;

RssReader::RssReader(vector<string> & files)
: _files(files)
{
    cout<<"RssReader()"<<endl;
}

RssReader::~RssReader()
{
    cout<< "~RssReader()"<<endl;
}

void RssReader::loadFiles()
{
    for(size_t idx = 0; idx!=_files.size(); ++idx){
        loadFile(_files[idx]);
    }
}

void RssReader::loadFile(const string & filename)
{
    XMLDocument doc;
    doc.LoadFile(filename.c_str());
    cout<<"loadFile: "<<filename<<endl;
    XMLError errorID = doc.ErrorID();
    if(errorID){
        cout<<"XMLDocument loadFile error!"<<endl;
        return;
    }else{
        parseRss(doc);
        cout<<"parse "<<filename<<" over!"<<endl;
    }
}

void RssReader::parseRss(XMLDocument & doc)
{
    XMLElement * root = doc.RootElement();
    XMLElement * channel = root->FirstChildElement("channel");
    XMLElement * item = channel->FirstChildElement("item");

    for(; item; item = item->NextSiblingElement()){
        shared_ptr<RssItem> rssItemPtr(new RssItem);
        const char * itemTitle = item->FirstChildElement("title")->GetText();
        const char * itemLink = item->FirstChildElement("link")->GetText();
        const char * itemDescription = item->FirstChildElement("description")->GetText();
        const char * itemContent = nullptr;
        XMLElement * contentEncoded = item->FirstChildElement("content:encoded");
        if(contentEncoded)
            itemContent = contentEncoded->GetText();
        else
            itemContent = itemDescription;

        std::regex pattern("<.*?>");
        string content = std::regex_replace(string(itemContent), pattern, "");

        rssItemPtr->title = itemTitle ? itemTitle : string("");
        rssItemPtr->link = itemLink ? itemLink : string("");
        rssItemPtr->content = content;

        _items.push_back(rssItemPtr);
    }
}

void RssReader::makePages(vector<string> & pages)
{
    for(size_t idx = 0; idx!=_items.size(); ++idx)
    {
        ostringstream oss;        
        oss << "<doc>\n"
            << "  <docid>" << (idx+1) << "</docid>\n"
            << "  <title>" << _items[idx]->title << "</title>\n"
            << "  <link>"  << _items[idx]->link << "</link>\n"
            << "  <content>" << _items[idx]->content << "</content>\n"
            << "</doc>\n";
        string page = oss.str();
        pages.push_back(page);
    }
}
