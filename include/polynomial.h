#pragma once
#include <iostream>

using namespace std;

inline void copy(const char a[80], char b[80]) {
	for (int i = 0; i < 80; i++)b[i] = a[i];
}

struct monomial {
	int power;
	double coef;
	monomial* next;

	monomial(int _power = 0, double _coef = 0, monomial* _next = nullptr):power(_power),coef(_coef),next(_next) {
		if (power > 999 || power<0) throw "invalid power";
	}

	monomial(const monomial& t, monomial* _next=nullptr) :power(t.power), coef(t.coef), next(_next) {};

	~monomial() {}

	bool operator < (const monomial& t) { return power < t.power; }
	bool operator <= (const monomial& t) { return power <= t.power; }
	bool operator > (const monomial& t) { return power > t.power; }
	bool operator == (const monomial& t) { return (power == t.power); }
	bool operator == (double c) { return (coef == c); }
	int x() { return power / 100; }
	int y() { return power / 10%10; }
	int z() { return power %10; }

	monomial operator * (monomial& t) {
		if (x() + t.x() > 9 || y() + t.y() > 9 || z() + t.z() > 9)throw "power after multiplication >9";
		return monomial(power+t.power,coef*t.coef,nullptr);
	}

	monomial operator*(const double a) {
		return monomial(power, coef * a);
	}

	void operator=(const monomial& t) {
		power = t.power;
		coef = t.coef;
	}

	monomial operator + (const monomial& t) {
		if (t.power != power) throw "op + powers do not match";
		return monomial(power, coef + t.coef);
	}
};


class polynomial {
private:
	size_t sz=0;
	void push(monomial& to,const monomial& a);

	void pop_next(monomial& from);
public:
	monomial head=monomial();

	polynomial();
	polynomial(int n,int* powers, double* coefs);
	polynomial(const polynomial& a);
	~polynomial();

	polynomial& operator=(const polynomial& p);
	polynomial operator=(polynomial&& t);

	polynomial& operator+=(const monomial& m);

	polynomial& operator+=(const polynomial& p);
	polynomial operator+(const polynomial& p);

	polynomial& operator*=(const double a);
	polynomial operator*(const double a);

	polynomial& operator-=(polynomial& p);
	polynomial operator-(polynomial& p);

	polynomial operator*(monomial& p) ;
	polynomial& operator*=(monomial& p) ;

	polynomial operator*(polynomial& p);
	polynomial& operator*=(polynomial& p);

	bool operator==(polynomial& p);
	bool operator!=(polynomial& p);

	bool is_empty() const;

	size_t size() const;


	friend ostream& operator <<(ostream& out, const polynomial& a);
};

inline polynomial test_poly(int size_modifier = 0) {
	int powers[] = { 0,1,2 };
	double coefs[] = { 1,2,3 };
	polynomial p(3, powers, coefs);
	for (int i = 0; i < size_modifier; i++) {
		p += monomial(10 + i, 5.0);
	}
	return p;
}