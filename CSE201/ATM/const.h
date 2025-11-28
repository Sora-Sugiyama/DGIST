//
//  const.h
//  term
//
//  Created by Sora Sugiyama on 11/28/25.
//

#ifndef const_h
#define const_h

#include "include.h"

using u64=uint64_t;
using str=std::string;

constexpr u64 krw50k=0,krw10k=1,krw5k=2,krw1k=3;
constexpr size_t MAX_ARRAY_LENGTH=0b1111111111111111;
constexpr u64 LIMIT_BILL_TRANSACTION=0xffff,LIMIT_CHECK_TRANSACTION=0xff;
constexpr std::string_view part="----------------------------------------";
constexpr std::string_view kor="\
환영\n\
시작 하려면, 제발 너의 직불 카드를 삽입하라.\n\
[1] 카드 삽입\n\
[2] 저축\n\
[3] 인출\n\
[4] 송금\n\
[5] 세션 종료\n\
[6] 홈\n\
";

constexpr std::string_view eng="\
Welcome\n\
To start, please insert your debit card\n\
[1] Card Insert\n\
[2] Deposit\n\
[3] Withdrawal\n\
[4] Transfer\n\
[5] End Session\n\
[6] Home\n\
";



constexpr std::string_view helpPage="\
help: open help page\n\
ls <options>:\n\
    list all ATMs that satisfy options.\n\
    Variable options:\n\
        --lang=LANG     language support (bi, uni)\n\
        --type=TYPE     ATM type (multi,single)\n\
        --bank=BANK     Primary Bankname. It can be substring of name.\n\
slc <ATM-serial-number>: select ATM\n\
exit: exit\n\
";

constexpr std::string_view lsHelpr="\
------------------------------------\n\
 Primary Bank Name: {:<}\n\
              Type: {:<}\n\
   Language Suppor: {:<}\n\
     Serial Number: {:<}\n\
------------------------------------\n";

constexpr std::string_view blackboxHelp1="\
------------------------------------\n\
 Primary Bank Name: {:<}\n\
              Type: {:<}\n\
   Language Suppor: {:<}\n\
     Serial Number: {:<}\n\
    Remaining Cash: KRW50k {:<d}; KRW10k {:<d}; KRW5k {:<d}; KRW1k {:<d}\n\
------------------------------------\n";

constexpr std::string_view blackboxHelp2="\
------------------------------------\n\
         Bank Name: {:<}\n\
    Account Number: {:<}\n\
             Owner: {:<}\n\
           Balance: {:<d}\n\
------------------------------------\n";

constexpr std::string_view TS_HELP="\
           CARD NUMBER: {:<}\n\
               ACCOUNT: {:<}\n\
        TRANSACTION ID: {:<d}\n\
      TRANSACTION TYPE: {:<}\n\
                AMOUNT: {:<d}\n\
                   FEE: {:<d}\n\
";

constexpr std::string_view TS_HELP_KR="\
               카드 번호: {:<}\n\
                   계좌: {:<}\n\
               거래 번호: {:<d}\n\
               거래 유형: {:<}\n\
                    양: {:<d}\n\
                 수수료: {:<d}\n\
";

constexpr std::string_view TS_HELP_TRANSFER="\
           CARD NUMBER: {:<}\n\
        TRANSACTION ID: {:<d}\n\
      TRANSACTION TYPE: TRANSFER\n\
                AMOUNT: {:<}\n\
        FUNDING SOURCE: {:<}\n\
                   FEE: {:<d}\n\
        SOURCE ACCOUNT: {:<}\n\
   DESTINATION ACCOUNT: {:<}\n\
";

constexpr std::string_view TS_HELP_TRANSFER_KR="\
               카드 번호: {:<}\n\
               거래 번호: {:<d}\n\
               거래 유형: 이체\n\
                    양: {:<}\n\
               자금 출처: {:<}\n\
                 수수료: {:<d}\n\
              보내는 사람: {:<}\n\
               받는 사람: {:<}\n\
";

const u64 commandMapper(const str &cmd){
    if(cmd=="help")return 0;
    else if(cmd=="ls")return 1;
    else if(cmd=="slc")return 2;
    else if(cmd=="exit")return 3;
    return 2374;
}

#endif /* const_h */
