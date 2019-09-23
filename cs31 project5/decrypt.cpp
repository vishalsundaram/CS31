//
//  decrypt.cpp
//  cs31 project5
//
//  Created by Vishal Sundaram on 18/5/19.
//  Copyright © 2019 Vishal Sundaram. All rights reserved.
//

#include <cstring>
#include <iostream>
#include <cctype>
using namespace std;

int newLineCounter(const char ciphertext[]);
//void decoder(char nlsplit[][82], char crib2[], int cribwlen[], int nlc, int ln, int last);
bool decrypt(const char ciphertext[], const char crib[]);
void cleanCrib(const char crib[], char crib2[], int b);
//int spaceCounter(char crib2[]);
void criblen(char crib2[], int cribwlen[]);
void cipherlen(const char ciphertext[], int cipherwlen[], int bb);
//void cipherSplit(const char ciphertext[], char nlsplit[][82], int nlc);
bool testCharMatch(char crib2[], int lastIndex, const char ciphertext[], int cribwlen[]);

void runtest(const char ciphertext[], const char crib[])
{
    cout << "====== " << crib << endl;
    bool result = decrypt(ciphertext, crib);
    cout << "Return value: " << result << endl;
}

int main()
{
    cout.setf(ios::boolalpha); // output bools as "true"/"false"
    
    runtest("boo \n boo boy boy", "dog dog");

    
}

