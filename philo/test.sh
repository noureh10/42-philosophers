#!/bin/bash

make re

if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

die_test=(
	"./philo 1 800 200 200"
	"./philo 4 310 200 100"
	"./philo 4 200 205 200"
)

no_die_tests=(
	"./philo 5 800 200 200"
	"./philo 5 600 150 150"
	"./philo 4 410 200 200"
	"./philo 100 800 200 200"
	"./philo 105 800 200 200"
	"./philo 200 800 200 200"
)

no_run_test=(
	"./philo -1 60 60 60"
	"./philo 60 -1 60 60"
	"./philo 60 60 -1 60"
	"./philo 60 60 60 -1"
	"./philo 0 60 60 60"
	"./philo 201 60 60 60"
)

echo "Running tests where philosophers should not die":

for d_test in "${die_test[@]}"; do
	echo "Running test: $d_test"

done


for test in "${tests[@]}"; do
    echo "Running test: $test"
    
    $test &
    PID=$!
    
    sleep 10
    
    if ps -p $PID > /dev/null; then
        kill $PID
        wait $PID 2>/dev/null
        
        echo "OK!"
    else
        echo "Test failed: $test"
    fi
    
    echo
done

make fclean
