#include <Rcpp.h>

// Custom class
class Double {
public:
    Double( double v ) : value(v) {}
    double square() {return value*value;}
private:
    double value;
};

RCPP_MODULE(double_cpp) {
    using namespace Rcpp;
    
    class_<Double>("Double")
        .constructor<double>("Wraps a double")
        .method("square", &Double::square, "square of value")
    ;
}

/***R
(d1 <- new(Double, 5.4))
d1$square()
*/