bool decrypt(const char ciphertext[], const char crib[])
{
    char crib2[150];
    int b = 0; //used for checking first dig for crib
    int cribSz = 0;
    for(int j = 0; crib[j] != '\0'; j++){
        cribSz++;
    }
    if(cribSz == 0){
        return false;
    }
    if(!isalpha(crib[b])){
        while(!isalpha(crib[b]) && crib[b] != '\0'){
            b++;
        }
    }
    if(crib[b] == '\0'){
        return false;
    }
    int bb = 0;
    if(!isalpha(ciphertext[bb])){
        while(!isalpha(ciphertext[bb]) && ciphertext[bb] != '\0'){
            bb++;
        }
    }
    if(ciphertext[bb] == '\0'){
        return false;
    }
    cleanCrib(crib, crib2, b);
    cribSz = 0;
    for(int k = 0; crib[k] != '\0'; k++){
        cribSz++;
    }
    if(cribSz > 82){
        return false;
    }  //done with elementary prechecks for code
    /*for(int a = 0; crib2[a] != '\0'; a++){
        cout << crib2[a];
    }
    cout << "" << endl;*/
    int nlc = newLineCounter(ciphertext);
    //int sc = spaceCounter(crib2);
    int cribwlen[82];
    criblen(crib2, cribwlen);
    /*if(nlc == 0){
        int tr = 0;
        int alph = 0;
        int consAlph = 0;
        for(int b = 0; ciphertext[b] != '\0'; b++){
            if(b == 0){
                alph = 0;
                consAlph = 0;
            }
            if(isalpha(ciphertext[b])){
                alph++;
                if(alph == cribwlen[tr] && !isalpha(ciphertext[b+1])){
                    consAlph++;
                    tr++;
                    alph = 0;
                }
                if(alph == cribwlen[tr] && cribwlen[tr+1] == '\0'){
                    consAlph++;
                    tr++;
                    alph = 0;
                }
                else if(alph == cribwlen[tr] && isalpha(ciphertext[b+1])){
                    alph--;
                }
                if(cribwlen[tr] == '\0'){
                    int lastIndex = b;
                    char nlsplit[1][81];
                    int bb = 0;
                    for(bb = 0; ciphertext[bb] != '\0'; bb++){
                        nlsplit[0][bb] = ciphertext[bb];
                    }
                    nlsplit[0][bb] = '\0';
                    int correctLine = 0;
                    decoder(nlsplit, crib2, cribwlen, nlc, correctLine, lastIndex);
                    return true;
                }
            }
            else {
                if(alph != 0 && alph != cribwlen[tr]){
                    alph = 0;
                    consAlph = 0;
                    tr = 0;
                }
            }
        }
        return false;
    }
    else {
        char nlsplit[nlc+1][81];
        cipherSplit(ciphertext, nlsplit, nlc);
        /*int i = 0;
        while(i < nlc+1){
            for(int j = 0; nlsplit[i][j] != '\0'; j++){
                cout << nlsplit[i][j];
            }
            i++;
            cout << endl;
        }*/
        /*int tr = 0; //traverses thru nlsplit
        int alph = 0;  //consecutive alphabet count
        int consAlph = 0; //consecutive words with right alphabet counts
        int tr2 = 0; //traverses thru criblen
        int totalindex = 0;
        while(tr < nlc+1){
            for(int a = 0; ciphertext[a] != '\n'; a++){
                if(ciphertext[a] == '\0'){
                    tr++;
                }
                if(a == 0){
                    alph = 0;
                    consAlph = 0;
                    tr2 = 0;
                }
                if(isalpha(ciphertext[a])){
                    alph++;
                    if(alph == cribwlen[tr2] && cribwlen[tr2+1] == '\0'){
                        consAlph++;
                        tr2++;
                        alph = 0;
                    }
                    else if(alph == cribwlen[tr2] && !isalpha(ciphertext[a+1])){
                        alph = 0;
                        if(cribwlen[tr2 + 2] != '\0'){
                            int b = a + 1;
                            while(!isalpha(ciphertext[a]) || ciphertext[a] == '\n'){
                                b++;
                            }
                            if(ciphertext[a] == '\0'){
                                return false;
                            }
                            else {
                                int temp = b;
                                while(isalpha(ciphertext[b])){
                                    b++;
                                }
                                if(b - temp == cribwlen[tr2+1]){
                                    tr2++;
                                }
                                else if(b - temp >= cribwlen[0]){
                                    consAlph = 1;
                                    tr2 = 1;
                                }
                                else {
                                    tr2 = 0;
                                    consAlph = 0;
                                }
                            }
                        }
                        else {
                            tr2++;
                            consAlph++;
                        }
                    }
                    else if(alph == cribwlen[tr2] && isalpha(ciphertext[a+1])){
                        alph--;
                        if(consAlph != 0){
                            consAlph = 0;
                        }
                    }
                    if(cribwlen[tr2] == '\0'){
                        correctLine = tr;
                        int lastIndex = a;
                        decoder(nlsplit, crib2, cribwlen, nlc, correctLine, lastIndex);
                        return true;
                    }
                }
                else {
                    if(alph != 0 && alph != cribwlen[tr2]){
                        alph = 0;
                        consAlph = 0;
                        tr2 = 0;
                    }
                }
            }
            tr++;
        }
    }
    return false;*/
    int trav2 = 0; //traverses thru cribwlen
        int alph = 0;
        int consalph = 0; //consecutive words
        int lastnonalph = bb;
        int lasttry = bb;
        for(int a = 0; ciphertext[a] != '\0'; a++){
            if(ciphertext[a] == '\n'){
                alph = 0;
                consalph = 0;
                trav2 = 0;
            }
            if(isalpha(ciphertext[a])){
                alph++;
                if(alph == cribwlen[trav2] && cribwlen[trav2+1] == '\0'){
                    int lastIndex = a;
                    if(!isalpha(ciphertext[a+1])){
                        if(testCharMatch(crib2, lastIndex, ciphertext, cribwlen)){
                            return true;
                        }
                    }
                    /*if(consalph == 0){
                        lasttry = lasttry+1;
                        if(ciphertext[lasttry] != '\0'){
                            a = lasttry;
                            alph = 0;
                        }
                        else{
                            return testCharMatch(crib2, lastIndex, ciphertext, cribwlen);
                        }
                    }
                    else {*/
                    else {
                    int g = lasttry;
                        while(isalpha(ciphertext[g])){
                                g++;
                        }
                    while(!isalpha(ciphertext[g])){
                        if(ciphertext[g] != '\0'){
                            g++;
                        }
                        else {
                            return false;
                        }
                    }
                        a = g;
                        lasttry = g;
                        alph = 0;
                        consalph = 0;
                        trav2 = 0;
                    }
                }
                else if(alph == cribwlen[trav2] && !isalpha(ciphertext[a+1])){
                    alph = 0;
                    consalph++;
                    trav2++;
                }
                else if(alph == cribwlen[trav2] && isalpha(ciphertext[a+1])){
                    if(consalph == 0){
                        alph = 0;
                        int abcde = a;
                        while(isalpha(ciphertext[abcde])){
                            abcde++;
                        }
                        if(!isalpha(ciphertext[abcde])){
                            if(ciphertext[abcde] != '\0'){
                                a = abcde;
                            }
                            else {
                                return false;
                            }
                        }
                    }
                    else {
                        consalph = 0;
                        alph = 0;
                        trav2 = 0;
                        a = lastnonalph;
                    }
                }
            }
            else {
                if(alph != 0){
                    if(consalph == 0){
                        alph = 0;
                    }
                    else {
                        alph = 0;
                        consalph = 0;
                        int temp = a;
                        a = lastnonalph;
                        lastnonalph = temp;
                        trav2 = 0;
                        
                    }
                }
                else {
                lastnonalph = a;
                }
            }
        }
    return false;
}

