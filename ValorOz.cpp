#include <iostream>
#include <cstdlib>
#include "ValorOz.h"

int ValorOz::get_val(){
  ValorOz *recorredor;
  recorredor = this;
  while (recorredor->sons.size()) {
    recorredor = recorredor->sons[0];
  }
  return recorredor->val;
}


void ValorOz::operator =(char v){
  if (val == -1){
    if (v != '_'){
      fprintf(stderr, "Asignación desconocida\n");
      exit(1);
    }
  }
  else{
    fprintf(stderr, "Asignación a un valor no vacío\n");
    exit(1);
  }
}


void ValorOz::operator =(int num){
  if (sons.size() == 0 && val == -1){
    val = num;
    /*Su padre y antecesores "tendrán" el mismo val porque a la hora de hacer
    /*get_val se busca hasta el nivel más profundo de hijos*/
  }
  else{
    fprintf(stderr, "Asignación de una constante a un valor con referencia\n");
    exit(1);
    /*referencia => que apunta a alguien,
    /*referenciado => que alguien apunta a él.*/
  }
}


void ValorOz::operator =(ValorOz &val2){
  if (sons.size() > 1 && val2.sons.size() > 1 &&
      sons.size() == val2.sons.size()){
    /*Caso etiquetas*/
    /*Mas de un campo e igual cantidad de campos
    /*Etiquetas de 1 solo campo seran manejadas como variables normales*/
  }
  /*Condicion: hace que nunca se haga un caso de asignacion de variables
  con valores ya asignados normales*/
  else if ((sons.size() + val2.sons.size()) < 2 &&
            (get_val() == -1 || val2.get_val() == -1)){
    /*Caso varaibles*/
    /*Recursividad para agregar ultimo nivel, ejemplo
    /*x = y
    /*z = y
    /*No queremos tener dos variables apuntanto a la misma variable, por esto
    /*llevamos la Recursividad de "y" al máximo y se la agregamos a "z" para que
    /*quede asi:
    /*z->x->y*/
    if (!sons.size()){
      sons.push_back(&val2);
    }
    else{
      val2.add_son(this);
    }
  }
  else{
    /*Esta condicion debe ir priemro*/
    if ((sons.size() + val2.sons.size()) == 2){
      fprintf(stderr, "Asignacion de variables con valores ya definidos\n");
      exit(1);
    }
    else if (sons.size() != val2.sons.size()){
      fprintf(stderr, "Las etiquetas tuvieron diferentes cantidades de campos\n");
      exit(1);
    }
  }
}


void ValorOz::add_son(ValorOz *n_son){
  sons.push_back(n_son);
}
