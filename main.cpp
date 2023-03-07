#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

char files[10][50] {"Users.txt", "Librarians.txt", "Books.txt", "Activitylog.txt", "Report.txt", "temp.txt", "Requests.txt", "Accepted.txt", "Blacklist.txt"};

// Set time for Activity log
time_t now = time(0);
char* dt = ctime(&now);
// Structures to store user and book
struct book{
    char title[50];
    char author[50];
    char id[50]; };
struct user{
    char name[50];
    char id[15];
    char pass[50];
    string type;
};user currentuser;
// Function Prototype
void firstMenu();
void studentMenu();
void studentPage();
bool login(int);
void signin(int);
void forgotpassword(int);
void showfile(int);
void borrowBook();
void myBooks(int);
void accountManagement(int);
void myInfo();
void changename(int);
void changepass(int);
void deleteAcc(int);
void librarianMenu(int);
void bookManagement();
void addbook();
void searchbook();
void updatebook();
void deletebook();
void lendManagement();
void acceptrequest();
void acceptreturn();
void userManagement();
void showUsers(int);
void addblacklist();
void removeblacklist();
void inventory(int);
void adminMenu();
void clear();
bool verifyPassword(int);
string securePassword(char*, char);
string replace(char*, char, char);
// Clear Screen
void clear(){
    system("CLS");
}
// Ask user to continue after a display
void cont(int t=0){
    char x[50];
    cout << "\n\n\t\t>> Press Enter to Continue :-)";
    if(t==0)
        cin.ignore();
    cin.getline(x, 50);
    clear();
}
// Hash passwords for security
string securePassword(char *pass, char t = 'e'){ // e - encrypt d - decrypt
    int len = strlen(pass);
    string hidden;
    for(int i=0; i<len; i++){
        if (t=='d'){
            if (pass[i] == ' ')
                pass[i] = '#';
            hidden += pass[i] + 1;
        }
        else{
            if (pass[i] == '#')
                pass[i] = ' ';
            hidden += pass[i] - 1;
        }
    }return hidden;
}
// Check if the password is correct
bool verifyPassword(int t){ clear();
    string p, n; char u[50];
    bool verified = false;
    cout << "\n\n\t\t Hi " << replace(currentuser.name, '_', ' ') << ":-)\n\n\t\t>> Enter your Password: \t";
    cin.getline(currentuser.pass, 50);
    ifstream file(files[t]);
    while(file>>u>>p>>n){
        if(p==securePassword(currentuser.pass) && strcasecmp(u, currentuser.id) == 0){
        verified = true;
        break;
        }
    }file.close();
    clear();
    return verified;
}
// Replace ' ' blank space for files and return string
string replace(char *value, char x = ' ', char y= '_'){
    string v;
    for(int i=0; i<strlen(value); i++){
        if (value[i] == x)
            value[i] = y;
        v += value[i];
    }return v;
}
// Replace ' ' blank space from memory
void replace2(char *value, char x = ' ', char y= '_'){
     for(int i=0; i<strlen(value); i++){
         if (value[i] == x)
             value[i] = y;}
 }
