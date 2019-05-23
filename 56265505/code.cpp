#include <Rcpp.h>
// [[Rcpp::plugins("cpp11")]]
// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
// [[Rcpp::depends(RcppZiggurat)]]
#include <Ziggurat.h>

static Ziggurat::Ziggurat::Ziggurat zigg;

using namespace RcppParallel;

struct Norm : public Worker
{   
  int input;
  
  // saved draws
  RVector<double> draws;
  
  // constructors
  Norm(const int input, Rcpp::NumericVector draws)
    : input(input), draws(draws) {}
  
  void operator()(std::size_t begin, std::size_t end) {
    for (std::size_t i = begin; i < end; i++) {
      draws[i] = zigg.norm();
    }
  }
};

// [[Rcpp::export]]
Rcpp::NumericVector parallelDraws(int x) {
  
  // allocate the output vector
  Rcpp::NumericVector draws(x);
  
  // declare the Sum instance 
  Norm norm(x, draws);
  
  // call parallelFor to start the work
  parallelFor(0, x, norm);
  
  // return the draws
  return draws;
};

// [[Rcpp::export]]
Rcpp::NumericVector serialDraws(int x) {
  
  // allocate the output vector
  Rcpp::NumericVector draws(x);
  
  for (int i = 0; i < x; i++) {
    draws[i] = zigg.norm();
  }
  
  // return the draws
  return draws;
};

/*** R
library(microbenchmark)
microbenchmark(parallelDraws(1e5), serialDraws(1e5), rnorm(1e5))
*/
