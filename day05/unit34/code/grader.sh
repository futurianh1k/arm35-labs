#!/bin/sh
# ARM35 PBL Grader — 각 미션 make check의 exit만 신뢰한다. (--sol: 강사 검증)
TGT=check; [ "$1" = "--sol" ] && TGT=check-sol
S1=30; S2=30; S3=40
total=0; pass=0
echo "=============================="
echo " ARM35 PBL Grader"
echo "=============================="
run(){ # $1=id $2=이름 $3=배점
  printf "[%s] %s\n" "$1" "$2"
  if ( cd "missions/$1" && make -s $TGT ) > ".${1}.log" 2>&1; then
    grep -E "회귀|신규" ".${1}.log" | sed 's/^/    /'
    echo "    -> ${3}점"
    total=$((total+$3)); pass=$((pass+1))
  else
    grep -E "회귀|신규|FAIL" ".${1}.log" | sed 's/^/    /'
    echo "    -> 0점   (hint: missions/$1 에서 make check 로그를 읽어라)"
  fi
}
run m1 "이중 IRQ      " $S1
run m2 "시민의 임무   " $S2
run m3 "화물 탑재     " $S3
echo "------------------------------"
echo " 통과 ${pass}/3 미션   점수 ${total}/100"
echo " Evidence 체크: 미션별 관측 한 줄·로그 첨부는 사람이 확인한다"
echo "=============================="
[ $pass -eq 3 ]
