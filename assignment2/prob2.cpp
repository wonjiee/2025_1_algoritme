#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

class Contact{
public:
    string name;
    string company;
    string address;
    string zipcode;
    string phone;
    string mail;

    void contactPrint(){
        cout<<name<<endl;
        cout<<"    Company: "<<company<<endl;
        cout<<"    Address: "<<address<<endl;
        cout<<"    Zipcode: "<<zipcode<<endl;
        cout<<"    Phones: "<<phone<<endl;
        cout<<"    Email: "<<mail<<endl;
    }
};

Contact substringContact(string line);

class AddressBook{
private:
    vector<Contact>contacts;
public:
    void readAddress(string name){
        ifstream infile(name);
        string line;
        while(getline(infile,line)){
            Contact tmp= substringContact(line);
            contacts.push_back(tmp);
        }
    }

    void printAll(){
        for(int i=0;i<contacts.size();i++){
            contacts[i].contactPrint();
        }
    }

    void addressBookSort(string type){
        if(type=="-name"){
            sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
                return a.name < b.name;
            });
        }
        else if(type=="-address"){
            sort(contacts.begin(), contacts.end(), [](const Contact& a, const Contact& b) {
                return a.address < b.address;
            });
        }
    }

};

Contact substringContact(string line){
    stringstream ss(line);
    string token;
    vector<string>fields;

    Contact user;

    while(getline(ss,token,'|')){
        fields.push_back(token);
    }

    user.name=fields[0];
    user.company=fields[1];
    user.address=fields[2];
    user.zipcode=fields[3];
    user.phone=fields[4];
    user.mail=fields[5];

    return user;
}


void startSystem(AddressBook &ab){
    string command=" ";
    while(command!="exit"){
        cout<<"$ ";
        cin>>command;
        if(command=="read") {
            string name;
            cin >> name;
            ab.readAddress(name);
        }
        else if(command=="sort"){
            string type;
            cin>>type;
            ab.addressBookSort(type);

        }
        else if(command=="print"){
            ab.printAll();
        }
    }

}


int main(){
    AddressBook ab;
    startSystem(ab);

    return 0;
}