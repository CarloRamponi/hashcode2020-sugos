#!/bin/bash

cat "a_example.txt" | ./a.out > a.output &
A=$!
echo "PID A = $A"

cat "b_read_on.txt" | ./a.out > b.output &
B=$!
echo "PID B = $B"

cat "c_incunabula.txt" | ./a.out > c.output &
C=$!
echo "PID C = $C"

cat "d_tough_choices.txt" | ./a.out > d.output &
D=$!
echo "PID D = $D"

cat "e_so_many_books.txt" | ./a.out > e.output &
E=$!
echo "PID E = $E"

cat "f_libraries_of_the_world.txt" | ./a.out > f.output &
F=$!
echo "PID F = $F"


wait $A
wait $B
wait $C
wait $D
wait $E
wait $F

notify-send "Operazione terminata"
