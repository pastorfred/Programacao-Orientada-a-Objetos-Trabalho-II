TRABALHOII = app
CFLAGS=-c -std=c++11

all: ${TRABALHOII}

${TRABALHOII}: Aplicacao.o Arbitro.o Data.o Evento.o Jogador.o Pais.o Partida.o Pessoa.o Tecnico.o app.o
				@g++ Aplicacao.o Arbitro.o Data.o Evento.o Jogador.o Pais.o Partida.o Pessoa.o Tecnico.o app.o -o ${TRABALHOII}

Aplicacao.o: Aplicacao.cpp Aplicacao.hpp Arbitro.o Data.o Evento.o Jogador.o Pais.o Partida.o Pessoa.o Tecnico.o
			@g++ ${CFLAGS} Aplicacao.cpp

Arbitro.o: Arbitro.cpp Arbitro.hpp Pessoa.o
			@g++ ${CFLAGS} Arbitro.cpp
			
Data.o: Data.cpp Data.hpp 
			@g++ ${CFLAGS} Data.cpp

Evento.o: Evento.cpp Evento.hpp Jogador.o
			@g++ ${CFLAGS} Evento.cpp

Jogador.o: Jogador.cpp Jogador.hpp Pessoa.o
			@g++ ${CFLAGS} Jogador.cpp

Pais.o: Pais.cpp Pais.hpp 
			@g++ ${CFLAGS} Pais.cpp

Partida.o: Partida.cpp Partida.hpp Data.o Pais.o Evento.o
			@g++ ${CFLAGS} Partida.cpp

Pessoa.o: Pessoa.cpp Pessoa.hpp Data.o
			@g++ ${CFLAGS} Pessoa.cpp

Tecnico.o: Tecnico.cpp Tecnico.hpp Pessoa.o
			@g++ ${CFLAGS} Tecnico.cpp

app.o:		app.cpp Aplicacao.o
			@g++ ${CFLAGS} app.cpp

run: 		${TRABALHOII}
			@./${TRABALHOII}

clean:	
				@rm -f Aplicacao.o Arbitro.o Data.o Evento.o Jogador.o Pais.o Partida.o Pessoa.o Tecnico.o app.o ${TRABALHOII}