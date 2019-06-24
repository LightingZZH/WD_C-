#include "wow2.h"
#include <vector>
using std::vector;
using std::cin;

int main()
{
    int cnt,Hp,hp1,hp2,hp3,hp4,hp5;
    vector<int> hHp;
    vector<vector<int>> wHp;
    cin>>cnt;
    
    for(int i=0;i!=cnt;++i)
    {
        vector<int> v;
        cin>>Hp>>hp1>>hp2>>hp3>>hp4>>hp5;
        hHp.push_back(Hp);
        v.push_back(hp1);
        v.push_back(hp2);
        v.push_back(hp3);
        v.push_back(hp4);
        v.push_back(hp5);
        wHp.push_back(v);
    }

    for(int i=0;i!=cnt;i++)
    {
        //cout<<"----------------"<<endl;
        cout<<"Case:"<<i+1<<endl;
        //cout<<hHp[i]<<endl;
        //cout<<wHp[i][0]<<" "<<wHp[i][1]<<" "<<wHp[i][2]<<" "
        //    <<wHp[i][3]<<" "<<wHp[i][4]<<endl;
        Headquarter h1(hHp[i],"red",wHp[i][0],wHp[i][1],wHp[i][2],wHp[i][3],wHp[i][4]);
        Headquarter h2(hHp[i],"blue",wHp[i][0],wHp[i][1],wHp[i][2],wHp[i][3],wHp[i][4]);
        while(h1.getFlag()!=-3 || h2.getFlag()!=-3)
        {
            h1.Create();
            h2.Create();
        }
    }

    return 0;
}

