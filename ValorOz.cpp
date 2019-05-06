#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include "ValorOz.h"

using namespace std;

bool comparar(ValorOz *val1, ValorOz *val2){
  return (val1 > val2);
}

int prev_union(ValorOz *objetivo, ValorOz *contenedor){
/*Revisa si dos ValorOz están ligados*/
/*Pre: objetivo != NULL && contenedor != NULL*/
/*Pos: True si objetivo -> contenedor
        False si !(objetivo -> contenedor)*/
  if (!(objetivo != NULL && contenedor != NULL)){
    fprintf(stderr, "Revisión de ligación con parámetro NULL\n");
    exit(1);
  }
  list<ValorOz *>::iterator it = contenedor->get_sons().begin();
  for (int i = 0; i < contenedor->get_sons().size(); i++, it++) {
    if (*it == objetivo){
      return 1;
    }
  }
  return 0;
}


void ValorOz::set_father(ValorOz *n_father){
/*Se le da un valor al father del ValorOz*/
/*Pre: n_father != NULL*/
/*Pos: father = n_father*/
  if (n_father != NULL){
    father = n_father;
  }
}


void ValorOz::add_sons(ValorOz *n_son){
/*Se agrega un ValorOz al lista de hijos del ValorOz*/
/*Pre: n_son != NULL*/
/*Pos: sons = <n_son> si sons == <>
       sons = <...n_son...> si sons != <>*/
  if (n_son != NULL){
    sons.push_back(n_son);
    n_son->set_father(this);
  }
}
void ValorOz::add_sons(list<ValorOz *> n_sons){
/*Se añade un lista de ValorOz al lista de hijos del ValorOz*/
/*Pre: n_sons != <>*/
/*Pos: sons = <n_sons> si sons == <>
       sons = <...n_sons...> si sons != <>*/
  if (!n_sons.empty()){
    for (list<ValorOz *>::iterator it = n_sons.begin(); it != n_sons.end(); it++) {
      (*it)->set_father(this);
      sons.push_back(*it);
    }
  }
}


void ValorOz::elim_sons(){
/*Se elimian todos los hijos del ValorOz*/
/*Pre: sons != <>*/
/*Pos: sons = <>*/
  if (!sons.empty()){
    sons.clear();
  }
}


void ValorOz::set_campo(string llave, ValorOz *n_ValorOz){
  if (etiqueta != ""){
    campos.insert(cam(llave, n_ValorOz));
  }
  else{
    fprintf(stderr, "Operacion de registro en una variable simple\n");
    exit(1);
  }
}


void ValorOz::elim_campo(string llave){
  if (etiqueta != ""){
    bool find = false;
    int i = 0;
    for (list<string>::iterator it = get_campos_llaves().begin(); i < get_campos_llaves().size(); i++, it++) {
      if (*it == llave){
        find = true;
      }
    }
    if (find){
      campos.erase(llave);
    }
    else{
      fprintf(stderr, "Eliminacion de un campo inexistente en el ValorOz\n");
    }
  }
  else{
    fprintf(stderr, "Operacion de registro en una variable simple\n");
    exit(1);
  }
}


int ValorOz::get_val(){
/*Retorna el valor de un ValorOz*/
/*Pre: True*/
/*Pos: -1 si Val == Vacio
        Val si Val != Vacio*/
  if (father != NULL){
    return father->val;
  }
  else{
    return val;
  }
}


string ValorOz::get_etiqueta(){
/*Retorna la etiqueta de un ValorOz*/
/*Pre: etiqueta != vacio*/
/*Pos: "" si etiqueta == Vacio
        etiqueta si etiqueta != Vacio*/
  if (etiqueta != ""){
    return etiqueta;
  }
  else{
    return "";
  }
}


ValorOz* ValorOz::get_father(){
/*Retorna el puntero father del ValorOz*/
/*Pre: True*/
/*Pos: NULL si father == NULL
        *ValorOz si father != NULL*/
  return father;
}


list<ValorOz *> ValorOz::get_sons(){
/*Retorna la lista de hijos del ValorOz*/
  return sons;
}


list<string> ValorOz::get_campos_llaves(){
  list<string> llaves;
  for (map<string, ValorOz *>::iterator it = campos.begin(); it != campos.end();
   it++) {
    llaves.push_back(it->first);
  }
  return llaves;
}


