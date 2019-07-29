#include <Rcpp.h>

// [[Rcpp::export]]
Rcpp::LogicalVector identifyValidSignalsTest(Rcpp::DatetimeVector & dtvopen) {
    Rcpp::Datetime dtv("2000-01-01 00:00:00");
    return dtv > dtvopen;
}


/***R
dates <- c(Sys.time(), as.POSIXct("1999-01-01"))
identifyValidSignalsTest(dates)
*/
