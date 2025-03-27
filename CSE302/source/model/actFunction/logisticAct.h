//
//  logisticAct.h
//  CSE302
//
//  Created by Sora Sugiyama on 3/26/25.
//

#ifndef logisticAct_h
#define logisticAct_h

#include <cmath>

namespace model{

namespace actFunction{

double logistic(double x){
    x=50>x?x:50;
    x=-50<x?x:50;
    return 1/(1+exp(-x));
}

double dlogistic(double x){
    x=50>x?x:50;
    x=-50<x?x:50;
    const double ex=exp(-x);
    return ex/(ex*ex+ex+ex+1);
}

}

}

#endif /* logisticAct_h */
