#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

double f(double x)
{
	return sin(x)/(1+x*x);
}

double rectangles(double a, double b, double h)
{
	double sum = 0;
	double x;
	for(x = a + h * 0.5; x < b; x += h)
		sum += f(x);
	sum *= h;
	return sum;
}

double Simpson(double a, double b, double h)
{
	double sum = f(a) + f(b);
	double x;
	int i = 1;
	for(x = a + h; x < b - h; x += h){
		if(i%2 != 0)
			sum += 4*f(x);
		else
			sum += 2*f(x);
		i++;
	}
	return h*sum/3.;
}


int main(int argc, char ** argv)
{
	double a = 0.0, b = 1.0; 
    double h = 0.5; // задаём шаг интегрирования
	double errrect;
		do {
		double rect = rectangles(a, b, h);
		
		h /= 2;
		
		double divrect = rectangles(a, b, h); 
		
		errrect = abs(rect - divrect)/4.; // вычисляем погрешность
	} while (errrect > 1e-4);
	ofstream outf;
    outf.open("ans1.dat", ios_base::out);
	outf << "Integral = " << rectangles(a, b, h) << " " <<"Error = " << errrect << "\n";
	outf.close();
	
	do {
		double simp = Simpson(a, b, h);
		
		h /= 2;
		
		double divsimp = Simpson(a, b, h); 
		
		errrect = abs(simp - divsimp)/12.; // вычисляем погрешность
	} while (errrect > 1e-5);
	outf.open("ans2.dat", ios_base::out);
	outf << "Integral = " << Simpson(a, b, h) << " " <<"Error = " << errrect << "\n";
    outf.close();
	return 0;
}
