#include <Rcpp.h>

// [[Rcpp::export]]
Rcpp::ComplexVector foo(Rcpp::ComplexVector v) {
    std::complex<double>* F = reinterpret_cast<std::complex<double>*>(v.begin());
    int N = v.length();
    // do something with F
    Rcpp::ComplexVector Fd(reinterpret_cast<Rcomplex*>(F), 
                     reinterpret_cast<Rcomplex*>(F + N));
    return Fd;
}

// [[Rcpp::export]]
std::vector<std::complex<double>> bar(std::vector<std::complex<double>> v) {
    std::complex<double>* F = v.data();
    int N = v.size();
    // do something with F
    std::vector<std::complex<double>> Fd(F, F + N);
    return Fd;
}


int finufft1d1(int M, double *xd, std::complex<double> *cd, int N, std::complex<double> *Fd) {
    return 0;
}

// [[Rcpp::export]]
std::vector<std::complex<double>> finufft(int M, 
                                          std::vector<double> x, 
                                          std::vector<std::complex<double>> c, 
                                          int N) {
    
    // allocate output array for the finufft routine:
    std::vector<std::complex<double>> F(N);
    // Change vector inputs from R types to C++ types
    double* xd = x.data();
    std::complex<double>* cd = c.data();      
    std::complex<double>* Fd = F.data();      
    
    int ier = finufft1d1(M, xd, cd, N, Fd);

    return F;
}



/*** R
set.seed(42)
foo(runif(4)*(1+1i))
bar(runif(4)*(1+1i))
*/
