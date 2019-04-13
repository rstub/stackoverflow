#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

// [[Rcpp::export]]
Rcpp::NumericVector subset() {
  Rcpp::NumericVector in = {1.0, 2.0, 3.0, 4.0};
  Rcpp::LogicalVector mask = {false, true, true, true};
  return in[mask];
}


// [[Rcpp::export]]
Rcpp::NumericVector subset2() {
  Rcpp::NumericVector in = Rcpp::runif(10);
  Rcpp::LogicalVector mask = in > 0.5;
  return in[mask];
}

/*** R
subset()
set.seed(42)
subset2()
*/
