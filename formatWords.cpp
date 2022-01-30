#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
    freopen("all_words_not_formated.txt","r",stdin);
    freopen("WordList.txt","w",stdout);
    vector<string>s;
    string tmp;
    while(cin>>tmp){
        s.push_back(tmp);
    }
    sort(s.begin(),s.end());
    ll len=s.size();
    for(ll i=0;i<len;i++){
        cout<<s[i]<<"\n";
    }
    return 0;
}