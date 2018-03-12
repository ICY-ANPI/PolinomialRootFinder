#ifndef DEFLATE2_H
#define DEFLATE2_H

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
polynomial<T> deflate2(const polynomial<T> &poly, const T& root, polynomial<T> &residuo);


template <typename T>
polynomial<T> deflate2(const polynomial<T> &poly, const std::complex<T>& root, polynomial<T> &residuo){
	polynomial<T> a;
	return a;
}


#endif // DEFLATE2_H
