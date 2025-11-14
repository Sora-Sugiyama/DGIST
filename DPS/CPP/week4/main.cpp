//
//  main.cpp
//  dpslang
//
//  Created by Sora Sugiyama on 11/1/25.
//

#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <cstdint>
#include "variable.hpp"

void kernelMode(){
    loop:{
        std::cout<<">";
        std::string cmd,tmp;
        std::getline(std::cin,cmd);
        std::stringstream ss(cmd);
        
        cmd.clear();
        while(ss>>tmp){
            cmd+=tmp;
        }
        
        if(cmd=="exit")return;
        
        if(cmd.substr(0,3)=="let"){
            if(cmd.substr(3,3)=="int"){
                std::stringstream pars(std::string(cmd.begin()+6,cmd.end()));
                std::string lhs;
                int32_t rhs;
                std::getline(pars,lhs,'=');
                pars>>rhs;
                varInt32.addVar(lhs,rhs);
            }
            /* You can implement more */
        }else if(cmd.substr(0,5)=="print"){
            if(cmd[5]=='\"'){
                std::string line(cmd.begin()+6,cmd.end());
                std::stringstream pars(line);
                std::string str,res;
                pars>>str;
                for(std::size_t i=0;i<str.size();i++){
                    if(str[i]=='\"')break;
                    if(i>0&&str[i]=='d'&&str[i-1]=='%'){
                        pars>>tmp;
                        res.pop_back();
                        res+=std::to_string(varInt32.getVal(tmp));
                        continue;
                    }
                    
                    /* You can implement more */
                    
                    res.push_back(str[i]);
                }
                std::cout<<res<<std::endl;
            }
        }
        
        goto loop;
    }
}

int main(int argc, const char * argv[]) {
    switch(argc){
        case 1:{
            kernelMode();
            break;
        }
        case 2:{
            std::cout<<"NOT IMPLEMENTED YET\n";
            return 1;
        }
    }
    return 0;
}


/*
 cpp 연습할 때
 
 프로그램
 
 
 simple language
 --> 인터렉션 하면서 어떤 결과가 나올 수 있는
 */
//+4
