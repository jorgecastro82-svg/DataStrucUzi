#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>
#include <time.h>
#include <iostring.h>
#include <arbol.h>
#include <pila.h>

void infixToPostfix(char *infix,char *postfix);
int precedencia(char opc);
int verificarParentesis(char *cadena);

