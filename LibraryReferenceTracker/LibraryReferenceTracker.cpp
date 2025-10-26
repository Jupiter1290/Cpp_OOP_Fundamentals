#include<iostream>
#include<vector>
#include<string>
#include<memory>
#include<limits>
#include<iomanip>
using namespace std;

class Book{
    public:
    string title;
    string dept;
    int refCount;
    Book(string title,string dept):title(title),dept(dept),refCount(0){};
};

void referBook(vector<unique_ptr<Book>>& books,const string title){
    for(unique_ptr<Book> &b:books){
        if(b->title==title){
            b->refCount++;
            cout<<"Book title: '"<<title<<"' referred..."<<endl;
            return;
        }
    }
    cout<<"Book not found..."<<endl;
    return;
}

void displayMinRefBook(const vector<unique_ptr<Book>>& books){
    int minReference=numeric_limits<int>::max();
    for(const unique_ptr<Book> &b:books){
        minReference=min(minReference,b->refCount);
    }
    cout<<"Least referenced book(s):\n----------------------------------\n "<<endl;
    for(const unique_ptr<Book> &b:books){
        if(b->refCount==minReference){
            cout<<right<<setw(25)<<"bookTitle:"<<right<<setw(25)<<"department: "<<right<<setw(25)<<"referenceCount: "<<endl;
            cout<<"============================================================"<<endl;
            cout<<right<<setw(25)<<b->title<<right<<setw(25)<<b->dept<<right<<setw(25)<<b->refCount<<endl;
        }
    }
}

void display(const vector<unique_ptr<Book>> &books){
    cout<<"Displaying all books..."<<endl;
    cout<<right<<setw(25)<<"bookTitle:"<<right<<setw(25)<<"department: "<<right<<setw(25)<<"referenceCount: "<<endl;
    cout<<"============================================================"<<endl;

    for(const unique_ptr<Book> &b:books){
        cout<<right<<setw(25)<<b->title<<right<<setw(25)<<b->dept<<right<<setw(25)<<b->refCount<<endl;
    }
    cout<<"_________________________________________________________________________"<<endl;
}

int main(){
    int n;
    vector<unique_ptr<Book>> books;
    cout<<"Enter number of books: "<<endl;
    cin>>n;
    cin.ignore();

    for(int i=1;i<=n;i++){
        string title,dept;
        cout<<"Entry for Book Number:"<<i<<endl;
        cout<<"-----------------------------------"<<endl;
        cout<<"Enter Title: "<<endl;
        getline(cin,title);
        cout<<"Enter Department: "<<endl;
        getline(cin,dept);
        cout<<"----------------------------"<<endl;
        books.push_back(make_unique<Book>(title,dept));
    }

    int choice;
    bool loopSwitch=true;
    do{
        cout<<"Menu/n*************"<<endl;
        cout << "1. Refer a Book"<<endl;
        cout << "2. Display All Books"<<endl;
        cout << "3. Display Least Referred Books"<<endl;
        cout << "0. Exit"<<endl;
        cout << "Enter choice: ";
        cin>>choice;
        cin.ignore();
        switch(choice){
            case 1:{
                string title2ref;
                cout<<"Enter Title to Refer: "<<endl;
                getline(cin,title2ref);
                referBook(books,title2ref);
                break;
            }
            case 2:{
                display(books);
                break;
            }
            case 3:{
                displayMinRefBook(books);
                break;
            }
            case 0:{
                cout<<"Exiting application\n+++++++++++++++++++++++++++"<<endl;
                loopSwitch=false;
                break;
            }
        }
    }while(loopSwitch);

    return 0;
}