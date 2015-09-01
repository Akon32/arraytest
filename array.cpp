#include <iostream>
#include <time.h>

template<class T>
class FlatArray{
public:
	int x,y,z,sx,sy,sz;
	T *data;
	FlatArray(int x,int y,int z):x(x),y(y),z(z),sx(1),sy(x),sz(x*y){
		data=new T[x*y*z];
		for(int i=0;i<x*y*z;i++)
			data[i]=0;
	}
	~FlatArray(){
		delete[]data;
	}
	T& operator()(int i,int j,int k){
		return data[i*sx+j*sy+k*sz];
	}
};
template<class T>
class ThreeDArray{
public:
	int x,y,z;
	T ***data;
	ThreeDArray(int x,int y,int z):x(x),y(y),z(z){
		data=new T**[z];
		for(int i=0;i<z;i++){
			data[i] = new T*[y];
			for(int j=0;j<y;j++){
				data[i][j]=new T[x];
				for(int k=0;k<x;k++)
					data[i][j][k] = 0;
			}
		}
	}
	~ThreeDArray(){
		for(int i=0;i<z;i++){
			for(int j=0;j<y;j++)
				delete[] data[i][j];
			delete[] data[i];
		}
		delete[]data;
	}
	T& operator()(int i,int j,int k){
		return data[k][j][i];
	}
};

template<class A,class B=A>
void move(A&a,B&b){
	for(int k=0;k<a.z;k++)
		for(int j=0;j<a.y;j++)
			for(int i=0;i<a.x;i++)
				a(rand()%a.x,rand()%a.y,rand()%a.z)=b(rand()%b.x,rand()%b.y,rand()%b.z);
}

//void move1(ThreeDArray<int>&a,ThreeDArray<int>&b){move(a,b);}
//void move2(FlatArray<int>&a,FlatArray<int>&b){move(a,b);}
//void move3(ThreeDArray<int>&a,FlatArray<int>&b){move(a,b);}

template<class A,class B=A>
class Tester{
	A a;
	B b;
public:
	Tester(int x,int y,int z):a(x,y,z),b(x,y,z){}
	clock_t test(){
		clock_t start = clock();
		move(a,b);
		clock_t finish = clock();
		std::cout<<__PRETTY_FUNCTION__<<std::endl<<" start="<<start<<" finish="<<finish<<" dt="<<(finish-start)<<std::endl;
		return finish-start;
	}
};

int main(){
	int x=300,y=300,z=300;
	int N=5;
	long long clocks[4]={};
	using T=int;
	srand(time(0));
	for(int i=0;i<N;i++){
		std::cout<<"i="<<i<<std::endl;
		Tester<ThreeDArray<T>> t1(x,y,z);
		Tester<FlatArray<T>> t2(x,y,z);
		Tester<ThreeDArray<T>,FlatArray<T>> t3(x,y,z);
		Tester<FlatArray<T>,ThreeDArray<T>> t4(x,y,z);
		clocks[0]+=t1.test();
		clocks[1]+=t2.test();
		clocks[2]+=t3.test();
		clocks[3]+=t4.test();
	}
	std::cout<<clocks[0]/N<<"\t"<<clocks[1]/N<<"\t"<<clocks[2]/N<<"\t"<<clocks[3]/N<<std::endl;
	return 0;
}

