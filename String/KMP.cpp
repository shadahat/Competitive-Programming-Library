/***
    * Complexity = O(P+S)
    * Searches pat in str

    * We can avoid the matcher by calculating the prefix function for the string = P + "#" + S
    * To find the smallest period of a string ,
      If ( len % ( len – pref[len-1] ) ) == 0
      then the string has a period of length ( len – pref[len-1] )
      and it occurs len / ( len – pref[len-1] ) times


***/

#include <bits/stdc++.h>
using namespace std;

const int MAX = 100010;

char str[MAX], pat[MAX];
int pref[MAX];
int match[MAX];

/// pref[i] =   length of the longest suffix which is also
/// a proper prefix of the original string
void prefixFunction(int P) {
    int j=0;
    for(int i=1; i<P; i++) {
        while(true) {
            if(pat[i]==pat[j]) {
                j = pref[i] = j+1; break;
            }
            else {
                if(j==0) {
                    pref[i] = 0; break;
                }
                else j = pref[j-1];
            }
        }
    }
}

void KMPMatcher(int S) {
    int j = 0;
    for(int i=0; i<S; i++) {
        while(true) {
            if(str[i]==pat[j]) {
                j = match[i] = j+1; break;
            }
            else {
                if(j==0) {
                    match[i] = 0; break;
                }
                else j = pref[j-1];
            }
        }
    }
}

int main() {
    scanf("%s",str);
    scanf("%s",pat);
    int S = strlen(str);
    int P = strlen(pat);

    prefixFunction(P);
    KMPMatcher(S);
    return 0;
}

