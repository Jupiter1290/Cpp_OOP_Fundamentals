#include<iostream>
#include<vector>
#include<iomanip>
#include<memory>
using namespace std;

enum Type{Gas=0, Diesel, Electric};

int tireLimit=50000;
int oilLimit=5000;
int battLimit=400;
int electricRange=325;

class Vehicle{
    protected:
    string make;
    string model;
    int year;
    int odometer;
    public:
    Vehicle(string mk,string mdl, int yr, int odo):make(mk),model(mdl),year(yr),odometer(odo){};
    virtual ~Vehicle(){};
    virtual Type getType()=0;
    //get and set functrions defined...
    string getMake() const {return make;}
    string getModel() const {return model;}
    int getOdometerReading() const {return odometer;}
    int getYear() const {return year;}
    void setMake(string newMake){make=newMake;}
    void setModel(string newModel){model=newModel;}
    void setOdometerReading(int newOdo){odometer=newOdo;}
    void setYear(int newYr){year=newYr;}
    void getCarInfo(){
        cout<<right<<setw(15)<<"Make: "<<right<<setw(15)<<"Model: "<<right<<setw(15)<<"Year: "<<right<<setw(15)<<"Odometer Reading: "<<endl;
        cout<<"------------------------------------------------------------------------"<<endl;
        cout<<right<<setw(15)<<make<<right<<setw(15)<<model<<right<<setw(15)<<year<<right<<setw(15)<<odometer<<endl;
        cout<<"------------------------------------------------------------------------"<<endl;
    }
    void checkTireRotation() const {
        int cycles=odometer/tireLimit;
        int kmOverLimit=odometer%tireLimit;
        if(cycles>0){
            cout<<"Tire rotation cycle: "<<cycles;
            cout<<(tireLimit-kmOverLimit)<<"km left till next rotation."<<endl;
            if(kmOverLimit==0){
                cout<<"Tire rotation needed..."<<endl;
            }
        }else{
                cout<<(tireLimit-kmOverLimit)<<"km left till first rotation."<<endl;
            }
    }
};

class FuelVehicle: public Vehicle{
    public:
    FuelVehicle(string mk, string mdl, int yr, int odo) : Vehicle(mk, mdl, yr, odo) {};
    void checkOil() const {
        int cycles=odometer/oilLimit;
        int kmOverLimit=odometer%oilLimit;
        if(cycles>1){
            if(kmOverLimit==0){
                cout<<"Oil cycle:"<<cycles<<endl;
                cout<<"Oil Change needed! Changing oil..."<<endl;
            }else{
                cout<<"Oil cycle:"<<cycles<<endl;
                cout<<(oilLimit-kmOverLimit)<<"km left till next oil change."<<endl;
            }
        }else{
            cout<<(oilLimit-kmOverLimit)<<"km left till first oil change."<<endl;
        }
    }
    void checkBatteryPower() const {
        int cycles=odometer/battLimit;
        int kmOverLimit=odometer%battLimit;
        if(cycles>1){
            if(kmOverLimit==0){
                cout<<"Battery cycle:"<<cycles<<endl;
                cout<<"Battery recharge needed! recharging the 12V lead acid battery..."<<endl;
            }else{
                cout<<"Battery cycle:"<<cycles<<endl;
                cout<<(battLimit-kmOverLimit)<<"km left till next battery recharge."<<endl;
            }
        }else{
            cout<<(battLimit-kmOverLimit)<<"km left till first oil change."<<endl;
        }

    }
    virtual string getFuelType()=0;
};

class GasCar: public FuelVehicle{
    public:
    GasCar(string mk, string mdl, int yr, int odo): FuelVehicle(mk, mdl, yr, odo){};
    string getFuelType() override {return "Gas";}
    Type getType() override {return Gas;}
};

class DieselCar: public FuelVehicle{
    public:
    DieselCar(string mk, string mdl, int yr, int odo): FuelVehicle(mk, mdl, yr, odo){};
    string getFuelType() override {return "Diesel";}
    Type getType() override {return Diesel;}
};

class ElectricCar: public Vehicle{
    public:
    ElectricCar(string mk, string mdl, int yr, int odo) : Vehicle(mk, mdl, yr, odo) {};
    Type getType() override {return Electric;}
    void checkChargePower(){
        int kmOverLimit=odometer%electricRange;
        if(kmOverLimit==0){
            cout<<"Range is zero... Charging car!"<<endl;
        }else{
            cout<<(electricRange-kmOverLimit)<<"km left till next charge..."<<endl;
        }
    }

};

vector<shared_ptr<Vehicle>> inventory;

string getNewMake(){
    string make;
    do{
        cout<<"Enter make: "<<endl;
        getline(cin,make);
    }while(make.empty());
    return make;
}

