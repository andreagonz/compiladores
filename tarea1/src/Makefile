OBJ = token.o lex.yy.o

interprete: $(OBJ)
			$(LINK.cc) $^ -o $@ -lfl

$(OBJ): token.h

.PHONY: clean
clean :
		rm -f interprete *.o

flex:
		flex++ scanner.lex
