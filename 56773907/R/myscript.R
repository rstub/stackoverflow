# sourceCpp("src/GetBBoxes.cpp")
# see src/GetBBoxes for GetBBoxesAsList
#' @export 
GetBBoxes <-function(sp,outType="data.frame"){
    out <- GetBBoxesAsList(sp)
    if(outType=="data.frame"){
        out <- data.frame(matrix(unlist(out),ncol=4,byrow=TRUE))
        names(out) <- c("minX","minY","maxX","maxY")
    }
    return(out)
}
