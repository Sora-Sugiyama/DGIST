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
    auto test=MNIST::readMNIST("MNIST/archive/t10k-images.idx3-ubyte","MNIST/archive/t10k-labels.idx1-ubyte",600);
    auto train=MNIST::readMNIST("MNIST/archive/train-images.idx3-ubyte","MNIST/archive/train-labels.idx1-ubyte",600);

    linAlge::mat X(600,784),w(784,10),y(600,10);
    for(int i=0;i<600;i++){
        for(int j=0;j<784;j++)X(i,j)=train[i].first[j];
        y(i,train[i].second)=1;
    }
    std::vector<linAlge::mat>W={w};
    std::cout<<model::objFunction::calcMSE(X,W,y,model::actFunction::logistic)<<std::endl;

    std::cout.precision(4);
    optimizer::gradientDescent(
                               model::objFunction::MSE,
                               model::objFunction::dMSE,
                               model::actFunction::logistic,
                               model::actFunction::dlogistic,
                               W,
                               X,
                               y,
                               0.005,
                               100,
                               10
                               );


    std::cout<<model::objFunction::calcMSE(X,W,y,model::actFunction::logistic)<<std::endl;


    return 0;
}

