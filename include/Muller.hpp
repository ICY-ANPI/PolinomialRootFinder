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

#include <cstdlib>
#include <ctime>

#include <type_traits>
#include "ComplexSupport.hpp"
#include "Deflate.hpp"

using namespace boost::math;
using namespace boost::math::tools; // para polynomial
//using namespace std;
using std::complex;
using std::cout;
using std::abs;
using std::endl;
//int RANGE_RANDOM_LIMIT_ANPI = 150;


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
	//este if se realiza debido a que raices que son casi reales entran aqui
	//su componente imaginaria es igual a cero.
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
	T evaluarParabola(T xi);
	T mullerStep(polynomial<T> poly, T xActual,T xPrevio,T xTransPrevio);
public:
	Muller():convergencia(0),pulidoDeRaices(false){}
	std::vector<T> muller(polynomial<T> poly, T errorSoportado,T a, T b, T c);
	int getConvergencia() const {
		return convergencia;
	}
	~Muller(){};
};


template <class T>
typename std::enable_if<is_tt<std::complex,  T>::value>::type randomRoot(T &x, int limit) {
	srand(time(0));
	T sign = T((rand()%2 == 1)?1:-1,(rand()%2 == 1)?1:-1);
	x =  sign*T(rand()%limit,rand()%limit);
	//cout << x << endl;
}

template <class T>
typename std::enable_if<!is_tt<std::complex, T>::value>::type randomRoot(T &x, int limit) {
	srand(time(0));
	static std::default_random_engine e{};
	static std::uniform_int_distribution<int> d{(-1*limit), (limit)};
	x = T(d(e));
}



template <class T>
typename std::enable_if<is_tt<std::complex,  T>::value>::type intervalo(T inicialValue, T &x0, T &x1, T &x2, polynomial<T> poly, int limit) {
	//throw anpi::Exception("unimplemented method Regula Falsi complex");

	x2 = inicialValue;
	T y = poly.evaluate(x2);
	T y2 =poly.evaluate(x1);
	//condicion de bolzano
	//existe una raiz si los extremos son ceros
	while (y.real()*y2.real() > T(0).real()) {
		randomRoot<T>(x1, limit);
		y2 = poly.evaluate(x1);
	}

	x0 = x1/T(2);

}

template <class T>
typename std::enable_if<!is_tt<std::complex, T>::value>::type intervalo(T inicialValue, T &x0, T &x1, T &x2, polynomial<T> poly, int limit) {
	//throw anpi::Exception("unimplemented method Regula Falsi real");
	x2 = inicialValue;
	T y = poly.evaluate(x2);
	T y2 =poly.evaluate(x1);
	//condicion de bolzano
	//existe una raiz si los extremos son ceros
	while (y*y2 > T(0)) {
		randomRoot<T>(x1, limit);
		y2 = poly.evaluate(x1);
		//cout << x1 << endl;
	}
	x0 = x1/T(2);
}



template <typename T>
T f(T x){
	return std::exp(-x)-x;

}


template <typename T>
std::vector<T> Muller<T>::muller(polynomial<T> poly, T errorSoportado,T x2, T x1, T x0){
	std::vector<T> v(poly.size()-1);
	convergencia = 0;
	polynomial<T> poly2(poly);
	//cout << "Muller is working" << endl;
	//cout << "=================" << endl;


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
		xActual=x2 = T(150);
		xPrevio = x1 = x2/T(2);
		xTransPrevio = x0 = T(-150);
		while (convergencia < 150*v.size()){
			//Definicion de los h's
			//set h1
			h2 = xActual - xPrevio;
			//set h2
			h1= xPrevio - xTransPrevio;

			//Definicion de los delta's
			Delta1 = (poly2.evaluate(xPrevio) - poly2.evaluate(xTransPrevio))/h1;
			Delta2 = (poly2.evaluate(xActual) - poly2.evaluate(xPrevio))/h2;
			//Definiendo los valores de la funcion cuadratica
			a = (Delta2-Delta1)/(h2-h1);
			b = a*h2+Delta2;
			c = poly2.evaluate(xActual);
			if(std::abs(c*T(10)) < std::abs(errorSoportado))break;

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
		poly2 = deflate<T>(poly2,xActual,residuo);
		v[index] = xActual;

	}

	return v;
}

template <typename T>
std::vector<T> mullerTest(polynomial< T > p, T presicion, int &convergencia){
	Muller< T > muller;
	std::vector<T> v;
	try{
		v =  muller.muller(p,presicion,T(0),T(30),T(-30));
		convergencia = muller.getConvergencia();
		return v;
	}
	catch(anpi::Exception &e){
		std::cout << e.what() << std::endl;
	}
	return v;
}



#endif //MULLER_H
