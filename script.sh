#!/bin/bash

( ./a.out < a_example.txt > a.output; echo "A completed" ) &
A=$!
echo "PID A = $A"

( cat "b_read_on.txt" | ./a.out > b.output; echo "B completed" ) &
B=$!
echo "PID B = $B"

( cat "c_incunabula.txt" | ./a.out > c.output; echo "C completed" ) &
C=$!
echo "PID C = $C"

( cat "d_tough_choices.txt" | ./a.out > d.output; echo "D completed" ) &
D=$!
echo "PID D = $D"

( cat "e_so_many_books.txt" | ./a.out > e.output; echo "E completed" ) &
E=$!
echo "PID E = $E"

( cat "f_libraries_of_the_world.txt" | ./a.out > f.output; echo "F completed" ) &
F=$!
echo "PID F = $F"


wait $A
wait $B
wait $C
wait $D
wait $E
wait $F

notify-send "Operazione terminata"
