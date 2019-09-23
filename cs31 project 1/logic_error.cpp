//
//  main.cpp
//  cs31 project1 part 2
//
//  Created by Vishal Sundaram on 8/4/19.
//  Copyright © 2019 Vishal Sundaram. All rights reserved.
//

// Code for Project 1
// Report poll results

#include <iostream>
using namespace std;   // pp. 38-39 in Savitch 6/e explains this line

int main()
{
    int numberSurveyed;
    int numberOfRemainers;
    int numberOfLeavers;
    
    cout << "How many UK citizens were surveyed? ";
    cin >> numberSurveyed;
    cout << "How many of them want to remain in the EU? ";
    cin >> numberOfRemainers;
    cout << "How many of them want to leave the EU? ";
    cin >> numberOfLeavers;
    
    double pctRemainers = 100.0 + numberOfRemainers / numberSurveyed; //added 100 to the remainers proportion instead of multiplying (logic error)
    double pctLeavers = 100.0 * numberSurveyed / numberOfLeavers; //multiplied the number surveyed/number of leavers by 100 instead of the number of leavers/number surveyed (logic error)
    
    cout.setf(ios::fixed);       // see pp. 32-33 in Savitch 6/e
    cout.precision(1);
    
    cout << endl;
    cout << pctRemainers << "% are Remainers." << endl;
    cout << pctLeavers << "% are Leavers." << endl;
    
    if (numberOfRemainers > numberOfLeavers)
        cout << "More people want to Remain than Leave." << endl;
    else
        cout << "More people want to Leave than Remain." << endl;
}

