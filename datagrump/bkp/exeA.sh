#!/bin/bash
#lista=('1' '2' '3' '4' '5' '6' '7' '8' '9' '10' '11' '12' '13' '14' '15' '16' '17' '18' '19' '20' '30' '40' '50' '60' '70' '80' '90' '100' '110' '120' '130' '140' '150' '160' '170' '180' '190' '200' '220' '240' '280' '300' '350') 
lista=('1')
#for i in $(seq 3)
for i in ${lista[@]}
do	
	echo Experimento com window size = $i
	sed -i 's/unsigned int the_window_size =.*/unsigned int the_window_size = '$i';/' controller.cc

	cd ..
	make
	cd datagrump
	
	#./run-contest jose_wilson &> 'result_exeA/windowsize'$i'.txt'
	saida=$(./run-contest jose_wilson | grep "Average throughput:" | cut -d: -f2 | cut -d ' ' -f2 &> 'result_exeA/windowsize.txt')
	echo $saida
	#ler o arquivo
	#capturar o throughput e delay
	#calcular a potencia
	#gravar o valor da potencia no arquivo
	echo ok
done

