#! /bin/bash
# author Lauri Westerholm
# a small bash script which makes and runs all tests
# exits on failure

# runs tests by ./TestAll
# runs memory leak tests by ./TestAll valgrind


make
if [ $? != 0 ]; then
  printf "\nFail: make\n"
  exit
fi
printf "\nInfo: make finished\n\n"
Tests=(*.exe)
for test in "${Tests[@]}"; do
  printf "\n\nRunning $test\n"
  if [ $# == 1 ] && [ $1 == "valgrind" ]; then
    valgrind --leak-check=yes ./$test
  else
    ./$test
  fi
  if [ $? != 0 ]; then
    printf "\n$test failed\n"
    exit
  fi
done
printf "\n\nALL FOUND TESTS COMPLETED\n"
