//  [[Rcpp::depends(RcppArmadillo)]]
#include <RcppArmadillo.h>
using namespace Rcpp;

// [[Rcpp::export]]
List arma_test(const arma::vec& Delta,
	       const arma::mat& delta,
	       const arma::mat& rx) {
  int l = delta.n_cols;
  List c(l);

  for (int i = 0; i < l; ++i) {
    c(i) = rx.each_col() % (Delta / (1 + delta.col(i)));
  }
  
  return c;  
}

// [[Rcpp::export]]
List rcpp_test(NumericVector Delta, 
               NumericMatrix delta, 
               NumericMatrix rx) {

  int n = Delta.length();
  int m = rx.ncol();

  List c(delta.ncol()); 
  NumericMatrix c1;
  for(int i = 0; i < delta.ncol(); ++i){
    c1 = NumericMatrix(n, m);
    for(int k = 0; k < n; ++k){
      double tmp = Delta[k] / (1 + delta(k, i));
      for(int j = 0; j < m; ++j){
        c1(k, j) = rx(k, j) * tmp; 
      }
    }
    c(i) = c1;
  }

  return c;

}

/*** R
test <- function(Delta, delta, rx){

  const <- list()
  for(i in 1:ncol(delta)){
    const[[i]] <- rx * (Delta / (1 + delta[, i]))
  }

  const

}

n <- 50000
Delta <- exp(rnorm(n))
delta <- exp(matrix(rnorm(n * 5), nrow = n))
rx <- matrix(rnorm(n * 20), nrow = n)
bench::mark(test(Delta, delta, rx),
            arma_test(Delta, delta, rx),
            rcpp_test(Delta, delta, rx))
 */
