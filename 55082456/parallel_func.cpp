#include <RcppArmadillo.h>
#include <RcppParallel.h>
#include "ExampleInternal.h"
using namespace ExampleInternal;

// [[Rcpp::export]]
arma::vec Parallelfunc(int Len_in){

  arma::vec input = arma::regspace(0, 500);
  arma::vec output(Len_in);

  ExampleInternal::PARALLEL_WORKER parallel_woker(input, output);
  parallelFor( 0, Len_in, parallel_woker);
  return output;
}
