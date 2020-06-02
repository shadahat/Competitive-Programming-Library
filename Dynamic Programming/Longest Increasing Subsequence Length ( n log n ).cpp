/***
    The size of the vector after each iteration denotes the size
    of the LIS of the sub array starting at 1 and ending at i
***/

int ara[MAX];
vector <int> v;
int max_lis = 0;
for(i=1;i<=n;i++){
    x = lower_bound(all(v),ara[i])-v.begin();
    if(x==0){
        if(v.size()==0) v.pb(ara[i]);
        else v[0] = ara[i];
    }
    else if(x==v.size()) v.pb(ara[i]);
    else if(ara[i]<v[x]) v[x] = ara[i];
    max_lis = max(max_lis,(int)v.size());
}
cout << "The size of the lis is : " << max_lis << endl;

