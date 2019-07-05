#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]
// [[Rcpp::depends(BH)]]
#include <boost/math/tools/minima.hpp>

class phi_rcpp {
private:
    double mean;
    double beta;
public:
    phi_rcpp(double _mean, double _beta) : mean(_mean), beta(_beta) {}
    double operator()(const double &x) {
        double y = x - mean;
        return (2*beta*beta*pow(y, 6))-(3*beta*y*y);
    }
};

template<class T>
class negate : public T {
public:
    using T::T;
    double operator() (const double &x) {
        return - T::operator()(x);
    }
};

// [[Rcpp::export]]
Rcpp::List bound_phi_rcpp(const double &mean,
                          const double &beta,
                          const double &lower,
                          const double &upper) {
    using boost::math::tools::brent_find_minima;
    const int double_bits = std::numeric_limits<double>::digits;
    phi_rcpp func(mean, beta);
    negate<phi_rcpp> nfunc(mean, beta);
    std::pair<double, double> min = brent_find_minima(func, lower, upper, double_bits);
    std::pair<double, double> max = brent_find_minima(nfunc, lower, upper, double_bits);

    double at_upper = func(upper);
    double at_lower = func(lower);
    
    return Rcpp::List::create(Rcpp::Named("low_bound") = std::min(min.second, std::min(at_upper, at_lower)),
                              Rcpp::Named("up_bound") =  std::max(max.second, std::max(at_upper, at_lower)));
}

/*** R
phi_R <- function(x, mean = 0, beta) {
    return(2*(beta^2)*((x-mean)^6) - 3*beta*((x-mean)^2))
}

bound_phi_R <- function(beta, mean = 0, lower, upper) {
    # finding maxima and minimma in the interval
    maxim <- optimise(function(x) phi_R(x, mean, beta), interval = c(lower, upper), 
                      maximum = TRUE)$objective
    minim <- optimise(function(x) phi_R(x, mean, beta), interval = c(lower, upper), 
                      maximum = FALSE)$objective
    
    # checking end points
    at_lower <- phi_R(lower, mean, beta)
    at_upper <- phi_R(upper, mean, beta)
    
    # obtaining upper and lower bounds
    upper_bound <- max(maxim, at_lower, at_upper)
    lower_bound <- min(minim, at_lower, at_upper)
    
    return(list('low_bound' = lower_bound, 'up_bound' = upper_bound))
}


set.seed(42)
limits <- runif(2, -2, 2)
bench::mark(cpp = bound_phi_rcpp(beta = 1/4, mean = 0, lower = min(limits), upper = max(limits)),
            R = bound_phi_R(beta = 1/4, mean = 0, lower = min(limits), upper = max(limits)))

*/
