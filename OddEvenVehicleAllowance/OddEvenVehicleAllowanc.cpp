#include<iostream>
#include<iomanip>
#include<vector>
#include<memory>
using namespace std;

class Vehicle{
    protected:
    int vId;
    public:
    Vehicle(int vId):vId(vId){};
    virtual bool isAllowed(int day)=0;
    virtual ~Vehicle()=default;
};

class fourWheeler: public Vehicle{
    public:
    static int count_4Wheeler_odd;
    static int count_4Wheeler_even;
    fourWheeler(int vId):Vehicle(vId){};
    bool isAllowed(int day) override {
        if(day%2==0&&vId%2==0){
            count_4Wheeler_even++;
            return true;
        }else if(day%2!=0&&vId%2!=0){
            count_4Wheeler_odd++;
            return true;
        }
        return false;
    }
};
int fourWheeler::count_4Wheeler_odd=0;
int fourWheeler::count_4Wheeler_even=0;

class twoWheeler: public Vehicle{
    public:
    static int count_2Wheeler_odd;
    static int count_2Wheeler_even;
    twoWheeler(int vId):Vehicle(vId){};
    bool isAllowed(int day) override {
        if(day%2==0&&vId%2==0){
            count_2Wheeler_even++;
            return true;
        }else if(day%2!=0&&vId%2!=0){
            count_2Wheeler_odd++;
            return true;
        }
        return false;
    }
};
int twoWheeler::count_2Wheeler_odd=0;
int twoWheeler::count_2Wheeler_even=0;
int evenDayCount=0;
int oddDayCount=0;

int countVehicles(int day,const vector<unique_ptr<Vehicle>> &vehicles){
    int count=0;
    for(const unique_ptr<Vehicle> &v : vehicles){
        if(v->isAllowed(day)){
            count++;
        }
    }
    return count;
}

void displayReport(){
    cout<<"=====Report====="<<endl;
    cout<<"Even day count: "<<evenDayCount<<endl;
    cout<<"Odd day count: "<<oddDayCount<<endl;
    cout<<"Total number of 2 wheelers on even days: "<<twoWheeler::count_2Wheeler_even<<endl;
    cout<<"Total number of 2 wheelers on odd days: "<<twoWheeler::count_2Wheeler_odd<<endl;
    cout<<"Total number of 4 wheelers on even days: "<<fourWheeler::count_4Wheeler_even<<endl;
    cout<<"Total number of 4 wheelers on odd days: "<<fourWheeler::count_4Wheeler_odd<<endl;
    
};



int main(){
    cout<<"Enter the number of days: "<<endl;
    int totalDays;
    cin>>totalDays;
    int type,n,vId,temp;
    
    for(int day=1;day<=totalDays;day++){
        vector<unique_ptr<Vehicle>> vehicles;
        cout<<"Entry for day: "<<day<<endl;
        cout<<"--------------------------------"<<endl;
        cout<<"Enter the number of vehicles: "<<endl;
        cin>>n;
        for(int i=0;i<n;i++){
            cout<<"Enter the type of vehicle:\n1.Two Wheeler\n2.Four Wheeler "<<endl;
            cin>>type;
            switch(type){
                case 1:{
                    cout<<"Enter the registered id of the two wheeler: "<<endl;
                    cin>>vId;
                    vehicles.push_back(make_unique<twoWheeler>(vId));
                    break;
                }
                case 2:{
                    cout<<"Enter the registered id of the four wheeler: "<<endl;
                    cin>>vId;
                    vehicles.push_back(make_unique<fourWheeler>(vId));
                    break;
                }
                default:{
                    cout<<"Invalid entry:"<<endl;
                    break;
                }
            }
        }
        if(day%2==0){
            evenDayCount+=countVehicles(day,vehicles);
        }else{
            oddDayCount+=countVehicles(day,vehicles);
        }
  
    }
    displayReport();
    return 0;
    
}
