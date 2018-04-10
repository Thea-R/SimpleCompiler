#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::hasDigit(string gram, int i)
{
    return (gram[i+1]=='d' && gram[i+2]=='i' && gram[i+3]=='g'
            && gram[i+4]=='i' && gram[i+5]=='t' && gram[i+6]=='>');
}

bool MainWindow::hasLetter(string gram, int i)
{
    return (gram[i+1]=='l' && gram[i+2]=='e' && gram[i+3]=='t'
            && gram[i+4]=='t' && gram[i+5]=='e' && gram[i+6]=='r' && gram[i+7]=='>');
}

bool MainWindow::hasNull(string gram, int i)
{
    return (gram[i+1]=='n' && gram[i+2]=='u' && gram[i+3]=='l'
            && gram[i+4]=='l' && gram[i+5]=='>');
}

void MainWindow::insertGram3(string gram)
{
    int sizeg=gram.size(), cnt=0;
    bool getpre=false, mul=false, hasd[55], hasl[55], muls[55], end[55];
    string pre[55], lat[55];

    for(int i=0; i<sizeg; i++)
    {
        if(gram[i]=='<' && !getpre)
        {
            ++cnt, pre[cnt]=lat[cnt]="", muls[cnt]=hasd[cnt]=hasl[cnt]=end[cnt]=false;
            for(i++; i<sizeg && gram[i]!='>'; i++) pre[cnt]+=gram[i];
            getpre=true;
        }
        else if(gram[i]==' ')   i+=3;
        else if(gram[i]=='\n')  getpre=false;
        else
        {
            lat[cnt]+=gram[i];
            if(gram[i]=='<')
            {
                if(i+6<sizeg && hasDigit(gram, i))  hasd[cnt]=true;
                else if(i+7<sizeg && hasLetter(gram, i))    hasl[cnt]=true;
                else if(i+5<sizeg && hasNull(gram, i))  end[cnt]=true;
                else if(pre[cnt]!="operator") muls[cnt]=mul=true;
            }
        }
    }
    if(!premap[pre[1]])
    {
        premap[pre[1]]=++cntpre;
        tos[cntpre]=pre[1];
        alfList[premap[pre[1]]].clear();
    }

    int mainid=premap[pre[1]];
    if(!mul)
    {
        for(int i=1; i<=cnt; i++)
            alfList[mainid].insert(lat[i]);
    }
    else
    {
        hasnet[mainid]=true;
        netnode[mainid].setRoot(pre[1]);
        for(int i=1; i<=cnt; i++)
        {
            if(end[i])
            {
                netnode[mainid].setEnd(pre[i]);
                continue;
            }

            string tmp0="", tmp1[55], tmp2="";
            for(int j=0; j<52; j++) tmp1[j]="";
            for(int j=0, len=lat[i].size(); j<len; j++)
            {
                if(lat[i][j]!='<')  tmp0+=lat[i][j];
                else if(j+6<sizeg && hasDigit(lat[i], j))
                {
                    for(int k=0; k<9; k++) tmp1[k]+=(char)(k+'0');
                    j+=6;
                }
                else if(j+7<sizeg && hasLetter(lat[i], j))
                {
                    for(int k=0; k<26; k++) tmp1[k]+=(char)(k+'A');
                    for(int k=0; k<26; k++) tmp1[k+26]+=(char)(k+'a');
                    j+=7;
                }
                else
                {
                    for(j++; j<len && lat[i][j]!='>'; j++)  tmp2+=lat[i][j];
                }
            }

            if(hasd[i])
            {
                for(int j=0; j<9; j++)  netnode[mainid].insert(pre[i], tmp1[j], tmp2);
            }
            else if(hasl[i])
            {
                for(int j=0; j<52; j++)  netnode[mainid].insert(pre[i], tmp1[j], tmp2);
            }
            else
            {
                netnode[mainid].insert(pre[i], tmp0, tmp2);
            }
        }
    }
    return ;
}

