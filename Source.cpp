#include<iostream>
using namespace std;
#include<string>
#include <windows.h>
#include <future>
#include <conio.h>
#include <ctime> 
#pragma warning(disable:4996)

int new_seconds;  // varables 
int new_hours;
int new_minutes;
int maxChoice;

string twoDigitString(unsigned int n) {  //formats input
    if (n < 10) {
        string singleNum = to_string(n);
        string newSingleNum = "0" + singleNum;
        return newSingleNum;
    }
    else {
        string doubleNum = to_string(n);
        return doubleNum;
    }
}

string nCharString(size_t n, char c) { // creates * in correct order and number 
    std::string starSpaces;
    return starSpaces.append(n, c);
}

string formatTime12(int hour,  int minutes,  int second) { // formats time 12 into two sections "AM" and "PM"
    if (hour >= 12) {
        if (hour == 12) {
            return twoDigitString(hour) + ":" + twoDigitString(minutes) + ":" + twoDigitString(second) + " P M";
        }
        else {
            int realTime = 12;
            int newH = hour - realTime;
            return twoDigitString(newH) + ":" + twoDigitString(minutes) + ":" + twoDigitString(second) + " P M";
        }
    }
    else if (hour == 0) {
        int newH = 12;
        return twoDigitString(newH) + ":" + twoDigitString(minutes) + ":" + twoDigitString(second) + " A M";
    }
    else {
        return twoDigitString(hour) + ":" + twoDigitString(minutes) + ":" + twoDigitString(second) + " A M";
    }
}

string formatTime24(int hour, int minutes, int second) { // formats time 12 into two sections "AM" and "PM
    return twoDigitString(hour) + ":" + twoDigitString(minutes) + ":" + twoDigitString(second);
}
void printMenu() { // displays menue to user 
    cout << nCharString(25, '*') << endl;
    cout << nCharString(1, '*') << nCharString(1, ' ') << "1 " << nCharString(1, '-') << " Add One Hour" << nCharString(6, ' ') << '*' << endl;
    cout << endl;
    cout << nCharString(1, '*') << nCharString(1, ' ') << "2 " << nCharString(1, '-') << " Add One Minute" << nCharString(4, ' ') << '*' << endl;
    cout << endl;
    cout << nCharString(1, '*') << nCharString(1, ' ') << "3 " << nCharString(1, '-') << " Add One Second" << nCharString(4, ' ') << '*' << endl;
    cout << endl;
    cout << nCharString(1, '*') << nCharString(1, ' ') << "4 " << nCharString(1, '-') << " Exit Program" << nCharString(6, ' ') << '*' << endl;
    cout << nCharString(25, '*') << endl;
}

void displayClocks(unsigned int h, unsigned int m, unsigned int s) { //displays clocks 12 and 24 with chars '*' and ' ' 
    cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;
    cout << '*' << nCharString(6, ' ') << "12-HOUR CLOCK" << nCharString(6, ' ') << '*' << nCharString(3, ' ');
    cout << '*' << nCharString(6, ' ') << "24-HOUR CLOCK" << nCharString(6, ' ') << '*' << endl;
    cout << endl;
    cout << '*' << nCharString(6, ' ') << formatTime12(h, m, s) << nCharString(7, ' ') << '*' << nCharString(3, ' ');
    cout << '*' << nCharString(8, ' ') << formatTime24(h, m, s) << nCharString(9, ' ') << '*' << endl;
    cout << nCharString(27, '*') << nCharString(3, ' ') << nCharString(27, '*') << endl;
}

void addOneMinute(int new_seconds, int second, int hour, int minutes) { // adds minutes to current time
    if ((new_minutes >= 0) && (new_minutes <= 58)) {
        int diff_minutes = minutes + new_minutes + 1;
        if (diff_minutes > 60) {
            int difference_of = diff_minutes - 60;
            displayClocks(hour + 1, difference_of, second); //caluclates diff in time and adds it to them to hour 
        }
        else {
            displayClocks(hour, diff_minutes, second);
        }
    }
    else if (new_minutes == 59) {
        displayClocks(hour + 1, minutes, second);
    }
}

void addOneSecond(int new_seconds, int second, int hour, int minutes){ // adds seconds to current time 
    if ((new_seconds >= 0) && (new_seconds <= 58)){
        int diff_second = second + new_seconds + 1;
        if (diff_second > 60) {
            int difference_of = diff_second - second;
            displayClocks(hour, minutes + 1, difference_of);  // caluclates diff in time and adds it to them inutes 
        }
        else {
            displayClocks(hour, minutes, diff_second);
        }
    }
    else if (new_seconds == 59) {
        displayClocks(hour, minutes +1, second);
    }
}

void addOneHour(int new_hours, int second, int hour, int minutes) { //adds hours to current time in corret format 
    if ((new_hours >= 0) && (new_hours <= 22)) {
        hour = hour + new_hours;
        displayClocks(hour, minutes, second);
    }
    else if (new_hours == 23) {
        hour = 0;
        displayClocks(hour, minutes, second);
    }
}

    int main() {  //this block allows current time to show on clock + in my system it doesnt seem to fuction outside of main(). 
        time_t currentTime;
        struct tm* localTime_s;
        time(&currentTime);
        localTime_s = localtime(&currentTime);
        int hour = localTime_s->tm_hour;
        int minutes = localTime_s->tm_min;
        int second = localTime_s->tm_sec;
        displayClocks(hour, minutes, second); /// displays 24 and 12 hour clock 

    

        while (true) {
            printMenu(); // prints menu 
            cout << "Please slect an option." << endl;
            char c = _getch(); // allows to user to make a select from the menu
            if (c == '1') {
                cout << " How many hours would you like to add?" << endl;
                cin >> new_hours;
                system("CLS"); // clears screen
                addOneHour(new_hours, second, hour, minutes); // adds hour - resets to origional time every new time is inputted 
            }
            else if (c == '2') {
                cout << " How many minutes would you like to add?" << endl;// adds minutes - resets to origional time every new time is inputted 
                cin >> new_minutes;
                system("CLS");
                addOneMinute(new_minutes, second, hour, minutes);
            }
            else if (c == '3') {
                cout << " How many seconds would you like to add?"<< endl;
                cin >> new_seconds;
                system("CLS");
                addOneSecond(new_seconds, second, hour, minutes);// adds seconds - resets to origional time every new time is inputted 
            }
            else if (c == '4') {
                break; // breaks loop if user quits 
            }
            else {
                cout << "Please choose a valid option" << endl;
                continue;
            }
        }
    }