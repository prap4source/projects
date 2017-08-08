#include "common.hpp"
using namespace std;
class cloud {
 public:
       void print() {
              cout <<"This is "<<name<<" class"<<endl;
       }
       cloud() {
	 name = __func__;
	}
 private:
 	const char *name;
	
 };

class privateCloud: public cloud {
 public:
       void print() {
              cout <<"This is "<<name<<" class"<<endl;
       }
       privateCloud() {
	 name = __func__;
	}
 private:
 	const char *name;
};

void start_classes(int argc, char *argv[]) {
 	cloud a;
	privateCloud b;
	a.print();
	b.print();
}
