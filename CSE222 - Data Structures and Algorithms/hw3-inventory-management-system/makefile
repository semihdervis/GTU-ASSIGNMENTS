# Java compiler
JAVAC = javac
# Java runtime
JAVA = java
# Java source files directory
SRCDIR = .
# Java classes directory
BINDIR = bin
# Main class to run
MAINCLASS = Main

# Default target, will run when you type just `make`
default: clean compile run

# Target to clean up compiled files
clean:
	@rm -rf $(BINDIR)/*

# Target to compile Java source files
compile:
	@mkdir -p $(BINDIR)
	@$(JAVAC) -d $(BINDIR) $(SRCDIR)/*.java

# Target to run the Java program
run:
	@$(JAVA) -cp $(BINDIR) $(MAINCLASS)

jdoc:
	@javadoc -d jdoc *.java