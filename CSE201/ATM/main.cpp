//
//  main.cpp
//  term
//
//  Created by Sora Sugiyama on 10/5/25.
//


/* -------------------------------------------------- */

/* DGIST 2025 CSE201 term project */
/* Written by 202411063 Seojin Park */
/* Compiler : Apple GNU C++ 20 */
/* If you cannot compile this code in other C++20 compiler, you should use C++ 23 compiler */

/* -------------------------------------------------- */

#include "include.h"
#include "card.h"
#include "const.h"
#include "ATM.h"

// Do not use this.
namespace weekSecure{

constexpr u64 p=2147483647,q=17,pp=40659686737877,qq=73;
static str hash(const str &pw){
    str s;
    u64 v=0;
    for(char c:pw)v=(v*q+c)%p;
    v+=0x2914;
    
    s=std::to_string(v);
    s=s+s;
    s+=str(40-s.size(),'*');
    std::reverse(s.begin()+13,s.end());
    std::reverse(s.begin(),s.begin()+23);
    
    u64 t=0x2374;
    std::vector<u64>tmp(s.begin(),s.end());
    for(u64 &x:tmp){
        x=(x*t+q)%pp;
        t=t*qq%pp;
    }
    
    std::stringstream ss;
    ss<<std::hex<<std::setfill('0');
    for(u64 x:tmp)ss<<std::setw(16)<<x;
    
    return ss.str();
}

}


bool blackbox(const str &x){
    if(x!="/")return false;
    std::cout<<"ATM INFORMATIONS\n";
    for(ATM* atm=ATMs.begin();atm!=ATMs.begin()+SIZE_ATMS;atm++){
        std::cout<<format(blackboxHelp1,atm->getBank(),(atm->isMulti())?"Multi":"Single",(atm->isBi())?"Bilingual":"Unilingual",atm->getSerial(),atm->N50k(),atm->N10k(),atm->N5k(),atm->N1k());
    }
    std::cout<<"ACCOUNT INFORMATIONS\n";
    for(Account* acc=accs.begin();acc!=accs.begin()+SIZE_ACCOUNT;acc++){
        std::cout<<format(blackboxHelp2,acc->getBank(),acc->getAcc(),acc->getName(),acc->getFund());
    }
    std::cout<<std::endl;
    return true;
}

bool ATM::VERIFY_PASSWORD(Card* bananana,const bool lang){
    str banana;
    input012:
    std::cout<<(lang?"비밀번호: ":"Password: ")<<std::flush;
    std::getline(std::cin,banana);
    if(blackbox(banana))goto input012;
    if(Bank::b41332a2447f8c40(banana,bananana)){
        std::cout<<(lang?"검증됨":"VERIFIED")<<std::endl;
        return true;
    }
    std::cout<<(lang?"잘못된 비밀번호":"Wrong Password.")<<std::endl;
    input013:
    std::cout<<(lang?"비밀번호: ":"Password: ")<<std::flush;
    std::getline(std::cin,banana);
    if(blackbox(banana))goto input013;
    if(Bank::b41332a2447f8c40(banana,bananana)){
        std::cout<<(lang?"검증됨":"VERIFIED")<<std::endl;
        return true;
    }
    std::cout<<(lang?"잘못된 비밀번호":"Wrong Password.")<<std::endl;
    input014:
    std::cout<<(lang?"비밀번호: ":"Password: ")<<std::flush;
    std::getline(std::cin,banana);
    if(blackbox(banana))goto input014;
    if(Bank::b41332a2447f8c40(banana,bananana)){
        std::cout<<(lang?"검증됨":"VERIFIED")<<std::endl;
        return true;
    }
    std::cout<<(lang?"잘못된 비밀번호":"Wrong Password.")<<std::endl;
    return false;
}

void displayTransactionHistroy(ATM& atm,bool lang){
    std::stringstream ss;
    std::cout<<(lang?atm.exportTS_KR():atm.exportTS_EN())<<std::endl;
    std::ofstream fout(atm.getSerial()+"TSHISTORY");
    fout<<(lang?atm.exportTS_KR():atm.exportTS_EN())<<std::flush;
}

