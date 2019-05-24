#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
NumericMatrix imembrandc(int n, int k) {
  NumericMatrix u(n, k);
  for (int i = 0; i < n; ++i) {
    NumericVector row = runif(k - 1);
    row.push_back(0.0);
    row.push_back(1.0);
    u(i, _) = diff(row.sort());
  }
  return u;
}

/*** R
set.seed(42)
res = imembrandc(n = 10, k = 5)
rowSums(res)
rowSums(res) == 1
all.equal(rowSums(res),rep(1, nrow(res)))
*/
