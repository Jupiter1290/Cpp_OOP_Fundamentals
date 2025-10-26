#include<iostream>
#include<iomanip>
using namespace std;

template <typename T>
class BillingOp{
    string *nameArr;
    T *priceArr;
    int *qty;
    int n;
    public:
    BillingOp(int n):n(n){
        cout<<"Billing operations performed on data type: "<<typeid(T).name()<<endl;;
        nameArr=new string [n];
        priceArr=new T [n];
        qty=new int [n];
        for(int i=0;i<n;i++){
            cout<<"Enter Product Name: "<<endl;
            cin>>nameArr[i];
            cout<<"Enter Price: "<<endl;
            cin>>priceArr[i];
            cout<<"Enter quantity: "<<endl;
            cin>>qty[i];
        }
        cout<<"Entries Done\n.-------------------------------------------.\n"<<endl;
    }
    ~BillingOp() {
        delete[] nameArr;
        delete[] priceArr;
        delete[] qty;
    }

    T multiply(T a,int b){
        return (a*b);
    }
    T add(T a, T b){
        return (a+b);
    }

    void generateInvoice(){
        T temp=0,result=0;
         cout<<right<<setw(15)<<"Commodity"<<right<<setw(15)<<"Price per unit"<<right<<setw(15)<<"Total Price:"<<endl;
        for(int i=0;i<n;i++){      
            result=multiply(priceArr[i],qty[i]);
            cout<<right<<setw(15)<<nameArr[i]<<right<<setw(15)<<priceArr[i]<<right<<setw(15)<<result<<endl;
            temp=add(temp,result);
        }
        cout<<"-----------------------------------------------------------------------------------"<<endl;
        cout<<"Total Price: "<<temp;
    }

}; 

int main(){
    int n,choice;
    cout<<"Enter the number of commodities to be billed: "<<endl;
    cin>>n;
    cout<<"Enter the data type\n1.Integer\n2.Floating Point\n3.Double Precision\n.--------------------------------------------------."<<endl;
    cout<<"Selection: \n"<<endl;
    cin>>choice;

    switch(choice){
        case 1:{
        BillingOp<int>*ptr=new BillingOp<int>(n);
        ptr->generateInvoice();
        delete ptr;
        break;}
        case 2:{
        BillingOp<float>*ptr=new BillingOp<float>(n);
        ptr->generateInvoice();
        delete ptr;
        break;}
        case 3:{
        BillingOp<double>*ptr=new BillingOp<double>(n);
        ptr->generateInvoice();
        delete ptr;
        break;}
        default:{
        cout<<"Invalid Entry..."<<endl;
        break;}
    }

    return 0;
}