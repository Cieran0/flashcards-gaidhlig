default:
	g++ -g main.cpp -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all:
	cp LearnGaelic.scot-scraper/*.txt .
	./getAudio.sh
	
install:
	make all
	cp LearnGaelic.scot-scraper/*.txt ~/usr/flashcards-gàidhlig/text/
	cp audio/*.mp3 ~/usr/flashcards-gàidhlig/audio
	cp images/*.png ~/usr/flashcards-gàidhlig/images
	sudo cp flashcards.desktop /usr/share/applications
	cp main	~/bin/flashcards-gàidhlig