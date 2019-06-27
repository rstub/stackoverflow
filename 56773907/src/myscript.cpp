// -*- mode: C++; c-indent-level: 4; c-basic-offset: 4; indent-tabs-mode: nil; -*-

#include "string"
#include "RcppArmadillo.h"

// [[Rcpp::depends(RcppArmadillo)]]

using namespace Rcpp;

// [[Rcpp::export]]
SEXP GetBBoxesAsList( SEXP x ){
    // determines object type and adapts the search of coordinates
    S4 obj(x) ;
    std::string nameList; 
    std::string nameSubList;
    if(Rf_inherits(x, "SpatialLines") || Rf_inherits(x, "SpatialLinesDataFrame")){
        nameList = "lines";
        nameSubList = "Lines";
    }else if(Rf_inherits(x, "SpatialPolygons") || Rf_inherits(x, "SpatialPolygonsDataFrame")){
        nameList = "polygons";
        nameSubList = "Polygons";
    }else{
        ::Rf_error("In GetBBoxes, class must be Spatial[Polygons|Lines][DataFrame]");
    }
    List a =  obj.slot(nameList);
    
    // count items
    int nPol = a.length();
    // NumericMatrix bboxes(nPol,4);
    List bboxes(nPol);
    
    // get the range
    for(int iPol = 0;iPol < nPol;iPol++){
        S4 pol = a(iPol);
        List b = pol.slot(nameSubList);
        
        double minX = std::numeric_limits<double>::infinity();
        double maxX = -std::numeric_limits<double>::infinity();
        double minY = std::numeric_limits<double>::infinity();
        double maxY = -std::numeric_limits<double>::infinity();
        
        for(int iSP = 0; iSP < b.length(); iSP++){
            S4 subPol = b(iSP);
            NumericMatrix coords = subPol.slot("coords");
            // X
            NumericVector rangeX = range(coords(_,0));
            if(rangeX(0)<minX) minX = rangeX(0);
            if(rangeX(1)>maxX) maxX = rangeX(1);
            // Y
            NumericVector rangeY = range(coords(_,1));
            if(rangeY(0)<minY) minY = rangeY(0);
            if(rangeY(1)>maxY) maxY = rangeY(1);
        }
        
        NumericVector bbox(4);
        bbox(0) = minX;
        bbox(1) = minY;
        bbox(2) = maxX;
        bbox(3) = maxY;
        bboxes(iPol) = bbox;
        // bboxes(iPol,0) = minX;
        // bboxes(iPol,1) = minY;
        // bboxes(iPol,2) = maxX;
        // bboxes(iPol,3) = maxY;
    }
    // Rcpp::DataFrame BBoxes = Rcpp::DataFrame::create(Rcpp::Named("minX")=bboxes(_,0),
    //         Rcpp::Named("minY")=bboxes(_,1),
    //         Rcpp::Named("maxX")=bboxes(_,2),
    //         Rcpp::Named("maxY")=bboxes(_,3));
    
    return bboxes;// BBoxes;
}