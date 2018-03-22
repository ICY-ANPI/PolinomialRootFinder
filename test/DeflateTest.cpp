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



template <typename T>
void evalDeflate(polynomial<T> p, std::vector<T>v){
	polynomial<T> redux;
	for(int x = 0; x < v.size();x++){
		deflate<T>(p,v[x], redux);
		bool isZero = true;
		for (int i = 0; i < redux.size(); ++i) {
			isZero = isZero && std::abs(redux[i]) < std::abs(T(0.01));
		}
		BOOST_ASSERT(isZero && "Residuo diferente de cero!");
	}

}


template <typename T>
void evalDeflate2(polynomial<T> p, std::vector<std::complex<T> >v){
	polynomial<T> redux;
	for(int x = 0; x < v.size();x++){
		deflate2<T>(p,v[x], redux);
		bool isZero = true;
		for (int i = 0; i < redux.size(); ++i) {
			isZero = isZero && std::abs(redux[i]) < std::abs(T(0.01));
		}
		BOOST_ASSERT(isZero && "Residuo diferente de cero!");
	}

}


template<typename T>
void firstPol(polynomial<T> p){

	std::vector<T> v{{33,-55,88}};
	evalDeflate<T>(p,v);
}

template<typename T>
void firstPol2(polynomial<T> p){

	std::vector<std::complex<T>> v{{std::complex<T>(0,3),std::complex<T>(0,-3)}};
	evalDeflate2<T>(p,v);
}


BOOST_AUTO_TEST_CASE(DeflateFloatTestNonPolished)
{
	//Insert your code here!
	polynomial< float > p{{float(159720),float(-3751),float(-66),float(1)}};
	firstPol<float>(p);

	firstPol< std::complex<float> >(p);

}

BOOST_AUTO_TEST_CASE(DeflateDoubleTestNonPolished)
{
	//Insert your code here!
	polynomial< double> p{{double(159720),double(-3751),double(-66),double(1)}};
	firstPol<double>(p);

	firstPol< std::complex<double> >(p);
}



BOOST_AUTO_TEST_CASE(Deflate2FloatTestNonPolished)
{
	//Insert your code here!
	/*
	polynomial< float> p{{float(9),float(0),float(1)}};
	firstPol2<float>(p);
	*/
}

BOOST_AUTO_TEST_CASE(Deflate2DoubleTestNonPolished)
{
	//Insert your code here!
	/*
	polynomial< double> p{{double(9),double(0),double(1)}};
	firstPol2<double>(p);
	*/
}

