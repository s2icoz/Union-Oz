#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "ValorOz.h"

using namespace std;

int main(){
  Operaciones input;
  char *id1 = new char(), *id2 = new char(), *v1 = new char(), *v2 = new char();
  int x = 3;
  while(x--){
    //char id_1[3] = tolower(id1), id_2[3] = tolower(id2);
    scanf("%[^.]%*c %s %[^=]%*c %[^\n]%*c",id1,id2,v1,v2);
    input.entrada(id1,id2,v1,v2);
  }
  input.imprimir();
  return 0;
}
