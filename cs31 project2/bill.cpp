//
//  main.cpp
//  cs31 project 2
//
//  Created by Vishal Sundaram on 19/4/19.
//  Copyright © 2019 Vishal Sundaram. All rights reserved.
//

//
//  bill.cpp
//  cs31 project2
//
//  Created by Vishal Sundaram on 14/4/19.
//  Copyright © 2019 Vishal Sundaram. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
    
    cout.setf(ios::fixed);
    cout.precision(2); //rounds doubles to 2 digits after the decimal
    
    cout << "Initial meter reading: " ;
    int imr;
    cin >> imr; //gets user input
    if(imr < 0){
        cout << "---" << endl;
        cout << "The initial meter reading must be nonnegative." << endl;
        return 1; //returns after error
    }
    
    cout << "Final meter reading: ";
    int fmr;
    cin >> fmr; //gets user input
    if(fmr < imr){
        cout << "---" << endl;
        cout << "The final meter reading must be at least as large as the initial reading." << endl;
        return 1; //returns after error
    }
    cin.ignore(10000, '\n'); //ignores newspace character, allows user to respond to customer name output
    
    cout << "Customer name: ";
    string name;
    getline(cin, name); //gets user input
    if(name.size() == 0){
        cout << "---" << endl;
        cout << "You must enter a customer name." << endl;
        return 1; //returns after error
    }
    
    cout << "Month number (1=Jan, 2=Feb, etc.): ";
    int month;
    cin >> month; //gets user input
    if(month > 12 || month < 1){
        cout << "---" << endl;
        cout << "The month number must be in the range 1 through 12" << endl;
        return 1; //returns after error
    }
    cout << "---" << endl; // done with user input
    
    if(4 <= month && month <= 10){ //high seasons
        int usage = fmr-imr;
        if(usage > 43) { //overusage
            double ans = 2.71*43 + 3.39* (usage-43); //ans stores final dollar value
            cout << "The bill for " + name + " is $" << ans << endl;
        }
        else {  //normal usage
            double ans = 2.71*usage;
            cout << "The bill for " + name + " is $" << ans << endl;
        }
    }
    else { //low seasons
        int usage = fmr - imr;
        if(usage > 29){  //overusage
            double ans = 2.71*29 + 2.87* (usage - 29);
            cout << "The bill for " + name + " is $" << ans << endl;
        }
        else { //normal usage
            double ans = 2.71*usage;
            cout << "The bill for " + name + " is $" << ans << endl;
        }
    }
    
}


