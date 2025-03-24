//
//  main.cpp
//  CSE302
//
//  Created by Sora Sugiyama on 3/17/25.
//

#include <iostream>
#include "linAlge/matrix.h"
#include "bmp/bmplot.h"
#include "optimizer/GA.h"
#include <cmath>
#include <random>

int main(int argc, const char * argv[]) {
    BMP::fnct_plotter tmp(0,1,-1.5,1.5,2048,1200);
    auto fp=[](double x)->double{
        return sin(2*M_PI*x);
    };
    tmp.plotFnct(fp,0,1,2,0,255,0);
    std::vector<std::pair<double,double> >P;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> gd{0.0,0.1};
    
    std::uniform_real_distribution<double>urd(0,1);
    for(int i=0;i<10;i++){
        double x=urd(gen);
        P.push_back({x,fp(x)+gd(gen)});
    }
    
    tmp.plotScatter(P,10,255,200,100);
    
    std::vector<double>coef;
    
    // Define objective function. (In this case, MSE)
    auto objf=[&P](std::vector<double>&C)->double{
        double ret=0;
        for(auto &p:P){
            double cur=0,x=1;
            for(double &c:C){
                cur+=c*x;
                x*=p.first;
            }
            ret+=(cur-p.second)*(cur-p.second);
        }
        return ret/(C.size());
    };
    
    auto polyf=[&coef](double x)->double{
        double ret=0,t=1;
        for(auto &c:coef){
            ret+=t*c;
            t*=x;
        }
        return ret;
    };
    
    std::uniform_real_distribution<double>urd2(-0.01,0.01),urd3(-5,5);
    auto mut=[&gen,&urd2](std::vector<double>&C,const std::vector<double>&sup){
        for(int i=0;i<(int)sup.size();i++){
            C[i]=sup[i]+urd2(gen);
        }
    };
    
    auto init=[&gen,&urd3](std::vector<std::vector<double> >&Cs){
        for(auto &C:Cs){
            for(auto &c:C)c=urd3(gen);
        }
    };
    
    for(int k:{1,2,5,9,15}){
        coef.resize(k+1);
        optimizer::GA<std::vector<double>,double>(objf,mut,init,coef);
        for(auto &c:coef)std::cout<<c<<" ";
        std::cout<<"\n";
        tmp.plotFnct(polyf,0,1,2,k*123%256,k*10,255-k*10);
    }
    
    tmp.plot("","img.bmp");
    //p.plot("","img.bmp");
    return 0;
}

