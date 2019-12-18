#include <Rcpp.h>

// Custom class
class Double {
public:
    Double( double v ) : value(v) {}
    double square() {return value*value;}
private:
    double value;
};

// [[Rcpp::export]]
Rcpp::XPtr<Double> makeDouble(double value) {
    Double* pd = new Double(value);
    Rcpp::XPtr<Double> ptr(pd);
    return ptr;
}

// [[Rcpp::export]]
double squareDouble(Rcpp::XPtr<Double> value) {
    return value.get()->square();
}

/***R
(d2 <- makeDouble(5.4))
squareDouble(d2)
*/