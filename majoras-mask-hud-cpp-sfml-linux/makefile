sfmlLibs = -lsfml-graphics -lsfml-window -lsfml-system 
#g++ -o MMHud MMHud.cpp model/Clock.o view/Clock.o -lm

model = model/Clock.o
view = view/Clock.o
tests = test/ClockTests.h
tdd = -DMM_TDD

%.o: %.cpp %.h
		$(CXX) -c -o $@ $< -Wall

all: tests MMHud
		./tests
		./MMHud
#fontTest: fontTest.cpp $(view)
#		$(CXX) -o $@ $^ $(sfmlLibs) -Wall

MMHud : MMHud.cpp $(model) $(view)
		$(CXX) -o $@ $^ $(sfmlLibs) -lm -Wall


#Test Driven Rules
tests: test/tests.cpp $(model) 
		$(CXX) -o $@ $^ -I. $(tdd)
		
test/tests.cpp: $(tests)
		python cxxtestgen.py -o $@ --error-printer $^ -lm

#Support Rules
clean:
		rm -f */*.o 

ctags: 
		ctags -R --c++-kinds=+p --fields=+iaS --extra=+q . 
clang: pchHeader.h
		clang -x c++-header ./pchHeader.h -fno-exceptions -fnu-runtime -o ./pchHeader.pch

