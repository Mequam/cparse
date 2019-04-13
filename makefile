cparse.o: parse.cc
	g++ -c -fpic parse.cc -o parse.o
build: parse.o
	g++ -shared parse.o -o libparse.so
clean:
	rm parse.o
install:
	mv libparse.so $(DESTDIR)/usr/lib
	cp parse.h $(DESTDIR)/usr/local/include
uninstall:
	rm $(DESTDIR)/usr/lib/libparse.so
	rm $(DESTDIR)/usr/local/include/parse.h
