//
//  variable.hpp
//  dpslang
//
//  Created by Sora Sugiyama on 11/1/25.
//

#ifndef variable_hpp
#define variable_hpp

#include <iostream>
#include <unordered_map>
#include <string>
#include <stack>


template<class T>
class VarManager{
    std::unordered_map<std::string,std::unique_ptr<T> >vars;
    
public:
    void addVar(const std::string &varName, T val){
        vars[varName]=std::make_unique<T>(val);
    }
    
    T getVal(const std::string &varName){
        if(vars[varName]==nullptr){
            std::cout<<"No such varaible\n"<<std::endl;
            return T();
        }
        return *(vars[varName]);
    }
    
    void clear(){
        std::stack<std::string_view>garb;
        for(auto &it:vars){
            if(it->second==nullptr)garb.push(it->first);
        }
        while(!garb.empty()){
            vars.erase(garb.top());
            garb.pop();
        }
    }
};

// extern : 선언만 해두겠다.
extern VarManager<float_t>varfloat;
extern VarManager<char16_t>varUTF16;
extern VarManager<char32_t>varUTF32;
extern VarManager<int32_t>varInt32;
extern VarManager<int64_t>varInt64;
extern VarManager<uint32_t>varUInt32;
extern VarManager<uint64_t>varUInt64;
extern VarManager<double_t>varDouble;

#endif /* variable_hpp */
