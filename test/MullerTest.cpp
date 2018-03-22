#include <boost/test/unit_test.hpp>
#include "Muller.hpp"
#include "Deflate.hpp"
#include <complex>

#include "ComplexSupport.hpp"
#include "PrintPolynomial.hpp"


template<typename T>
void evaluate(polynomial<T> p){
	T presicion = 0.1;
	for (int x = 0; x < 10; x++) {
		//printExpression(p);
		int convergencia = 0;
		std::vector<T> v = mullerTest< T >(p, T(presicion),convergencia);
		/*
		cout << "roots: ";
		for (int i = 0; i < v.size(); i++) {
			printCoefficient(v[i]);
			cout << " ";
		}
		cout<< endl;
		*/
		for (int i = 0; i < v.size(); i++) {
			T a = p.evaluate(v[i]);
			BOOST_CHECK(abs(a) < abs(presicion));
		}
		presicion /= 10.0;
	}
}








//complex simple presicion

BOOST_AUTO_TEST_CASE(ComplexCaseSimplePresicion)
{

	polynomial< float > p{{float(159720),float(-3751),float(-66),float(1)}};
	evaluate<complex<float>>(p);
}


BOOST_AUTO_TEST_CASE(ComplexCaseSimplePresicion2doPolynomial)
{
	polynomial< float > p{{float(-18),float(9),float(7),float(1),float(1)}};
	evaluate<complex<float>>(p);
}

BOOST_AUTO_TEST_CASE(ComplexCaseSimplePresicion3rdPolynomial)
{

	polynomial< float > p{{float(504),float(128),float(71),float(16),float(1)}};
	evaluate<complex<float>>(p);
}


//Real simple presicion

BOOST_AUTO_TEST_CASE(RealCaseSimplePresicion)
{

	polynomial< float > p{{float(159720),float(-3751),float(-66),float(1)}};
	evaluate<float>(p);
}


BOOST_AUTO_TEST_CASE(RealCaseSimplePresicion2doPolynomial)
{
	polynomial< float > p{{float(-18),float(9),float(7),float(1),float(1)}};
	evaluate<float>(p);
}

BOOST_AUTO_TEST_CASE(RealCaseSimplePresicion3rdPolynomial)
{

	polynomial< float > p{{float(504),float(128),float(71),float(16),float(1)}};
	evaluate<float>(p);
}











//complex double presicion

BOOST_AUTO_TEST_CASE(ComplexCaseDoublePresicion)
{

	polynomial< double > p{{double(159720),double(-3751),double(-66),double(1)}};
	evaluate<complex<double>>(p);
}


BOOST_AUTO_TEST_CASE(ComplexCaseDoublePresicion2doPolynomial)
{
	polynomial< double > p{{double(-18),double(9),double(7),double(1),double(1)}};
	evaluate<complex<double>>(p);
}

BOOST_AUTO_TEST_CASE(ComplexCaseDoublePresicion3rdPolynomial)
{

	polynomial< double > p{{double(504),double(128),double(71),double(16),double(1)}};
	evaluate<complex<double>>(p);
}


//Real double presicion

BOOST_AUTO_TEST_CASE(RealCaseDoublePresicion)
{

	polynomial< double > p{{double(159720),double(-3751),double(-66),double(1)}};
	evaluate<double>(p);
}


BOOST_AUTO_TEST_CASE(RealCaseDoublePresicion2doPolynomial)
{
	polynomial< double > p{{double(-18),double(9),double(7),double(1),double(1)}};
	evaluate<double>(p);
}

BOOST_AUTO_TEST_CASE(RealCaseDoublePresicion3rdPolynomial)
{

	polynomial< double > p{{double(504),double(128),double(71),double(16),double(1)}};
	evaluate<double>(p);
}