void cleanCrib(const char crib[], char crib2[], int b)
{   //makes crib a readable string with just a space to separate word
    int cnd = 0; //counts non digits
    int d = 0; //precurses thru crib2
    for(int a = b; crib[a] != '\0'; a++){
        if(isalpha(crib[a])){
            crib2[d] = tolower(crib[a]);
            d++;
            cnd = 0;
        }
        else if(!isalpha(crib[a]) && cnd == 0){
            crib2[d] = ' ';
            d++;
            cnd++;
        }
    }
    int c = 0;
    int consna = 0;
    while(consna != 2){
        if(isalpha(crib2[c])){
            consna = 0;
            c++;
        }
        else {
            consna++;
            if(consna == 1){
                c++;
            }
        }
    }
    crib2[c-1] = '\0';
}

int newLineCounter(const char ciphertext[]){
    int c = 0;
    int nlcount = 0;
    while(ciphertext[c] != '\0'){
        if(ciphertext[c] == '\n'){
            nlcount++;
        }
        c++;
    }
    return nlcount;
}

/*int spaceCounter(char crib2[]){
    int sc = 0;
    for(int a = 0; crib2[a] != '\0'; a++){
        if(crib2[a] == ' '){
            sc++;
        }
    }
    return sc;
}*/

void criblen(char crib2[], int cribwlen[]){  //makes array with lengths of each word in crib
    int wl = 0;
    int c2 = 0;
    int lastspace = 0;
    while(crib2[c2] != '\0'){
        if(crib2[c2] == ' '){
            cribwlen[wl] = c2 - lastspace;
            lastspace = c2+1;
            wl++;
        }
        c2++;
    }
    if(crib2[c2] == '\0'){
        cribwlen[wl] = c2-lastspace;
        cribwlen[wl+1] = '\0';
    }
    /*cribwlen[wl+1] = '\0';
    for(int i = 0; cribwlen[i] != '\0'; i++){
        cout << cribwlen[i];
    }*/
}

/*void cipherSplit(const char ciphertext[], char nlsplit[][81], int nlc){  //makes 2d c-string array of each c-string b4 \n
    int i = 0;
    int k = 0;
    while(i < nlc+1){
        for(int j = 0; ciphertext[j] != '\0'; j++){
            if(ciphertext[j] == '\n'){
                nlsplit[i][k] = '\0';
                i++;
                k = 0;
                if(ciphertext[j+1] == '\0'){
                    nlsplit[i][k] = '\0';
                    i++;
                }
            }
            else if(i == nlc){
                if(ciphertext[j+1] == '\0'){
                    nlsplit[i][k] = tolower(ciphertext[j]);
                    nlsplit[i][k+1] = '\0';
                    i++;
                }
                else {
                    nlsplit[i][k] = tolower(ciphertext[j]);
                    k++;
                }
            }
            else{
                nlsplit[i][k] = tolower(ciphertext[j]);
                k++;
            }
        }
    }
}*/


