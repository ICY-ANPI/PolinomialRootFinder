#ifndef COMPLEX_SUPPORT_H
#define COMPLEX_SUPPORT_H

#include <type_traits>
#include <complex>
#include <iostream>

//complementary approach to specialization one would be to use function overloading
template <template <class...> class TT, class... Args>
std::true_type is_tt_impl(TT<Args...>);
template <template <class...> class TT>
std::false_type is_tt_impl(...);

template <template <class...> class TT, class T>
using is_tt = decltype(is_tt_impl<TT>(std::declval<typename std::decay<T>::type>()));


template <class T>
typename std::enable_if<is_tt<std::complex, T>::value>::type printCoefficient(T t) {
	if (t.imag() && t.real())
		std::cout << "(" << t.real() << " + " << t.imag() << "i)";
	else if(t.imag())
		std::cout  << ""<< t.imag() << "i";
	else
		std::cout << t.real();
}

template <class T>
typename std::enable_if<!is_tt<std::complex, T>::value>::type printCoefficient(T t) {
    std::cout << t;
}

template <class T>
bool isZero(T t);

template <class T>
typename std::enable_if<is_tt<std::complex, T>::value>::type isZero(T t) {
	return t.real() == T(0) && t.imag() == T(0);
}

template <class T>
typename std::enable_if<!is_tt<std::complex, T>::value>::type isZero(T t) {
	return t == T(0);
}



#endif //COMPLEX_SUPPORT_H
