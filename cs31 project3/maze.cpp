//
//  main.cpp
//  test
//
//  Created by Vishal Sundaram on 19/4/19.
//  Copyright © 2019 Vishal Sundaram. All rights reserved.
//

#include "grid.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;

bool isCourseWellFormed(string course);
int driveSegment(int r, int c, char dir, int maxSteps);
int driveCourse(int sr, int sc, int er, int ec, string course, int& nsteps);

int main()
{
    setSize(3,4);      // make a 3 by 4 grid
    setWall(1,4);      // put a wall at (1,4)
    setWall(2,2);      // put a wall at (2,2)
    if (!isWall(3,2))  // if there's no wall at (3,2)  [there isn't]
        setWall(3,2);  //    put a wall at (3,2)
    draw(3,1, 3,4);    // draw the grid, showing an S at (3,1)
    //    start position, and an E at (3,4)
    int nsteps;
    cout << driveCourse(3, 1, 3, 1, "", nsteps);
    cout << endl;
    cout << nsteps << endl;
    cout << isCourseWellFormed("") << endl;
    cout << driveSegment(3, 1, 'e', 0) << endl;
}

bool isCourseWellFormed(string course){
    if(course == ""){
        return true;
    }
    if(isdigit(course[0])){
        return false;
    }
    string acceptable = "1234567890NSEWnsew"; //shows acceptable characters for well-formed string
    int ok = 0; //checks if course value is one of acceptable values
    int i = 0;
    while(i < course.size()){
        for(int j = 0; j < acceptable.size(); j++){
            if(acceptable[j] == course[i]){
                ok++;
            }
        }
        if(ok == 0){
            return false;
        }
        ok = 0;
        i++;
    }
    string dir = "NSEWnsew";
    int treydig = 0;
    for(int k = 0; k < course.size(); k++){
        for(int l = 0; l < dir.size(); l++){
            if(dir[l] == course[k]){
                int temp = k+1; //going to check three chars in front of k to check for a 3 digit number
                while(temp < course.size() && temp < k+4){
                    if(isdigit(course[temp])){
                        treydig++;
                        temp++;
                    }
                    else
                       temp = 10000000; //breaks out of while
                }
                if(treydig == 3){
                    return false; //means theres a triple digit number
                }
                else {
                    treydig = 0;
                }
            }
        }
    }
    return true;
}

int driveSegment(int r, int c, char dir, int maxSteps){
    if(getRows() < r || getCols() < c){
        return -1;  //if r or c is not valid
    }
    if(r < 1 || c < 1){
        return -1; //if r or c is not valid
    }
    string d = "NSEWnsew";
    int count = 0;
    for(int a = 0; a < d.size(); a++){
        if(d[a] == dir){
            count++;
        }
    }
    if(count == 0){
        return -1; //checks if dir valid
    }
    if(maxSteps < 0){
        return -1; //checks if maxsteps is negative
    }
    if(isWall(r, c)){
        return -1; //checks if r,c is valid empty grid pos
    }
    if(dir == 'E' || dir == 'e'){
        int check = 0;
        int ecol = c+1; //col addition means moving east
        while(check < maxSteps){
            if(ecol <= getCols()){
                if(isWall(r, ecol)){
                    return check;
                }
                ecol++;
                check++;
            }
            else {
                return check;
            }
            if(check == maxSteps)
                return check;
        }
        return maxSteps;
    }
    if(dir == 'W' || dir == 'w'){
        int check = 0;
        int wcol = c-1; //col subtraction means moving west
        while(check < maxSteps){
            if(wcol > 0){
                if(isWall(r, wcol)){
                    return check;
                }
                wcol--;
                check++;
            }
            else {
                return check;
            }
            if(check == maxSteps)
                return check;
        }
        return maxSteps;
    }
    if(dir == 'N' || dir == 'n'){
        int check = 0;
        int nrow = r-1; //row subtraction means moving north
        while(check < maxSteps){
            if(nrow > 0){
                if(isWall(nrow, c)){
                    return check;
                }
                nrow--;
                check++;
            }
            else {
                return check;
            }
            if(check == maxSteps)
                return check;
        }
        return maxSteps;
    }
    if(dir == 'S' || dir == 's'){
        int check = 0;
        int srow = r+1; //row addition means moving south
        while(check < maxSteps){
            if(srow <= getRows()){
                if(isWall(srow, c)){
                    return check;
                }
                srow++;
                check++;
            }
            else {
                return check;
            }
            if(check == maxSteps)
                return check;;
        }
        return maxSteps;
    }
    return 0; //should never get here if code runs properly, just makes sure function not void
}

int driveCourse(int sr, int sc, int er, int ec, string course, int& nsteps){
    nsteps = 0;
    if(course == ""){
        if(sr == er && sc == ec){
            return 0;
        }
        else {
            return 1;
        }
    }
    if(!isCourseWellFormed(course)){
        return 2;
    }
    if(sr > getRows() || sr < 1){
        return 2;
    }
    if(er > getRows() || er < 1){
        return 2;
    }
    if(sc > getCols() || sc < 1){
        return 2;
    }
    if(ec > getCols() || ec < 1){
        return 2;
    }
    if(isWall(sr, sc) || isWall(er, ec)){ //checks if sr,sc and er,ec are empty
        return 2;
    }
    int t = 0;
    while(t < course.size()){
       string d = "NSEWnsew";
        int a;
        for(a = 0; a < d.size(); a++){
            if(course[t] == d[a]){
                char dir = course[t];
                int temp = t;
                t++;
                while(isdigit(course[t]) && t < course.size()){
                    t++;
                }
                int numdig = t-temp-1; //finds out how large the digit is
                int step = 0;
                int dig = 0;
                if(numdig == 0){
                    dig = 1;
                    step = driveSegment(sr, sc, dir, dig);
                }
                if(numdig == 1){
                    dig = course[t-1] - '0';
                    step = driveSegment(sr, sc, dir, dig);
                }
                if(numdig == 2){
                    dig = 10*(course[t-2] - '0') + (course[t-1]-'0');
                    step = driveSegment(sr, sc, dir, dig);
                }
                
                    if(step < dig && step > -1){
                        nsteps += step;
                        return 3;
                    }
                    if(step <= 0 && dig != 0){
                        return 3;
                    }
                    if(dir == 'e' || dir == 'E'){
                        /*int temp = dig;
                        while(temp > 0){
                            if(isWall(sr, sc+1) || sc > getCols()){
                                return 3;
                            }
                            sc++;
                            temp--;
                            nsteps++;
                        }*/
                        sc += step;
                    }
                    if(dir == 'w' || dir == 'W'){
                        /*int temp = dig;
                        while(temp >0){
                            if(isWall(sr, sc-1) || sc < 1){
                                return 3;
                            }
                            sc--;
                            temp--;
                            nsteps++;
                        }*/
                        sc -= step;
                    }
                    if(dir == 'n' || dir == 'N'){
                        /*int temp = dig;
                        while(temp >0){
                            if(isWall(sr-1, sc) || sr < 1){
                                return 3;
                            }
                            sr--;
                            temp--;
                            nsteps++;
                        }*/
                        sr -= step;
                    }
                    if(dir == 's' || dir == 'S'){
                        /*int temp = dig;
                        while(temp >0){
                            if(isWall(sr+1, sc) || sr > getRows()){
                                return 3;
                            }
                            sr++;
                            temp--;
                            nsteps++;
                        }*/
                        sr += step;
                        
                    }
                nsteps += step;
                a = 0;
                }
            }
        }
    if(sr == er && sc == ec){
        return 0;
    }
    else {
        return 1;
    }
}