void adminMenu(ATM& atm,bool lang){
    loop:{
        std::cout<<(lang?"[1] 거래 내역 표시\n[2] 세션 종료\n>":"[1] Display Transaction History\n[2] Terminate Session\n>")<<std::flush;
        str cmd;
        std::getline(std::cin,cmd);
        if(blackbox(cmd))goto loop;
        if(cmd=="1"){
            displayTransactionHistroy(atm, lang);
        }else if(cmd=="2"){
            return;
        }
    }
    goto loop;
}

Card* insertCard(ATM& atm,str& cardnum,bool banana){
    SESSION_NUM++;
    std::cout<<"START SESSION "<<SESSION_NUM<<std::endl;
    if(cardnum=="admin"){
        str pw,in;
        std::ifstream fin("password");
        fin>>pw;
        fin.close();
        int CHANCE=3;
        while(CHANCE--){
            input011:
            std::cout<<(banana?"비밀번호 입력: ":"Enter the password: ")<<std::flush;
            std::getline(std::cin,in);
            if(blackbox(in))goto input011;
            if(pw!=weekSecure::hash(in)){
                if(CHANCE)std::cout<<(banana?"잘못된 비밀번호. 다시 시도하라.":"Wrong password. Try again.")<<std::endl;
                else{
                    std::cout<<(banana?"잘못된 비밀번호":"Wrong password.")<<std::endl;
                    return nullptr;
                }
            }else{
                adminMenu(atm,banana);
                std::cout<<"SESSION SUMMARY - YOU ARE ADMIN\n";
                std::cout<<"SESSION "<<SESSION_NUM<<" TERMINATED"<<std::endl;
                return nullptr;
            }
        }
        return nullptr;
    }else{
        for(Card *card=cards.begin();card!=cards.begin()+SIZE_CARDS;card++){
            if(card->getCardnum()==cardnum){
                if(card->getBank()!=atm.getBank()&&!atm.isMulti()){
                    std::cout<<(banana?"유효하지 않은 카드":"Invalid Card")<<std::endl;
                    return nullptr;
                }
                std::cout<<(banana?"카드 삽임됨":"Card Inserted")<<std::endl;
                if(ATM::VERIFY_PASSWORD(card, banana))return card;
                std::cout<<(banana?"카드 배출됨":"Card Dispensed")<<std::endl;
                std::cout<<"SESSION "<<SESSION_NUM<<" TERMINATED\nSUMMARY\n------------"<<std::endl;
                return nullptr;
            }
        }
    }
    std::cout<<(banana?"유효하지 않은 카드":"Invalid Card")<<std::endl;
    return nullptr;
}

