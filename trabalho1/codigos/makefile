casca:
	gcc -c bufferEntrada.c -o bufferEntrada.o
	gcc -c bufferSaida.c -o bufferSaida.o
	gcc -c k_vias.c -o k_vias.o
	gcc -c ARN.c -o ARN.o
	gcc -c casca.c -o casca.o
	gcc main.c bufferEntrada.o bufferSaida.o k_vias.o ARN.o casca.o -o main.exe -lm
	.\main.exe

entrada:
	gcc -c bufferEntrada.c -o bufferEntrada.o
	gcc testeBufferEntrada.c bufferEntrada.o -o testeBufferEntrada.exe
	.\testeBufferEntrada.exe

saida:
	gcc -c bufferSaida.c -o bufferSaida.o
	gcc -c ARN.c -o ARN.o
	gcc testeBufferSaida.c ARN.o bufferSaida.o -o testeBufferSaida.exe
	.\testeBufferSaida.exe

kvias:
	gcc -c bufferEntrada.c -o bufferEntrada.o
	gcc -c bufferSaida.c -o bufferSaida.o
	gcc -c k_vias.c -o k_vias.o
	gcc -c ARN.c -o ARN.o
	gcc teste_k_vias.c k_vias.o ARN.o bufferSaida.o bufferEntrada.o -o teste_k_vias.exe
	.\teste_k_vias.exe