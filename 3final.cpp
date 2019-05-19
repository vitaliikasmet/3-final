#include <iostream>
 
using namespace std;
#include <vector>
#include <cmath>
#include <GLBall>
#include <NBodyScene>
 

 
 
 
class Body: public GLBall 
{
	friend class Mesh;
 
	private:
		long double x;
		long double y;
		long double vx;
		long double vy;
		long double ax;
		long double ay;
		long double m;
	public:
		Body(double x, double y, double vx, double vy, double m ): x(x), vx(vx), y(y), vy(vy), m(m), ax(0.0), ay(0.0)
		{}
		~Body(){}
 
		double getX() const  {
 
        return x;
 
    }
 
    double getY() const  {
 
        return y;
 
    }
    double getR() const  {
 
        return 1;
 
    }
 
 
 
};
 
class Mesh : public NBodyScene
{
	friend class Body;
	private:
		vector<Body> v;
		int i;
	public:
 
		Mesh(): i(0){}
		~Mesh(){}
		void add (Body k)
		{
			v.push_back(k);
			i=i+1;
		}
		void show()
		{
			int d;
			for (d=0; d<i; d++)
			{
				cout << v[d].x;
				cout<< " ";
				cout << v[d].y;
				cout<< "    ";
			}
		}
		void  doTimestep() 
		{
			int d;
			int c;
			for (d=0; d<i; d++)
			{
				v[d].ax=0;
				v[d].ay=0;
				for (c=0; c<i; c++)
				{
					if (c!=d)
					{
						v[d].ax+=6.67*v[c].m*(v[c].x-v[d].x)/100000/((v[c].x-v[d].x)*(v[c].x-v[d].x)+(v[c].y-v[d].y)*(v[c].y-v[d].y))/sqrt(((v[c].x-v[d].x)*(v[c].x-v[d].x)+(v[c].y-v[d].y)*(v[c].y-v[d].y)));
						v[d].ay+=6.67*v[c].m*(v[c].y-v[d].y)/100000/((v[c].x-v[d].x)*(v[c].x-v[d].x)+(v[c].y-v[d].y)*(v[c].y-v[d].y))/sqrt(((v[c].x-v[d].x)*(v[c].x-v[d].x)+(v[c].y-v[d].y)*(v[c].y-v[d].y)));
					}
 
				}
				v[d].x+=v[d].vx*0.01;
				v[d].y+=v[c].vy*0.01;
				v[d].vx+=v[d].ax*0.01;
				v[d].vy+=v[d].ay*0.01;
			}
		}
 
 
		void delay (double t)
		{
			while (t>0)
			{
				int c;
				t=t-0.01;
				doTimestep();
 
 
			}
		}
		unsigned int getNumberOfBodies() const 
		{
			cout<< i;
			return i;
		}
		GLBall& getBody(unsigned int number) const 
		{
			return v&[number];
		}
 
 
 
};
 
int main()
{
	Mesh h;
	Body a(0, 0, 0,0, 16);
	Body c(1000, 1000, 0,0, 10);
	Body l(1000, 0, 0,0, 10);
	Body k(0, 1000, 0,0, 10);
	h.add (a);
	h.add(c);
	h.add (l);
	h.add(k);
	h.delay(10);
	h.show();
	return 0;
}