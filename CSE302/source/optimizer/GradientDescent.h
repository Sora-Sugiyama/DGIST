//
//  GradientDescent.h
//  CSE302
//
//  Created by Sora Sugiyama on 3/26/25.
//

#ifndef GradientDescent_h
#define GradientDescent_h

#include "../linAlge/matrix.h"
#include <vector>
#include <cstddef>
#include <iostream>
#include <stack>
#include <cmath>

namespace optimizer{

using u32=uint_fast32_t;

template<
class F,
class DF,
class Act,
class DAct
>void gradientDescent(
                      F loss,
                      DF dloss,
                      Act actf,
                      DAct dactf,
                      std::vector<linAlge::mat>&coef,
                      linAlge::mat &X,
                      linAlge::mat &Y,
                      const double theta,
                      u32 gn=10000,const u32 &printCur=1<<30){

    u32 i=0,ii=0,jj=0;

    for(i=1;i<=gn;i++){
        std::stack<linAlge::mat>log;
        linAlge::mat x=X;

        // Forward Prop
        for(linAlge::mat &w:coef){
            log.push(x);
            x=x*w;
            for(ii=0;ii<x.n;ii++){
                for(jj=0;jj<x.m;jj++)x(ii,jj)=actf(x(ii,jj));
            }
        }

        if((i-1)%printCur==0){
            std::cout<<"End of "<<i-1<<"th step ; loss: "<<loss(x,Y)<<std::endl;
        }

        x=dloss(x,Y);
        for(ii=0;ii<x.n;ii++){
            for(jj=0;jj<x.m;jj++){
                x(ii,jj)*=dactf(x(ii,jj));
            }
        }


        // Backward Prop
        for(auto it=coef.rbegin();it!=coef.rend();it++){
            linAlge::mat Z=log.top().T();log.pop();
            linAlge::mat &w=*it;
            x=Z*x;

            for(ii=0;ii<x.n;ii++){
                for(jj=0;jj<x.m;jj++){
                    w(ii,jj)-=theta*x(ii,jj);
                    x(ii,jj)*=dactf(x(ii,jj));
                }
            }
        }
    }
}

}

#endif /* GradientDescent_h */
