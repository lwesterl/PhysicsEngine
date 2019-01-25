#! /bin/bash

Tests=(*.exe)
for test in "${Tests[@]}"; do
  echo "Running $test"
  ./$test
  if [ $? != 0 ]; then
    printf "\n$test failed\n"
    exit
  fi
done
printf "\n\nALL FOUND TESTS COMPLETED\n"
