#include <Rcpp.h>

extern "C" {
    double cfunction(double (*input_function)(const double&)) {
        return input_function(42);
    }
}

namespace {
std::unique_ptr<Rcpp::Function> func;
}

double input_function(const double &x) {
    Rcpp::NumericVector result = (*func)(x);
    return result(0);
}


// [[Rcpp::export]]
double rfunction(Rcpp::Function F){
    func = std::make_unique<Rcpp::Function>(F);
    return cfunction(input_function);
}

/*** R
rfunction(sqrt)
rfunction(log)
*/
