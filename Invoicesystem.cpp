#include<iostream>
#include<iomanip>
#include<fstream>
#include<ctime>
#include<string>
using namespace std;
void generateinvoices();
void mainmenu();
class Customer{
     private:
     string name;
     string contact;
     public:
     void setcustomername(string name, string contact){
        this->name=name;
        this->contact=contact;
     }
     string getname(){
        return name;
     }
     string getcontact(){
        return contact;
     }
};
class products{
    /*
    products is an abstract class which provides blueprint for class 
    Electronic and class Clothing
    Functions: void indsaveproduct, double addproduct
    */
    protected:
    string nop;//nameoftheproduct
    double price;
    int quantity;
    public:
    products(string nop,double price,double quantity){
        this->nop=nop;
        this->price=price;
        this->quantity=quantity;
    } 
    virtual void indsaveproduct() {}
    virtual ~products(){}
    virtual double addproduct(){}
    
};

class Electronics: public products{
    /*
    Electronics is a derived class while base class is products.
    Function: void indsaveproduct(), double addproduct()
    */
    private:
    double w_period;//warrantyperiod
    public:
    Electronics(string nop,double price, int quantity,double w_period): products(nop,price,quantity){
           this->w_period=w_period;
     }
     void indsaveproduct(){
        ofstream o("InvoiceHistory.txt", ios::app);
        if(!o){
            cout<<"Couldnot Read the File."<<endl;
            return;
        }
        o << left << setw(31) << nop << "| " << setw(12) << price << "| " << setw(10) << quantity << "| " << setw(14) << w_period << " year(s) " << "    |\n";
        o.close();
     }
     double addproduct(){
        return price*quantity;
     }
};
class Clothing: public products{
    /*
    Clothing is a derived class while base class is products.
    Function: void indsaveproduct(), double addproduct()
    */
      private:
        string size;
    public:
    Clothing(string nop, double price, int quantity, string size): products(nop,price,quantity){
        this->size=size;
    }
    void indsaveproduct(){
        ofstream o("InvoiceHistory.txt", ios::app);
        if(!o){
            cout<<"Couldnot Read the File."<<endl;
            return;
        }
        o << left << setw(31) << nop << "| " << setw(12) << price << "| " << setw(10) << quantity << "| " <<setw(21) << "Size: "<< size << "   |\n";
        o.close();
     }
    double addproduct(){
        return price*quantity;
     }
};

