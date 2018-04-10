#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<map>
#include<set>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#define mp(a, b) make_pair(a, b)
using namespace std;
const int def=0x7f7f7f7f;

namespace Ui {
class MainWindow;
}

struct netNode
{
    bool end[210];
    int root, cntstate, con[210][210];
    map<string, int> statemap;
    netNode()
    {
        root=cntstate=0;
        memset(con, 0, sizeof con);
        memset(end, false, sizeof end);
        statemap.clear();
    }
    bool find(string ch)
    {
        int p=root;
        for(int i=0, len=ch.size(); i<len; i++)
        {
            string tmp="";
            tmp+=ch[i];
            if((!statemap[tmp]) || !con[p][statemap[tmp]])  return false;
            p=con[p][statemap[tmp]];
        }
        return end[p];
    }
    void insert(string u, string cost, string v)
    {
        if(!statemap[u])    statemap[u]=++cntstate;
        if(!statemap[v])    statemap[v]=++cntstate;
        if(!statemap[cost]) statemap[cost]=++cntstate;
        con[statemap[u]][statemap[cost]]=statemap[v];
        return ;
    }
    void setRoot(string ch)
    {
        if(!statemap[ch])   statemap[ch]=++cntstate;
        root=statemap[ch];
        return ;
    }
    void setEnd(string ch)
    {
        if(!statemap[ch])   statemap[ch]=++cntstate;
        end[statemap[ch]]=true;
        return ;
    }
};//每一个关系网图

struct gram2Node
{
    string pre, lat;
    vector<bool> isNTer;
    gram2Node()
    {
        pre=lat="";
        isNTer.clear();
    }
    gram2Node(string tpre, string tlat)
    {
        pre=tpre;
        for(int i=0, len=tlat.size(); i<len; i++)
        {
            if(tlat[i]=='<')
            {
                lat+=tlat[i+1], i+=2;
                isNTer.push_back(true);
            }
            else
            {
                lat+=tlat[i];
                isNTer.push_back(false);
            }
        }
    }
    void pr()
    {
        cout<<pre<<' '<<lat<<endl;
        return ;
    }
};//每一条推导式

struct closureElement
{
    int id, term, nxt;
    closureElement(){}
    closureElement(int i, int t, int n)
    {
        id=i, term=t, nxt=n;
    }
    bool operator ==(const closureElement&t)const
    {
        return id==t.id && term==t.term && nxt==t.nxt;
    }
    bool operator <(const closureElement&t)const
    {
        return id==t.id ? (term==t.term ? nxt<t.nxt : term<t.term) : id<t.id;
    }
};//每个状态集合中的元素

struct closureNode
{
    vector<closureElement> elelist;
    bool operator ==(const closureNode &t)const
    {
        if(elelist.size()!=t.elelist.size())    return false;
        for(int i=0; i<(int)elelist.size(); i++)
            if(!(elelist[i]==t.elelist[i]))    return false;
        return true;
    }
};//单个状态集合

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_start_clicked();

private:
    Ui::MainWindow *ui;

protected:
    int cntpre;//非终结符的编号
    string tos[25];//对应编号的非终结符
    map<string, int> premap;//非终结符的编号
    set<string> alfList[25];//alfList[i]：非终结符i直接推导出的所有终结符
    netNode netnode[25];//netnode[i]：非终结符i对应的推导网
    bool hasnet[25];//hasnet[i]：非终结符i是否有推导网
    map<string, string> cppID;//cppID[i]：源码中token串i对应的种类属性
    bool hasDigit(string, int);
    bool hasLetter(string, int);
    bool hasNull(string, int);
    void insertGram3(string);
    string printType(string);
    string getToken(string, string);

    string initToken;
    vector<int> nterList[200];//nterList[i]：非终结符i对应的所有推导式下标
    vector<gram2Node> gram2List;//所有推导式
    vector<closureNode> closureList;//所有集合
    set<int> firstList[200];//firstList[i]：非终结符i所有的first元素
    int REDUCE[400][200];//REDUCE[i][j]：状态i遇到终结符j的推导式下标
    int ACTION[400][200];//ACTION[i][j]：状态i遇到终结符j的跳转状态
    int GOTO[400][200];//GOTO[i][j]：状态i遇到非终结符j的跳转状态
    void insertGram2(string);
    void getFirst();
    int getClosure(vector<closureElement>);
    string printTables();
    string startTrans(string);
    string getTrans(string, string);
};

#endif // MAINWINDOW_H
