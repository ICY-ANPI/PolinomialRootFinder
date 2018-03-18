#ifndef ANPI_POLYNOMIAL_H
#define ANPI_POLYNOMIAL_H
#include <vector>
#include <string>
#include <iostream>
#include "ComplexSupport.hpp"
using std::cout;
using std::endl;
namespace anpi{




template <typename T>
class polynomial{
private:
	//guardar los coeficientes en un vector
	//al igual que en la clase de boost se representa el polinomio de la siguiente manera a_0 + a_1*x + a_2*x^2 + ... a_n*x^n-1
	//donde n es el tamaño del vector y n-1 el ultimo indice de la lista coefficients
	std::vector<T> coefficients;
public:
	polynomial(std::vector<T> coefficient);
	T evaluate(T x);
	T coefficientAt(int x);

	void printExpression();

	~polynomial(){}
};



template<typename T>
polynomial<T>::polynomial(std::vector< T > coeff){
	coefficients = coeff;
}


template<typename T>
T polynomial<T>::evaluate(T x){
	//Se evalua el polinomio en la variable x
	T temp(1), result;
	for(int x = 0; x < coefficients.size(); x++){
		result += temp*coefficients[x];
		temp *= x;
	}
}

template<typename T>
T polynomial<T>::coefficientAt(int x){
	// agregar logica para  verificar limites de los coeficientes
	return coefficients[x];
}

template<typename T>
void polynomial<T>::printExpression(){
	// agregar logica para  verificar limites de los coeficientes
	for(int x = coefficients.size()-1; x > 0; x--){
		if (!isZero(coefficients[x])){
			printCoefficient(coefficients[x]);
			cout << "*x^" << x << " + ";
		}
	}
	printCoefficient(coefficients[0]);
	cout << endl;
}

}
#endif