void startATM(ATM& atm){
    bool lang=false;
    start:{
        std::cout<<"ATM "<<atm.getSerial()<<std::endl;
        bool cardInserted=false;
        if(atm.isBi()){
            std::cout<<(lang?"만약 언어를 바꾸고 싶다면, 입력 \"x\"":"If you want to change language, enter \"x\"")<<std::endl;
        }
        
        std::stringstream ANNONYMOUS_VARIABLE_001;
        std::stringstream &fun=ANNONYMOUS_VARIABLE_001;
        
        u64 withdrawalCount=0;
        Card* IntegratedCircuit;
        Card* &ic=IntegratedCircuit;
        
        loop:{
            str cmd;
            input001:
            std::cout<<(lang?kor:eng)<<">"<<std::flush;
            std::getline(std::cin,cmd);
            if(blackbox(cmd))goto input001;
            
            if(cmd=="x")lang^=1;
            else if(cmd=="1"){
                
                if(cardInserted){
                    std::cout<<(lang?"세션을 먼저 종료하라":"Terminate your session first.")<<std::endl;
                    goto loop;
                }
                
                str cardNum;
                
                input002:
                std::cout<<(lang?"카드 번호 입력: ":"Enter your card number: ")<<std::flush;
                
                std::getline(std::cin,cardNum);
                if(blackbox(cardNum))goto input002;
                
                Card* chickenBanana=insertCard(atm,cardNum,lang);
                
                if(chickenBanana){
                    Card &cb=*chickenBanana;
                    ic=chickenBanana;
                    cardInserted=true;
                    
                    if(!lang){
                        fun<<std::format("ATM session {:d} summary\n\
------------------------------------\n\
Card Information\n\
   Card Number: {:<}\n\
     User Name: {:<}\n\
          Bank: {:<}\n\
Account Number: {:<}\n\
------------------------------------\n",SESSION_NUM,cb.getCardnum(),cb.getName(),cb.getBank(),cb.getAcc());
                    }else{
                        fun<<std::format("ATM 세션 {:d} 요약\n\
------------------------------------\n\
카드 정보\n\
카드 번호: {:<}\n\
 사용자명: {:<}\n\
    은행: {:<}\n\
계좌 번호: {:<}\n\
------------------------------------\n",SESSION_NUM,cb.getCardnum(),cb.getName(),cb.getBank(),cb.getAcc());
                    }
                }
            }else if(cmd=="3"){
                if(withdrawalCount>=3){
                    std::cout<<(lang?"더 이상 인출할 수 없음":"No more withdrawal allowed")<<std::endl;
                    goto loop;
                }
                if(!cardInserted){
                    std::cout<<(lang?"카드를 먼저 삽입하라":"Insert your card first.")<<std::endl;
                    goto loop;
                }
                
                str AMOUNT;
                input003:
                std::cout<<(lang?"인출할 금액: ":"Withdrawal amount: ")<<std::flush;
                std::getline(std::cin,AMOUNT);
                if(blackbox(AMOUNT))goto input003;
                
                u64 amount;
                try{
                    amount=std::stoull(AMOUNT);
                }catch(std::exception &e){
                    std::cout<<"SOMETHING WRONG"<<std::endl;
                    goto loop;
                }
                bool success=atm.WITHDRAWAL(ic, amount, lang, fun);
                if(success){
                    withdrawalCount++;
                }
            }else if(cmd=="2"){
                TRANSACTION_NUM++;
                if(!cardInserted){
                    std::cout<<(lang?"카드를 먼저 삽입하라":"Insert your card first.")<<std::endl;
                    goto loop;
                }
                
                str BILLS;
                input004:
                std::cout<<(lang?"투입할 지폐의 개수 입력":"Enter the number of bills to insert")<<std::endl;
                std::cout<<"[50000] [10000] [5000] [1000]"<<std::endl;
                std::getline(std::cin,BILLS);
                if(blackbox(BILLS))goto input004;
                std::stringstream ssBILL(BILLS);
                std::array<u64,4>bill={};
                for(int i=0;i<4;i++){
                    try{
                        ssBILL>>bill[i];
                    }catch(std::exception &e){
                        std::cout<<"SOMETHING WRONG"<<std::endl;
                        goto loop;
                    }
                }
                
                str CHECKS;
                
                input005:
                std::cout<<(lang?"투입할 수표 입력":"Enter the checks to insert")<<std::endl;
                std::cout<<(lang?"[수표1 금액] [수표2 금액] ...":"[check1 amout] [check2 amout] ...")<<std::endl;
                std::getline(std::cin,CHECKS);
                if(blackbox(CHECKS))goto input005;
                
                std::stringstream ssCHECK(CHECKS);
                size_t n_checks=0;
                u64 carrot=0,radish;
                while(ssCHECK>>radish){
                    n_checks++;
                    carrot+=radish;
                }
                if(bill[0]+bill[1]+bill[2]+bill[3]>LIMIT_BILL_TRANSACTION||n_checks>LIMIT_CHECK_TRANSACTION){
                    std::cout<<(lang?"너무 많은 지폐 혹은 수표":"Too many bills or checks")<<std::endl;
                }else{
                    atm.DEPOSIT(ic, bill, carrot, lang, fun);
                }
            }
            else if(cmd=="4"){
                if(!cardInserted){
                    std::cout<<(lang?"카드를 먼저 삽입하라":"Insert your card first.")<<std::endl;
                    goto loop;
                }
                
                str OPTION;
                
                input006:
                std::cout<<(lang?"[1] 현금\n[2] 계좌":"[1] Cash\n[2] Account")<<std::endl;
                std::getline(std::cin,OPTION);
                if(blackbox(OPTION))goto input006;
                std::array<u64,4>bill={};
                u64 amount=0;
                if(OPTION=="1"){
                    
                    str BILLS;
                    
                    input007:
                    std::cout<<(lang?"투입할 지폐의 개수 입력":"Enter the number of bills to insert")<<std::endl;
                    std::cout<<"[50000] [10000] [5000] [1000]"<<std::endl;
                    std::getline(std::cin,BILLS);
                    if(blackbox(BILLS))goto input007;
                    
                    std::stringstream ssBILL(BILLS);
                    
                    for(int i=0;i<4;i++){
                        try{
                            ssBILL>>bill[i];
                        }catch(std::exception &e){
                            std::cout<<"SOMETHING WRONG"<<std::endl;
                            goto loop;
                        }
                    }
                    if(bill[0]+bill[1]+bill[2]+bill[3]>LIMIT_BILL_TRANSACTION){
                        std::cout<<(lang?"너무 많은 지폐":"Too many bills")<<std::endl;
                    }
                    amount=bill[0]*50000+bill[1]*10000+bill[2]*5000+bill[3]*1000;
                }else if(OPTION=="2"){
                    str AMOUNT;
                    input008:
                    std::cout<<(lang?"이체 금액:":"Transfer amount: ")<<std::flush;
                    std::getline(std::cin,AMOUNT);
                    
                    if(blackbox(AMOUNT))goto input008;
                    
                    try{
                        amount=std::stoull(AMOUNT);
                    }catch(std::exception &e){
                        std::cout<<"SOMETHING WRONG"<<std::endl;
                        goto loop;
                    }
                }
                
                str ACCOUNT;
                input009:
                std::cout<<(lang?"받는 사람 계좌: ":"Receiving Account: ")<<std::flush;
                std::getline(std::cin,ACCOUNT);
                if(blackbox(ACCOUNT))goto input009;
                u64 fee=0;
                Account* account=Bank::b41332a2447f8c44(ACCOUNT);
                if(account==nullptr){
                    std::cout<<(lang?"계좌 없음: ":"No account: ")<<ACCOUNT<<std::endl;
                    goto loop;
                }
                if(OPTION=="1"){
                    fee=2000;
                    if(amount<fee){
                        std::cout<<(lang?"현금이 너무 적습니다":"Insufficient cash")<<std::endl;
                        goto loop;
                    }
                    amount-=fee;
                }else{
                    int tmp=(atm.getBank()==ic->getBank())+(atm.getBank()==account->getBank());
                    switch(tmp){
                        case 0:{
                            fee=4000;
                            break;
                        }
                        case 1:{
                            fee=2000;
                            break;
                        }
                        case 2:{
                            fee=1000;
                            break;
                        }
                    }
                }
                atm.TRANSFER(OPTION=="1", ic, account, bill, amount, fee, lang, fun);
            }else if(cmd=="5"){
                if(!cardInserted){
                    std::cout<<(lang?"카드를 먼저 삽입하라":"Insert your card first.")<<std::endl;
                    goto loop;
                }
                if(lang){
                    fun<<std::format("세션 {:d} 종료\n",SESSION_NUM);
                }else{
                    fun<<std::format("Session {:d} Terminated\n",SESSION_NUM);
                }
                std::cout<<fun.str()<<std::flush;
                if(lang){
                    std::cout<<std::format("잔고: {:d}\n카드를 챙겨라\n",ic->getFund())<<part<<std::endl;
                }else{
                    std::cout<<std::format("Funds: {:d}\nTake your card.\n",ic->getFund())<<part<<std::endl;
                }
                goto start;
            }else if(cmd=="6"){
                if(cardInserted){
                    std::cout<<(lang?"세션을 먼저 종료하라":"Terminate your session first.")<<std::endl;
                    goto loop;
                }else return;
            }
        }
        goto loop;
    }
}

