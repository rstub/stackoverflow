#include <Rcpp.h>
// [[Rcpp::depends(dqrng)]]
#include <xoshiro.h>
#include <convert_seed.h>
// [[Rcpp::plugins(cpp11)]]

namespace {
dqrng::xoshiro256plus rng{};
}

// [[Rcpp::export]]
void set_seed(Rcpp::IntegerVector seed) {
  rng.seed(dqrng::convert_seed<uint64_t>(seed));
}

// [[Rcpp::export]]
int rbinom01(int size) {
  if (!size) {
    return 0;
  }

  int result = 0;
  while (size >= 64) {
    result += __builtin_popcountll(rng());
    size -= 64;
  }

  result += __builtin_popcountll(rng() & ((1LLU << size) - 1));

  return result;
}

/*** R
set_seed(c(47, 11))
rbinom01(10)
rbinom01(10)
rbinom01(10)
*/
