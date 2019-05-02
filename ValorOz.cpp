#include <iostream>
#include <cstdlib>
#include "ValorOz.h"

using namespace std;

int prev_union(ValorOz *objetivo, ValorOz *contenedor){
  for (int i = 0; i < contenedor->get_sons().size(); i ++) {
    if (contenedor->get_sons()[i] == objetivo){
      return 1;
    }
  }
  return 0;
}


int ValorOz::get_val(){
  if (father != NULL){
    return father->val;
  }
  else{
    return val;
  }
}


ValorOz* ValorOz::get_father(){
  return father;
}


std::vector<ValorOz *> ValorOz::get_sons(){
  return sons;
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
  if (val == -1){
    if (father != NULL){
      *father = num;
    }
    else{
      val = num;
    }
  }
  else{
    fprintf(stderr, "Asignación de una constante a un valor con referencia\n");
    exit(1);
    /*referencia => que apunta a alguien,
    /*referenciado => que alguien apunta a él.*/
  }
}


void ValorOz::operator =(ValorOz &val2){
  if (this == &val2){
    fprintf(stderr, "Unión de una variable a si misma\n");
  }
  if (campos.size() > 0 && val2.campos.size() > 0 &&
      campos.size() == val2.campos.size()){
    /*Caso etiquetas*/
    /*Mas de un campo e igual cantidad de campos
    /*Etiquetas de 1 solo campo seran manejadas como variables normales*/
  }
  /*Condicion: hace que nunca se haga un caso de asignacion de variables
  con valores ya asignados normales*/
  else if (campos.size() + val2.campos.size() == 0){
    ValorOz *temp_father;
    if (!prev_union(this, &val2) && !prev_union(&val2, this)){
      if (father == NULL){
        if (val2.get_father() && val2.get_sons().size()){
          fprintf(stderr, "Asignacion entre variables previamente ligadas\n");
          exit(1);
        }
        //Emparentamiento de izquierda a derecha
        val2.get_father()?temp_father = val2.get_father(): temp_father = &val2;
        set_father(temp_father);
        temp_father->add_sons(this);
        if (sons.size()){
          temp_father->add_sons(get_sons());
          elim_sons();
        }
      }
      else if (val2.father == NULL){
        if(get_sons().size()){
          fprintf(stderr, "Asignacion entre variables previamente ligadas\n");
          exit(1);
        }
        //Emparentamiento de derecha a izquierda
        get_father()?temp_father = get_father(): temp_father = this;
        val2.set_father(temp_father);
        temp_father->add_sons(&val2);
        if (sons.size()){
          temp_father->add_sons(val2.get_sons());
          val2.elim_sons();
        }
      }
      else{
        fprintf(stderr, "Asignacion entre variables previamente ligadas\n");
      }
    }
  }
  else{
    if (campos.size() != val2.campos.size()){
      fprintf(stderr, "Las etiquetas tuvieron diferentes cantidades de campos\n");
      exit(1);
    }
  }
}

void ValorOz::set_father(ValorOz *n_father){
  father = n_father;
}


void ValorOz::add_sons(ValorOz *n_son){
  sons.push_back(n_son);
  n_son->set_father(this);
}
void ValorOz::add_sons(std::vector<ValorOz *> n_sons){
  for (vector<ValorOz *>::iterator it = n_sons.begin(); it != n_sons.end(); it++) {
    (*it)->set_father(this);
    sons.push_back(*it);
  }
}


void ValorOz::elim_sons(){
  sons.clear();
}