ValorOz* ValorOz::get_campo_valor(string llave){
  if (etiqueta != ""){
    bool find = false;
    int i = 0;
    for (list<string>::iterator it = get_campos_llaves().begin(); i < get_campos_llaves().size(); i++, it++) {
      if (*it == llave){
        return campos[llave];
      }
    }
    fprintf(stderr, "Eliminacion de un campo inexistente en el ValorOz\n");
  }
  else{
    fprintf(stderr, "Operacion de registro en una variable simple\n");
    exit(1);
  }
}


void ValorOz::operator =(char v){
  /*Da el valor de vacio al ValorOz*/
  /*Pre: El valor no debe tener un valor asignado, la convencion de vacio
  debe ser '_'*/
  /*Pos: ...*/
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
  /*Liga el ValorOz a un entero*/
  /*Pre: El val de ValorOz debe ser el mismo parámetro o vacio*/
  /*Pos: val == num*/
  if (etiqueta == ""){
    if (get_val() == num);
    else if (val == -1){
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
  else{
    fprintf(stderr, "Asignación de una constante a un registro\n");
    exit(1);
  }
}


void ValorOz::operator =(ValorOz &val2){
  /*Liga el ValorOz con otro ValorOz*/
  /*Pre: No pueden ambos ValorOz estar previamente ligados a otros ValorOz
  que no sean el otro ValorOz de la operación; a no ser que compartan un
  val diferente a vacio. Además para registros, deben tener en común:
  etiquetas, número de campos y campos*/
  /*Pos: ValorOz ligado a Val2*/
  if (this == &val2 || get_val() == val2.get_val() && get_val() != -1){
    /*Caso en el que se trate de ligar un ValorOz a si mismo, o a alguien
    ligado a él, o se iguale a un ValorOz con quien comparta val y que este
    sea diferente a vacio*/
    //fprintf(stderr, "Unión de una variable a si misma\n");
  }
  else if (campos.size() > 0 && val2.campos.size() > 0 &&
  campos.size() == val2.campos.size()){
    /*Caso etiquetas*/
    /*Mas de un campo e igual cantidad de campos*/
  }
  else if (campos.size() + val2.campos.size() == 0){
    ValorOz *temp_father;
    //Comprueba si ya están ligados entre si
    if (!prev_union(this, &val2) && !prev_union(&val2, this)){
      //Emparentamiento de izquierda a derecha
      if (father == NULL){
        /*Si el otro tiene father se le pasaran los hijos del ValorOz al
        father de val2, de lo contrario se pasaran a val2*/
        val2.get_father()?temp_father = val2.get_father(): temp_father = &val2;
        if (get_val() != -1){
          *(temp_father) = get_val();
        }
        else if (val2.get_val() != -1)
        *(temp_father) = val2.get_val();

        temp_father->add_sons(this);
        if (sons.size()){
          temp_father->add_sons(get_sons());
          elim_sons();
        }
        /*Si val2 tiene father el ValorOz se liga al father de val2, de lo
        contrario se ligara a val2*/
        set_father(temp_father);
      }
      //Emparentamiento de derecha a izquierda
      else if (val2.father == NULL){
        /*Si el ValorOz tiene father se le pasaran los hijos de val2 al
        father, de lo contrario se pasaran al ValorOz*/
        get_father()?temp_father = get_father(): temp_father = this;
        if (get_val() != -1)
        *(temp_father) = get_val();
        else if (val2.get_val() != -1)
        *(temp_father) = val2.get_val();

        temp_father->add_sons(&val2);
        if (val2.sons.size()){
          temp_father->add_sons(val2.get_sons());
          val2.elim_sons();
        }
        /*Si el ValorOz tiene father val2 se liga al father del ValorOz, de lo
        contrario se ligara a ValorOz*/
        val2.set_father(temp_father);
      }
      else{
        //Casos de error
        fprintf(stderr, "Asignacion entre variables previamente ligadas\n");
        exit(1);
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

void ValorOz::operator =(string n_etiqueta){
  /*Se asigna un nombre a la etiqueta del ValorOz*/
  /*Pre: No puede estar ligado a algo diferente a vacio*/
  /*Pos: etiqueta = n_etiqueta*/
  if (get_val() ==  -1){
    etiqueta = n_etiqueta;
  }
  else{
    fprintf(stderr, "Asignacion de etiqueta a un ValorOz con valor ya definido\n");
    exit(1);
  }
}
