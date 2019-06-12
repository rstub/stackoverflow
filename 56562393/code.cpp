#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

class Foo {
public:
    Foo() {Rcpp::stop("Disallowed default constructor");}
    Foo(int arg) {Rprintf("Foo OK\n");}
};

class Bar {
public:
    Bar() = delete;
    Bar(int arg) {Rprintf("Bar OK\n");}
};

RCPP_MODULE(mod) {
    
    Rcpp::class_<Foo>("Foo")
    .constructor("Disallowed default constructor")
    .constructor<int>("Intended 1-argument constructor")
    ;
    
    Rcpp::class_<Bar>("Bar")
    .constructor<int>("Intended 1-argument constructor")
    ;
} 

/*** R
# OK as expected:
f1 <- new(Foo, 1)
# Fails as expected:
tryCatch(f2 <- new(Foo), error = print)

# OK as expected:
b1 <- new(Bar, 1)
# Unexpectedly succeeds:
tryCatch(b2 <- new(Bar), error = print)
*/
