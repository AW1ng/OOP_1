#include <iostream>
using namespace std;


class Window {
	protected:
		int ScrWidth = 50, ScrHeight = 80;
		int Width, Height, LtcX = 0, LtcY = 0;
	public:
		Window( int ltcX, int ltcY, int WWidth = 0, int WHeight = 0 ) { 
		
			if( Width < 0 || Height < 0 ) {
				cout << "Window size can`t be less 0\n";
			}
			
			if( ( WHeight < 0 && WWidth > ScrWidth ) || ( WWidth < 0 && WHeight > ScrHeight ) 
				|| ( WWidth > ScrWidth ) || ( WHeight > ScrHeight ) ) {
				
				cout << "Window size can`t be bigger than screen size\n";
				Width  = 0;
				Height = 0;
			}
			
			Width = WWidth;
			Height = WHeight;
			LtcX = ltcX;
			LtcY = ltcY;
			
		}
		
		void move( int ltcx, int ltcy ) {
			if( ltcx < 0 || ltcx > ScrWidth || ltcy < 0 || ltcy > ScrHeight ) cout << "Out of boundaries\n";
			LtcX = ltcx;
			LtcY = ltcy;
		}
		
		void resize(int NewWidth, int NewHeight ) {
			if( NewWidth < 0 || NewHeight < 0 ) {
				cout << "Window size can`t be less 0\n";
				NewWidth  = Width;
				NewHeight = Height;
			}
			
			if( NewWidth > ScrWidth || NewHeight > ScrHeight 
			||( NewHeight < 0 && NewWidth > ScrWidth ) || ( NewWidth < 0 && NewHeight > ScrHeight ) ) {
				cout << "Window size can`t be bigger than screen size\n";
				NewWidth = Width;
				NewHeight = Height;
			}
			Width = NewWidth;
			Height = NewHeight;
		}
		
		void display() {
			
			int offsety = 0;

			for( int i = 0; i <= ScrWidth ; i++ ) {

				
				for( int j = 0; j <= ScrHeight; j++ ) {
					if( i == LtcX && j >= LtcY && j < Height + LtcY ) cout << "1";
					else if( i >= LtcX && i < Width + LtcX && j >= LtcY && j < Height + LtcY )  cout << "1"; // && i <= Width
					else cout << "0";
					if( j == ScrHeight ) cout << "|";
				}
				cout << "\n";	
			}
		}
		
		void close() {
			cout << "Closing window...\n";
			resize(0,0);
			display();
			cout << "Window closed.\nExiting...";
			exit(2);
		}
		
};


int main() {
	Window W(20, 5, 9, 6);
	W.display();
//	W.resize(90, 9);
	cout << '\n';
//	W.move(10,20);
//	W.display();
	cout << '\n';
//	W.close();
}

