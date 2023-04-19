#include <iostream>
#include <ctime>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

bool check_len( string n ) {  // param 10
	if(n.length() > 10 || n.length() < 10) return false;
	return true;
}

vector<string> Split(string Data, string Delimiter=" ") {
    //cout<<"\nSplitting string: >"<<Data<<"< by delimiter >"<<Delimiter<<"<\n";
    vector<string> result;
    string CurrSubs;
    auto start = 0U;
    auto end = Data.find(Delimiter);
    while (end != string::npos) {
        CurrSubs = Data.substr(start, end - start);
        //cout<<CurrSubs<<endl;
        result.push_back(CurrSubs);
        start = end + Delimiter.length();
        end = Data.find(Delimiter, start);
        }
    CurrSubs = Data.substr(start, end - start);
    //cout<<CurrSubs<<endl;
    //cout << Data.substr(start, end);
    result.push_back(CurrSubs);
    return result;
    }


class Phonebook {
	protected:
		string Name;
		string PhoneNumber;
	public:
		string getPhoneNumber() {
			return PhoneNumber;
		}
		
		map<string, string> Contact; // make protected
		Phonebook(string name, string number) { 
			Name = name;
			PhoneNumber = number;
		}
		
		Phonebook() {	}
		
		void Add(string name, string number) { // may be bool
			Name = name;
			PhoneNumber = number;
			if(check_len(PhoneNumber)) Contact.insert(pair<string, string>(Name, "+7" + PhoneNumber) ); 
		}
		
		void print() {
			for( auto it = Contact.begin(); it != Contact.end(); it++) {
				cout << it->first << " " << it->second << "\n";
			}
		}
		
		string FindByName(string name) {
			string id;
				auto i = Contact.find(name);
				if( i->first == name) {
					id = i->second;
				} else return " No number!";
			return id;
		}

		string FindByNumber(string number) {
			string id;
			for( auto it = Contact.begin(); it != Contact.end(); it++ ) {
				if( "+7" + number == Contact[it->first]) {
					id = Contact[it->first];
				}
			}

		return id;	
	}
	
	bool true_name(string name) {
			auto i = Contact.find( name );
			if( i->first == name) return true;
		return 0;
	}
	
	bool true_number(string number) {
		for(auto a = Contact.begin(); a != Contact.end(); a++ ){
			if( "+7" + number == Contact[a->first] ){
				return true;
			} 
		}
		return 0;
	}
		
};




class MobilePhone :public Phonebook{
	protected:
		Phonebook *PB;
	public:
		MobilePhone(Phonebook *pb) { 
			PB = pb;		
		}
		
	string Call( string NameOrNumber ) { 
		string caller;
		if( true_name( NameOrNumber ) ){
			caller = FindByName( NameOrNumber );
		}
		else caller = FindByNumber( NameOrNumber ); 
		return "Calling... " + caller + "\n\n";
	}
	
	
	string sms(string NameOrNumber) { // if sms length > 20 than create new sms
		string smser = "Sending message... ", sms;
		if( true_name( NameOrNumber ) ){
			smser = FindByName( NameOrNumber );
			cout << "Your sms will be sent to: " + smser + "\nEnter your text: ";
			cin.ignore();
			getline(cin, sms);
			if(sms == "exit"){
				Exit();
			} 
		}
		else if( true_number( NameOrNumber ) ){
			smser = FindByNumber( NameOrNumber );
			cout << "Your sms will be sent to: " + smser + "\nEnter your text: ";
			cin.ignore();
			getline(cin, sms);
		}
		else smser = "oops!";
		return smser + " " + sms + "\n\n";
	}
	
	int Exit() {
		cout << "TADADA...\n";	
		return 2;
//		exit( 0 );
	}	
	

	bool dialer() { 
		string Input, Name, Number, NameOrNumber; 
		string Commands[5] = { "add", "sms", "call", "print", "exit" };
		
		cout << "your option: \nadd - to add Name and phone number\n" \
		"call - enter name and/or number to call\n" \
		"sms - enter name and/or number to sms\n" \
		"exit - to exit programm\n" \
		"print - to show phonebook\n"; 
		cin >> Input;
		if(Input == Commands[0]) {
			cout << "Enter name\n";
			cin >> Name;
			cout << "Enter number\n";
			cin >> Number;
			Add( Name, Number );
			return true;
		}
		else if( Input == Commands[1]) {
			cout << "Enter name or number\n";
			cin >> NameOrNumber;
			cout << sms( NameOrNumber );
			return true;
		}
		else if(Input == Commands[2]) {
			cout << "Enter name or number\n";
			cin >> NameOrNumber;
			cout << Call( NameOrNumber );
			return true;
		}
		else if( Input == Commands[3] ){
			print();
			return true;
		}
		else if( Input == Commands[4]) {
			Exit();
			return false;
		};
		return true;
	}
		
};


int main() {
	Phonebook *p = new Phonebook();

	MobilePhone *mp = new MobilePhone(p);
	mp->Add("Alex", "9055573444");

	do {
		if( !mp->dialer() ) break;
	}while( mp->dialer());
	
	delete p; delete mp;
}
