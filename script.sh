#!/bin/bash

cat "a_example.txt" | ./a.out > a.output
echo "PID = $!"

cat "b_read_on.txt" | ./a.out > b.output
echo "PID = $!"

cat "c_incunabula.txt" | ./a.out > a.output
echo "PID = $!"

cat "d_tough_choices.txt" | ./a.out > a.output
echo "PID = $!"

cat "e_so_many_books.txt" | ./a.out > a.output
echo "PID = $!"

cat "f_libraries_of_the_world.txt" | ./a.out > a.output
echo "PID = $!"
