// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// Copyright Jeremy W. Murphy 2015.

// This file is written to be included from a Quickbook .qbk document.
// It can be compiled by the C++ compiler, and run. Any output can
// also be added here as comment or included or pasted in elsewhere.
// Caution: this file contains Quickbook markup as well as code
// and comments: don't change any of the special comment markups!

//[polynomial_arithmetic_0
/*`First include the essential polynomial header (and others) to make the example:
*/
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
#include "ComplexSupport.hpp"

//[polynomial_arithmetic_1
/*`and some using statements are convenient:
*/

using std::string;
using std::exception;
using std::cout;
using std::endl;
using std::abs;
using std::pair;

using namespace boost::math;
using namespace boost::math::tools; // for polynomial
using boost::lexical_cast;

//] [/polynomial_arithmetic_1]

template <typename T>
string sign_str(T const &x)
{
  return x < 0 ? "-" : "+";
}

template <typename T>
string inner_coefficient(T const &x)
{
  string result(" " + sign_str(x) + " ");
  if (abs(x) != T(1))
      result += lexical_cast<string>(abs(x));
  return result;
}

/*! Output in formula format.
For example: from a polynomial in Boost container storage  [ 10, -6, -4, 3 ]
show as human-friendly formula notation: 3x^3 - 4x^2 - 6x + 10.
*/
template <typename T>
string formula_format(polynomial<T> const &a)
{
  string result;
  if (a.size() == 0)
      result += lexical_cast<string>(T(0));
  else
  {
    // First one is a special case as it may need unary negate.
    unsigned i = a.size() - 1;
    if (a[i] < 0)
        result += "-";
    if (abs(a[i]) != T(1))
        result += lexical_cast<string>(abs(a[i]));

    if (i > 0)
    {
      result += "x";
      if (i > 1)
      {
          result += "^" + lexical_cast<string>(i);
          i--;
          for (; i != 1; i--)
              result += inner_coefficient(a[i]) + "x^" + lexical_cast<string>(i);

          result += inner_coefficient(a[i]) + "x";
      }
      i--;

      result += " " + sign_str(a[i]) + " " + lexical_cast<string>(abs(a[i]));
    }
  }
  return result;
} // string formula_format(polynomial<T> const &a)

template <typename T>
void print_polinomial(polynomial<T> const &a)
{
	cout << formula_format(a) << std::endl;
}


template <typename T>
void printExpression(polynomial<T> const &a){
	// agregar logica para  verificar limites de los coeficientes
	for(int x = a.size()-1; x > 0; x--){
			printCoefficient(a[x]);
			cout << "*x^" << x << " + ";
	}
	printCoefficient(a[0]);
	cout << endl;
}
