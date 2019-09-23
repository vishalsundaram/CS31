//
//  main.cpp
//  cs project4
//
//  Created by Vishal Sundaram on 12/5/19.
//  Copyright © 2019 Vishal Sundaram. All rights reserved.
//

#include <iostream>
using namespace std;
#include <string>
#include <cassert>

int countMatches(const string a[], int n, string target);
int detectMatch(const string a[], int n, string target);
bool detectSequence(const string a[], int n, string target, int& begin, int& end);
int detectMin(const string a[], int n);
int moveToBack(string a[], int n, int pos);
int moveToFront(string a[], int n, int pos);
int detectDifference(const string a1[], int n1, const string a2[], int n2);
int deleteDups(string a[], int n);
bool contains(const string a1[], int n1, const string a2[], int n2);
int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max);
int split(string a[], int n, string splitter);

int main() {
    string people[5] = { "danvers", "thor", "stark", "banner", "romanoff" };
    int j = moveToBack(people, 5, 4);
    for(int a = 0; a < 5; a++){
        cout << people[a] << endl;
    }
    cout << j << endl;

}

int countMatches(const string a[], int n, string target){
    if(n == 0){
        return 0;
    }
    if(n < 0){
        return -1;
    }
    int count = 0;
    for(int i = 0; i < n; i++){
        if(a[i] == target){
            count++;
        }
    }
    return count;
}

int detectMatch(const string a[], int n, string target) {
    if(n < 0){
        return -1;
    }
    for(int i = 0; i < n; i++){
        if(a[i] == target){
            return i;
        }
    }
    return -1;
}

bool detectSequence(const string a[], int n, string target, int& begin, int& end) {
    if(n < 0){
        return false;
    }
    int count = 0;
    for(int b = 0; b < n; b++){
        if(a[b] == target && count == 0){
                begin = b;
                count++;
                b++;
            while(b < n && a[b] == target){
            count++;
            b++;
            }
        }
    }
    if(count == 0){
        return false;
    }
    if(count == 1){
        end = begin;
        return true;
    }
    int endcount = 0; //used to check to see if endcount = count to find last occurrence of target;
    for(int c = 0; c < n; c++){
        if(a[c] == target){
            endcount++;
        }
        if(endcount == count){
            end = c;
            return true;
        }
    }
    return false;
}

int detectMin(const string a[], int n) {
    if(n <= 0){
        return -1;
    }
    string min = a[0];
    int index = 0;
    int i = 1;
    for(i = 1; i < n; i++){
        if(a[i] < min){
            min = a[i];
            index = i;
        }
    }
    return index;
}

int moveToBack(string a[], int n, int pos){
    if(n < 0 || pos < 0){
        return -1;
    }
    if(n < pos){
        return -1;
    }
    if(pos == n-1){
        return pos;
    }
    string spos = a[pos]; //the string that must be moved to the end
    for(int j = pos; j < n-1; j++){
        a[j] = a[j+1];
    }
    a[n-1] = spos;
    return pos;
}

int moveToFront(string a[], int n, int pos){
    if(n < 0 || pos < 0){
        return -1;
    }
    if(n < pos){
        return -1;
    }
    string fpos = a[pos]; //the string that needs to be moved to the front
    string temp = a[0]; //saves the string being replaced
    for(int j = 0; j < pos; j++){
        string t = a[j+1];
        a[j+1] = temp;
        temp = t;
    }
    a[0] = fpos;
    return pos;
}

int detectDifference(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0){
        return -1;
    }
    int minn;
    if(n1 < n2){
        minn = n1;
    }
    else{
        minn = n2; //minn now contains the lower value of n1 and n2
    }
    for(int k = 0; k < minn; k++){
        if(a1[k] != a2[k]){
            return k;
        }
    }
    return minn;
}

int deleteDups(string a[], int n) {
    if(n < 0){
        return -1;
    }
    int k = 0;
    int count = 0; //counts non duplicates
    string b[1000];
    while(k < n-1){
        if(a[k] != a[k+1]){
            b[count] = a[k];
            count++;
        }
        if(k == n-2){
                b[count] = a[k+1];
                count++;
        }
        k++;
    }
    for(int i = 0; i < count; i++){
        a[i] = b[i];
    }
    return count;
}

bool contains(const string a1[], int n1, const string a2[], int n2) {
    if(n2 < 0 || n1 < 0){
        return -1;
    }
    if(n2 > n1){
        return false;
    }
    int i = 0;
    int j = 0;
    int count = 0; //checks to make sure all the a2 elements were found
        while(j < n1 && i < n2){
            if(a1[j] == a2[i]){
                count++;
                j++;
                i++;
            }
            else {
            j++;
            }
        }
    if(count == n2){
        return true;
    }
    return false;
}

int meld(const string a1[], int n1, const string a2[], int n2, string result[], int max){
    if(n1 + n2 > max){
        return -1;
    }
    if(n1 < 0 || n2 < 0){
        return -1;
    }
    for(int c = 0; c < n1-1; c++){
        if(a1[c] > a1[c+1]){
            return -1;
        }
    }
    for(int d = 0; d < n2-1; d++){
        if(a2[d] > a2[d+1]){
            return -1;
        }
    }
    int total = n1 + n2;
    int e = 0;
    int a1c = 0; //makes sure a1 doesn't go past n1
    int a2c = 0; //makes sure a2 doesnt go past n2
    while(e < total){
        if(a1c < n1 && a2c < n2){
            if(a1[a1c] < a2[a2c]){
                result[e] = a1[a1c];
                a1c++;
            }
            else {
                result[e] = a2[a2c];
                a2c++;
            }
        }
        else if(a1c == n1){
            while(a2c < n2){
                result[e] = a2[a2c];
                a2c++;
                e++;
            }
        }
        else if(a2c == n2){
            while(a1c < n1){
                result[e] = a1[a1c];
                a1c++;
                e++;
            }
        }
        e++;
    }
    return n1+n2;
}

int split(string a[], int n, string splitter) {
    if(n < 0){
        return -1;
    }
    int countless = 0; //counts number of strings less than splitter;
    int countgreat = 0; //counts number of strings greater than spliter
    int countsame = 0; //counts number of strings equal to splitter
    string b[1000];
    string c[1000];
    string d[1000];
    for(int g = 0; g < n; g++){
        if(a[g] < splitter){
            b[countless] = a[g];
            countless++;
        }
        else if(a[g] > splitter){
            c[countgreat] = a[g];
            countgreat++;
        }
        else {
            d[countsame] = a[g];
            countsame++;
        }
    }
    for(int y = 0; y < countless; y++){
        a[y] = b[y];
    }
    for(int z = countless; z < countless + countsame; z++){
        a[z] = d[z-countless];
    }
    for(int x = countless + countsame; x < n; x++){
        a[x] = c[x-(countless + countsame)];
    }
    if(countgreat == 0){
        return n;
    }
    return countless;
    
    /* int lessCount = 0; //counts strings which are less than splitter
    int g = 0;
    while(g < n){
        string word = a[g];
        if(word < splitter){
            moveToFront(a, n, g);
            g++;
        }
        else {
            moveToBack(a, n, g);
            g++;
        }
    }
    for(int i = 0; i < n; i++){
        if(a[i] < splitter){
            lessCount++;
        }
    }
    return lessCount; */
}
