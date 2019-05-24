#include <Rcpp.h>
// [[Rcpp::plugins("cpp11")]]
// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
// [[Rcpp::depends(RcppZiggurat)]]
#include <Ziggurat.h>


using namespace RcppParallel;

struct Norm : public Worker
{   
  // saved draws
  RVector<double> draws;
  
  // constructors
  Norm(Rcpp::NumericVector draws)
    : draws(draws) {}
  
  void operator()(std::size_t begin, std::size_t end) {
    Ziggurat::Ziggurat::Ziggurat zigg(end);
    for (std::size_t i = begin; i < end; i++) {
      draws[i] = zigg.norm();
    }
  }
};

// [[Rcpp::export]]
Rcpp::NumericVector parallelDraws(int x) {
  // allocate the output vector
  Rcpp::NumericVector draws(Rcpp::no_init(x));
  Norm norm(draws);
  parallelFor(0, x, norm);
  return draws;
}

// [[Rcpp::export]]
Rcpp::NumericVector serialDraws(int x) {
  // allocate the output vector
  Rcpp::NumericVector draws(Rcpp::no_init(x));
  Ziggurat::Ziggurat::Ziggurat zigg(42);
  for (int i = 0; i < x; i++) {
    draws[i] = zigg.norm();
  }
  return draws;
}

/*** R
bench::mark(parallelDraws(1e5), serialDraws(1e5), check = FALSE, min_iterations = 10)[,1:5]
bench::mark(parallelDraws(1e8), serialDraws(1e8), check = FALSE, min_iterations = 10)[,1:5]
*/
