#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
using namespace std;



class Track {
	protected:
		string *TrackName;
		tm *Date;
		tm *Len;
		int Size = 32, TracksCount;
	public:
		string GetName( int num ) { 
			string name;
			for(int i = 0; i < num; i++ ) {
				name = TrackName[i];
			}
			return name;	
		 }
		tm GetDate() { return *Date; }
		tm GetLen() { return *Len; }
		GetTracks() { return TracksCount; }
		int TrackNumber;
		Track() { }
		Track( string *TName, tm *date, tm *len) { 
			TrackName = TName;
			Date = date;
			Len = len;
		}
		
		
		~Track() {
			"Track d-tor...\n";
//			delete TrackName;
//			delete Date;
//			delete Len;
		}
		
		void PrintInfo( string TName ) {
			cout << "PrintInfo\n";
//			for(int i = 1 ; i < 6; i++) cout << &TrackName << " ";
			cout << "Printing...\n" << "TrackName is " << TName << "\n";
			if ( Date->tm_mday > 31) Date->tm_mday = 0;
//			int size = sizeof( TrackName[Size] ) / sizeof( TrackName[0] );
//			cout << size;

			for( int i = 0; i < TracksCount; i++ ) {
//				cout << "TrackName[i]: " << TrackName[i] << " Tname: " << TName << "\n";
//				cout << Date[i].tm_year << "\n"
				if( *(TrackName + i) == TName ) {
					cout << "Track name: " << TrackName[i] << endl;
					cout <<"Date: " << Date[i].tm_year << "/" << Date[i].tm_mon << "/" << Date[i].tm_mday << endl;
					cout << "Track length: " << Len[i].tm_sec << endl; 
				}
				
			}
			
		}
		
		void ReadInfo( string path ) {
			TrackName = new string[Size];
			Date = new tm[Size];
			Len = new tm[Size];
			
			cout << "ReadINfo here...\n";
			fstream Text( path );
			string line, Word, name[Size], y[Size], m[Size], d[Size], len[Size];
			int words = 0, names = 0, years = 0, months = 0, days = 0, length = 0;
			stringstream SS(path);
			
			if( Text.is_open() ) {
				stringstream Txt;
				while( getline( Text, line )) {
//					cout << line <<"\n";	
					SS << line;
				}
				while( SS >> Word ) {
//					cout << Word << "\n";
//						
					if( Word == "Name:" )  { // fix names can be longer and with indents
						SS >> name[words];
//						cout << name[words] << ' ';
						TrackName[names] = name[words];
						names++;
						TracksCount = names;
					}
					else if( Word == "Year:") {
						SS >> y[words];	
						Date[years].tm_year = stoi( y[words] );
//						cout <<Date[years].tm_year << " ";
						years++;
					}
					else if( Word == "Month:"){
						SS >> m[words];
						Date[months].tm_mon = stoi( m[words] );
//						cout << stoi( m[words] ) << ' ';
						months++;
					} 
					else if( Word == "Day:"){
						SS >> d[words];
						Date[days].tm_mday = stoi( d[words] );
//						cout << stoi( d[words] ) << ' ';
						days++;
					} 
					else if( Word == "Length:"){
						SS >> len[words];
						Len[length].tm_sec = stoi( len[words] );
//						cout << stoi( len[words] ) << ' ';
						length++;
					} 
					else words++;
				}
				
//				cout << "\n!!!TrackName[i]: " << TrackName[6] <<"\n";
//				cout << name[0] << " " << stoi( y[0] ) << " " << stoi( m[0] ) << "\n";
				
//				Date->tm_year = stoi( y[0] );
//				Date->tm_mon = stoi(m[0]);
//				Date->tm_mday = stoi( d[0] );
//
//				Len[0].tm_sec = stoi( len[0] );
//
//				TrackName[0] = name[0];
//				cout << TrackName[0];
//				cout <<"Size is " <<  TrackName->size();

			}
			else cout << "no such file or directory!\n";
			Text.close();
		}
		
};


class Player : public Track {
	protected:
		bool Playing, Paused, Next, Stopped = 0;
	public:
		Track *T = new Track();
		Player() { }
		Player( Track TrackList, string Path ) { cout << "Player c-tor here...\n"; T->ReadInfo(Path); }
		string t_name;
		
		
		void play( string TName = "" ) {
			if( Playing ) return;
			cout << "Playin...\n";
			cout << TName << "\n";
			T->PrintInfo( TName );
			Playing = true;
			if( Next ){
				T->PrintInfo(t_name);
				Playing = true;
			} 
		}
		
		void pause() {
			if( !Paused && Playing && Next ){
				cout << "Pause\n";
				Paused = true;
			} 
			else if( !Playing ) cout << "Not playing\n";// && Paused || !Playing && // || !Paused
			else if( Paused ) cout << "Already paused\n";
		}
		
		void next() {
			cout << "Next---->\n";
			int R = rand() % T->GetTracks();
//			cout << "Stopp= " << Stopped << "\n";
			if( !Playing  ) { // && !Stopped
				t_name = T->GetName(R);
				cout << T->GetName(R) << endl;
				Next = true;
			} 
			else if( Stopped ) {
				t_name = T->GetName(R);
				cout << T->GetName(R) << endl;
				Next = true;
			}
			else if( Playing ) {
				play(T->GetName(R));
				Playing = true;
				Paused = false;
			}
			
		}
		
		void stop() {
			if( !Stopped ) { cout << "Stoppped\n"; Stopped = true; Paused = false; Playing = false;  }
			else cout << "Already stopped\n";
		}
		
		void exit() {
			cout << "Bye!\n";
			return;
		}
		~Player() {
			delete T;
		}
};



int main() {
	srand(time(0));
//	tm *inf = new tm;
//	tm *len = new tm;
//	inf->tm_year = 1999;
//	inf->tm_mon = 11;
//	inf->tm_mday = 1;
//	len->tm_sec = 190;
	
//	Track T("name1");
	Track T;
	Player P(T, "C:\\Users\\Alex_dev\\Desktop\\Prog\\skill\\OOP intro\\Tracks\\Track_info.txt");
//	P.play("Param pam pam");
//	Track K;
//	K.ReadInfo( "C:\\Users\\Alex_dev\\Desktop\\Prog\\skill\\OOP intro\\Tracks\\Track_info.txt" ); //Track_info
//	K.PrintInfo("name1");
//	T.ReadInfo( "C:\\Users\\Alex_dev\\Desktop\\Prog\\skill\\OOP intro\\Tracks\\Track_info.txt" );

//	P.play("name8");
	P.next();
	P.pause();
	P.pause();
	P.play();
	P.play();
	P.play();
	P.stop();
	P.stop();
	P.next();
	P.pause();
	P.pause();
	P.play();
	P.exit();
	
//	P.PrintInfo("name1");
//	K.PrintInfo("name1");
}


//map<string, int>::iterator it;
//				for( it = Info.begin(); it != Info.end(); it++ ){
////					cout << it->first << " "<< it->second << "\n";
//				}