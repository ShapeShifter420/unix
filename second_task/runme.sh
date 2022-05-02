#/bin/bash
rm -f file.lck stat_file
touch file
make
pid=()

./second & pid+=($!)
./second & pid+=($!)
./second & pid+=($!)
./second & pid+=($!)
./second & pid+=($!)
./second & pid+=($!)
./second & pid+=($!)
./second & pid+=($!)
./second & pid+=($!)
./second & pid+=($!)

su=0
sleep 5m

for p in ${pid[@]}
do
	kill -s INT $p
	if [[ $? -eq 0 ]]
	then
		((su++))
	fi
done

echo "Успешное завершение(10)" >"result.txt"
echo $su >>"result.txt"

echo "Количество записей(10)" >>"result.txt"
echo $(cat stat_file | wc -l) >>"result.txt"

echo "Статистика блокировок" >>"result.txt"
echo $(cat stat_file) >>"result.txt"

./second & p=($!) >> "result.txt"
sleep 5
rm -f file.lck
sleep 5
kill -s INT $p


cat result.txt