string MainWindow::printType(string cpp)
{
    string ans="";
    initToken+=cpp;

    for(int i=1; i<=cntpre; i++)
    {
        if(!hasnet[i])
        {
            if(alfList[i].find(cpp)!=alfList[i].end())
            {
                ans+=tos[i];
                cppID[cpp]=tos[i];
                for(int j=1, len=tos[i].size(); j<=15-len; j++) ans+=' ';
                ans+="->   ";
                ans+=cpp;
                ans+='\n';
                return ans;
            }
        }
        else
        {
            if(netnode[i].find(cpp))
            {
                ans+=tos[i];
                cppID[cpp]=tos[i];
                for(int j=1, len=tos[i].size(); j<=15-len; j++) ans+=' ';
                ans+="->   ";
                ans+=cpp;
                ans+='\n';
                return ans;
            }
        }
    }

    ans+="undefined";
    cppID[cpp]="undefined";
    for(int i=1; i<=6; i++) ans+=' ';
    ans+="->   ";
    ans+=cpp;
    ans+='\n';
    return ans;
}

string MainWindow::getToken(string gram, string cpp)
{
    string ans="";

    int sizeg=gram.size(), p=0;
    string tgram="";
    while(p<sizeg)
    {
        if(gram[p]!='#')    tgram+=gram[p];
        else
        {
            if(tgram.size())  insertGram3(tgram);
            tgram="";
        }
        p++;
    }

    int sizec=cpp.size(), q=0, op=premap["operator"], lm=premap["limiter"];
    bool qua=false;
    string tmp="";
    while(q<sizec)
    {
        if(cpp[q]==' ' || cpp[q]=='\n' || cpp[q]=='\t')
        {
            if(tmp.size())  ans+=printType(tmp);
            tmp="";
        }
        else
        {
            string tmp2="";
            tmp2+=cpp[q];
            if(alfList[op].find(tmp2)!=alfList[op].end())
            {
                if((tmp2=="+" || tmp2=="-") && q-1>=0 && (cpp[q-1]=='e' || cpp[q-1]=='E'))	tmp+=cpp[q];
                else
                {
                    if(tmp.size())  ans+=printType(tmp);
                    ans+=printType(tmp2);
                    tmp="";
                }
            }
            else if(alfList[lm].find(tmp2)!=alfList[lm].end())
            {
                if(cpp[q]=='"' || tmp2=="'")
                {
                    if(!qua)    qua=true;
                    else
                    {
                        if(tmp.size())
                        {
                            ans+="stringconst";

                            string ttmp="";
                            ttmp+=cpp[q];
                            ttmp+=tmp;
                            ttmp+=cpp[q];
                            cppID[ttmp]="stringconst";
                            initToken+=ttmp;

                            for(int i=1; i<=4; i++) ans+=' ';
                            ans+="->   ";
                            ans+=ttmp;
                            ans+='\n';
                        }
                        qua=false;
                        tmp="";
                    }
                }
                else
                {
                    if(tmp.size())  ans+=printType(tmp);
                    ans+=printType(tmp2);
                    tmp="";
                }
            }
            else tmp+=cpp[q];
        }
        q++;
    }
    if(tmp.size())  ans+=printType(tmp);
    return ans;
}

void MainWindow::insertGram2(string gram)
{
    int sizeg=gram.size(), cnt=1;
    bool getpre=false;
    string pre="", lat="";
    queue<string> q;
    q.push(lat);

    for(int i=0; i<sizeg; i++)
    {
        if(gram[i]=='<' && !getpre) pre+=gram[i+1], i+=2, getpre=true;
        else if(gram[i]==' ')   i+=3;
        else
        {
            if(gram[i]=='<')
            {
                if(i+2<sizeg && gram[i+2]=='>')
                {
                    for(int j=1; j<=cnt; j++)
                    {
                        lat=q.front();
                        q.pop();
                        lat+="<", lat+=gram[i+1], lat+=">";
                        q.push(lat);
                    }
                    i+=2;
                }
                else
                {
                    int ncnt=0;
                    string tmp="";
                    for(i++; i<sizeg && gram[i]!='>'; i++) tmp+=gram[i];
                    for(int j=1; j<=cnt; j++)
                    {
                        for(map<string, string>::iterator it=cppID.begin(); it!=cppID.end(); it++)
                        {
                            if(it->second==tmp)
                            {
                                lat=q.front();
                                lat+=it->first;
                                q.push(lat);
                                ncnt++;
                            }
                        }
                        q.pop();
                    }
                    cnt=ncnt;
                }
            }
            else
            {
                for(int j=1; j<=cnt; j++)
                {
                    lat=q.front();
                    q.pop();
                    lat+=gram[i];
                    q.push(lat);
                }
            }
        }
    }

    while(!q.empty())
    {
        lat=q.front();
        q.pop();
        gram2List.push_back(gram2Node(pre, lat));
        nterList[(int)pre[0]].push_back(gram2List.size()-1);
    }
    return ;
}

