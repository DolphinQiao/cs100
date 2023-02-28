#ifndef FUNCTIONAL_FORMS_HPP_
#define FUNCTIONAL_FORMS_HPP_

#include <stdlib.h>
#include <utility>
#include <math.h>

/* For all lambda functions below, if you are not clear how they work, please refer to the given example for details. */


/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1+f2)(m) as first, and (d(f1+f2)/dx)(m) as second.
 */
auto derSum = []( auto f1, auto f2 ){
  //add your code here ...
	  return [f1,f2](auto m)mutable 
  {
    return std::make_pair(f1(m).first + f2(m).first, f1(m).second + f2(m).second);
  };
};


/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1-f2)(m) as first, and (d(f1-f2)/dx)(m) as second.
 */
auto derSub = []( auto f1, auto f2 ){
  //add your code here ...
	  return [f1,f2](auto m)mutable
  {
    return std::make_pair(f1(m).first - f2(m).first, f1(m).second - f2(m).second);
  };
};

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1*f2)(m) as first, and (d(f1*f2)/dx)(m) as second.
 */
auto derMul = []( auto f1, auto f2 ) {
  //add your code here ...
	  return ([f1,f2](auto m)mutable{return std::make_pair(f1(m).first * f2(m).first, f1(m).second * f2(m).first);});
};

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f1/f2)(m) as first, and (d(f1/f2)/dx)(m) as second.
 */
auto derDiv = []( auto f1, auto f2 ){
  //add your code here ...
  return [f1,f2](auto m)mutable
  {
    return std::make_pair(f1(m).first / f2(m).first, f1(m).second / f2(m).first);
  };
};

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has (f2(f1))(m) as first, and (d(f2(f1))/dx)(m) as second.
 */
auto derComp = []( auto f1, auto f2 ){
  //add your code here ...
  return [f1,f2](auto m )mutable
  {
	  return std::make_pair(f2.eval(f1.eval(m)),f2.der().eval(f1.eval(m)));
  };
};

/*
 * Return a lambda function that takes one parameter (m) and returns a pair<double, double> that:
 * has [(f1)(m)]^exp as first, and (d(f1^exp)/dx)(m) as second.
 */
auto derPow = []( auto f, int exp ){
  //add your code here ...
  return [f,exp](auto m )mutable
  {
    auto ans = f(m).first;
    for (int i = 1; i < exp; ++i) ans *= f(m).first;
    return std::make_pair(ans, ans / f(m).first * f(m).second);
  };
};

#endif