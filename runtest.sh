#!/bin/bash

main() {
  if [ "$1" = "all" ]; then
    test_all
    exit
  fi
  if [ -z "$1" ]; then
    usage
    exit
  fi
  p=`basename $1`
  pexe=$p.exe
  pf=`pwd`/$pexe
  if [ ! -e $pexe ]; then
    echo Program "$pexe" not exists.
    exit
  fi
  testdir=test_$p
  if [ ! -d $testdir ]; then
    echo Test dir "$testdir" not exists.
    exit
  fi
  mask='*'
  if [ "$2" != "" ]; then
    mask=$2
  fi
  param1=
  if [ "$3" != "" ]; then
    param1=$3
  fi
  c=0
  cp=0
  cf=0
  pushd $testdir > /dev/null
  set +f
  for t in $mask.in; do
    run_test $t
  done
  popd > /dev/null
  if [[ $c == $cp ]]; then
    beep 5000 100
    echo_green Total: $c, passed: $cp, failed: $cf
  else
    beep 1000 100
    echo_red Total: $c, passed: $cp, failed: $cf
  fi
}

run_test() {
  tn=`basename $1 .in`
  ta=${tn}_actual.out
  $pf $param1<$1| tr -d '\r' > $ta
  if diff -N $tn.out $ta > /dev/null; then
    echo $1... ok
    rm $ta
    (( cp++ ))
  else
    echo $1... FAILED
    (( cf++ ))
  fi
  (( c++ ))
}

beep() { uname | grep CYGWIN > /dev/null && nircmd beep $1 $2; }

test_all() {
  set +f
  for dir in $(ls -1d *[1]_[0-9]*); do
    set -f
    pushd $dir > /dev/null
    basename $(pwd)
    make -Br -j --output-sync=target && make test && make clean
    popd > /dev/null
  done
}

usage() {
  echo "Usage: $0 [program] [filemask|all] [param1]"
}

echo_green() {
  echo -e '\E[37;32m'"\033[1m${*}\033[0m"
}

echo_red() {
  echo -e '\E[37;31m'"\033[1m${*}\033[0m"
}

set -f
main $*
