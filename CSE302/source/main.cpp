//
//  main.cpp
//  CSE302
//
//  Created by Sora Sugiyama on 3/17/25.
//

#include <iostream>
#include <vector>
#include "linAlge/matrix.h"
#include "MNIST/readMNIST.h"
#include "optimizer/GradientDescent.h"
#include "model/objFunction/MSE.h"
#include "model/regularization/L1L2.h"
#include "model/actFunction/logisticAct.h"

int main(int argc, const char * argv[]) {
    auto test=MNIST::readMNIST("CSE302/MNIST/archive/t10k-images.idx3-ubyte","CSE302/MNIST/archive/t10k-labels.idx1-ubyte",10);
    auto train=MNIST::readMNIST("CSE302/MNIST/archive/train-images.idx3-ubyte","CSE302/MNIST/archive/train-labels.idx1-ubyte",40);
    
    linAlge::mat X(40,784),w(784,10),y(40,10);
    for(int i=0;i<40;i++){
        for(int j=0;j<784;j++)X(i,j)=train[i].first[j];
        y(i,train[i].second)=1;
    }
    std::vector<linAlge::mat>W={w};
    std::cout<<model::objFunction::calcMSE(X,W,y,model::actFunction::logistic)<<std::endl;
    
    optimizer::gradientDescent(
                               model::objFunction::MSE,
                               model::objFunction::dMSE,
                               model::actFunction::logistic,
                               model::actFunction::dlogistic,
                               W,
                               X,
                               y,
                               0.01
                               );
    std::cout<<model::objFunction::calcMSE(X,W,y,model::actFunction::logistic)<<std::endl;
    
    std::cout<<"COMPILED"<<std::endl;
    return 0;
}

