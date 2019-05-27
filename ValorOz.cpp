#include <iostream>
#include <cstdlib>
#include <list>
#include <algorithm>
#include "ValorOz.h"

using namespace std;

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


ValorOz::ValorOz(string n_key){
/*Constructor incial de ValorOz que le concede una clave*/
/*Pre: n_key*/
/*Pos: ValorOz {key = n_key, val = none, father = NULL}*/
  key = n_key;
  val = vacio;
  father = NULL;
}

void ValorOz::set_father(ValorOz *n_father){
/*Se le da un valor al father del ValorOz*/
/*Pre: n_father == NULL*/
/*Pos: father = n_father*/
  if (n_father != NULL && n_father != this){
    father = n_father;
  }
}


void ValorOz::add_sons(ValorOz *n_son){
/*Se agrega un ValorOz al lista de hijos del ValorOz*/
/*Pre: n_son != NULL*/
/*Pos: sons = <n_son> si sons == <>
       sons = <...n_son...> si sons != <>*/
  int i=0;
  if (n_son != NULL){
    int i = 0;
    sons.push_front(n_son);
    n_son->set_father(this);
    i = 0;
  }
}
void ValorOz::add_sons(list<ValorOz *> n_sons){
/*Se añade un lista de ValorOz al lista de hijos del ValorOz*/
/*Pre: n_sons != <>*/
/*Pos: sons = <n_sons> si sons == <>
       sons = <...n_sons...> si sons != <>*/
  if (!n_sons.empty()){
    int i = 0;
    for (list<ValorOz *>::iterator it = n_sons.begin(); i < n_sons.size(); it++, i++) {
      add_sons(*it);
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


string ValorOz::get_key(){
/*Funcion que consulta la clave de un ValorOz*/
/*Pre: key != ""*/
/*Pos: key*/
  return key;
}


ValorOz* ValorOz::get_father(){
/*Retorna el puntero father del ValorOz*/
/*Pre: True*/
/*Pos: NULL si father == NULL
       *ValorOz si father != NULL*/
  if(father)
    return father;
  else
    return NULL;
}


list<ValorOz *> ValorOz::get_sons(){
/*Retorna la lista de hijos del ValorOz*/
  return sons;
}


void ValorOz::get_val(char &ans){
/*Retorna el val del ValorOz*/
  ans = val;
}


void ValorOz::get_val(Comparator &ans){
  if (father){
    father->get_val(ans);
  }
  else{
    ans = val;
  }
}


void ValorOz::set_val(char v){
/*Da el valor de vacio al ValorOz*/
/*Pre: El valor no debe tener un valor asignado, la convencion de vacio
debe ser '_'*/
/*Pos: ()*/
  if (val == '_'){
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


bool ValorOz::empty(){
  if (father){
    return father->empty();
  }
  else{
    return (val == vacio);
  }
}


void ValorOz::consultar_val(){
  cout << val;
}

/*===ValorOz_Int===*/

ValorOz_Int::ValorOz_Int(string n_key, int entero) : ValorOz(n_key){
/*Se hace el constructor de ValorOz con la misma llave n_key y se le cambia el
val al int entero*/
/*Pre: n_key, entero*/
/*Pos: ValorOz_Int {key = n_key, val = entero, father = NULL}*/
  val = entero;
};


void ValorOz_Int::get_val(int &ans){
/*Le da el valor interno del ValorOz_Int a un entero*/
/*Pre: ans*/
/*Pos: ans = val*/
  ans = val;
}


void ValorOz_Int::get_val(Comparator &ans){
/*Le da el valor interno del ValorOz_Int a un Comparator*/
/*Pre: ans sin haber sido afectado*/
/*Pos: ans = val*/
  if (father){
    father->get_val(ans);
  }
  else{
    ans = val;
  }
}


void ValorOz_Int::set_val(int num){
/*Le da un valor al val del ValorOz_Int*/
/*Pre: val == 0*/
/*Pos: val = num*/
  if (val == num);
  else if (val == 0){
    val = num;
  }
  else{
    fprintf(stderr, "Asignación de una constante a un valor con referencia\n");
    exit(1);
  }
}


void ValorOz_Int::set_val(Comparator &comp){
  /*Iguala el val del ValorOz_Int al valor de un Comparator*/
  /*Pre: val == vacio*/
  /*Pos: val = Comparator->entero*/
  if (val == comp.un_comp.i);
  else if (val == 0){
    val = comp.un_comp.i;
  }
  else{
    fprintf(stderr, "Asignación de una constante a un valor con referencia\n");
    exit(1);
  }
}


bool ValorOz_Int::empty(){
/*Observa si un ValorOz_Int está vacio*/
/*Pre: True*/
/*Pos: True si val == vacio
       False si val != vacio*/
  return (val == vacio);
}


void ValorOz_Int::consultar_val(){
/*Imprime el val del ValorOz_Int*/
/*Pre: True*/
/*Pos: val por consola*/
  cout << val;
}

/*===ValorOz_Float===*/

ValorOz_Float::ValorOz_Float(string n_key, float flotante) : ValorOz(n_key){
/*Se hace el constructor de ValorOz con la misma llave n_key y se le cambia el
val al float flotante*/
/*Pre: n_key, flotante*/
/*Pos: ValorOz_Float {key = n_key, val = flotante, father = NULL}*/
  val = flotante;
}

float ValorOz_Float::get_val(float &ans){
/*Le da el valor interno del ValorOz_Float a un float*/
/*Pre: ans*/
/*Pos: ans = val*/
  ans = val;
}


void ValorOz_Float::get_val(Comparator &ans){
/*Le da el valor interno del ValorOz_Float a un Comparator*/
/*Pre: ans sin haber sido afectado*/
/*Pos: ans = val*/
  if (father){
    father->get_val(ans);
  }
  else{
    ans = val;
  }
}


void ValorOz_Float::set_val(float num){
/*Le da un valor al val del ValorOz_Float*/
/*Pre: val == 0*/
/*Pos: val = num*/
  if (val == num);
  else if (val == 0){
    val = num;
  }
  else{
    fprintf(stderr, "Asignación de una constante a un valor con referencia\n");
    exit(1);
  }
}


void ValorOz_Float::set_val(Comparator &comp){
/*Iguala el val del ValorOz_Float al valor de un Comparator*/
/*Pre: val == vacio*/
/*Pos: val = Comparator->flotante*/
  if (val == comp.un_comp.f);
  else if (val == 0){
    val = comp.un_comp.f;
  }
  else{
    fprintf(stderr, "Asignación de una constante a un valor con referencia\n");
    exit(1);
  }
}


bool ValorOz_Float::empty(){
/*Observa si un ValorOz_Float está vacio*/
/*Pre: True*/
/*Pos: True si val == vacio
       False si val != vacio*/
  return (val == vacio);
}

void ValorOz_Float::consultar_val(){
/*Imprime el val del ValorOz_Float*/
/*Pre: True*/
/*Pos: val por consola*/
  cout << val;
}

/*====ValorOz_Reg====*/
Campo::Campo(string n_name){
  name = n_name;
  type = "vacio";
}
string Campo::get_val(){
  return val;
}
void Campo::cons_val(){
  cout << val;
}

Campo_Int::Campo_Int(string n_name, int n_entero) : Campo(n_name){
  val = n_entero;
  type = "int";
}
void Campo_Int::cons_val(){
  cout << name << ':' << val;
}

Campo_Float::Campo_Float(string n_name, float n_flotante) : Campo(n_name){
  val = n_flotante;
  type = "float";
}
void Campo_Float::cons_val(){
  cout << name << ':' << val;
}

Campo_Key::Campo_Key(string n_name, string key) : Campo(n_name){
  val = key;
  type = "key";
}
string Campo_Key::get_val(){
  return val;
}
void Campo_Key::cons_val(){
  cout << name << ':' << val;
}

Campo_Oz::Campo_Oz(string n_name, ValorOz *n_Oz) : Campo(n_name){
  val = n_Oz;
  type = "Oz";
}
void Campo_Oz::cons_val(){
  Comparator comp;
  val->get_val(comp);
  if (comp.type == "int")
    cout << comp.un_comp.i;
  if (comp.type == "float")
    cout << comp.un_comp.f;
  if (comp.type == "char")
    if (comp.un_comp.c == '|')
      cout << val->get_key();
    else if (comp.un_comp.c == '_')
      val->consultar_val();
}

ValorOz_Reg::ValorOz_Reg(string n_key, string n_etiqueta, list<Campo *> n_campos) : ValorOz(n_key){
  etiqueta = n_etiqueta;
  campos = n_campos;
}


string ValorOz_Reg::get_etiqueta(){
  return etiqueta;
}


list<Campo *> ValorOz_Reg::get_campos(){
  return campos;
}


void ValorOz_Reg::consultar_val(){
  cout << '['<< etiqueta << '(';
  int i = 0;
  for (auto it = campos.begin(); i < campos.size(); it++, i++) {
    cout<< (*it)->name << ": ";
    (*it)->cons_val();
    if (i < campos.size() - 1)cout << ", ";
  }
  cout << ")]";
}

/*=====Almacen=====*/

bool Almacen::in_almacen(string key){
/*Determina si existe algun ValorOz para la clave key en el Almacen*/
/*Pre: key*/
/*Pos: True si key pertenece a las claves de Almacen
       False si key no pertenece a las claves del Almacen*/
  int i = 0;
  for (map<string, ValorOz *>::iterator it = variables.begin();
   it != variables.end() && it->first != key;
    it++, i++);
  return (i != variables.size());
}


bool Almacen::is_empty(string key){
/*Determina si un ValorOz del Almacen está vacio*/
/*Pre: Existe ValorOz->key == key && key pertenece a variables->keys*/
/*Pos: /*Pos: True si ValorOz->val == vacio
       False si ValorOz->val != vacio*/
  if(!in_almacen(key)){
    fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
    exit(1);
  }
  return variables[key]->empty();
}


void Almacen::agregar_variable(string n_key){
/*Agrega un nuevo ValorOz al Almacen*/
/*Pre: !(Existe ValorOz->key == key && key pertenece a variables->keys)*/
/*Pos Almacen = {...(n_key, nuevo ValorOz)...}*/
  if (in_almacen(n_key)){
    fprintf(stderr, "Redefinición de un ValorOz existente en el Almacen\n");
    exit(1);
  }
  ValorOz *n_var;
  n_var = new ValorOz(n_key);
  variables[n_key] = n_var;
}


void Almacen::agregar_variable(string n_key, int entero){
/*Agrega un nuevo ValorOz al Almacen*/
/*Pre: !(Existe ValorOz->key == key && key pertenece a variables->keys), entero*/
/*Pos Almacen = {...(n_key, nuevo ValorOz_Int)...}
      ValorOz_Int->val = entero*/
  if (in_almacen(n_key)){
    fprintf(stderr, "Redefinición de un ValorOz existente en el Almacen\n");
    exit(1);
  }
  ValorOz_Int *n_var;
  n_var = new ValorOz_Int(n_key, entero);
  variables[n_key] = n_var;
}


void Almacen::agregar_variable(string n_key, float flotante){
/*Agrega un nuevo ValorOz al Almacen*/
/*Pre: !(Existe ValorOz->key == key && key pertenece a variables->keys)*/
/*Pos Almacen = {...(n_key, nuevo ValorOz_Float)...}
      ValorOz_Float->val = flotante*/
  if (in_almacen(n_key)){
    fprintf(stderr, "Redefinición de un ValorOz existente en el Almacen\n");
    exit(1);
  }
  ValorOz_Float *n_var;
  n_var = new ValorOz_Float(n_key, flotante);
  variables[n_key] = n_var;
}


void Almacen::agregar_variable(string n_key, string n_etiqueta, list<Campo *> n_campos){
/*Agrega un nuevo ValorOz al Almacen*/
/*Pre: !(Existe ValorOz->key == key && key pertenece a variables->keys)*/
/*Pos Almacen = {...(n_key, nuevo ValorOz_Reg)...}
      ValorOz_Float->etiqueta = n_etiqueta*/
  if (in_almacen(n_key)){
    fprintf(stderr, "Redefinición de un ValorOz existente en el Almacen\n");
    exit(1);
  }
  ValorOz_Reg *n_var;
  int i = 0;
  list<Campo *> n_campos2;
  for (list<Campo *>::iterator it = n_campos.begin(); i < n_campos.size(); it++, i++) {
    if ((*it)->type == "key"){
      if (in_almacen((*it)->get_val())){
        Campo_Oz *temp;
        temp = new Campo_Oz((*it)->name, variables[(*it)->get_val()]);
        n_campos2.push_front(temp);
      }
      else{
        fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
        exit(1);
      }
    }
    else{
      n_campos2.push_front(*it);
    }
  }
  n_var = new ValorOz_Reg(n_key, n_etiqueta, n_campos2);
  variables[n_key] = n_var;
}


void Almacen::unificar(string key, int n_val){
  if (!in_almacen(key)){
    fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
    exit(1);
  }
  if (variables[key]->get_father())
    key = variables[key]->get_father()->get_key();
  Comparator comp;
  variables[key]->get_val(comp);
  if (is_empty(key)){
    // Se supone que solo hay ValorOz_Int o Float con valores != vacio ya que
    // el cambio de valor es lo que supone su creacion
    if (comp.type == "char"){
      ValorOz_Int *n_Int;
      n_Int = new ValorOz_Int(variables[key]->get_key(), n_val);
      n_Int->set_father(variables[key]->get_father());
      n_Int->add_sons(variables[key]->get_sons());
      delete variables[key];
      variables[key] = n_Int;
    }
    else{
      fprintf(stderr, "Asignación de valor a un ValorOz no vacio\n");
      exit(1);
    }
  }
  else{
    if (n_val != comp.un_comp.i){
      fprintf(stderr, "Asignación de valor a un ValorOz no vacio\n");
      exit(1);
    }
  }
}


void Almacen::unificar(string key, float n_val){
  if (!in_almacen(key)){
    fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
    exit(1);
  }
  if (variables[key]->get_father())
    key = variables[key]->get_father()->get_key();
  Comparator comp;
  variables[key]->get_val(comp); //Extrae el valor de la variable correspondiente
  //a key en el mapa
  if (is_empty(key)){
    if (comp.type == "char"){
      ValorOz_Float *n_Float;
      n_Float = new ValorOz_Float(variables[key]->get_key(), n_val);
      n_Float->set_father(variables[key]->get_father());
      n_Float->add_sons(variables[key]->get_sons());
      delete variables[key];
      variables[key] = n_Float;
    }
    else{
      fprintf(stderr, "Asignación de valor a un ValorOz no vacio\n");
      exit(1);
    }
  }
  else{
    if (n_val != comp.un_comp.f){
      fprintf(stderr, "Asignación de valor a un ValorOz no vacio\n");
      exit(1);
    }
  }
}


void Almacen::unificar(string key, string n_etiqueta, list<Campo *>n_campos){
  if (!in_almacen(key)){
    fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
    exit(1);
  }
  Comparator comp;
  variables[key]->get_val(comp);
  if (is_empty(key)){
    if (comp.type == "char"){
      ValorOz_Reg *n_Reg;
      n_Reg = new ValorOz_Reg(variables[key]->get_key(), n_etiqueta, n_campos);
      n_Reg->set_father(variables[key]->get_father());
      n_Reg->add_sons(variables[key]->get_sons());
      delete variables[key];
      variables[key] = n_Reg;
    }
    else{
      fprintf(stderr, "Asignación de valor a un ValorOz no vacio\n");
      exit(1);
    }
  }
}


void Almacen::print_almacen(){
/*Imprime la informacion de cada elemento del Almacen*/
/*Pre: True*/
/*Pos: informacion de cada elemento del Almacen por consola*/
  for (map<string, ValorOz *>::iterator it = variables.begin();
   it != variables.end(); it++){
     if (it->second->get_father()){
       cout << it->first << " -> " << it->second->get_father()->get_key() << endl;
     }
     else{
       cout << it->first << ' ';
       it->second->consultar_val();
       cout << endl;
     }
  }
}


bool Almacen::equal_vals(string key1, string key2){
/*Determina si dos ValorOz del Almacen tienen el mismo ValorOz*/
/*Pre: (key1, key2) e variables*/
/*Pos: True si valor de key1 == valor de key2
       False si valor de key1 != valor de key2*/
  if(in_almacen(key1) && in_almacen(key2)){
    Comparator comp1, comp2;
    variables[key1]->get_val(comp1);
    variables[key2]->get_val(comp2);
    return (comp1 == comp2);
  }
  fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
  exit(1);
}


void Almacen::unificar(string val1, string val2){
/*Liga dos ValorOz del Almacen*/
/*Pre (val1 == vacio || val2 == vacio) || (val1->val == val2->val)*/
/*Pos val1 <-> val2*/
  if(!in_almacen(val1) || !in_almacen(val2)){
    fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
    exit(1);
  }
  ValorOz *temp_father1, *temp_father2;

  if (is_empty(val1)){
    //hacer que val2 sea el padre;
    if (prev_union(variables[val1], variables[val2]) ||
     prev_union(variables[val2], variables[val1])){}
    else{
      /*Asignación temp_father*/
      if (variables[val2]->get_father())
        temp_father2 = variables[val2]->get_father();
      else
        temp_father2 = variables[val2];
      //Cambio de ValorOz
      /*if (!is_empty(val2)){
        Comparator comp;
        temp_father2->get_val(comp);
        variables.erase(val1);
        if(comp.type == "int"){
          //ValorOz_Int *n_ValorOz = new ValorOz_Int(val2, comp)
          agregar_variable(val1, comp.un_comp.i);
        }
        if (comp.type == "float"){
          //ValorOz_Float *n_ValorOz = new ValorOz_Float(val2, comp)
          agregar_variable(val1, comp.un_comp.f);
        }
      }*/
      /*Asignación temp_father*/
      if (variables[val1]->get_father())
        temp_father1 = variables[val1]->get_father();
      else
        temp_father1 = variables[val1];

      temp_father2->add_sons(temp_father1);
      if (temp_father1->get_sons().size()){
        temp_father2->add_sons(temp_father1->get_sons());
        temp_father1->elim_sons();
      }
    }
  }
  else{
    if (is_empty(val2) || equal_vals(val1, val2)){
      if (prev_union(variables[val1], variables[val2]) ||
       prev_union(variables[val2], variables[val1])){}
      else{
        //hacer que val1 sea el padre;
        /*Asignación temp_father*/
        if (variables[val1]->get_father())
          temp_father1 = variables[val1]->get_father();
        else
          temp_father1 = variables[val1];
        /*Asignación temp_father*/
        if (variables[val2]->get_father())
          temp_father2 = variables[val2]->get_father();
        else
          temp_father2 = variables[val2];
        temp_father1->add_sons(temp_father2);
        if (temp_father2->get_sons().size()){
          temp_father1->add_sons(temp_father2->get_sons());
          temp_father2->elim_sons();
        }
      }
    }
    else{
      fprintf(stderr, "Unificación de variables con valores diferentes\n");
      exit(1);
    }
  }
}
