#include <polynomial.h>

polynomial::polynomial() {}

polynomial::polynomial(int n, int* powers, double* coefs) {
	monomial m;
	for (int i = 0; i < n; i++) {
		m = monomial(powers[i], coefs[i]);
		*this += m;
	}
}

polynomial::polynomial(const polynomial& a) {
	sz = a.sz;
	monomial* t1 = a.head.next;
	monomial* t2 = &head;
	while (t1) {
		t2->next = new monomial(*t1);
		t1 = t1->next;
		t2 = t2->next;
	}
}

polynomial::~polynomial() {
	sz = 0;
	while (head.next) {
		pop_next(head);
	}
}

polynomial& polynomial::operator=(const polynomial& p) {
	this->~polynomial();
	sz = p.sz;
	monomial* t1 = p.head.next;
	monomial* t2 = &head;
	while (t1 != nullptr) {
		t2->next = new monomial(*t1);
		t1 = t1->next;
		t2 = t2->next;
	}
	return *this;
}

polynomial polynomial::operator=(polynomial&& t) {
	if (this == &t) return *this;
	this->~polynomial();
	head.next = t.head.next;
	sz = t.sz;
	t.head.next = nullptr;
	return *this;
}

polynomial& polynomial::operator+=(const monomial& m) {
	if (m.coef == 0)return *this;
	if (!head.next) {
		push(head, m);
		sz++;
		return *this;
	}
	monomial* t = &head;
	while (t->next != nullptr && *(t->next) < m) {
		t = t->next;
	}
	if (t->next!=nullptr && *(t->next) == m) {
		*(t->next) = *(t->next) + m;
		if (t->next->coef == 0) {
			pop_next(*t);
			sz--;
		}
	}
	else {
		push(*t, m);
		sz++;
	}
	return *this;
}

polynomial& polynomial::operator+=(const polynomial& p) {
	if (!head.next) {
		*this = p;
		return *this;
	}
	monomial* prev=&(head);
	monomial* t1 = &head;
	const monomial* t2 = p.head.next;
	while (t2) {
		while (t1->next != nullptr && *(t1->next) < *t2) {
			prev = t1;
			t1 = t1->next;
		}
		if (t1->next == nullptr) {
			while (t2 != nullptr) {
				t1->next = new monomial(*t2);
				t1 = t1->next;
				t2 = t2->next;
				sz++;
			}
			return *this;
		}
		if (*(t1->next) == *t2) {
			t1->next->coef += t2->coef;
			if (t1->next->coef == 0) {
				pop_next(*t1);
				sz--;
			}
			else t1 = t1->next;
			t2 = t2->next;
		}
		else {
			push(*t1, *t2);
			sz++;
			t1 = t1->next;
			t2 = t2->next;
		}
	}
	return *this;
};

polynomial polynomial::operator+(const polynomial& p) {
	polynomial t(*this);
	t += p;
	return t;
};

polynomial& polynomial::operator*=(const double a) {
	if (a == 0) {
		this->~polynomial();
		return *this;
	}
	monomial* t = head.next;
	while (t) {
		(*t) =(*t)* a;
		t = t->next;
	}
	return *this;
};

polynomial polynomial::operator*(const double a) {
	polynomial ans(*this);
	ans *= a;
	return ans;
};

polynomial& polynomial::operator-=(polynomial& p) {
	*this += p * (-1);
	return *this;
};

polynomial polynomial::operator-(polynomial& p) {
	polynomial ans(*this);
	ans += p * (-1);
	return ans;
};

polynomial& polynomial::operator*=(monomial& p) {
	if (p.coef == 0) {
		this->~polynomial();
		return *this;
	}
	monomial* t = head.next;
	while (t) {
		*t = *t * p;
		t = t->next;
	}
	return *this;
};

polynomial polynomial::operator*(monomial& p) {
	polynomial t(*this);
	t *= p;
	return t;
};

polynomial polynomial::operator*(polynomial& p) {
	if (is_empty() || p.is_empty()) {
		return polynomial();
	}
	polynomial ans;
	monomial* t = head.next;
	while (t) {
		ans += p * (*t);
		t = t->next;
	}
	return ans;
};

polynomial& polynomial::operator*=(polynomial& p) {
	*this = (*this) * p;
	return *this;
};

bool polynomial::operator==(polynomial& p) {
	monomial* t1 = head.next;
	monomial* t2 = p.head.next;
	while (t1) {
		if (t1->power != t2->power || t1->coef != t2->coef)return false;
		t1 = t1->next;
		t2 = t2->next;
	}
	return true;
}

bool polynomial::operator!=(polynomial& p) {
	return !(*this == p);
}

void polynomial::push(monomial& to,const monomial& a) {
	to.next = new monomial(a, to.next);
}

void polynomial::pop_next(monomial& from) {
	monomial* t = from.next;
	from.next = from.next->next;
	delete t;
}

bool polynomial::is_empty() const { return (sz == 0); };


size_t polynomial::size() const { return sz; };


std::ostream& operator <<(std::ostream& out, const polynomial& a) {
	monomial* t = a.head.next;
	if (t == nullptr) {
		out << "0\n";
		return out;
	}
	if (t->coef == -1)out << "-";
	else if (t->coef != 1 || t->x() + t->y() + t->z() == 0)out << t->coef;

	if (t->x() + t->y() + t->z() != 0 && t->coef!=1 && t->coef!=-1)cout << "*";

	if (t->x() == 1)out << "x";
	else if (t->x())out << "x^" << t->x();

	if (t->x() != 0 && t->y() + t->z() != 0)cout << "*";

	if (t->y() == 1)out << "y";
	else if (t->y())out << "y^" << t->y();

	if (t->y() != 0 && t->z() != 0)cout << "*";

	if (t->z() == 1)out << "z";
	else if (t->z())out << "z^" << t->z();
	t = t->next;
	while (t) {
		if (t->coef > 0) out << " + ";
		if (t->coef == -1 && t->x() + t->y() + t->z() != 0)cout << " - ";
		else if (t->coef != 1 || t->x() + t->y() + t->z() == 0)cout << t->coef;

		if (t->x() + t->y() + t->z() != 0 && t->coef != 1 && t->coef != -1)cout << "*";

		if (t->x() == 1)out << "x";
		else if (t->x())out << "x^" << t->x();

		if (t->x() != 0 && t->y() + t->z() != 0)cout << "*";

		if (t->y() == 1)out << "y";
		else if (t->y())out << "y^" << t->y();

		if (t->y() != 0 && t->z() != 0)cout << "*";

		if (t->z() == 1)out << "z";
		else if (t->z())out << "z^" << t->z();
		t = t->next;
	}
	cout << "\n";
	return out;
};