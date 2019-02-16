#include <Rcpp.h>
// [[Rcpp::plugins(openmp)]]
#include <omp.h>

// [[Rcpp::depends(RcppParallel)]]
#include <RcppParallel.h>

using namespace Rcpp;

// [[Rcpp::export]]
NumericMatrix my_matrix(int I, int J, int nthreads) {
  NumericMatrix A(I,J);
  // create a thread safe accessor for A
  RcppParallel::RMatrix<double> a(A);
  int tid;
  omp_set_num_threads(nthreads);
#pragma omp parallel for private(tid)
  for(int j = 0; j < J; j++) {
    for(int i = 0; i < I; i++) {
      tid = omp_get_thread_num();
      a(i, j) = tid ;
    }
  }

  return A;
}


/*** R
set.seed(42)
my_matrix(12,10,5)
*/