void MainWindow::getFirst()
{
    while(1)
    {
        bool flag=false;

        for(int i=0; i<(int)gram2List.size(); i++)//遍历推导式列表
        {
            int pre=gram2List[i].pre[0], lat=gram2List[i].lat[0];
            if(lat>='A' && lat<='Z')
            {
                for(set<int>::iterator it=firstList[lat].begin(); it!=firstList[lat].end(); it++)
                {
                    if(firstList[pre].find(*it)==firstList[pre].end())
                    {
                        flag=true;
                        firstList[pre].insert(*it);
                    }
                }
            }
            else
            {
                if(firstList[pre].find(lat)==firstList[pre].end())
                {
                    flag=true;
                    firstList[pre].insert((int)lat);
                }
            }
        }

        if(!flag)   break;
    }
    return ;
}

int MainWindow::getClosure(vector<closureElement> initv)
{
    closureNode tmpc;//临时状态集合
    for(int p=0; p<(int)initv.size(); p++)   tmpc.elelist.push_back(initv[p]);
    for(int p=0; p<(int)tmpc.elelist.size(); p++)//遍历所有元素
    {
        closureElement tmpp=tmpc.elelist[p];
        int id=tmpp.id, term=tmpp.term, nxt=tmpp.nxt;
        if(term<(int)gram2List[id].lat.size() && gram2List[id].isNTer[term])//没有到推导式尾、非终结符
        {
            int npre=gram2List[id].lat[term];
            for(int i=0; i<(int)nterList[npre].size(); i++)//遍历所有非终结符的推导式
            {
                if(term==(int)gram2List[id].lat.size()-1)//.A, nxt
                {
                    closureElement ntmp=closureElement(nterList[npre][i], 0, nxt);
                    bool nelement=true;
                    for(int j=0; j<(int)tmpc.elelist.size(); j++)//确保新的元素不在当前状态集合
                    {
                        if(tmpc.elelist[j]==ntmp)
                        {
                            nelement=false;
                            break;
                        }
                    }
                    if(nelement)    tmpc.elelist.push_back(ntmp);
                }
                else if(!gram2List[id].isNTer[term+1])//.Ab, nxt
                {
                    closureElement ntmp=closureElement(nterList[npre][i], 0, gram2List[id].lat[term+1]);
                    bool nelement=true;
                    for(int j=0; j<(int)tmpc.elelist.size(); j++)
                    {
                        if(tmpc.elelist[j]==ntmp)
                        {
                            nelement=false;
                            break;
                        }
                    }
                    if(nelement)    tmpc.elelist.push_back(ntmp);
                    if(nelement && id==9) cout<<gram2List[id].lat[term]<<' '<<gram2List[id].lat[term+1]<<endl;
                }
                else//.AB, nxt
                {
                    int nnxt=gram2List[id].lat[term+1];
                    for(set<int>::iterator k=firstList[nnxt].begin(); k!=firstList[nnxt].end(); k++)
                    {
                        closureElement ntmp=closureElement(nterList[npre][i], 0, *k);
                        bool nelement=true;
                        for(int j=0; j<(int)tmpc.elelist.size(); j++)
                        {
                            if(tmpc.elelist[j]==ntmp)
                            {
                                nelement=false;
                                break;
                            }
                        }
                        if(nelement)    tmpc.elelist.push_back(ntmp);
                    }
                }
            }
        }
    }
    sort(tmpc.elelist.begin(), tmpc.elelist.end());//排序后方便集合判重

    for(int i=0; i<(int)closureList.size(); i++) if(closureList[i]==tmpc)    return i;

    closureList.push_back(tmpc);
    int sid=closureList.size()-1;

    int cnt=0, nxtID[400]={0};
    vector<closureElement> nxtinitv[400];//nxtinitv[i]：通过i跳转的状态集合
    for(int i=0; i<(int)tmpc.elelist.size(); i++)
    {
        int id=tmpc.elelist[i].id, term=tmpc.elelist[i].term, nxt=tmpc.elelist[i].nxt;
        if(term==(int)gram2List[id].lat.size())
        {
            //reduce
            REDUCE[sid][nxt]=id;
            continue;
        }
        int ch=gram2List[id].lat[term];
        if(gram2List[id].isNTer[term])
        {
            if(!nxtID[ch+200])  nxtID[ch+200]=++cnt;
            nxtinitv[nxtID[ch+200]].push_back(closureElement(id, term+1, nxt));
        }
        else
        {
            if(!nxtID[ch])  nxtID[ch]=++cnt;
            nxtinitv[nxtID[ch]].push_back(closureElement(id, term+1, nxt));
        }
    }

    for(int i=0; i<400; i++) if(nxtID[i])
    {
        int vid=getClosure(nxtinitv[nxtID[i]]);
        if(i>200)	GOTO[sid][i-200]=vid;//GOTO
        else	ACTION[sid][i]=vid;//ACTION

    }

    return sid;
}

