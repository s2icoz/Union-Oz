#include <iostream>
#include <cstdlib>
#include "ValorOz.h"

int ValorOz::get_val(){
  if (sons.size() < 1){
      return val;
  }
  else{
    return sons[0]->val;
  }
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
    /*No queremos tener mas de un nivel de recursividad asi que a la hora de
    *asignar variables envez de hacer que una apunte a la otra, hacemos que la
    *vacia apunte al hijo de la otra, si es que lo tiene.
    /*x = y, z = x : No z->x->y, Si x->y z->y*/
    if (!sons.size()){
      if (!val2.sons.size()){ /*Ninguno tiene hijos*/
        set_son(&val2);
        if (father != NULL)
          father->set_son(&val2);
      }
      else{
        set_son(val2.sons[0]);
        if (father != NULL)
          father->set_son(&val2);
      }
    }
    else{
      val2.set_son(sons[0]);
      if (val2.father != NULL)
        val2.father->set_son(sons[0]);
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


void ValorOz::set_son(ValorOz *n_son){
  sons.clear();
  sons.push_back(n_son);
}
