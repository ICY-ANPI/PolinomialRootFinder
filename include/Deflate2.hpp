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
#include "Deflate.hpp"

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
polynomial<T> deflate2(const polynomial<T> &poly, const std::complex<T>& root, polynomial<T> &residuo){
	polynomial<std::complex<T>> a(poly);
	polynomial<std::complex<T>> redux(residuo);
	polynomial<T> result(poly);

	polynomial<std::complex<T>> deflated = deflate<std::complex<T>>(a,root,redux);
	bool isReal = true;
	for(int x = 0; x < a.size();x++){
		if (deflated[x].imag() > T(0.001)){
			isReal = false;
			break;
		}
	}

	if (isReal){
		for(int x = 0; x < a.size(); x++){
			result[x] = deflated[x].real();
			residuo[x] = redux[x].real();
		}
	}

	return result;
}


#endif // DEFLATE2_H
