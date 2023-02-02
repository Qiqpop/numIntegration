#include <iostream>
#include <cmath>
#define M_PI 3.1415

using namespace std;

double eMach();
double functione(double x);
double newtonСotes(double b, double a, int n);
double centralRect(double b, double a, int n);
double trapeze(double b, double a, int n);
double simpson(double b, double a, int n);

int main() {
	setlocale(0, "ru");
	int n;
	double b, a;
	cout << "Введите: верхний придел интегрирования, нижний и разбиение с шагом 10" << endl;
	//cin >> b >> a >> n;
	cin >> n; b = M_PI / 2; a = 0;	// Для тригонометрических пределов интегрирования
	cout << "Формула Ньютона-Котеса" << endl;
	for (int i = 3; i <= 7; i++) {
		cout << "n=" << i << '\t' << newtonСotes(b, a, i) << endl;
	}
	cout << endl;
	cout << "Центр. прям.\tТрап.\t\tСимпсона\n";
	for (int i = 10; i <= n; i+=10) {
		//cout << "Разбиение " << i << endl;
		cout << centralRect(b, a, i) << '\t';
		cout  << trapeze(b, a, i) << '\t';
		cout  << simpson(b, a, i) << endl;
	}
	return 0;
}

// Интегрируемая функция
double functione(double x) {
	//return (cos(x) - 1) / x;
	return cos(x) / (1 + x);
}

// Формула Ньютона-Котеса 
double newtonСotes(double b, double a, int n) {
	double H[8];
	double h = b - a;
	double sum = 0;
	double result = 0;
	switch (n) {
	case 3:
		H[0] = H[3] = 1 / 8.0;
		H[1] = H[2] = 3 / 8.0;
		break;
	case 4:
		H[0] = H[4] = 7 / 90.0;
		H[1] = H[3] = 32 / 90.0;
		H[2] = 12 / 90.0;
		break;
	case 5:
		H[0] = H[5] = 19 / 288.0;
		H[1] = H[4] = 25 / 96.0;
		H[2] = H[3] = 25 / 144.0;
		break;
	case 6:
		H[0] = H[6] = 41 / 840.0;
		H[1] = H[5] = 9 / 35.0;
		H[2] = H[4] = 9 / 280.0;
		H[3] = 34 / 105.0;
		break;
	case 7:
		H[0] = H[7] = 751 / 17280.0;
		H[1] = H[6] = 3577 / 17280.0;
		H[2] = H[5] = 1323 / 17280.0;
		H[3] = H[4] = 2989 / 17280.0;
		break;
	default:
		cout << "Неизвестный коэффициент" << endl;
	}
	double x[10];
	int i = 0;
	for (double xn = a; xn < b; xn += h / n, i++) {
		x[i] = xn;
	}
	for (i = 0; i <= n; i++) {
		double xi = x[i];
		if (xi == 0) xi += eMach();
		sum += functione(xi) * H[i];
	}
	result += sum;
	result *= h;
	return result;
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

// Формула трапеций
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