string MainWindow::printTables()
{
    string ans="";

    ans+="Derivation:\n";
    for(int i=0; i<(int)gram2List.size(); i++)
        ans+=gram2List[i].pre, ans+="->", ans+=gram2List[i].lat, ans+="\n";
    ans+="--------------------\n";

    ans+="first:\n";
    for(int i=0; i<200; i++) if(firstList[i].size())
    {
        ans+=(char)i;
        ans+=": ";
        for(set<int>::iterator it=firstList[i].begin(); it!=firstList[i].end(); it++)
            ans+=(char)*it, ans+=" ";
        ans+="\n";
    }
    ans+="--------------------\n";

    for(int i=0; i<(int)closureList.size(); i++)
    {
        ans+="closure[", ans+=to_string(i), ans+="]\n";
        for(int j=0; j<(int)closureList[i].elelist.size(); j++)
        {
            int id=closureList[i].elelist[j].id, term=closureList[i].elelist[j].term, nxt=closureList[i].elelist[j].nxt;
            ans+=gram2List[id].pre, ans+="->";
            for(int k=0; k<term; k++) ans+=gram2List[id].lat[k];
            ans+=".";
            for(int k=term; k<(int)gram2List[id].lat.size(); k++) ans+=gram2List[id].lat[k];
            ans+=" , ", ans+=(char)nxt, ans+="\n";
        }
        ans+="**********\n";
    }

    ans+="size of closures: ";
    ans+=to_string(closureList.size());
    ans+="\n--------------------\n";

    ans+="ACTION table:\n";
    for(int i=0; i<(int)closureList.size(); i++)
        for(int j=0; j<200; j++)
        {
            if(REDUCE[i][j]!=def)
            {
                ans+="ACTION[", ans+=to_string(i), ans+="][", ans+=((char)j);
                ans+="]=R", ans+=to_string(REDUCE[i][j]), ans+="\n";
            }
            if(ACTION[i][j]!=def)
            {
                ans+="ACTION[", ans+=to_string(i), ans+="][", ans+=((char)j);
                ans+="]=S", ans+=to_string(ACTION[i][j]), ans+="\n";
            }
        }
    ans+="--------------------\n";

    ans+="GOTO table:\n";
    for(int i=0; i<(int)closureList.size(); i++)
        for(int j=0; j<200; j++)
        {
            if(GOTO[i][j]!=def)
            {
                ans+="GOTO[", ans+=to_string(i), ans+="][", ans+=((char)j);
                ans+="]=", ans+=to_string(GOTO[i][j]), ans+="\n";
            }
        }
    ans+="--------------------\n";
    return ans;
}

