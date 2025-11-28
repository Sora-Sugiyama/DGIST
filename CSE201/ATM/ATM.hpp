//
//  ATM.hpp
//  term
//
//  Created by Sora Sugiyama on 11/28/25.
//

#ifndef ATM_hpp
#define ATM_hpp

#include "include.h"
#include "card.h"
#include "const.h"

inline u64 SESSION_NUM=0x15571556;
inline u64 TRANSACTION_NUM=0x23741557;

class ATM{
    str primaryBankName,serial;
    bool type,lang;
    
    struct Fund{
        std::array<u64,4>bill;
        Fund(std::array<u64,4>bill):bill(bill){}
        u64& N50K(){return bill[krw50k];}
        u64& N10K(){return bill[krw10k];}
        u64& N5K(){return bill[krw5k];}
        u64& N1K(){return bill[krw1k];}
    }fund;
    
    std::stringstream tsHistoryKR,tsHistoryEN;
public:
    ATM(str pbn="",str sn="",str t="",str l="",std::array<u64,4>initFund={}):primaryBankName(pbn),serial(sn),type(t=="Multi"),lang(l=="Bilingual"),fund(initFund){
        tsHistoryEN<<"TRANSACTION HISTORY OF ATM"<<sn<<"\n"<<part<<std::endl;
        tsHistoryKR<<"거래 내역; ATM "<<sn<<"\n"<<part<<std::endl;
    }
    str getSerial(){return serial;}
    bool isBi(){return lang;}
    bool isMulti(){return type;}
    str getBank(){return primaryBankName;}
    
    inline static bool VERIFY_PASSWORD(Card* bananana,const bool lang);
    bool DEPOSIT(Card *banana,const std::array<u64,4>&bill,const u64 check,const bool lang,std::stringstream &orange);
    bool WITHDRAWAL(Card *banana,const u64 amount,const bool lang,std::stringstream &orange);
    bool TRANSFER(bool bycash,Card *x,Account *y,const u64 amount,const u64 fee,const bool lang,std::stringstream &orange);
    
    const u64 N50k(){return fund.N50K();}
    const u64 N10k(){return fund.N10K();}
    const u64 N5k(){return fund.N5K();}
    const u64 N1k(){return fund.N1K();}
    
    const str exportTS_EN()const{return tsHistoryEN.str();}
    const str exportTS_KR()const{return tsHistoryKR.str();}
};

inline size_t SIZE_ATMS=0;
inline std::array<ATM,MAX_ARRAY_LENGTH>ATMs;


#endif /* ATM_hpp */
