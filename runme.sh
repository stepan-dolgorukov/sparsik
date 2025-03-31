#!/usr/bin/env sh

rm --force ./A ./A.gz ./B ./B.gz ./C ./D
make
chmod u+x ./create_A.py
./create_A.py
./sparsik ./A ./B
gzip --keep ./A
gzip --keep ./B
gzip --stdout --decompress ./B.gz | ./sparsik ./C
./create_A.py
./sparsik -s 100 ./A ./D
stat --format='File name = %n, number of blocks allocated = %b' ./A ./A.gz ./B ./B.gz ./C ./D