string MainWindow::startTrans(string token)
{
    string ans="Process:\n";
    token+='#';
    int cntst=0, state[1000], cntsy=0, symbol[1000];
    state[++cntst]=0;
    symbol[++cntsy]=(int)'#';

    int cnt=0, sizet=token.size(), flag=0;
    for(int i=0; i<sizet; i++)
    {
        ans+="step[", ans+=to_string(++cnt), ans+="]\n";
        ans+="state_stack: ";
        for(int j=1; j<=cntst; j++) ans+=to_string(state[j]), ans+=" \n"[j==cntst];
        ans+="symbol_stack: ";
        for(int j=1; j<=cntsy; j++) ans+=(char)symbol[j], ans+=" \n"[j==cntsy];
        ans+="next_symbol: ", ans+=token[i], ans+="\n";

        int curst=state[cntst], nxtsy=(int)token[i];
        if(ACTION[curst][nxtsy]==def && REDUCE[curst][nxtsy]==def)
        {
            ans+="ERROR!\n";
            flag=-1;
            break;
        }
        if(ACTION[curst][nxtsy]!=def && REDUCE[curst][nxtsy]!=def)
        {
            ans+="ERROR!\n";
            flag=-1;
            break;
        }
        if(ACTION[curst][nxtsy]!=def)
        {
            ans+="ACTION[", ans+=to_string(curst);
            ans+="][", ans+=(char)nxtsy;
            ans+="]=S", ans+=to_string(ACTION[curst][nxtsy]);
            ans+="\n";

            state[++cntst]=ACTION[curst][nxtsy];
            symbol[++cntsy]=nxtsy;
        }
        else
        {
            if(REDUCE[curst][nxtsy]==0)
            {
                ans+="ACC!";
                flag=1;
                break;
            }

            ans+="ACTION[", ans+=to_string(curst);
            ans+="][", ans+=(char)nxtsy;
            ans+="]=R", ans+=to_string(REDUCE[curst][nxtsy]);
            ans+="\n";

            cntst-=gram2List[REDUCE[curst][nxtsy]].lat.size();
            cntsy-=gram2List[REDUCE[curst][nxtsy]].lat.size();
            symbol[++cntsy]=(int)gram2List[REDUCE[curst][nxtsy]].pre[0];

            curst=state[cntst], nxtsy=symbol[cntsy];
            state[++cntst]=GOTO[curst][nxtsy];
            ans+="GOTO[", ans+=to_string(curst);
            ans+="][", ans+=(char)nxtsy;
            ans+="]=", ans+=to_string(GOTO[curst][nxtsy]);
            ans+="\n";
            i--;
        }
        ans+="**********\n";
    }

    if(!flag)   ans+="ERROR!\n";
    return ans;
}

string MainWindow::getTrans(string gram, string token)
{
    string ans="";

    int sizeg=gram.size(), p=0;
    string tgram="";
    while(p<sizeg)
    {
        if(gram[p]!='\n')    tgram+=gram[p];
        else
        {
            if(tgram.size())  insertGram2(tgram);
            tgram="";
        }
        p++;
    }
    if(tgram.size())    insertGram2(tgram);
    getFirst();

    memset(GOTO, 0x7f, sizeof GOTO);
    memset(ACTION, 0x7f, sizeof ACTION);
    memset(REDUCE, 0x7f, sizeof REDUCE);
    vector<closureElement> initv;
    initv.push_back(closureElement(0, 0, (int)'#'));
    getClosure(initv);

    ans+=printTables();
    ans+=startTrans(token);
    return ans;
}

void MainWindow::on_start_clicked()
{
    if(ui->gram2in->toPlainText().isEmpty())
        QMessageBox::warning(this, tr("Waring"), tr("请完成输入"), QMessageBox::Yes);
    else if(ui->gram3in->toPlainText().isEmpty())
        QMessageBox::warning(this, tr("Waring"), tr("请完成输入"), QMessageBox::Yes);
    else if(ui->cppin->toPlainText().isEmpty())
        QMessageBox::warning(this, tr("Waring"), tr("请完成输入"), QMessageBox::Yes);
    else
    {
        string gram2=ui->gram2in->toPlainText().toStdString();
        string gram3=ui->gram3in->toPlainText().toStdString();
        string cpp=ui->cppin->toPlainText().toStdString();

        string token=getToken(gram3, cpp);
        string trans=getTrans(gram2, initToken);

        ui->tokenout->clear();
        ui->tokenout->appendPlainText(QString::fromStdString(token));
        ui->transout->clear();
        ui->transout->appendPlainText(QString::fromStdString(trans));
    }
}