void invoicehistory(){
    /*
    Reads all the invoices present in the file named "InvoiceHistory.txt"
    */
    char choi;
    string file;
    ifstream read;
    read.open("InvoiceHistory.txt");
    if (!read){
        cout<<"Error opening the file for reading. "<<endl;
        return;
    }
    cout<<"\n\n";
    cout << "====================================== Invoice History =======================================\n";
    while(getline(read,file)){
           cout<<file<<"\n";
    }
    cout << "===============================================================================================\n";
    read.close();
    cout<<"Go to main menu: ";
    cin>>choi;
    if(choi=='y'||choi=='Y'){
        mainmenu();
    }
    else{
        exit(0);
    }
}
void generateinvoices(){
    /*
    Takes the customer credentials and creates objects along with 
    invoice calculation
    */
    time_t now=time(0);
    tm *ltm=localtime(&now);
    double sum=0;
    Customer cu;
    char opt;
    char more;
    //double total=0;
    string name;
    string contact;
    cin.ignore();
    cout<<"  Name of the customer: ";
    getline(cin,name);
    cout<<"  Contact Number: ";
   getline(cin,contact);
   
    cu.setcustomername(name,contact);
    ofstream c("InvoiceHistory.txt",ios::app);
    if(!c){
        cout<<"||"<<setw(75)<<"Couldnot Read the File."<<setw(45)<<endl;
        return;
    }
    c<<"DATE: "<<__DATE__<<"\t TIME: "<<setw(2) << setfill('0') << ltm->tm_hour << ":" 
                     << setw(2) << setfill('0') << ltm->tm_min << ":" 
                     << setw(2) << setfill('0') << ltm->tm_sec<<endl; 
                     
    c<<"Name of the Customer: "<<cu.getname()<<endl;
    c<<"Contact: "<<cu.getcontact()<<endl;   
    c<<"----------------------------------------------------------------------------------------------"<<endl;  
    c << "| Product Name                  | Price (each) | Quantity | Additional Information    |\n";
    c<<"----------------------------------------------------------------------------------------------"<<endl;
    c.close(); 
    cout<<"=========================================================INVOICE========================================================="<<endl; 
    char addMore;    
    do{
        string pname;
        char category;
        double price;
        int quantity;
        double ind_price;
        cout<<setw(80)<<"CATEGORY(e for Electronics, c for Clothing): ";
        cin>>category;
        cin.ignore();
        cout<<setw(60)<<"PRODUCT NAME: ";
        getline(cin,pname);
        cout<<setw(65)<<"INDIVIDUAL PRICE: ";
        cin>>price;
        cout<<setw(65)<<"QUANTITY: ";
        cin>>quantity;
        cin.ignore();

        if(category=='e'||category=='E'){
            double warranty;
            cout<<setw(80)<<"Enter the warranty period (in years): ";
            cin>>warranty;
            cin.ignore();
            Electronics elec(pname,price,quantity,warranty);
            elec.indsaveproduct();
            ind_price=elec.addproduct();
            sum=sum+ind_price;

         }
         else if(category=='c'||category=='C') {
            string size;
            cout<<setw(65)<<"Enter size: ";
            getline(cin,size);
            Clothing cloth(pname,price,quantity,size);
            cloth.indsaveproduct();
            ind_price=cloth.addproduct();
            sum=sum+ind_price;
            }
         else{
            cout<<"||"<<setw(60)<<"THERE IS NO SUCH CATERGORY."<<setw(60)<<"||"<<endl;
            
        }
    cout<<setw(80)<<"Do you want to add more products?(y/n): ";
    cin>>addMore;
    cin.ignore();
    }while(addMore=='y' || addMore == 'Y');
    cout<<setw(68)<<"The Grand Total is "<<sum<<endl;
    cout<<setw(75)<<"Invoice Saved Successfully!"<<endl;
    cout<<"..______________________________________________________________________________________________________________________.."<<endl;
    ofstream t("InvoiceHistory.txt",ios::app);
    if(!t){
        cout<<"Error Opening the File."<<endl;
        return;
    }
    t<<"Grand Total:\t\t\t\t\t    "<<sum<<endl;
    t<<"----------------------------------------------------------------------------------------------\n\n"<<endl;
    t.close();
}
void mainmenu(){//forconsoleview
    int option;
    //Customer customer;
    do{
    cout<<"..______________________________________________________________________________________________________________________.."<<endl;
    cout<<"||\t\t\t\t\tWelcome to Professional Invoice Software\t\t\t\t\t||"<<endl;
    cout<<"||\t\t\t\t\t\tDesigned By Rizan K.C.\t\t\t\t\t\t\t||"<<endl;
    cout<<"||\t\t\t\t\t      Date Accessed: "<<__DATE__<<"      \t\t\t\t\t\t||"<<endl;
    cout<<"||\t\t\t\t\t      Session Started:"<<__TIME__<<"      \t\t\t\t\t\t||"<<endl;
    cout<<"||                                                   \t\t\t\t\t\t\t\t\t||"<<endl;
    cout<<"||\t\t\t\t\t     The software is ready to use.\t\t\t\t\t\t||"<<endl;
    cout<<"**\t\t\t\t\t      What would you like to do?    \t\t\t\t\t\t**"<<endl;
    cout<<"**\t\t\t\t\t     Enter 1 for Invoice Generation    \t\t\t\t\t\t**"<<endl;
    cout<<"**\t\t\t\t\t     Enter 2 for Invoice History       \t\t\t\t\t\t**"<<endl;
    cout<<"**\t\t\t\t\t     Enter 3 to end this session    \t\t\t\t\t\t**"<<endl;
    cout<<"\t\t\t\t   Based on your preference, Enter your option: ";
    cin>>option;
    switch(option){
            case 1:
            cout<<"||"<<setw(63)<<"New Invoices"<<setw(57)<<"||"<<endl;
            generateinvoices();
            break;
            case 2:
            invoicehistory();
            break;
            case 3:{
                time_t now=time(0);
                tm *ltm=localtime(&now);
                cout << "||\t\t\t\t\t      Session Ended: " << setw(2) << setfill('0') << ltm->tm_hour << ":" 
                     << setw(2) << setfill('0') << ltm->tm_min << ":" 
                     << setw(2) << setfill('0') << ltm->tm_sec 
                     << "      \t\t\t\t\t\t||" << endl;
            //cout<<"||\t\t\t\t\t      Session Ended: "<<__TIME__<<"      \t\t\t\t\t\t||"<<endl;
            cout<<"..______________________________________________________________________________________________________________________.."<<endl;
            exit(0);
            }
            default:
            cout<<"||"<<setw(67)<<"Oops! Invalid Choice."<<setw(53)<<"||"<<endl; 
            break;
        }
    }while(option!=3);
}
void openapp(){//forconsoleview
    int uid;
    string password;
    homepage:
     cout<<"..______________________________________________________________________________________________________________________.."<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(70)<<"Welcome to Login Portal"<<setw(50)<<"||"<<endl;
     cout<<setw(62)<<"User ID: ";
     cin>>uid;
     if(cin.fail()){
        return;
     }
     cin.ignore();
     cout<<setw(60)<<"Password: ";
     getline(cin,password);
     if((uid==11210 && password=="drowssap")){
     cout<<"||"<<setw(75)<<"You have successfully logged in!"<<setw(45)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"||"<<setw(120)<<"||"<<endl;
     cout<<"..______________________________________________________________________________________________________________________.."<<endl;
     cout<<"\n\n\n";
     mainmenu();
     }
     else{
        cout<<"||"<<setw(67)<<"Oops! Login Failed!"<<setw(53)<<"||"<<endl;
        cout<<"||"<<setw(120)<<"||"<<endl;
        cout<<"||"<<setw(120)<<"||"<<endl;
        cout<<"||"<<setw(120)<<"||"<<endl;
        cout<<"||"<<setw(120)<<"||"<<endl;
        cout<<"||"<<setw(120)<<"||"<<endl;
        cout<<"||"<<setw(120)<<"||"<<endl;
        cout<<"..______________________________________________________________________________________________________________________.."<<endl;
        cout<<"\n\n\n";
        goto homepage;
     }     
}
int main(){
   openapp();//provides a login platform
   return 0;
}