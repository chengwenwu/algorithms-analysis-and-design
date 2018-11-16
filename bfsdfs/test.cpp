#include <iostream>
using namespace std;
class test{
private:
	string a;
public:
	test()
	{
		a = "test";
	}
	string get()
	{
		return a;
	}
	
};
class c{
public:
	void fset()
	{
		test b;// = new test();
		//*b = 1;
		t = &b;
	}
	test* get()
	{
		return t;
	}
private:
	test* t;
};

int main()
{

	c cc;
	cc.fset();
	cc.get();
	//fset(a);
	cout<<cc.get()->get()<<endl;
	//delete a;
}