Requisiti per poter eseguire il programma: 
	0a) installare opencv con brew  #installa la libreria opencv
		$ brew install opencv
	0b) installare pkg-config con brew  #serve per trovare la libreria opencv
		$ brew install pkg-config
	0c) installare openMP con brew  #installa la libreria omp
		$ brew install libomp

------------------------------------------------
Eseguire da terminale:
	-Sequenziale
		1) cambiare ../ con ./ all'interno di ogni path in main.cpp
		2) $ g++ -o prova main.cpp `pkg-config --cflags --libs opencv` 
		3) Una volta generato l'eseguibile:
			$ ./prova

	-OpenMP
		1) cambiare ../ con ./ all'interno di ogni path in main.cpp
		2) $ g++  -fopenmp main.cpp -o prova `pkg-config --cflags --libs opencv` 
		3) Una volta generato l'eseguibile di nome prova digitare:
			$ ./prova
------------------------------------------------
Eseguire con CLion:
	-Sequenziale:  Aprire il progetto Sequential 
	-OpenMP: Aprire il progetto OpenMP
------------------------------------------------
