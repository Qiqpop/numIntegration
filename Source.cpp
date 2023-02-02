#include <iostream>
#include <cmath>
#define M_PI 3.1415

using namespace std;

double eMach();
double functione(double x);
double centralRect(double x, double h, int n);
double trapeze(double b, double a, int n);
double simpson(double b, double a, int n);

int main() {
	setlocale(0, "ru");
	int n;
	double b, a;
	cout << "Введите: верхний придел интегрирования, нижний и разбиение с шагом 10" << endl;
	cin >> b >> a >> n;
	cout << "Центр. прям.\tТрап.\t\tСимпсона\n";
	for (int i = 10; i <= n; i+=10) {
		cout << "Разбиение " << i << endl;
		cout << centralRect(b, a, i) << '\t';
		cout  << trapeze(b, a, i) << '\t';
		cout  << simpson(b, a, i) << endl;
	}
	return 0;
}

// Интегрируемая функция
double functione(double x) {
	return (cos(x) - 1) / x;
}

// Формула центральных прямоугольников
double centralRect(double b, double a, int n) {
	double h = (b - a) / n;
	double result = 0;
	double element = 0;
	for (double x = a; x < b; x+=h) {
		element = functione(x + h/2);
		result += element;
	}
	result*= h;
	return result;
}

// Формула трапеции
double trapeze(double b, double a, int n) {
	double h = (b - a) / n;
	double result = (
		(a == 0 ? functione(a + eMach()) : functione(a)) +
		(b == 0 ? functione(b + eMach()) : functione(b))
		) / 2;
	double element = 0;
	for (double x = a+h; x < b; x += h)  {
		element = functione(x);
		result += element;
	}
	result *= h;
	return result;
}

// Формула Симпсона
double simpson(double b, double a, int n) {
	n *= 2;
	double h = (b - a) / (n);
	double result = (
		(a == 0 ? functione(a + eMach()) : functione(a)) +
		(b == 0 ? functione(b + eMach()) : functione(b)));
	double element = 0;
	double sum = 0;
	double* x = new double[n+10];
	int i = 0;
	for (double xn = a; xn < b; xn += h, i++) {
		x[i] = xn;
	}
	i = 1;
	do {
		double xi = x[2 * i - 1];
		if (xi == 0) xi += eMach();
		element = functione(xi);
		sum += element;
		i++;
	} while (i * 2 - 1 <= n);
	sum *= 4;
	result += sum;
	sum = 0;
	i = 0;
	do {
		double xi = x[2 * i];
		if (xi == 0) xi += eMach();
		element = functione(xi);
		sum += element;
		i++;
	} while (i * 2 <= n - 1);
	sum *= 2;
	result += sum;
	result *= h / 3;
	delete[]x;
	return result;
}

// Машинный эпсилон
double eMach() {
	double x = 1, y = 0, me;
	do {
		me = x;
		x = x / 2;
		y = 1 + x;
	} while (y != 1);
	return me;
}