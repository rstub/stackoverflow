#include <Rcpp.h>

// Custom class
class Double {
public:
    Double( double v ) : value(v) {}
    double square() {return value*value;}
private:
    double value;
};

// Make the class visible
RCPP_EXPOSED_CLASS(Double)

// [[Rcpp::export]]
Double makeDouble( double x ) {
    Double d(x);
    return d;
}

RCPP_MODULE(double_cpp) {
    using namespace Rcpp;
    
    class_<Double>("Double")
        .method("square", &Double::square, "square of value")
    ;
}

/***R
(d1 <- makeDouble(5.4))
d1$square()
*/