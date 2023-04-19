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
		
		
		void PrintInfo( string TName ) {
			cout << "Printing...\n";
			if ( Date->tm_mday > 31) Date->tm_mday = 0;

			for( int i = 0; i < TracksCount; i++ ) {
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
//						
					if( Word == "Name:" )  { 
						SS >> name[words];
						TrackName[names] = name[words];
						names++;
						TracksCount = names;
					}
					else if( Word == "Year:") {
						SS >> y[words];	
						Date[years].tm_year = stoi( y[words] );
						years++;
					}
					else if( Word == "Month:"){
						SS >> m[words];
						Date[months].tm_mon = stoi( m[words] );
						months++;
					} 
					else if( Word == "Day:"){
						SS >> d[words];
						Date[days].tm_mday = stoi( d[words] );
						days++;
					} 
					else if( Word == "Length:"){
						SS >> len[words];
						Len[length].tm_sec = stoi( len[words] );
						length++;
					} 
					else words++;
				}

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
			else if( !Playing ) cout << "Not playing\n";
			else if( Paused ) cout << "Already paused\n";
		}
		
		void next() {
			cout << "Next---->\n";
			int R = rand() % T->GetTracks();
			if( !Playing  ) { 
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
//	Track T("name1");
	Track T;
	Player P(T, "Track_info.txt");

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
	
}
