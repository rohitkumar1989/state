#include<iostream>

using namespace std;
class state;
class stateoff;
class vending_machine_context{
	state* current=NULL;
	public:
	vending_machine_context();
	void set_current(state* s){
		current=s;
	}
	
	void on();
	
	void off();
	
};

class state{
	public: 
	    virtual void on(vending_machine_context* v){cout<<"already on\n";}
	    virtual void off(vending_machine_context* v){cout<<"already off\n";}
};

class stateon:public state{
	public: 
	void off(vending_machine_context* v);
};


class stateoff:public state{
	public: 
	void on( vending_machine_context* v);
};
void stateon::off(vending_machine_context* v){
		cout<<"on to off\n";
		v->set_current(new stateoff);
		delete this;
	}
	void stateoff::on( vending_machine_context* v){
		cout<<"off to on\n";
		v->set_current(new stateon);
		delete this;
	}
vending_machine_context::vending_machine_context(){
    
    current=new stateoff;
}
	void vending_machine_context:: on(){
		current->on(this);
		
	}
	
	void vending_machine_context::off(){
		current->off(this);
	}
	
int main(){
	
	void (vending_machine_context::*ptr[])()={&vending_machine_context::on,&vending_machine_context::off};
	vending_machine_context fsm;
	(fsm.*ptr[0])();
	(fsm.*ptr[1])();
}