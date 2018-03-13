#ifndef PARABOLA_H
#define PARABOLA_H

template <typename T>
class Parabola{
private:
	T a,b,c;
public:
	Parabola(T pA, T pB , T pC);

	T getA() const {
		return a;
	}

	void setA(T a) {
		this->a = a;
	}

	T getB() const {
		return b;
	}

	void setB(T b) {
		this->b = b;
	}

	T getC() const {
		return c;
	}

	void setC(T c) {
		this->c = c;
	}
};


template <typename T>
Parabola<T>::Parabola(T pA, T pB , T pC):a(pA),b(pB),c(pC){

}

#endif //PARABOLA_H
