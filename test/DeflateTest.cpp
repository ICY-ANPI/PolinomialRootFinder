#define BOOST_TEST_MODULE PolynomialRootFinder
#include <boost/test/unit_test.hpp>

#include "Deflate.hpp"
#include "Deflate2.hpp"
#include "Example.hpp"
#include "PrintPolynomial.hpp"

#include <boost/math/tools/polynomial.hpp>

#include <boost/array.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assert.hpp>

#include <iostream>
#include <stdexcept>
#include <cmath>
#include <string>
#include <utility>

using std::string;
using std::exception;
using std::cout;
using std::endl;
using std::abs;
using std::pair;


using namespace boost::math;
using namespace boost::math::tools; // for polynomial
using boost::lexical_cast;



BOOST_AUTO_TEST_CASE(polynomialTestCase){
  boost::array<double, 3> const d3a = {{6, 5, 1}};
  polynomial<double> const a(d3a.begin(), d3a.end());
  polynomial<double> const b{{2,1}};
  polynomial<double> residuo{{5}};
  polynomial<double> resultado = deflate<double>(a,2,residuo);
  cout << "El resultado de divir " << formula_format(a) << " por " << formula_format(b) << " es: ";
  cout << formula_format(resultado) << std::endl;
  cout << "Y el residuo es: ";
  cout << formula_format(residuo) << std::endl;
}

BOOST_AUTO_TEST_CASE(ExampleCase)
{
	//Insert your code here!
	BOOST_CHECK_EQUAL(5, sqr(2));
}


BOOST_AUTO_TEST_CASE(ExampleCase2)
{
	//Insert your code here!
	BOOST_CHECK_EQUAL(4, sqr(2));
}


BOOST_AUTO_TEST_CASE(DeflateFloatTestNonPolished)
{
	//Insert your code here!
}

BOOST_AUTO_TEST_CASE(DeflateFloatTestPolished)
{
	//Insert your code here!
}

BOOST_AUTO_TEST_CASE(DeflateDoubleTestNonPolished)
{
	//Insert your code here!
}


BOOST_AUTO_TEST_CASE(DeflateDoubleTestPolished)
{
	//Insert your code here!
}






BOOST_AUTO_TEST_CASE(Deflate2FloatTestNonPolished)
{
	//Insert your code here!
}

BOOST_AUTO_TEST_CASE(Deflate2FloatTestPolished)
{
	//Insert your code here!
}

BOOST_AUTO_TEST_CASE(Deflate2DoubleTestNonPolished)
{
	//Insert your code here!
}


BOOST_AUTO_TEST_CASE(Deflate2DoubleTestPolished)
{
	//Insert your code here!
}
