/*************************************************************************
	> File Name: Vtable.cpp
	> Author: zyh_helen
	> Mail: zyh_helen@yeah.net 
	> Created Time: Tue 05 Apr 2016 09:14:57 PM EDT
 ************************************************************************/

#include<iostream>
using namespace std;

typedef void(*Func)();

class Base{
public:
	virtual void f(){
		cout<<"Base::f()"<<endl;
	}
	virtual void g(){
		cout<<"Base::g()"<<endl;
	}
	virtual void h(){
		cout<<"Base::h()"<<endl;
	}
};
/*	基类虚函数表
 *	要点：虚函数表中的内容是按照虚函数的声明顺序依次存放的
 * */
void test1(){
	Base b;
	cout<<sizeof(b)<<endl;	/*空类的默认大小为1（拥有一个虚表指针所以大小为4*/
	cout<<"虚函数表的地址："<<(void *)*(int *)(&b)<<endl;
	((Func)(*(int*)*(int*)(&b)))();   /*最后的()不可以省略，否则会报错*/
	((Func)(*((int*)*(int*)(&b)+1)))();
	((Func)(*((int*)*(int*)(&b)+2)))();
}

/*	单继承+无覆盖 */
class Derived:public Base{
public:
	virtual void f1(){
		cout<<"Derived::f1()"<<endl;
	}
	virtual void g1(){
		cout<<"Derived::g2()"<<endl;
	}
	virtual void h1(){
		cout<<"Derived::h3()"<<endl;
	}
	
};

/*	单继承+无覆盖
 *	要点：
 *		1）虚函数按照声明顺序出来在虚函数表中
 *		2）基类的虚函数在派生类的前面（先基类后派生类）
 *
 *	*/
void test2(){
	Derived d;
	cout<<sizeof(d)<<endl;
	((Func)(*(int*)*(int*)(&d)))();
	((Func)(*((int*)*(int*)(&d)+1)))();
	((Func)(*((int*)*(int*)(&d)+2)))();
	((Func)(*((int*)*(int*)(&d)+3)))();
	((Func)(*((int*)*(int*)(&d)+4)))();
	((Func)(*((int*)*(int*)(&d)+5)))();
}

/*	单继承+有覆盖 */
class Derived1:public Base{
public:
	virtual void f(){
		cout<<"Derived1::f()"<<endl;
	}
	virtual void g1(){
		cout<<"Derived1::g1()"<<endl;
	}
	virtual void h1(){
		cout<<"Derived1::h1()"<<endl;
	}
	
};
/*	单继承+有覆盖
 *	要点：
 *		1）覆盖的函数覆盖了基类的函数
 *		2）未覆盖的依旧
 *
 * */
void test3(){
	Derived1 d;
	cout<<sizeof(d)<<endl;
	((Func)(*(int*)*(int*)(&d)))();
	((Func)(*((int*)*(int*)(&d)+1)))();
	((Func)(*((int*)*(int*)(&d)+2)))();
	((Func)(*((int*)*(int*)(&d)+3)))();
	((Func)(*((int*)*(int*)(&d)+4)))();
}

class Base1{
public:
	virtual void f(){
		cout<<"Base1::f()"<<endl;
	}
	virtual void g(){
		cout<<"Base1::g()"<<endl;
	}
	virtual void h(){
		cout<<"Base1::h()"<<endl;
	}
};



/*	多继承+无覆盖
 *	要点：
 *		1）每个继承来的基类都有一张虚函数表
 *		2）派生类的虚函数存在于第一个继承的基类的虚函数表中（按照声明顺序）
 *
 */
class Derived2:public Base,Base1{
	virtual void f2(){
		cout<<"Derived2::f2()"<<endl;
	}
	virtual void g2(){
		cout<<"Derived2::g2()"<<endl;
	}
	virtual void h2(){
		cout<<"Derived2::h2()"<<endl;
	}
};

void test4(){
	Derived2 d;
	cout<<sizeof(d)<<endl;/* 大小为8 因为两个基类各有一个虚函数表*/
	/*base1*/
	((Func)(*(int*)*(int*)(&d)))();
	((Func)(*((int*)*(int*)(&d)+1)))();
	((Func)(*((int*)*(int*)(&d)+2)))();
	/*derived2 存在于第一个继承的基类的虚函数表中*/
	((Func)(*((int*)*(int*)(&d)+3)))();
	((Func)(*((int*)*(int*)(&d)+4)))();
	((Func)(*((int*)*(int*)(&d)+5)))();
	/*base2*/
	((Func)(*((int*)*((int*)(&d)+1))))();
	((Func)(*((int*)*((int*)(&d)+1)+1)))();
	((Func)(*((int*)*((int*)(&d)+1)+2)))();
}

/*	多继承+有覆盖
 *	要点：
 *		1）每个继承来的基类都有一张虚函数表
 *		2）派生类有覆盖的虚函数覆盖相应的函数
 *		3）派生类没有覆盖的虚函数存在于第一个基类的虚函数表中（按照声明顺序）
 *
 */
class Derived3:public Base,Base1{
	virtual void f(){
		cout<<"Derived3::f()"<<endl;
	}
	virtual void g2(){
		cout<<"Derived3::g2()"<<endl;
	}
	virtual void h2(){
		cout<<"Derived3::h2()"<<endl;
	}
};

void test5()
{

	Derived3 d;
	cout<<sizeof(d)<<endl;/* 大小为8 因为两个基类各有一个虚函数表*/
	/*base1*/
	((Func)(*(int*)*(int*)(&d)))();/*被派生类覆盖*/
	((Func)(*((int*)*(int*)(&d)+1)))();
	((Func)(*((int*)*(int*)(&d)+2)))();
	/*derived2 未覆盖的虚函数存在于第一个继承的基类的虚函数表中*/
	((Func)(*((int*)*(int*)(&d)+3)))();
	((Func)(*((int*)*(int*)(&d)+4)))();
	/*base2*/
	((Func)(*((int*)*((int*)(&d)+1))))();/*被派生类覆盖*/
	((Func)(*((int*)*((int*)(&d)+1)+1)))();
	((Func)(*((int*)*((int*)(&d)+1)+2)))();

}
int main()
{
	test5();
	return 0;
}
