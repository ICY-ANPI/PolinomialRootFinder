#ifndef MULLER_H
#define MULLER_H

#include <boost/math/tools/polynomial.hpp>
#include <boost/array.hpp>
#include <cmath>
#include <vector>
#include "Parabola.hpp"


using std::abs;
using namespace boost::math;
using namespace boost::math::tools; // para polynomial

template <typename T>
class Muller{
	//Verifica la cantidad de iteracones que realiza el algorimo de Muller para encontrar
	//las raices del polinomio;
	int convergencia;
public:
	std::vector<T> muller(polynomial<T> poly);

	int getConvergencia() const {
		return convergencia;
	}
};

template <typename T>
std::vector<T> Muller<T>::muller(polynomial<T> poly){
	std::vector<T> a;
	return a;
}



#endif //MULLER_H
