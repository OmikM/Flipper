#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;

class col {
	public:
		int is_in = false;
    	int pos = 0;
		vector<col> cols;
		string name;
		function<void()> func;

		void mcol(string n, function<void()> f){
			name = n;
			func =  f;
		}

      	void Print(){
			if(cols.size()>0){
	        	cout << cols[pos].name << endl;
			}
			if(cols.size()>1){
        		cout << cols[(pos+1)%(cols.size())].name << "\n" << endl;
			}
    	}	
		void scroll(bool up){
			pos = (cols.size()+pos +(up*2-1)*-1)%cols.size();
		}
		void add(string n, function<void()> f = NULL){
			col temp;
			temp.mcol(n,f);
			cols.push_back(temp);
		}

		col *cur(){
			if(is_in){
				return cols[pos].cur();
			}
			else{
				return this;
			}
		}

		void next(){
			if(cols[pos].cols.size())
				is_in = true;
			if(cols[pos].func){
				cols[pos].func();
			}
		}
		
		void back(){
			is_in = false;
		}

};

col fr;

void add_ir(){
	cout << "scanning...";
}

void setup(){
	fr.add("NFC");
	fr.add("IR");
	fr.cols[1].add("Add_IR", add_ir);
	fr.add("RF");
}

void up(){
	fr.cur()->scroll(1);
}
void down(){
	fr.cur()->scroll(0);
}
void left(){
	fr.cur()->back();
}
void right(){
	fr.cur()->next();
}


int main() {
	
	fr.mcol("fr", 0);
	setup();
  	fr.cur()->Print();
	
	while(true){
		//temp
		char temp;
		cin >> temp;
		if(temp=='w')up();
		if(temp=='s')down();
		if(temp=='a')left();
		if(temp=='d')right();
		if(temp=='i'){
			cout << fr.cur()->name << "\n";
		}

		//

		fr.cur()->Print();
	}

  	
  	return 0;
}