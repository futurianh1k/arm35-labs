#!/bin/sh
# ARM35 Final Practical Exam — 문항당 10점, 총 50점. 재실행 안전(멱등).
TGT=check; [ "$1" = "--sol" ] && TGT=check-sol
total=0
echo "=============================="
echo " ARM35 Final Practical Exam"
echo "=============================="
names_1="FIELD 연산 "; names_2="폴링 송신  "; names_3="Load 산수  "
names_4="매칭 성사  "; names_5="read 한 문 "
for q in 1 2 3 4 5; do
  eval nm=\$names_$q
  if ( cd "exam/q$q" && make -s $TGT ) > "exam/q$q/.out" 2>&1; then
    printf "[Q%s] %s ..... PASS (10/10)\n" "$q" "$nm"
    total=$((total+10))
  else
    printf "[Q%s] %s ..... FAIL ( 0/10)\n" "$q" "$nm"
    grep "기대" "exam/q$q/.out" | head -1 | sed "s|^|      log: exam/q$q/.out — |"
  fi
done
echo "------------------------------"
echo " 실기 총점 ${total}/50"
echo "=============================="
[ $total -eq 50 ]
