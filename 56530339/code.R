library(glmnet)

set.seed(1)
X = matrix(rnorm(1e3 * 201), 1e3, 201)
beta = -100:100
y = X%*%beta + rnorm(1e3)


# set seed since cv.glmnet uses random numbers
set.seed(1)
cvfit = cv.glmnet(X, y, alpha = 1)
coefs = coef(cvfit, s = "lambda.min")

# set seed since cv.glmnet uses random numbers
set.seed(1)
my.glmnet <- function(x, y, alpha) {
    cvfit <- cv.glmnet(x, y, alpha = alpha)
    coef(cvfit, s = "lambda.min")
}
Rcpp::cppFunction(depends = "RcppArmadillo", "
arma::sp_mat f_cpp(const arma::mat &x, const arma::vec &y, double alpha, Rcpp::Function f_R) {
    arma::sp_mat coef = Rcpp::as<arma::sp_mat>(f_R(x, y, alpha));
    return coef;
}", )
coefs2 <- f_cpp(X, y, alpha = 1, my.glmnet)

all(coefs - coefs2 == 0)
