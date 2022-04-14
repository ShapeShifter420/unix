#/bin/sh
python3 gen.py
./first fileA fileB
gzip -c fileA > fileA.gz
gzip -c fileB > fileB.gz
gzip -cd fileB.gz | ./first fileC
./first fileA fileD 100
stat fileA
stat fileA.gz
stat fileB
stat fileB.gz
stat fileC
stat fileD