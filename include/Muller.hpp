#ifndef MULLER_H
#define MULLER_H

#include <boost/math/tools/polynomial.hpp>
#include <boost/array.hpp>
//#include <cmath>
#include <vector>
#include "Parabola.hpp"
#include "Exception.hpp"
#include <iostream>
#include <complex>
#include <stdbool.h>
#include <type_traits>

using std::abs;
using namespace boost::math;
using namespace boost::math::tools; // para polynomial
using std::cout;
using std::endl;


template <typename T>
class Muller{
	//Verifica la cantidad de iteracones que realiza el algorimo de Muller para encontrar
	//las raices del polinomio;
	int convergencia;
	bool pulidoDeRaices;
	Parabola<T> parabola;
	T evaluarParabola(T xi);	
	//xi, xi_n = x_(i-n)
	void configurarParabola(polynomial<T> poly, T xi,T xi_1,T xi_2);
	T mullerStep(polynomial<T> poly, T xActual,T xPrevio,T xTransPrevio);
public:
	Muller():convergencia(0),pulidoDeRaices(false),parabola(0,0,0){
		//pulidoDeRaices = true;
	}
	std::vector<T> muller(polynomial<T> poly, T errorSoportado,T a, T b, T c);

	int getConvergencia() const {
		return convergencia;
	}
	~Muller(){};
};


template <typename T>
T Muller<T>::evaluarParabola(T xi){

}

template <typename T>
void Muller<T>::configurarParabola(polynomial<T> poly, T xActual,T xPrevio,T xTransPrevio){

}

template <typename T>
T f(T x){
	return std::exp(-x)-x;

}



/**
 *
 */
template <typename T>
std::vector<T> Muller<T>::muller(polynomial<T> poly, T errorSoportado,T x2, T x1, T x0){
	std::vector<T> v;
	
	//Raices
	T xSiguiente, xActual(x2),xPrevio(x1), xTransPrevio(x0);
	//Diferencias en las raices de prueba
	T h1,h2;
	//Deltas
	T Delta1, Delta2;

	//estas son los coeficientes que conforman una funcion cuadratica
	//f(x) = a*x^2 + b*x + c
	T a,b,c;

	//Se usara la definicion de error absoluto
	T error = errorSoportado + T(1);
	T discriminante;
	/*
	 * Se debe buscar las raices aqui
	 */

	//seccion de riesgo en el codigo, comparancion del error y el error soportado
	while (std::abs(error) > std::abs(errorSoportado)&& convergencia < 100){
		//Definicion de los h's

		//set h1
		h2 = xActual - xPrevio;
		//set h2
		h1= xPrevio - xTransPrevio;

		//Definicion de los delta's
		Delta1 = (poly.evaluate(xPrevio) - poly.evaluate(xTransPrevio))/h1;
		Delta2 = (poly.evaluate(xActual) - poly.evaluate(xPrevio))/h2;
		//Delta1 = (f(xPrevio) - f(xTransPrevio))/h1;
		//Delta2 = (f(xActual) - f(xPrevio))/h2;
		//Definiendo los valores de la funcion cuadratica
		a = (Delta2-Delta1)/(h2-h1);
		b = a*h2+Delta2;
		c = poly.evaluate(xActual);
		//c = f(xActual);
		parabola = {a,b,c};
		cout << "=============================================================================================" << endl;
		cout << "Iteracion: " << convergencia << ", valor x: " << xActual << " y el valor de f(x) es " << c << endl;
		cout << "x" << convergencia+2 << "= " << xActual
			 << " x"<< convergencia+1 << "= " << xPrevio
			 << " x"<< convergencia << "= " << xTransPrevio << endl;
		cout << "Discriminante: " << b*b-T(4)*a*c << ", a = " << a << ", b = " << b << ", c = " << c << endl;
		cout << "Solucion 1: " << xActual -(T(2)*c)/(b+std::sqrt(b*b-T(4)*a*c))<< endl
			 << "Solucion 2: " << xActual -(T(2)*c)/(b-std::sqrt(b*b-T(4)*a*c))<< endl;
		cout << "=============================================================================================" << endl<< endl;
		discriminante = b*b-T(4)*a*c;

		//seccion de riesgo en el codigo
		if (discriminante > 0)
			xSiguiente = xActual - (T(2)*c)/(b + std::sqrt(discriminante)*((b > T(0))?T(1):T(-1)));
		else
			throw anpi::Exception("Raiz compleja encontrada");
		xTransPrevio = xPrevio;
		xPrevio = xActual;
		xActual = xSiguiente;
		//error = poly.evaluate(xActual);
		error = c;
		convergencia++;
	}

	/*
	 * Se debe hacer deflación aquí.
	 */
	cout << "El valor de x Actual es: " << xActual << endl;

	return v;
}



#endif //MULLER_H
