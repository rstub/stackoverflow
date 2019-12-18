#include <Rcpp.h>

// Custom class
class Double {
public:
    Double( double v ) : value(v) {}
    double square() {return value*value;}
private:
    double value;
};

Double* makeDouble( double x ) {
    Double* pd = new Double(x);
    return pd;
}

RCPP_MODULE(double_cpp) {
    using namespace Rcpp;
    
    class_<Double>("Double")
        .factory<double>(makeDouble, "Wraps a double")
        .method("square", &Double::square, "square of value")
    ;
}

/***R
(d1 <- new(Double, 5.4))
d1$square()
*/