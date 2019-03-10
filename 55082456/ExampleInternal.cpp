// [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>
//  [[Rcpp::plugins(cpp11)]]
#include <random>
#include "ExampleInternal.h"

using namespace RcppParallel;
using namespace ExampleInternal;

namespace ExampleInternal{

  PARALLEL_WORKER::PARALLEL_WORKER(const arma::vec &input, arma::vec &output) : input(input), output(output) {}

  void PARALLEL_WORKER::operator()(std::size_t begin, std::size_t end){


    std::mt19937 engine(1);

    // Create a loop that runs through a selected section of the total Boot_reps
    for( std::size_t k = begin; k < end; k ++){
      engine.seed(k);
      arma::vec index = input;
      std::shuffle( index.begin(), index.end(), engine);

      output[k] = ExampleInternal::myfunc3(index);
    }
  }


} //Close Namespace
