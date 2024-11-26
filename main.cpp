#include <iostream>
#include <string>
#include <vector>
using namespace std;

class MyClass {
	public:
    	int pos = 0;
      	vector<string> opt = {"Zegar", "IR", "RF", "RFiD"};
      	void Print(){
	        cout << opt[pos] << endl;
        	cout << opt[(pos+1)%(opt.size())] << "\n" << endl;
    	}	
		void scroll(bool up){
			pos = (opt.size()+pos +(up*2-1)*-1)%opt.size();
		}

};

int main() {
	MyClass front;
  	front.Print();
	for (int i =0; i < 5; i++){
		front.scroll(0);
		front.Print();
	}

  	
  	return 0;
}