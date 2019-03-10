#ifndef ExampleInternal_H
#define ExampleInternal_H

namespace ExampleInternal{

#include <RcppArmadillo.h>
#include <RcppParallel.h>

double myfunc3(arma::vec vec_in){

  int Len = arma::size(vec_in)[0];
  return (vec_in[0] +vec_in[1])/Len;
}

struct PARALLEL_WORKER : RcppParallel::Worker{};

}


#endif