// Check if the search value exists in the file
bool check(char x[50], int t=0){
    char u[50], n[50], p[50]; bool exists = false;
    ifstream file(files[t]);
    while(file>>u>>p>>n){
        if(strcasecmp(u, x) == 0){
            exists = true; break;}
    } file.close();
    return exists;
}
// Access Account
bool login(int t=0){ clear();
    if (t==5) // Skip Login process for admin
        return true;
    char u[50], p[50], n[50];
    bool success = false;
    cout << "\n\n\t\t----------------- Enter Login Info -----------------\n";
    if(t==0)
        cout << "\n\t\t>> Enter your Student ID No: \t";
    else
        cout << "\n\t\t>> Enter your Librarian ID No: \t";
    cin.ignore();
    cin.getline(currentuser.id, 50);
    ifstream file(files[t]);
    while(file>>u>>p>>n){
        if(strcasecmp(currentuser.id, u)==0){
            strcpy(currentuser.name, n); strcpy(currentuser.id, u);
            t == 0 ? currentuser.type = "Student": currentuser.type = "Librarian";
            success = true;
            break;
        }
    } file.close();
    if(success){
        if (verifyPassword(t)){
            cout << "\n\n\t\t<> Logged in Successfully.\n";
            fstream log; log.open(files[3], ios::out | ios::app);
            log << dt << currentuser.type << " " << currentuser.id << " Logged in.\n";
            log.close();
        }else{
            success = false;
            cout << "\n\n\t\t<!> Incorrect Password. Try again later.\n";
        }
    }else{
        success = false;
        cout << "\n\n\t\t<!> Sorry, Can't find your ID in the list. Try registering.\n";
    }cont(1);
    return success;
}
// Display currently logged in Account
void info(){
    cout << "\n\t\t\t>> Logged in as " << currentuser.type << " " << currentuser.id << " <<\n";
}
// Count the lines of a file
int counter(int t=0){
    int count = -4;
    string getcontent;
    ifstream openfile (files[t]);
        if(openfile.is_open()){
            while(!openfile.eof()){
            getline (openfile, getcontent);
            count++;
        }openfile.close();
    }return count;
}
// Display users list
void showUsers(int t=0){ clear();
    char u[50], p[50], n[50];
     switch(t){
     case 0:
        cout << "\n\n\t\t-------- Users List -----------\n";
        break;
     case 1:
        cout << "\n\n\t\t------- Librarian List --------\n";
        break;
     case 8:
        cout << "\n\n\t\t--------- Blacklist -----------\n";
        break;
     default:
        break;
        }
    user x;
    cin.getline(x.id, 15);
    ifstream file(files[t]);
    bool flag = false;
    while(file>>u>>p>>n){
        cout << "\t\t" << setw(15) << left << u << setw(10) << right << n << endl;
    } file.close();
    cont(1);
}
// Admin Menu
void adminMenu(){ clear();
    int choice;
    currentuser.type = "Admin";
    for(int i=0; i<strlen(currentuser.name); i++){
        currentuser.name[i] = ' ';
        currentuser.id[i] = ' ';
    }
    do{
        cout << "\n\n\t\t----------------- WELCOME ADMIN -----------------\n\n"; info();
        cout << "\n\n\t\t1. Add Librarian\n\n\t\t2. Librarian List\n\n\t\t3. Activity Log\n\n\t\t4. Librarian mode\n\n\t\t5. Student Mode\n\n\t\t6. Inventory and Status\n\n\t\t7. Back\n\n\t\t0. Destroy System\n\n\t\t>> Enter your choice: \t";
        cin >> choice;
        switch (choice){
        case 1:
            signin(1); break;
        case 2:
            showUsers(1); break;
        case 3:
            showfile(3); break;
        case 4:
            librarianMenu(5); break;
        case 5:
            studentPage();break;
        case 6:
            inventory(5); break;
        case 7:
            break;
        case 0:
            clear(); cout << "\n\n\t\tBOOOOOOOOOOOOOMMMMMMM!" << endl; exit(0);
        default:
            clear(); cout << "\n\n\t\t<!> Wrong Input! Try Again!";
            break;
        }
    }while (choice != 7);
      clear();
}
// Main Menu
void firstMenu(){ clear();
    int choice;
    do {
        cout << "\n\n\t\t----------------- WELCOME TO AASTU LMS -----------------\n" << endl;
        cout << "\t\t >> I'm: \n\n\t\t1. Student\n\n\t\t2. Librarian\n\n\t\t3. Admin\n\n\n\t\t0. Exit\n\n\t\t>> Enter your choice: \t";
        cin >> choice;
        switch (choice){
        case 1:
            studentMenu(); break;
        case 2:
            librarianMenu(1); break;
        case 3:
            clear(); int x; cout << "\n\n\t\t>> Passcode: \t"; cin>>x;
            x == 9 ? adminMenu() : exit(0); break;
        case 0:
            break;
        default:
            clear(); cout << "\n\n\t\t<!> Wrong Input! Try Again"; break;
        }
    }while(choice != 0);
    clear(); cout << "\n\n\t\tBye, See you later!\n\n\n";
}
// Student Log in menu
void studentMenu(){ clear();
    int choice;
    do{
        cout << "\n\n\t\t----------------- STUDENT MENU -----------------\n";
        cout << "\n\t\t1. Log in\n\n\t\t2. Register\n\n\t\t3. Forgot Password\n\n\t\t4. Back\n\n\n\t\t0. Exit\n\n\t\t>> Enter your choice: \t";
        cin >> choice;
        switch (choice)
        {
        case 1:
            if(login())
                studentPage();
            break;
        case 2:
            signin(0); break;
        case 3:
            forgotpassword(0); break;
        case 4:
            break;
        case 0:
            exit(0); break;
        default:
            clear(); cout << "\n\n\t\t<!> Wrong Input! Try Again!"; break;
        }
    }while(choice!=4);
    clear();
}
// Student Menu
void studentPage(){ clear();
    int choice;
    do{
        cout << "\n\n\t\t----------------- WELCOME TO AASTU LMS -----------------\n\n";info();
        cout << "\n\n\t\t1. Show Books\n\n\t\t2. Search Book\n\n\t\t3. Request to Borrow Book\n\n\t\t4. My Requests\n\n\t\t5. My Borrows\n\n\t\t6. Account Setting\n\n\t\t7. Back\n\n\t\t0. Exit\n\n\t\t>> Enter your choice: \t";
        cin >> choice;
        switch (choice){
        case 1:
            showfile(2); break;
        case 2:
            searchbook(); break;
        case 3:
            borrowBook(); break;
        case 4:
            myBooks(6); break;
        case 5:
            myBooks(7); break;
        case 6:
            accountManagement(0); break;
        case 7:
            break;
        case 0:
            exit(0); break;
        default:
            clear(); cout << "\n\n\t\t<!> Wrong Input! Try Again!"; break;
        }
    }while (choice != 7);
    clear();
}
// User Registration
void signin(int t=0){ clear();
    user newuser;
    cout << "\n\n\t\t----------------- Enter Sign in Info -----------------";
    cin.ignore();
    cout << "\n\n\t\t Enter Full Name: \t";
    cin.getline(newuser.name, 50);
    if(strlen(newuser.name) > 3){
    cout << "\n\n\t\t Hi " << newuser.name << ":-)\n\n\t\t Enter your Id No: \t";
    cin.getline(newuser.id, 15);
    if(!check(newuser.id, t)){
        if (strlen(newuser.id)>3){
            cout << "\n\n\t\t>Enter Password: \t";
            cin.getline(newuser.pass, 50);
            if(strlen(newuser.pass)>3){
                fstream file;
                file.open(files[t], ios::out | ios::app);
                file << setw(10) << left <<  replace(newuser.id) << "\t" <<  setw(20) << left << securePassword(newuser.pass) << "\t" << setw(20) << left <<  replace(newuser.name) << endl;
                file.close();
                cout << "\n\n\t\t Registration Successfull\n";
                fstream log; log.open(files[3], ios::out | ios::app);
                t == 1? log << dt << "New Librarian " << newuser.id << " added by Admin.\n": log << dt << "New Student " << newuser.id << " Registered.\n";
                log.close();
            }else
                cout << "\n\t\tInvalid Password!\n";
        }else
            cout << "\n\t\tInvalid ID!\n";
    }else
        cout << "\n\n\t\t I think you already have an Account.\n\t\tTry Logging in..." << endl;
    }else
        cout << "\n\t\tInvalid Name. Please Enter your full name!\n";
    cont(1);
}
// Recover Forgotten Password
void forgotpassword(int t=0){ clear();
    char u[50], p[50], n[50];
    cout << "\n\n\t\t----------------- Password Recovery -----------------\n";
    user x;
    if (t==0)
        cout << "\n\t\tEnter your Student ID No: \t";
    else if (t==1)
        cout << "\n\t\tEnter your Librarian ID No: \t";
    cin.ignore();
    cin.getline(x.id, 15);
    ifstream file(files[t]);
    bool flag = false;
    while(file>>u>>p>>n){
        if(strcasecmp(u, x.id) == 0){
            flag = true;
            cout << "\n\n\t\tEnter your Full Name: \t";
            cin.getline(x.name, 50);
            if(n== replace(x.name)){
                cout << "\n\n\t\t>> Your password is: \t" << securePassword(p, 'd') << endl << "\n\t\tTry Not to forget Again!\n";
                fstream log; log.open(files[3], ios::out | ios::app);
                log << dt << "Student " << x.id << " Recovered his/her Password.\n";
                log.close();
            }else
                cout << "\n\n\t\t <!> Who are you?  Try Registering.\n" << endl;
        }
    }file.close();
    if(!flag)
       cout << "\n\n\t\tSorry, Can't find your ID in the list. Try registering.";
    cont(1);
}
// Display Everything in a file
void showfile(int t=2){ clear();
    string getcontent;
    ifstream openfile (files[t]);
        if(openfile.is_open()){
            while(!openfile.eof()){
            getline (openfile, getcontent);
            cout << "\t\t" << getcontent << endl; // these two lines alone in a while loop display ALL records
        }
        openfile.close();
     }cont();
}
// User Search for a book
void searchbook(){ clear();
    int choice;
    cout << "\n\n\t\t----------------- Search Book By -----------------\n" << endl;
    cout << "\n\t\t1. ID\n\n\t\t2. Title\n\n\t\t3. Author\n\n\t\tEnter your choice: \t";
    cin >> choice;
    switch (choice){
    case 1:
        cout << "\n\n\t\tEnter Book ID to search: \t"; break;
    case 2:
        cout << "\n\n\t\tEnter Book Title to search: \t"; break;
    case 3:
        cout << "\n\n\t\tEnter Author Name to search: \t"; break;
    }
    char value[4][50];
    cin.ignore();
    cin.getline(value[0], 50);
    replace2(value[0]);
    bool found = false;
    ifstream searchb(files[2]);
    cout << "\n\n\t\t>> Search Results: \t";
    while(searchb>>value[1]>>value[2]>>value[3]){
        int x = strncasecmp(value[0], value[choice], strlen(value[0]));
        if(x == 0){
            found = true;
            cout << "\n\t\t--------------\n";
            cout << "\t\t" << setw(10) << left << value[1] << setw(40) << left << replace(value[2], '_', ' ') << "by " <<setw(10) << left  << replace(value[3], '_', ' ');
        }
    }
    if (!found)
            cout << "\n\n\t\t<!> Nothing found!";
    fstream log; log.open(files[3], ios::out | ios::app);
    log << dt << currentuser.type << " " << currentuser.id << " Searched for book " << value[0] <<".\n";
    log.close();
    cont(1);
}
// Request to borrow Book
void borrowBook(){ clear();
    string bn, an; char value[50], bid[50];
    cout << "\n\n\t\t----------------- BORROW BOOK -----------------\n";
    cin.ignore(); cout << "\n\n\t\t>> Enter book ID to borrow: \t";
    cin.getline(value, 50);
    if(check(value, 2)){
        if(!check(value, 7)){
            ifstream open(files[2]);
            ofstream write(files[6], ios::app);
            while (open >> bid >> bn >> an) {
                if (strcasecmp(bid, value) == 0) {
                    string confirm; char y;
                    cout << "\n\t\t----------------------------------\n";
                    cout << "\t\t" << bid << "\t" << bn << "\tby " << an << endl;
                    cout << "\t\t----------------------------------\n";
                    cout << "\n\n\t\t >> Are you sure? Do you want to borrow the this book(Y/N)? ";
                    cin >> confirm;
                    if (confirm[0] == 'Y' || confirm[0] == 'y')
                        y = 'y';
                    else
                        y = 'n';
                    switch(y){
                        case 'y':
                        case 'Y':{
                            write << setw(10) << left << bid << "\t" << setw(40) << left << bn << "\t" << setw(20) << left << currentuser.id << endl;
                            cout << "\n\n\t\t<> Request Successfull" << endl;
                            fstream log; log.open(files[3], ios::out | ios::app);
                            log << dt << currentuser.type << " " << currentuser.id << " Requested to borrow book " << bid <<".\n"; log.close();
                            }break;
                        default:
                            cout << "\n\n\t\t<!>Request canceled!\n";
                            break;
                    }
                }
            }write.close();
        }else
            cout << "\n\n\t\t<!> Sorry, omeone Already borrowed the book! You can try another one." << endl;
    }else
        cout << "\n\n\t\t<!> Could not find the book. Check your Book ID!" << endl;
    cont();
}
// Books borrowed by current user
void myBooks(int t = 7){
    char bid[50], bn[50], un[50]; int i = 0;
    switch (t){
    case 6:
        cout << "\n\n\t\t------------------ My Requests -------------------\n"; break;
    case 7:
        cout << "\n\n\t\t-------------------- My Books --------------------\n"; break;
    } ifstream file(files[t]);
    while(file>>bid>>bn>>un){
        if (i < 3 || strcasecmp(un, currentuser.id) == 0){
            cout << "\t\t" << setw(10) << left << bid << setw(10) << right << bn << endl;
        } i++;
    } file.close();
    cont();
}
// Account Menu
void accountManagement(int t=0){ clear();
    int choice;
    do{
        cout << "\n\n\t\t----------------- ACCOUNT SETTING -----------------\n\n"; info();
        cout << "\n\n\t\t1. My Information\n\n\t\t2. Change Name\n\n\t\t3. Change Password\n\n\t\t4. Delete Account \n\n\t\t5. Back\n\n\n\t\t0. Exit\n\n\t\t>>Enter your choice: \t";
        cin >> choice;
        switch (choice){
        case 1:
            myInfo(); break;
        case 2:
            changename(t); break;
        case 3:
            changepass(t); break;
        case 4:
            deleteAcc(t); break;
        case 5:
            break;
        case 0:
            exit(0);
        default:
            clear(); cout << "\n\n\t\t>> Wrong Input! Try Again!"; break;
        }
    }while (choice != 5);
    clear();
}
// Display Current User Information
void myInfo(){ clear();
    cout << "\n\n\t\tName: " << replace(currentuser.name, '_', ' ') << endl;
    cout << "\n\t\t  Id: " << currentuser.id << endl;
    cout << "\n\t\tType: " << currentuser.type << endl;
    cont();
}
// Change current user account name
void changename(int t=0){ clear();
    char uid[50], p[50], n[50], search[50], nn[50]; string np;
    cout << "\n\n\t\t----------------- CHANGE NAME -----------------\n\n";
    cout << "\n\n\t\t >> Enter your ID: \t";
    cin >> search;
    if(check(search, t) && strcasecmp(search, currentuser.id)==0){
        ifstream open(files[t]);
        ofstream write("temp.txt");
        while (open >> uid >> p >> n) {
            if (strcasecmp(uid, search) == 0) {
                cout << "\n\n\t\t Current Name: \t" << replace(n, '_', ' ') <<"\n\n\t\t>> Enter new Name: \t";
                cin.ignore();
                cin.getline(nn, 50);
                cout << "\n\n\t\t>> Enter your password to confirm: \t";
                cin >> np;
                if(np== securePassword(p, 'd')){
                    strcpy(currentuser.name, nn);
                    write << setw(10) << left <<  uid << "\t" <<  setw(20) << left << p << "\t" <<  setw(20) << left << replace(nn) << endl;
                    cout << "\n\n\t\tUpdate successfull!\n";
                    fstream log; log.open(files[3], ios::out | ios::app);
                    log << dt << currentuser.type << " " << currentuser.id << " Changed his/her name from " << replace(n, '_', ' ') << " to " << nn <<".\n";
                    log.close();
                }
                else{
                    write << setw(10) << left <<  uid << "\t" <<  setw(20) << left << p << "\t" << setw(20) << left <<  n << endl;
                    cout << "\n\n\t\t<!> Incorrect Password\n";
                }
            }else
                write << setw(10) << left <<  uid << "\t" <<  setw(20) << left << p << "\t" << setw(20) << left <<  n << endl;
        }
        write.close(); open.close();
        remove(files[t]); rename("temp.txt", files[t]);
    }else
        cout << "\n\n\t\t<!> Incorrect ID.\n";
    cont();
}
// Change current user account Password
void changepass(int t=0){ clear();
    char uid[50], p[50], n[50], search[50], np[50]; string cp;
    cout << "\n\n\t\t----------------- CHANGE PASSWORD -----------------\n\n";
    cout << "\n\n\t\t>> Enter your ID: \t";
    cin >> search;
    if(check(search, t) && strcasecmp(search, currentuser.id)==0){
        ifstream open(files[t]);
        ofstream write("temp.txt");
        while (open >> uid >> p >> n) {
            if (strcasecmp(uid, search) == 0) {
                cout << "\n\n\t\t>> Enter your current password: \t";
                cin >> cp;
                if(cp== securePassword(p, 'd')){
                    cout <<"\n\n\t\t>> Enter new Password: \t";
                    cin.ignore();
                    cin.getline(np, 50);
                    write << setw(10) << left <<  uid << "\t" <<  setw(20) << left << securePassword(np) << "\t" <<  setw(20) << left << n << endl;
                    strcpy(currentuser.pass, np);
                    cout << "\n\n\t\t<> Password changed successfully!\n";
                    fstream log; log.open(files[3], ios::out | ios::app);
                    log << dt << currentuser.type << " " << currentuser.id << " Changed password."<<".\n";
                    log.close();
                }else{
                    write << setw(10) << left <<  uid << "\t" <<  setw(20) << left << p << "\t" << setw(20) << left <<  n << endl;
                    cout << "\n\n\t\t<!> Incorrect Password!\n";
                }
            }else
                write << setw(10) << left <<  uid << "\t" <<  setw(20) << left << p << "\t" << setw(20) << left <<  n << endl;
        }write.close(); open.close();
        remove(files[t]); rename("temp.txt", files[t]);
    }else
        cout << "\n\n\t\t<!> Incorrect ID.\n";
    cont(1);
}
// Delete Account
void deleteAcc(int t=0){ clear();
    char uid[50], p[50], n[50], search[50], np[50]; string cp;
    cout << "\n\n\t\t----------------- DELETE ACCOUNT -----------------\n\n";
    cout << "\n\n\t\t>> Enter your ID: ";
    cin >> search;
    if(check(search, t) && strcasecmp(search, currentuser.id)==0){
        ifstream open(files[t]);
        ofstream write("temp.txt");
        while (open >> uid >> p >> n) {
            if (strcasecmp(uid, search) == 0) {
                cout << "\n\n\t\t<?> Your Account will be deleted.\n\n\t\t>> Enter your password to confirm: \t";
                cin >> cp;
                if(cp== securePassword(p, 'd')){
                    cout << "\n\n\t\t Account Deleted successfully!\n";
                    cont();
                    fstream log; log.open(files[3], ios::out | ios::app);
                    log << dt << currentuser.type << " " << currentuser.id << " deleted his/her Account.\n";
                    log.close();
                }else{
                    write << setw(10) << left <<  uid << "\t" <<  setw(20) << left << p << "\t" << setw(20) << left <<  n << endl;
                    cout << "\n\n\t\t<!> Incorrect Password! Logging out....";
                    cont();
                }
            }else
                write << setw(10) << left <<  uid << "\t" <<  setw(20) << left << p << "\t" << setw(20) << left <<  n << endl;
        }write.close(); open.close();
        remove(files[t]); rename("temp.txt", files[t]);
        firstMenu();
    }else
        cout << "\n\n\t\t<!> Incorrect ID.\n";
    cont();
}
// Librarian Menu
void librarianMenu(int t=1){ clear();
    if (login(t)){
        int choice;
        do{
            cout << "\n\n\t\t----------------- WELCOME TO AASTU LMS -----------------\n\n"; info();
            cout << "\n\n\t\t1. Manage Books\n\n\t\t2. Transactions\n\n\t\t3. Manage Users\n\n\t\t4. Inventory and Status\n\n\t\t5. Account Setting\n\n\t\t6. Back\n\n\n\t\t0. Exit\n\n\t\t>> Enter your choice: \t";
            cin >> choice;
            switch (choice){
            case 1:
                bookManagement(); break;
            case 2:
                lendManagement(); break;
            case 3:
                userManagement(); break;
            case 4:
                inventory(t); break;
            case 5:
                accountManagement(1); break;
            case 6:
                break;
            case 0:
                exit(0);
            default:
                clear(); cout << "\n\n\t\t<!> Wrong Input! Try Again!"; break;
            }
        }while (choice != 6);
        clear();
    }
}
// Book Management Menu
void bookManagement(){ clear();
    int choice;
    do{
        cout << "\n\n\t\t----------------- BOOK MANAGEMENT -----------------\n"; info();
        cout << "\n\n\t\t1. Add Book\n\n\t\t2. Update Book\n\n\t\t3. Delete Book\n\n\t\t4. Show Books\n\n\t\t5. Back\n\n\t\t0. Exit\n\n\t\t>> Enter your choice: \t";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addbook(); break;
        case 2:
            updatebook(); break;
        case 3:
            deletebook(); break;
        case 4:
            showfile(2); break;
        case 5:
            break;
        case 0:
            exit(0);
        default:
            cout << "\n\n\t\t<!> Wrong Input! \n See you later!"; break;
        }
    }while (choice != 5);
      clear();
}
// Librarian Add Books
void addbook(){ clear();
    book newbook; string n;
    cout << "\n\n\t\t----------------- ADD BOOK -----------------\n "; 
    do{
        ofstream file;
        file.open(files[2],ios::app);
        cout << "\n\n\t\t>> Enter Book ID: ";
        cin >> newbook.id;
        if(!check(newbook.id, 2)){
            cin.ignore();
            cout << "\n\n\t\t>> Enter Book name: ";
            cin.getline(newbook.title, 50);
            cout << "\n\n\t\t>> Enter Author name: ";
            cin.getline(newbook.author, 50);
            file << setw(10) << left << newbook.id << "\t" << setw(40) << left<< replace(newbook.title, ' ', '_') << "\t" << setw(20) << left << replace(newbook.author, ' ', '_') << "\n";
            file.close();
            fstream log; log.open(files[3], ios::out | ios::app);
            log << dt << currentuser.type << " " << currentuser.id << " added new book " << newbook.id <<".\n";
            log.close();
        }else{
            cout << "\n\n\t\t<!> There is a Book with this ID! Check the Id or Delete the existing Book.\n"; break;}
    cout << "\n\n\t\t>> Do you want to add another book? Y/N: \t";
    cin >> n;
    }while(n[0] == 'y' ||n[0] == 'Y');
    cont();
}
// Change Book Info
void updatebook(){ clear();
    char bid[50], bn[50], an[50], search[50];
    cout << "\n\n\t\t----------------- CHANGE BOOK INFO -----------------\n "; 
    cout << "\n\n\t\t >> Enter the book id you want to modify: \t";
    cin >> search;
    if(check(search, 2)){
        ifstream open(files[2]);
        ofstream write("temp.txt");
        while (open >> bid >> bn >> an) {
            if (strcasecmp(bid, search) == 0) {
                cout << "\n\n\t\t>> Enter new records for the book with id " << bid;
                cout << "\n\n\t\tCurrent Book Name: \t" << bn <<"\n\n\t\t>> Enter new Book Name: \t";
                cin.ignore();
                cin.getline(bn, 50);
                cout << "\n\n\t\tCurrent Author Name: \t" << an  << "\n\n\t\t>> Enter new Author Name: \t";
                cin.getline(an, 50);
                fstream log; log.open(files[3], ios::out | ios::app);
                log << dt << currentuser.type << " " << currentuser.id << " updated book " << bid <<" info.\n";
                log.close();
            } write << setw(10) << left <<  bid << "\t" <<  setw(40) << left << replace(bn) << "\t" <<  setw(20) << left << replace(an) << endl;
        } write.close(); open.close();
        remove(files[2]); rename("temp.txt", files[2]);
        cout << "\n\n\t\t <> Update successful!\n\n";
    }else
        cout << "\n\n\t\t<!> Sorry, can't find a book with this ID.\n";
    cont(1);
}
// Remove Book Info
void deletebook(){ clear();
    char bid[50], bn[50], an[50], search[50];
    cout << "\n\n\t\t----------------- DELETE BOOK -----------------\n "; 
    cout << "\n\n\t\t>> Enter the book ID to delete: \t";
    cin >> search;
    if(check(search, 2)){
        ifstream open(files[2]);
        ofstream write("temp.txt");
        while (open >> bid >> bn >> an) {
            if (strcasecmp(bid, search) == 0) {
                string confirm; char y;
                cout << "\n\t\t----------------------------------\n";
                cout << bid << "\t" << replace(bn, '_', ' ') << " \tby " << replace(an, '_', ' ') << endl;
                cout << "\t\t----------------------------------\n";
                cout << "\n\n\t\t <?> Are you sure? Do you want to delete the this book's data(Y/N)? \t";
                cin >> confirm;
                if (confirm[0] == 'Y' || confirm[0] == 'y')
                    y = 'y';
                else
                    y = 'n';
                switch(y){
                    case 'y':
                    case 'Y':{
                        cout << "\n\n\t\t Deleted successfully!\n";
                        fstream log; log.open(files[3], ios::out | ios::app);
                        log << dt << currentuser.type << " " << currentuser.id << " Deleted book " << bid <<".\n";
                        log.close();
                        }break;
                    default:
                        cout << "\n\n\t\t<!> Process canceled!\n";
                        write << setw(10) << left << bid << "\t" << setw(40) << left << bn << "\t" << setw(20) << left << an << endl;
                        break;
                }
            }else{
                write << setw(10) << left << bid << "\t" << setw(40) << left << bn << "\t" << setw(20) << left << an << endl;
            }
        }write.close(); open.close();
        remove(files[2]); rename("temp.txt", files[2]);
    }else
        cout << "\n\n\t\t <!> Sorry, can't find a book with this ID.\n";
    cont();
}
// Lend Transaction Menu
void lendManagement(){ clear();
    int choice;
    do{
        cout << "\n\n\t\t----------------- BOOK LEND MANAGEMENT -----------------\n "; info();
        cout << "\n\n\t\t1. Show Requests\n\n\t\t2. Accept / Decline Requests\n\n\t\t3. Show Borrowed Books\n\n\t\t4. Accept Book Return\n\n\t\t5. Back\n\n\n\t\t0. Exit\n\n\t\t>> Enter your choice: \t";
        cin >> choice;
        switch (choice){
        case 1:
            showfile(6); break;
        case 2:
            acceptrequest(); break;
        case 3:
            showfile(7); break;
        case 4:
            acceptreturn(); break;
        case 5:
            break;
        case 0:
            exit(0);
        default:
            clear(); cout << "\n\n\t\t<!> Wrong Input! Try Again!"; break;
        }
    }while (choice != 5);
    clear();
}
// Librarian accept book borrow request
void acceptrequest(){ clear();
    string bn, uid;
    char value[50], bid[50];
    cout << "\n\n\t\t----------------- ACCEPT / DECLINE BORROW -----------------\n ";
    cin.ignore();
    cout << "\n\n\t\t>> Enter book ID to Accept/Decline borrow: \t";
    cin.getline(value, 50);
    if(check(value, 6)){
        if(!check(value, 7)){
            ifstream open(files[6]);
            ofstream write(files[7], ios::app);
            ofstream neww("temp.txt", ios::app);
            while (open >> bid >> bn >> uid) {
                if (strcasecmp(bid, value) == 0) {
                    string confirm; char y;
                    cout <<"\n\n\t\tUser ID: \t" << uid << endl << "\n\t\tBook ID: \t" << bid << endl << "\n\t\tBook Title: \t" << bn << endl;
                    cout << "\n\t\t<?> Confirm Transaction? \n\t\t1. Accept \n\t\t2. Decline\n\t\t3. Cancel\n\n\t\t>> Enter your choice: \t";
                    cin >> confirm;
                    switch(confirm[0]){
                        case '1':
                            write << setw(10) << left << bid << "\t" << setw(40) << left << bn << "\t" << setw(20) << left << uid << endl;
                            cout << "\n\t\t<> Transfer Successful.\n" << endl;
                            cout << "\n\t\tUser with ID: \t" << uid << " lent The Book: \t" << bn << endl;
                            break;
                        case '2':
                            cout << "\n\t\t<> Request declined Successful.\n" << endl;
                            break;
                        default:
                            neww << setw(10) << left << bid << "\t" << setw(40) << left << bn << "\t" << setw(20) << left << uid << endl;
                            cout << "\n\n\t\t<!> Transfer canceled!\n";
                            break;
                    }
                }else
                    neww << setw(10) << left << bid << "\t" << setw(40) << left << bn << "\t" << setw(20) << left << uid << endl;
            } write.close(); open.close(); neww.close();
            remove(files[6]); rename("temp.txt", files[6]);
        }else
            cout << "\n\n\t\t<!> Book Already lent!\n" << endl;
    }else
        cout << "\n\n\t\t<!> No Request for This Book!\n";
    cont();
}
// Librarian accept book return
void acceptreturn(){
    string bn, uid;
    char value[50], bid[50];
    cout << "\n\n\t\t----------------- ACCEPT BOOK RETURN -----------------\n ";
    cin.ignore();
    cout << "\n\n\t\t>> Enter book ID to accept return: ";
    cin.getline(value, 50);
    if(check(value, 7)){
            ifstream open(files[7]);
            ofstream neww("temp.txt");
            while (open >> bid >> bn >> uid) {
                if (strcasecmp(bid, value) == 0) {
                    string confirm; char y;
                    cout <<"\t\tUser ID: " << uid << endl << "\t\tBook ID: " << bid << endl << "\t\tBook Title: " << bn << endl;
                    cout << "\n\t\tConfirm Book Return? y/n :";
                    cin >> confirm;
                    if (confirm[0] == 'Y' || confirm[0] == 'y')
                        y = 'y';
                    else
                        y = 'n';
                    switch(y){
                        case 'y':
                        case 'Y':
                            cout << "\n\t\t<> Book Return Successful.\n" << endl;
                            cout << "\t\tUser with ID: " << uid << " returned The Book: " << bn << endl;
                            break;
                        default:
                            neww << setw(10) << left << bid << "\t" << setw(40) << left << bn << "\t" << setw(20) << left << uid << endl;
                            cout << "\t\t\n<!> Transfer canceled!\n";
                            break;
                    }
                } else
                    neww << setw(10) << left << bid << "\t" << setw(40) << left << bn << "\t" << setw(20) << left << uid << endl;
            } open.close();
            remove(files[7]); rename("temp.txt", files[7]);
    } else
        cout << "\n\n\t\t<!> Book not Lent!\n";
    cont();
}
// Users List Menu
void userManagement(){ clear();
    int choice;
    do{
        cout << "\n\n\t\t----------------- BOOK MANAGEMENT -----------------\n"; info();
        cout << "\n\n\t\t1. Show Users\n\n\t\t2. Blacklists\n\n\t\t3. Add to Blacklist\n\n\t\t4. Remove from Blacklist\n\n\t\t5. Back\n\n\n\t\t0. Exit\n\n\t\t>> Enter your choice: \t";
        cin >> choice;
        switch (choice){
        case 1:
            showUsers();
            break;
        case 2:
            showUsers(8);
            break;
        case 3:
            addblacklist();
            break;
        case 4:
            removeblacklist();
            break;
        case 5:
            break;
        case 0:
            exit(0);
        default:
            clear();
            cout << "\n\n\t\t<!> Wrong Input! Try Again!";
            break;
        }
    }while (choice != 5);
      clear();
}
// Librarian Add User to Blacklist
void addblacklist(){
    string un, up;
    char value[50], uid[50], reason[100];
    cin.ignore();
    cout << "\n\n\t\t>> Enter User ID to add to blacklist: ";
    cin.getline(value, 50);
    if(check(value, 8)){
            ifstream open(files[8]);
            ofstream neww("temp.txt");
            while (open >> uid >> up >> un) {
                if (strcasecmp(uid, value) == 0) {
                    string confirm; char y;
                    cout <<"\n\t\tUser ID: " << uid << endl << "\n\t\tUser name: " << un << endl;
                    cout << "\n\n\t\t<?> Confirm to add user to blacklist? y/n :";
                    cin >> confirm;
                    if (confirm[0] == 'Y' || confirm[0] == 'y')
                        y = 'y';
                    else
                        y = 'n';
                    switch(y){
                        case 'y':
                        case 'Y':
                            cout << endl << "\n\n\t\t>> Enter Reason: " ;
                            cin.ignore();
                            cin.getline(reason, 100);
                            cout << "\n\n\t\tUser " << uid << "added to blacklist for " << reason << endl;
                            break;
                        default:
                            neww << setw(10) << left << uid << "\t" << setw(20) << left << up << "\t" << setw(20) << left << un << endl;
                            cout << "\n\n\t\t<!> Process canceled!\n";
                            break;
                    }
                }
                else
                    neww << setw(10) << left << uid << "\t" << setw(40) << left << up << "\t" << setw(20) << left << un << endl;
            } open.close(); remove(files[7]);
            rename("temp.txt", files[7]);
    }else
        cout << "\n\n\t\t<!> No user with this ID found!\n";
    cont(1);
}
// Remove User from Blacklist
void removeblacklist(){ clear();
    char uid[50], up[50], un[50], search[50];
    cout << "\n\n\t\t>> Enter the User ID to remove from blacklist: ";
    cin >> search;
    if(check(search, 8)){
        ifstream open(files[8]);
        ofstream write("temp.txt");
        while (open >> uid >> up >> un) {
            if (strcasecmp(uid, search) == 0) {
                string confirm; char y;
                cout << "\n\t\t----------------------------------\n";
                cout << uid << "\t" << replace(un, '_', ' ') << endl;
                cout << "\t\t----------------------------------\n";
                cout << "\n\n\t\t<?> Are you sure? Do you want to remove this user from blacklist(Y/N)? ";
                cin >> confirm;
                if (confirm[0] == 'Y' || confirm[0] == 'y')
                    y = 'y';
                else
                    y = 'n';
                switch(y){
                    case 'y':
                    case 'Y':{
                        cout << "\n\n\t\t<> User " << search <<" successfully removed from blacklist!\n";
                        fstream log; log.open(files[3], ios::out | ios::app);
                        log <<  dt << currentuser.type << " " << currentuser.id << " removed Student " << uid <<" from blacklist.\n";
                        log.close();
                        }break;
                    default:
                        cout << "\n\n\t\t<!> Process canceled!\n";
                        write << setw(10) << left << uid << "\t" << setw(20) << left << up << "\t" << setw(20) << left << un << endl;
                        break;
                }
            }
            else{
                write << setw(10) << left << uid << "\t" << setw(40) << left << up << "\t" << setw(20) << left << un << endl;
            }
        } write.close(); open.close();
        remove(files[8]); rename("temp.txt", files[8]);
    }else
        cout << "\n\n\t\t <!> Sorry, can't find a user with this ID in the blacklist.\n";
    cont();
}
// Total system population data
void inventory(int t = 1){clear();
    cout << "\n\n\t\t----------------- CURRENT INVENTORY AND USER STATUS -----------------\n";
    cout << "\n\t\t    Total Books: " << counter(2);
    cout << "\n\t\t  Total Borrows: " << counter(7);
    cout << "\n\t\t Total Requests: " << counter(6);
    cout << "\n\t\t    Total Users: " << counter(0);
    cout << "\n\t\tBlacklist Users: " << counter(8);
    t == 5? cout << "\n\t\tTotal Librarian: " << counter(1): cout << "";
    cout << endl; cont();
}
int main()
{   dt[strlen(dt) - 1] = ' ';
    firstMenu();
    return 0;
}
