#! /bin/bash
# author Lauri Westerholm
# a small bash script which makes and runs all tests
# exits on failure

make
if [ $? != 0 ]; then
  printf "\nFail: make\n"
  exit
fi
printf "\nInfo: make finished\n\n"
Tests=(*.exe)
for test in "${Tests[@]}"; do
  printf "\n\nRunning $test\n"
  ./$test
  if [ $? != 0 ]; then
    printf "\n$test failed\n"
    exit
  fi
done
printf "\n\nALL FOUND TESTS COMPLETED\n"
