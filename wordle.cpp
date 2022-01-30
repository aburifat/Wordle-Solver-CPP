#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<string>words;
vector<string>validList;

ll max_guess=6;
auto white="⬜";
auto yellow="🟨";
auto green="🟩";
vector<string>failed_case;
ll pass_count=0;
ll all_count=0;

ll guess=0;
map<char,ll>exclude;
map<char,ll>include;
map<pair<char,ll>,ll>notIn;
string theWord="*********";

void init(){
    string tmp;
    while(cin>>tmp){
        words.push_back(tmp);
    }
}

string SelectWord(ll a){
    srand(time(0)+a);
    ll idx=rand();
    idx%=2315;
    return words[idx];
}

string newGame(ll a){
    validList=words;
    guess=0;
    exclude.clear();
    include.clear();
    notIn.clear();
    theWord="*********";
    //return SelectWord(time(0)+a);
    return words[a];
}

string check(string word, string maybe){
    map<char,ll>mp;
    for(ll i=0;i<5;i++){
        mp[word[i]]++;
    }
    for(ll i=0;i<5;i++){
        if(maybe[i]==word[i]){
            mp[word[i]]--;
            maybe[i]='.';
        }
    }
    for(ll i=0;i<5;i++){
        if(maybe[i]=='.')continue;
        if(mp[maybe[i]]<=0)maybe[i]='#';
        else{
            mp[maybe[i]]--;
            if(maybe[i]!=word[i])maybe[i]='*';
        }
    }
    return maybe;
}

vector<string>getValidList(){
    ll len=validList.size();
    vector<string>nowList;
    map<char,ll>countMustOnce;
    vector<char>mustHave;
    for(ll i=0;i<26;i++){
        if((include[('a'+i)]!=0)&&(countMustOnce['a'+i]==0)){
            countMustOnce['a'+i]=include[('a'+i)];
            mustHave.push_back('a'+i);
        }
    }
    for(ll i=0;i<len;i++){
        ll ok=1;
        map<char,ll>itHas;
        for(ll j=0;j<5;j++)itHas[validList[i][j]]++;
        ll mustHaveLen=mustHave.size();
        for(ll j=0;j<mustHaveLen;j++){
            if(itHas[mustHave[j]]<include[mustHave[j]]){
                ok=0;
                break;
            }
        }
        if(ok==1){
            for(ll j=0;j<5;j++){
                if(theWord[j]!='*'){
                    if(theWord[j]!=validList[i][j]){
                        ok=0;
                        break;
                    }
                }else{
                    if(notIn[{validList[i][j],j}]!=0){
                        ok=0;
                        break;
                    }else if(exclude[validList[i][j]]!=0){
                        ok=0;
                        break;
                    }
                }
            }
        }
        
        if(ok==1)nowList.push_back(validList[i]);
    }
    return nowList;
}

void solve(string word){
    while(guess<max_guess){
        validList=getValidList();
        cout<<"Remaining Candidate: "<<validList.size()<<"\n";
        if(validList.size()==0){
            cout<<"Actual word: "<<word<<"\n";
            failed_case.push_back(word);
            return;
        }
        string maybe=validList[0];
        cout<<"Guessing: "<<maybe<<" ";
        string status=check(word,maybe);
        for(ll i=0;i<5;i++){
            if(status[i]=='#')cout<<white;
            else if(status[i]=='*')cout<<yellow;
            else cout<<green;
        }
        cout<<" ";
        if(word==maybe){
            pass_count++;
            cout<<"Actual word: "<<word<<"\n";
            return;
        }
        include.clear();
        for(ll i=0;i<5;i++){
            if(status[i]=='*'){
                include[maybe[i]]++;
                notIn[{maybe[i],i}]++;
            }
            else if((status[i]=='#')&&(include[maybe[i]]==0)){
                exclude[maybe[i]]++;
            }else if(status[i]=='.'){
                theWord[i]=maybe[i];
                include[maybe[i]]++;
            }
        }
        guess++;
    }
    failed_case.push_back(word);
    cout<<"Actual word: "<<word<<"\n";
}


int main(){
    freopen("WordList.txt","r",stdin);
    init();
    ll rounds=2315;
    all_count=rounds;
    for(ll i=0;i<rounds;i++){
        cout<<"====================\n";
        cout<<"Game: "<<i+1<<"\n";
        cout<<"====================\n";
        string word=newGame(i);
        solve(word);
        cout<<"\n";
    }
    cout<<"\n====================\n";
    cout<<"Failed Cases:\n";
    cout<<"====================\n";
    for(ll i=0;i<failed_case.size();i++)cout<<failed_case[i]<<"\n";
    return 0;
}