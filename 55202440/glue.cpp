//glue.cpp

#include <RcppCommon.h>

class MyData
{
public:
  MyData() = default;
};
RCPP_EXPOSED_CLASS(MyData)

class MyModel
{
public:
  MyModel() = default;
  void train(const MyData& data) { Rcpp::Rcout << "training model... " << std::endl; };
};


#include <Rcpp.h>

// Expose MyData
RCPP_MODULE(MyData){
  Rcpp::class_<MyData>("MyData")
  .constructor()
  ;
}

// Expose MyModel
RCPP_MODULE(MyModel){
  Rcpp::class_<MyModel>("MyModel")
  .constructor()
  .method("train", &MyModel::train)
  ;
}

/***R
myData <- new(MyData)
myModel <- new(MyModel)
myModel$train(myData) 
 */
