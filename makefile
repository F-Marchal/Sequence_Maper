# =================================== Basic Vars ===================================
CXX = g++ 	
CXXFLAG = -Wall -Wextra -Werror -ansi -pedantic -std=c++14
MAIN_CPP = main.cpp		
RESULT = ./main
DOCFOLDER = ./doc

# ====================================== Phony ======================================
.PHONY: run doxyW cleanDoxy cleanCode clean readDoc doxy

# =================================== Compilation ===================================
# Covert "main.cpp to main.o"
MAIN_o =  $(shell echo $(MAIN_CPP) | sed 's#\.cpp#\.o#g')	

# Find all dependicies of main.cpp      | remove "main.o :" | Conver .cpp to .hpp   | SubFolder/../ from paths "
FILES_hpp = $(shell g++ -MM $(MAIN_CPP) |  sed 's#[^:]*:##' | sed 's#\.cpp#\.hpp#g' | sed -E 's#\s.*\.\.\/# #g') 
FILES_cpp = $(shell echo $(FILES_hpp) | sed 's/\.hpp/\.cpp/g')
#									| Turn cpp to .O          | Turn "/" to "_"| Turn "\" to "_"| Add folder path
FILES_o = $(shell echo $(FILES_cpp) | sed 's#\.cpp#\.o#g') # | sed 's#\/#_#g' | sed 's#\\#_#g' | sed 's#\s# $(BIN)/#g' | sed 's#^#$(BIN)\/#'

# Default execution
all: run doxy

# Generate all .o next to the .cpp
$(RESULT): $(FILES_o)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Generate all .o next to the .cpp
%.o: %.cpp.replace("/", "_")
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(RESULT)
	clear
	$(RESULT)


cleanCode:
	find . -type f -name '*.o' | xargs rm -f

clean: cleanCode cleanDoxy


# =================================== Doxygen ===================================

doxyW:
	doxywizard &

doxy: cleanDoxy $(DOCFOLDER)
	doxygen Doxyfile -output $(DOCFOLDER)	

$(DOCFOLDER)/html/index.html:  doxy

readDoc: $(DOCFOLDER)/html/index.html
	firefox $(DOCFOLDER)/html/index.html		

$(DOCFOLDER):
	mkdir $(DOCFOLDER)

cleanDoxy:
	rm -r "$(DOCFOLDER)/html" -f
	rm -r "$(DOCFOLDER)/latex" -f
	
	
# Note :
# $^ = All prerequisites of a rule
# $< = First prerequisites of a rule
# $@ = Target of the tule
