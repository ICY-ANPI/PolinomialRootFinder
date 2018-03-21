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
#include "ComplexSupport.hpp"
#include "Deflate.hpp"

using std::abs;
using namespace boost::math;
using namespace boost::math::tools; // para polynomial
using std::cout;
using std::endl;
using std::complex;
//using anpi::polynomial;

template <class T>
T desplamiento(T a, T b, T c , T solucion) {
	return ;
}
template <class T>
typename std::enable_if<is_tt<std::complex, T>::value>::type siguienteRaiz(T a, T b, T c , T xActual, T &xSiguiente, T discriminante) {
	//throw anpi::Exception("unimplemented method");
	if (b + std::sqrt(discriminante) == T(0) && b - std::sqrt(discriminante) == T (0))
		throw anpi::Exception("Division por cero");

	T temp = xActual - (T(2)*c)/(b + std::sqrt(discriminante));
	T temp2 = xActual - (T(2)*c)/(b - std::sqrt(discriminante));
	if(b + std::sqrt(discriminante) == T(0)){
		xSiguiente = temp2;
		return;
	}
	else if (b - std::sqrt(discriminante) == T(0)){
		xSiguiente = temp;
		return;
	}
	else{
		if(abs(a-temp) + abs(b-temp) + abs(c-temp) < abs(a-temp2) + abs(b-temp2) + abs(c-temp2))
			xSiguiente = temp;
		else
			xSiguiente = temp2;
	}
}

template <class T>
typename std::enable_if<!is_tt<std::complex, T>::value>::type siguienteRaiz(T a, T b, T c, T xActual, T &xSiguiente, T discriminante) {
	if (discriminante > 0){
		if(b + std::sqrt(discriminante)*((b > T(0))?T(1):T(-1)) == 0)
			throw anpi::Exception("Division por cero");
		xSiguiente = xActual - (T(2)*c)/(b + std::sqrt(discriminante)*((b > T(0))?T(1):T(-1)));
	}
	else
		throw anpi::Exception("Raiz compleja encontrada");
}



template <typename T>
class Muller{
	//Verifica la cantidad de iteracones que realiza el algorimo de Muller para encontrar
	//las raices del polinomio;
	int convergencia;
	bool pulidoDeRaices;
	Parabola<T> parabola;
	T evaluarParabola(T xi);
	//void regulaFalsi();
	//xi, xi_n = xi_(n-1)
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









template <class T>
typename std::enable_if<is_tt<std::complex,  T>::value>::type regulaFalsi(T inicialValue, T &x0, T &x1, T &x2, polynomial<T> poly) {
	throw anpi::Exception("unimplemented method Regula Falsi complex");
	x2 = poly.evaluate(inicialValue);

	//condicion de bolzano
	//existe una raiz si los extremos son ceros
	while (poly.evaluate(x1)*poly.evaluate(x2) > 0) {
		x0 = (poly.evaluate(x1)-poly.evaluate(x2))/(x1-x2);
		x1 = x2;
		x2 = x0;
	}
	x0 = (poly.evaluate(x1)-poly.evaluate(x2))/(x1-x2);

}

template <class T>
typename std::enable_if<!is_tt<std::complex, T>::value>::type regulaFalsi(T initialValue, T &x0, T &x1, T &x2, polynomial<T> poly) {
	throw anpi::Exception("unimplemented method Regula Falsi real");

}









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
	std::vector<T> v(poly.size()-1);
	cout << "Muller is working" << endl;
	//regulaFalsi(x0);
	//Raices
	T xSiguiente, xActual(x2),xPrevio(x1), xTransPrevio(x0);
	//Diferencias en las raices de prueba
	T h1,h2;
	//Deltas
	T Delta1, Delta2;

	//estas son los coeficientes que conforman una funcion cuadratica
	//f(x) = a*x^2 + b*x + c
	T a,b,c;

	polynomial<T> residuo;


	T error;
	T discriminante;
	 for (int index = v.size()-1; index >= 0; index--) {
	 	/* code */

		//Se usara la definicion de error absoluto
		error = errorSoportado + T(1);
		xActual=x2;
		xPrevio = x1;
		xTransPrevio = x0;
		while (std::abs(error) > std::abs(errorSoportado)&& convergencia < 150){
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

			//Calculo previo del discriminante
			discriminante = b*b-T(4)*a*c;
			//Funcion que elije en tiempo de compilacion el tipo de variable.
			//sea raiz compleja o sea raiz real.
			siguienteRaiz(a, b, c, xActual, xSiguiente,discriminante);

			//actualizacion de los nuevos valores
			xTransPrevio = xPrevio;
			xPrevio = xActual;
			xActual = xSiguiente;
			error = c;
			convergencia++;
		}
		/*
		 * Se debe hacer deflación aquí.
		 */
		 poly = deflate<T>(poly,xActual,residuo);
		cout << "Raiz encontrada: ";
		printCoefficient(xActual);
		cout << endl;
		v[index] = xActual;
	 }

	return v;
}

template <typename T>
void mullerTest(polynomial< T > p){
	Muller< T > muller;
	try{
		std::vector<T> v =  muller.muller(p,T(0.00001),T(0),T(30),T(-30));
		for (int i = 0; i < v.size(); i++) {
			/* code */
			cout << "Raiz encontrada: ";
			printCoefficient(v[i]);
			cout << endl;
		}
	}
	catch(anpi::Exception &e){
		std::cout << e.what() << std::endl;
	}
	return;
}



#endif //MULLER_H
