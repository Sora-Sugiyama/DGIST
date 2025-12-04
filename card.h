//
//  card.h
//  term
//
//  Created by Sora Sugiyama on 11/28/25.
//

#ifndef card_h
#define card_h

#include "include.h"
#include "const.h"

class Card{
    str bank,user,account,cardNum,pw;
    u64 fund;
    
    friend class Bank;
public:
    Card(str bank="",str user="",str account="",u64 fund=0,str cardNum="",str pw=""):bank(bank),user(user),account(account),fund(fund),cardNum(cardNum),pw(pw){}
    str getCardnum()const{return cardNum;}
    str getBank()const{return bank;}
    str getPw()const{return pw;}
    str getName()const{return user;}
    str getAcc()const{return account;}
    u64 getFund()const{return fund;}
};

size_t SIZE_CARDS=0;
std::array<Card,MAX_ARRAY_LENGTH>cards;


class Account:Card{
    Card *card=nullptr;
    friend class Bank;
public:
    Account(Card *c=nullptr):Card("junk","junk","junk",~0ULL,"junk","junk"),card(c){}
    void setCard(Card* c){card=c;}
    str getCardnum()const{return card->getCardnum();}
    str getBank()const{return card->getBank();}
    str getPw()const{return card->getPw();}
    str getName()const{return card->getName();}
    str getAcc()const{return card->getAcc();}
    u64 getFund()const{return card->getFund();}
};

size_t SIZE_ACCOUNT=0;
std::array<Account,MAX_ARRAY_LENGTH>accs;

/* -------------------------------------------------- */



class Bank{
    static std::map<str,Account*>accounts;
public:
    static bool b41332a2447f8c40(const str &mango,Card* manko){
        return mango==manko->getPw();
    }
    
    static void b41332a2447f8c41(u64 mango,Card* manko){
        manko->fund+=mango;
    }
    
    static void b41332a2447f8c42(u64 mango,Card* manko){
        if(manko->fund<mango){
            std::cout<<"Something wrong..."<<std::endl;
            return;
        }
        manko->fund-=mango;
    }
    
    static void addmoney(u64 mango,Account* manko){
        manko->card->fund+=mango;
    }
    
    static void transfer(Card* mango,Account* manko,u64 womango,u64 fee){
        if(mango->fund<womango+fee){
            std::cout<<"Something wrong..."<<std::endl;
            return;
        }
        mango->fund-=womango+fee;
        manko->card->fund+=womango;
    }
    
    static Account* b41332a2447f8c44(const str &acc){
        return accounts[acc];
    }
    
    static void addAccount(Account *acc){
        accounts[acc->getAcc()]=acc;
    }
};

std::map<str,Account*>Bank::accounts;
/* -------------------------------------------------- */


#endif /* card_h */