/*void decoder(char nlsplit[][81], char crib2[], int cribwlen[], int nlc, int ln, int last){
    int cribTrav = 0;
    char cleanestCrib[81];
    int cc = 0;
    char temp[nlc+1][81];
    for(int i = 0; i < nlc+1; i++){
        for(int j = 0; nlsplit[i][j] != '\0'; j++){
            temp[i][j] = nlsplit[i][j];
        }
    }
    while(crib2[cribTrav] != '\0'){
        if(isalpha(crib2[cribTrav])){
            cleanestCrib[cc] = crib2[cribTrav];
            cc++;
            cribTrav++;
        }
        else{
            cribTrav++;
        }
    }
    cleanestCrib[cc] = '\0';
    cc--;
    int i = last;
    while(cc > -1){
        if(isalpha(nlsplit[ln][i])){
            /*char temp = tolower(nlsplit[ln][i]);
            char replace = toupper(cleanestCrib[cc]);
            for(int a = 0; a < nlc + 1; a++){
                for(int b = 0; nlsplit[a][b] != '\0'; b++){
                    if(islower(nlsplit[a][b]) && nlsplit[a][b] == temp){
                        nlsplit[a][b] = toupper(cleanestCrib[cc]);
                    }
                }
            }*/
            /*nlsplit[ln][i] = toupper(cleanestCrib[cc]);
            char temp = toupper(cleanestCrib[cc]);
            char replace = nlsplit[ln][i];
            for(int a = 0; a < nlc + 1; a++){
                for(int b = 0; nlsplit[a][b] != '\0'; b++){
                    if(nlsplit[a][b] == replace){
                        nlsplit[a][b] = temp;
                    }
                }
            }
            cc--;
            i--;
        }
        else {
        i--;
        }
    }
    int x = 0;
    while(x < nlc+1){
        for(int y = 0; nlsplit[x][y] != '\0'; y++){
            cout << nlsplit[x][y];
        }
        x++;
        cout << endl;
    }
}*/

bool testCharMatch(char crib2[], int lastIndex, const char ciphertext[], int cribwlen[]){
    int i = lastIndex;
    int tc = 0; //total chars in crib
    for(int a = 0; cribwlen[a] != '\0'; a++){
        tc += cribwlen[a];
    }
    char lig[82];
    int b = 0;
    for(b = 0; ciphertext[b] != '\0'; b++){
        lig[b] = tolower(ciphertext[b]);
    }
    lig[b] = '\0';
    int cc = 0;
    int cribTrav = 0;
    char cleanestCrib[82]; //removes spaces
    while(crib2[cribTrav] != '\0'){
        if(isalpha(crib2[cribTrav])){
            cleanestCrib[cc] = crib2[cribTrav];
            cc++;
            cribTrav++;
        }
        else{
            cribTrav++;
        }
    }
    cleanestCrib[cc] = '\0';
    cc--;
    for(int s = i; tc != 0; s--){
        if(isalpha(lig[s])){
            char og = lig[s];
            for(int x = 0; lig[x] != '\0'; x++){
                /*if(isupper(og)){
                    for(int y = 0; ciphertext[y] != '\0'; y++){
                        if(lig[y] == og){
                            if(tolower(ciphertext[s]) != tolower(ciphertext[y])){
                                return false;
                            }
                        }
                    }
                }*/
                char gai = toupper(cleanestCrib[cc]);
                if(isupper(og)){
                    if(og != gai){
                        return false;
                    }
                }
                if(lig[x] == og){
                    lig[x] = gai;
                }
            }
            tc--;
            cc--;
        }
    }
    for(int d = 0; lig[d] != '\0'; d++){
        if(lig[d] == '\n'){
            cout << endl;
        }
        cout << lig[d];
    }
    cout << endl;
    return true;
}
