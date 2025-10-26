#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

const int deptNumber=3;
const int venNumber=2;

int main(){
    int n,choice;
    cout<<"Enter the number of commodities: "<<endl;
    cin>>n;
    cin.ignore(1,'\n');
    double temp;
    const char* depNames[deptNumber]={"ADAC","Electro","Connexion"};
    char **commodityNames=new char*[n];
    for(int i=0;i<n;i++){
        *(commodityNames+i)=new char[50];
    }
    int **quantities=new int*[deptNumber];
    for(int i=0;i<deptNumber;i++){
        *(quantities+i)=new int[n];
    }
    double **venPrices=new double*[venNumber];
    for(int i=0;i<venNumber;i++){
        *(venPrices+i)=new double[n];
    }
    double deptwise_venTotal[deptNumber][venNumber];
    double venTotal[venNumber];

    ofstream outfile("purchaseData.txt",ios::out);
    if(!outfile){
        cout<<"Error opening file..."<<endl;
        return 1;
    }

    while(true){
        cout<<"===Menu===\n"<<endl;
        cout << "1. Enter Commodities to be Purchased"<<endl;
        cout << "2. Enter Vendor Quotations"<<endl;
        cout << "3. Exit\n"<<endl;
        cout<<"Enter choice: "<<endl;
        cin>>choice;
        cin.ignore(1,'\n');
        switch(choice){
            case 1:
            for(int i=0;i<n;i++){
                cout<<"********"<<endl;
                cout<<"Enter name of commodity number "<<i+1<<": "<<endl;
                cin.getline(*(commodityNames+i),50);
                cout<<"********"<<endl;
            }
            for(int i=0;i<deptNumber;i++){
                cout<<"Enter the quantities for "<<*(depNames+i)<<endl;
                for(int j=0;j<n;j++){
                    cout<<"Number of "<<*(commodityNames+j)<<" needed: "<<endl;
                    cin>>*(*(quantities+i)+j);
                    cout<<"-----"<<endl;
                }
            }
            break;
            case 2:
            for(int i=0;i<venNumber;i++){
                cout<<"Enter quotation by Vendor "<<i+1<<": "<<endl;
                for(int j=0;j<n;j++){
                    cout<<"Price of "<<*(commodityNames+j)<<": "<<endl;
                    cin>>*(*(venPrices+i)+j);
                    cout<<"-----"<<endl;
                }
            }
            cout<<"Calculating prices and finding the best options: "<<endl;
            for(int i=0;i<deptNumber;i++){
                for(int j=0;j<venNumber;j++){
                    temp=0;
                    cout<<"For "<<*(depNames+i)<<" according to vendor "<<j+1<<" quotations: "<<endl;
                    for(int k=0;k<n;k++){
                        temp+=(quantities[i][k])*(venPrices[j][k]);
                    }
                    cout<<temp<<endl;
                    deptwise_venTotal[i][j]=temp;
                    
                }
            }
            for(int t=0;t<venNumber;t++){
                temp=0;
                for(int s=0;s<deptNumber;s++){
                    temp+=deptwise_venTotal[s][t];
                }
                venTotal[t]=temp;
            }
            cout<<"Writing report..."<<endl;
            outfile <<left<<setw(20)<<"Department Name:"<<flush;
            for(int i=0;i<venNumber;i++){
                outfile<<right<<setw(20)<<"Vendor "+to_string(i+1)<<flush;
            }
            outfile<<endl;
            outfile<<string(20+20*venNumber,'=')<<endl;
            for(int i=0;i<deptNumber;i++){
                outfile<<left<<setw(20)<<*(depNames+i)<<"\t"<<flush;
                for(int j=0;j<venNumber;j++){
                    outfile<<right<<setw(20)<<fixed<<setprecision(2)<<deptwise_venTotal[i][j]<<flush;
                }
                outfile<<endl;
            }
            outfile<<"=========================="<<endl;

            outfile<<"Total cost according to:"<<endl;
            outfile<<"Vendor1: "<<venTotal[0]<<endl;
            outfile<<"Vendor2: "<<venTotal[1]<<endl;

            if(venTotal[0]==venTotal[1]){
                outfile<<"Both are equally good choices..."<<endl;
                cout<<"Both are equally good choices..."<<endl;
            }else{
            outfile<<((venTotal[0]>venTotal[1])?"Vendor 2 is a better choice...":"Vendor 1 is a better choice...");
            outfile<<flush;
            cout<<((venTotal[0]>venTotal[1])?"Vendor 2 is a better choice...":"Vendor 1 is a better choice...");
            cout<<flush;
            }
            break;

            
            case 3:
            cout<<"Exiting... Saving report and cleaning allocated memory..."<<endl;
            outfile.close();

            for(int i=0;i<n;i++){
                delete [] *(commodityNames+i);
            }
            delete [] commodityNames;

            for(int i=0;i<deptNumber;i++){
                delete [] *(quantities+i);
            }
            delete [] quantities;

            for(int i=0;i<venNumber;i++){
                delete [] *(venPrices+i);
            }
            delete [] venPrices;
            break;
            
            
            default:
            cout<<"Invalid entry: "<<endl;
            outfile.close();

            for(int i=0;i<n;i++){
                delete [] *(commodityNames+i);
            }
            delete [] commodityNames;

            for(int i=0;i<deptNumber;i++){
                delete [] *(quantities+i);
            }
            delete [] quantities;

            for(int i=0;i<venNumber;i++){
                delete [] *(venPrices+i);
            }
            delete [] venPrices;
            break;

        }
        if(choice==3){break;}
    }
    
}