string getNewModel(){
    string model;
    do{
        cout<<"Enter model: "<<endl;
        getline(cin,model);
    }while(model.empty());
    return model;
}

int getYear(){
    string input;
    int yr=-1;
    do{
        cout<<"Enter year: "<<endl;
        getline(cin,input);
        try{
            yr=stoi(input);
        }catch(...){
            cout<<"Invalid entry... Try again"<<endl;
            yr=-1;
        }
    }while(!(yr>999 && yr<10000));
    return yr;
}

int getNewOdometer(){
    string input;
    int odo=-1;
    do{
        cout<<"Enter odometer reading: "<<endl;
        getline(cin,input);
        try{
            odo=stoi(input);
        }catch(...){
            cout<<"Invalid entry... Try again"<<endl;
            odo=-1;
        }
    }while(!(odo>0));
    return odo;
}

Type getNewType(){
    int id_type=-1;
    do{
        cout<<"Enter the type:\n0.Gas\n1.Diesel\n2.Electric"<<endl;
        cin>>id_type; cin.ignore();
    }while(!(id_type>=0 && id_type<=2));
    Type ret=static_cast<Type>(id_type);
    return ret;
}

int selectCar(){
    int idx;
    do{
        cout<<"Enter the index from 0 -> "<<(int(inventory.size())-1)<<endl;
        cin>>idx; cin.ignore();
    }while(!(idx>=0 && idx<int(inventory.size())));
    return idx;
}

void addVehicle(){
    string make = getNewMake();
    string model = getNewModel();
    int year = getYear();
    int odo = getNewOdometer();
    Type type = getNewType();

    if (type == Gas){
        inventory.push_back(make_shared<GasCar>(make, model, year, odo));}
    else if (type == Diesel){
        inventory.push_back(make_shared<DieselCar>(make, model, year, odo));}
    else{
        inventory.push_back(make_shared<ElectricCar>(make, model, year, odo));}
}

void listVehicles(){
    if(inventory.empty()){cout<<"Inventory is empty!"<<endl; return;}
    for(size_t i=0;i<inventory.size();i++){
        cout<<"For vehicle:"<<(int)i<<endl;
        inventory[int(i)]->getCarInfo();
    }
}

void updateVehicle(){
    if(inventory.empty()){cout<<"Inventory is empty!"<<endl; return;}
    int newOdo=getNewOdometer();
    int id=selectCar();
    inventory[id]->setOdometerReading(newOdo);
}

void removeVehicle(){
    if(inventory.empty()){cout<<"Inventory is empty!"<<endl; return;}
    int id=selectCar();
    inventory.erase(inventory.begin()+id);
}

void tireRotation(){
    if(inventory.empty()){cout<<"Inventory is empty!"<<endl; return;}
    int id=selectCar();
    inventory[id]->checkTireRotation();
}

void oilChange(){
    if(inventory.empty()){cout<<"Inventory is empty!"<<endl; return;}
    int id=selectCar();
    FuelVehicle *f_ptr=dynamic_cast<FuelVehicle*>(inventory[id].get());
    if(f_ptr){
        cout<<"initiating oil check..."<<endl;
        f_ptr->checkOil();
    }
}

void recharge(){
    if(inventory.empty()){cout<<"Inventory is empty!"<<endl; return;}
    int id=selectCar();
    ElectricCar *e_ptr=dynamic_cast<ElectricCar*>(inventory[id].get());
    if(e_ptr){
        cout<<"Checking range on battery..."<<endl;
        e_ptr->checkChargePower();
    }else{
        FuelVehicle *f_ptr=dynamic_cast<FuelVehicle*>(inventory[id].get());
        if(f_ptr){
            cout<<"Checking power remaining in the 12V lead acid battery..."<<endl;
            f_ptr->checkBatteryPower();
        }else{
            cout<<"Bad Allocation!"<<endl;
            return;
        }
    }
}

int main(){
    int choice;
    do{
        cout<<"=========Menu========="<<endl;
        cout<<"1.Add Vehicle\n2.List Inventory\n3.Update Vehicle\n4.Remove Vehicle"<<endl;
        cout<<"5.Tire Rotation\n6.Oil Change\n7.Recharge\n0.QUIT"<<endl;
        cout<<"---------------------"<<endl;
        cout<<"Enter Choice: "<<endl;
        cin>>choice; cin.ignore();

        switch (choice) {
            case 1: addVehicle(); break;
            case 2: listVehicles(); break;
            case 3: updateVehicle(); break;
            case 4: removeVehicle(); break;
            case 5: tireRotation(); break;
            case 6: oilChange(); break;
            case 7: recharge(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid input. Try again.\n"; break;
        }
    }while(choice!=0);
    return 0;
}
