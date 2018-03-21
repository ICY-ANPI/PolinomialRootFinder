#include <boost/math/tools/polynomial.hpp>

#ifndef DEFLATE_H
#define DEFLATE_H

#include <boost/math/tools/polynomial.hpp>
//] [polynomial_arithmetic_0

#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <utility>

//[polynomial_arithmetic_1
/*`and some using statements are convenient:
*/

using std::string;
using std::exception;
using std::cout;
using std::abs;
using std::pair;

using namespace boost::math;
using namespace boost::math::tools; // for polynomial
using boost::lexical_cast;



template <typename T>
polynomial<T> deflate(const polynomial<T> &poly, const T& root, polynomial<T> &residuo);


template <typename T>
polynomial<T> deflate(const polynomial<T> &poly, const T& root, polynomial<T> &residuo){
	polynomial<T> cociente = poly;
	residuo = polynomial<T>(poly);

	for (int i = 0; i < poly.size(); i++) {
		cociente[i] = 0;
		residuo[i] = 0;
	}
	for (int x = poly.size()-2; x >= 0 ; x--) {
		cout << "Poly x: " << poly[x]<<"\n";
		cociente[x] = poly[x+1] + cociente[x+1] * root;
		cout << "Cociente: " << cociente[x] <<"\n";
		cout << "Residuo: " << residuo[x] <<"\n";
	}
	residuo[0] = poly[0] + cociente[0]*root;
	return cociente;
}


#endif // DEFLATE_H
