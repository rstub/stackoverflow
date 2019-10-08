#include <Rcpp.h>
#include "foo.h"

// [[Rcpp::export]]
double foo(double x) {
    return namefunction(x);
}