int main(int argc, const char * argv[]) {
    if(argc < 3){
        std::cerr<<"Initial condition not provieded.\nUseage: ./ATM <init condition path> <admin password>"<<std::endl;
        return 1;
    }
    
    std::ifstream fin(argv[1]);
    if(!fin){
        std::cerr<<"Failed to opening file"<<std::endl;
        return 2;
    }
    
    {
        const str pw=argv[2];
        std::ofstream writePW("password");
        writePW<<weekSecure::hash(pw);
    }
    
    u64 B,A,N; // BAN?
    fin>>B>>A>>N;
    
    while(B--){
        str bankName;fin>>bankName;
    }
    
    while(A--){
        str bankName,userName,accountName,cardNum,cardPw;
        u64 fund;
        fin>>bankName>>userName>>accountName>>fund>>cardNum>>cardPw;
        cards[SIZE_CARDS++]=Card(bankName,userName,accountName,fund,cardNum,cardPw);
        accs[SIZE_ACCOUNT++].setCard(&cards[SIZE_CARDS-1]);
        Bank::addAccount(&accs[SIZE_ACCOUNT-1]);
    }
    
    
    while(N--){
        str pbank,serial,type,lang;
        u64 a,b,c,d;
        fin>>pbank>>serial>>type>>lang>>a>>b>>c>>d;
        ATMs[SIZE_ATMS++]=ATM(pbank,serial,type,lang,std::array<u64,4>{a,b,c,d});
    }
    
    loop:{
        str cmd;
        
        input010:
        std::cout<<"% "<<std::flush;
        std::getline(std::cin,cmd);
        if(blackbox(cmd))goto input010;
        
        std::stringstream ss(cmd);
        str arg1;ss>>arg1;
        
        switch(commandMapper(arg1)){
            case 0:{ // help
                std::cout<<helpPage<<std::endl;
                break;
            }
            case 1:{ // ls
                str arg;
                
                std::vector<std::pair<str,str> >CMD_OPTIONS;
                while(ss>>arg){
                    std::stringstream xx(arg);
                    str option,keyword;
                    std::getline(xx,option,'=');
                    xx>>keyword;
                    
                    CMD_OPTIONS.push_back(std::pair<str,str>(option,keyword));
                }
                for(ATM *atm=ATMs.begin();atm!=ATMs.begin()+SIZE_ATMS;atm++){
                    bool sat=true;
                    for(auto [op,key]:CMD_OPTIONS){
                        if(op=="--lang"){
                            sat&=atm->isBi()==(key=="bi");
                        }else if(op=="--type"){
                            sat&=atm->isMulti()==(key=="multi");
                        }else if(op=="--bank"){
                            sat&=atm->getBank()==key;
                        }else{
                            std::cout<<"Wrong option. See help."<<std::endl;
                            break;
                        }
                    }
                    
                    if(sat){
                        std::cout<<std::format(lsHelpr,atm->getBank(),(atm->isMulti())?"Multi":"Single",(atm->isBi())?"Bilingual":"Unilingual",atm->getSerial())<<std::endl;
                    }
                }
                break;
            }
            case 2:{ // slc
                str arg;ss>>arg;
                if(!ss.eof()){
                    std::cout<<"Please enter the serial number. See help."<<std::endl;
                    break;
                }
                
                for(ATM *atm=ATMs.begin();atm!=ATMs.begin()+SIZE_ATMS;atm++){
                    if(arg==atm->getSerial()){
                        startATM(*atm);
                        goto loop;
                    }
                }
                std::cout<<"No ATM found with serial number: "<<arg<<std::endl;
                break;
            }
            case 3:{ // exit
                goto endLoop;
                break;
            }
            default:{
                std::cout<<"Invalid command. Use \"help\" to see all commands."<<std::endl;
                break;
            }
        }
    }goto loop;
    endLoop:
    
    return 0;
}



/*
 
 ERROR CODES
 1: Invalid argument
 2: Failed to opening file
 3: Invalid init file
 
 
 */
