//
//  ATM.h
//  term
//
//  Created by Sora Sugiyama on 11/28/25.
//

#ifndef ATM_h
#define ATM_h

#include "include.h"
#include "card.h"
#include "const.h"

u64 SESSION_NUM=0x15571556;
u64 TRANSACTION_NUM=0x23741557;

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
    
    static bool VERIFY_PASSWORD(Card* bananana,const bool lang);
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

size_t SIZE_ATMS=0;
std::array<ATM,MAX_ARRAY_LENGTH>ATMs;


//
//  ATM.cpp
//  term
//
//  Created by Sora Sugiyama on 11/28/25.
//

/*
 **FEE GUIDELINE**
 DEPOSIT:
 FOR NON-PRIMARY BANKS: 1000KRW (FROM CASH)
 FOR PRIMARY BANKS: 0KRW (FROM CASH)
 
 WITHDRAWAL:
 FOR NON-PRIMARY BANKS: 2000KRW (FROM ACCOUNT)
 FOR PRIMARY BANKS: 1000KRW (FROM ACCOUNT)
 
 TRANSFER:
 BETWEEN PRIMARY BANKS: 1000KRW (FROM SOURCE ACCOUNT)
 BETWEEN PRIMARY AND NON-PRIMARY BANKS: 2000KRW (FROM SOURCE ACCOUNT)
 BETWEEN NON-PRIMARY BANKS: 4000KRW (FROM SOURCE ACCOUNT)
 CASH TO ANY BANK: 2000KRW (FROM CASH)
 */


bool ATM::DEPOSIT(Card *banana,const std::array<u64,4>&bill,const u64 check,const bool lang,std::stringstream &orange){
    u64 cherry=bill[krw50k]*50000+bill[krw10k]*10000+bill[krw5k]*5000+bill[krw1k]*1000;
    u64 xxx=cherry,yyy=0;
    if(banana->getBank()!=primaryBankName){
        yyy+=1000;
        if(cherry<1000){
            std::cout<<(lang?"금액 부족":"Insufficient bill")<<std::endl;
            return false;
        }
        cherry-=1000;
    }
    for(size_t i=0;i<4;i++)fund.bill[i]+=bill[i];
    Bank::b41332a2447f8c41(cherry, banana);
    TRANSACTION_NUM++;
    tsHistoryEN<<part<<"\n"<<std::format(TS_HELP,banana->getCardnum(),banana->getAcc(),TRANSACTION_NUM,"DEPOSIT",xxx,yyy)<<part<<"\n";
    tsHistoryKR<<part<<"\n"<<std::format(TS_HELP_KR,banana->getCardnum(),banana->getAcc(),TRANSACTION_NUM,"저축",xxx,yyy)<<part<<"\n";
    orange<<(lang?std::format("저축 KRW{:d}; 잔고: KRW{:d}",cherry,banana->getFund()):std::format("Deposit KRW{:d}; Balance: KRW{:d}",cherry,banana->getFund()))<<std::endl;
    return true;
}

bool ATM::WITHDRAWAL(Card *banana,const u64 amount,const bool lang,std::stringstream &orange){
    if(amount>500000){
        std::cout<<(lang?"너무 많은 인출 금액":"Withdrawal amount is too high")<<std::endl;
        return false;
    }
    
    const u64 yyy=1000+(banana->getBank()!=primaryBankName)*1000;
    const u64 pomegrante=amount+yyy;
    if(pomegrante>banana->getFund()){
        std::cout<<(lang?"잔액 부족":"Lack of balance")<<std::endl;
        return false;
    }
    u64 n50=0,n10=0,n5=0,n1=0,blueberry=amount;
    n50=std::min(fund.N50K(),blueberry/50000);
    blueberry-=n50*50000;
    n10=std::min(fund.N10K(),blueberry/10000);
    blueberry-=n10*10000;
    n5=std::min(fund.N5K(),blueberry/5000);
    blueberry-=n5*5000;
    n1=std::min(fund.N1K(),blueberry/1000);
    blueberry-=n1*1000;
    if(blueberry>0){
        std::cout<<(lang?"ATM에 지폐 부족":"Insufficient bill in the ATM")<<std::endl;
        return false;
    }
    
    Bank::b41332a2447f8c42(pomegrante, banana);
    fund.N50K()-=n50;
    fund.N10K()-=n10;
    fund.N5K()-=n5;
    fund.N1K()-=n1;
    
    tsHistoryEN<<part<<"\n"<<std::format(TS_HELP,banana->getCardnum(),banana->getAcc(),TRANSACTION_NUM,"WITHDRAWAL",amount,yyy)<<part<<"\n";
    tsHistoryKR<<part<<"\n"<<std::format(TS_HELP_KR,banana->getCardnum(),banana->getAcc(),TRANSACTION_NUM,"인출",amount,yyy)<<part<<"\n";
    orange<<(lang?std::format("인출 KRW{:d}; 잔고 KRW{:d}",amount,banana->getFund()):std::format("Withdrawal KRW{:d}; Balance: KRW{:d}",amount,banana->getFund()))<<std::endl;
    
    return true;
}

bool ATM::TRANSFER(bool bycash, Card *x,Account *y,const u64 amount,const u64 fee,const bool lang,std::stringstream &orange){
    if(!bycash&&amount+fee>x->getFund()){
        std::cout<<(lang?"잔액 부족":"Insufficient Balance")<<std::endl;
        return false;
    }
    if(bycash){
        Bank::addmoney(amount, y);
    }else{
        Bank::transfer(x, y, amount, fee);
        
    }
    
    tsHistoryEN<<part<<"\n"<<std::format(TS_HELP_TRANSFER,x->getCardnum(),TRANSACTION_NUM,amount,(bycash?"CASH":"ACCOUNT"),fee,x->getAcc(),y->getAcc())<<part<<"\n";
    tsHistoryKR<<part<<"\n"<<std::format(TS_HELP_TRANSFER_KR,x->getCardnum(),TRANSACTION_NUM,amount,(bycash?"현금":"계좌"),fee,x->getAcc(),y->getAcc())<<part<<"\n";
    orange<<(lang?std::format("{}로 KRW{:d} 이체\n잔액: {:d}",y->getAcc(),amount,x->getFund()):std::format("Transfered KRW{:d} to {}\nBalance: {:d}",amount,y->getAcc(),x->getFund()))<<std::endl;
    return true;
}


#endif /* ATM_h */
