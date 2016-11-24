CXX = g++
OPTIONS = -std=c++11 -O2 -DNDEBUG -D_GLIBCXX_DEBUG -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -Wshadow

program.exe: Cjt_cites.o Cjt_text.o program.o Text.o
	$(CXX) -o $@ $^

program.o: program.cc
		$(CXX) -c $^ $(OPTIONS)

Cjt_cites.o: Cjt_cites.cc
	$(CXX) -c $^ $(OPTIONS)

Cjt_text.o: Cjt_text.cc
	$(CXX) -c $^ $(OPTIONS)

Text.o: Text.cc
	$(CXX) -c $^ $(OPTIONS)

clean:
	rm *.o
	rm *.tar
	rm *.exe
