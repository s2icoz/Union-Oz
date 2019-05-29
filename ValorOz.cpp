#include <iostream>
#include <cstdlib>
#include <list>
#include <sstream>
#include <string.h>
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
/*Pre: True*/
/*Pos: lista de los hijos del ValorOz*/
  return sons;
}


void ValorOz::get_val(char &ans){
/*Otorga el val del ValorOz a un char*/
/*Pre: char*/
/*Pos: char == val*/
  if (father){
    father->get_val(ans);
  }
  else{
    ans = val;
  }
}


void ValorOz::get_val(Comparator &ans){
/*Otorga el val del ValorOz a un Comparator*/
/*Pre: Comparator*/
/*Pos: Comparator == val*/
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
/*Confirma si un ValorOz está vacio*/
/*Pre: True*/
/*Pos: Si esta vacio True, de lo contrario False*/
  if (father){
    return father->empty();
  }
  else{
    return (val == vacio);
  }
}


void ValorOz::consultar_val(){
/*Muestra por pantalla el val del ValorOz*/
/*Pre: True*/
/*Pos: val por pantalla*/
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

Campo::Campo(){
  type = "vacio";
}
// string Campo:: get_val(){}
void Campo:: cons_val(){}

Campo_Int::Campo_Int(int n_entero) : Campo(){
  val = n_entero;
  type = "int";
}
int Campo_Int::get_val(){
  return val;
}
void Campo_Int::cons_val(){
  cout  << val;
}

Campo_Float::Campo_Float(float n_flotante) : Campo(){
  val = n_flotante;
  type = "float";
}
float Campo_Float::get_val(){
  return val;
}
void Campo_Float::cons_val(){
  cout << val;
}

Campo_Key::Campo_Key(string key) : Campo(){
  val = key;
  type = "key";
}
string Campo_Key::get_val(){
  return val;
}
void Campo_Key::cons_val(){
  cout << val;
}

Campo_Oz::Campo_Oz(ValorOz *n_Oz) : Campo(){
  val = n_Oz;
  type = "Oz";
}
string Campo_Oz::get_val(){
  return val->get_key();
}
void Campo_Oz::cons_val(){
  // Comparator comp;
  // val->get_val(comp);
  // if (comp.type == "int")
  //   cout << comp.un_comp.i;
  // if (comp.type == "float")
  //   cout << comp.un_comp.f;
  // if (comp.type == "char")
  //   if (comp.un_comp.c == '|'){
  //     val->consultar_val();
  //   }
  //   else if (comp.un_comp.c == '_')
  //     cout << val->get_key();
  cout << val->get_key();
}

ValorOz_Reg::ValorOz_Reg(string n_key, string n_etiqueta, map<string, Campo *> n_campos) : ValorOz(n_key){
/*Crea un ValorOz_Reg con una llave, etiqueta, y lista de campos definidas*/
/*Pre: n_key, n_etiqueta, n_campos*/
/*Pos: nuevo ValorOz_Reg {n_key, n_etiqueta, n_campos}*/
  etiqueta = n_etiqueta;
  campos = n_campos;
}


string ValorOz_Reg::get_etiqueta(){
/*Devuelve la etiqueta de un ValorOz_Reg*/
/*Pre: True*/
/*Pos: etiqueta*/
  return etiqueta;
}


map<string, Campo *> ValorOz_Reg::get_campos(){
/*Devuelve los campos de un ValorOz_Reg*/
/*Pre: True*/
/*Pos: campos*/
  return campos;
}


void ValorOz_Reg::set_campo(string name, Campo *val){
/*Modifica el valor de un campo en el ValorOz_Reg*/
/*Pre: nuevo campo*/
/*Pos: campos {c1, c2, ... cx {name, val} ... cn}*/
  campos[name] = val;
}


void ValorOz_Reg::consultar_val(){
/*Muestra por pantalla la etiqueta y los campos del ValorOz_Reg*/
/*Pre: True*/
/*Pos: etiqueta y campos por consola*/
  int i = 0;
  cout << '['<< etiqueta << '(';
  for (map<string, Campo *>::iterator it = campos.begin(); it != campos.end(); it++, i++) {
    cout<< it->first << ": ";
    it->second->cons_val();
    if (i < campos.size() - 1)cout << ", ";
  }
  cout << ")]";
}
void ValorOz_Reg::get_val(Comparator &ans){
/*Le da el val del ValorOz_Reg que es caracteristico para su facil identificacion*/
/*Pre: Comparator*/
/*Pos: Comparator = val*/
  if (father){
    father->get_val(ans);
  }
  else{
    ans = val;
  }
}


list<string> ValorOz_Reg::lista_campos(){
/*Devuelve la lista de los nombres de los campos de un ValorOz_Reg*/
/*Pre: True*/
/*Pos: campos*/
  list<string> ans;
  for (map<string, Campo *>::iterator it = campos.begin(); it != campos.end(); it++) {
    ans.push_front(it->first);
  }
  return ans;
}

/*=====Almacen=====*/

Almacen::Almacen(){}
Almacen::Almacen(list<string> n_variables){
/*Crea un almacen con una serie de ValorOzs vacios*/
/*Pre: n_variables*/
/*Pos: Almacen {n1, n2, n3} == n_variables*/
  int i = 0;
  for (list<string>::iterator it = n_variables.begin(); i < n_variables.size(); it++, i++) {
    agregar_variable(*it);
  }
}


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


void Almacen::consultar_variable(string key){
/*Muestra por pantalla el valor de un ValorOz precreado*/
/*Pre: key pertenece a las llaves de variables*/
/*Pos: valor del ValorOz correspondiente a key*/
  if(!in_almacen(key)){
    fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
    exit(1);
  }
  cout << "Valor de " << key << " ---> ";
  variables[key]->consultar_val();
  cout << endl;
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


bool Almacen::consultar_ligadura(string key){
/*Confirma si un ValorOz esta ligado en el almacen*/
/*Pre: True*/
/*Pos: True si esta ligado, de lo contrario False*/
  if(!in_almacen(key)){
    fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
    exit(1);
  }
  if (variables[key]->get_father() || !is_empty(key)){
    return true;
  }
  else{
    return false;
  }
}


string itos(int ent){
/*Conversor de int a string*/
/*Pre: entero*/
/*Pos: entero como un string*/
  string ans;
  while (ent > 9) {
    ans += (ent % 10) + '0';
    ent /= 10;
  }
  ans += ent + '0';
  reverse(ans.begin(),ans.end());
  return ans;
}
string ftos(float flot){
/*Conversor de float a string*/
/*Pre: flot*/
/*Pos: flot como un string*/
  ostringstream ss;
  ss << flot;
  return (ss.str());
}
string Almacen::cadena_valor(string key){
/*Devuelve la notacion sufija del Valor de un ValorOz*/
/*Pre: key pertenece a variables*/
/*Pos: sufija del valor del ValorOz correspondiente a key*/
  if(!in_almacen(key)){
    fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
    exit(1);
  }
  string cad;
  Comparator comp;
  cad += key; cad += " = ";
  variables[key]->get_val(comp);
  if (comp.type == "int"){
    cad += itos(comp.un_comp.i);
  }
  else if (comp.type == "float"){
    cad += ftos(comp.un_comp.f);
  }
  else if (comp.type == "char"){
    if (comp.un_comp.c == '_'){
      cad += '_';
    }
    else if(comp.un_comp.c == '|'){
      ValorOz_Reg *temp;
      temp = (ValorOz_Reg *)variables[key];
      cad += temp->get_etiqueta();
      cad += '(';
      map<string, Campo *> mp;
      mp = temp->get_campos();
      int i = 0;
      for (map<string, Campo *>::iterator it = mp.begin(); it != mp.end(); it++,i++) {
        cad += it->first;
        cad += ':';
        if (it->second->type == "int"){
          Campo_Int *tcamp;
          tcamp = (Campo_Int *)it->second;
          cad += itos(tcamp->val);
        }
        else if (it->second->type == "float"){
          Campo_Float *tcamp;
          tcamp = (Campo_Float *)it->second;
          cad += ftos(tcamp->val);
        }
        else if (it->second->type == "Oz"){
          Campo_Oz *tcamp;
          tcamp = (Campo_Oz *)it->second;
          cad += tcamp->val->get_key();
        }
        if (i < mp.size() - 1) cad += ' ';
      }
      cad += ')';
    }
  }

  return cad;
}


list<string> Almacen::get_variables(){
/*Devuelve la lista de las claves de los ValorOzs de un almacen*/
/*Pre: True*/
/*Pos: variables*/
  list<string> keys;
  for (map<string, ValorOz *>::iterator it = variables.begin(); it != variables.end(); it++) {
    cout << it->first << endl;
  }
  return keys;
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


void Almacen::agregar_variable(string n_key, string n_etiqueta, map<string, Campo *> n_campos){
/*Agrega un nuevo ValorOz al Almacen*/
/*Pre: !(Existe ValorOz->key == key && key pertenece a variables->keys)*/
/*Pos Almacen = {...(n_key, nuevo ValorOz_Reg)...}
      ValorOz_Float->etiqueta = n_etiqueta*/
  if (in_almacen(n_key)){
    fprintf(stderr, "Redefinición de un ValorOz existente en el Almacen\n");
    exit(1);
  }
  int i = 0;
  for (map<string, Campo *>::iterator it = n_campos.begin(); i < n_campos.size(); it++, i++) {
    if (it->second->type == "key"){
      Campo_Key *temp;
      temp = (Campo_Key *)it->second;
      if (temp->get_val() == n_key){
        fprintf(stderr, "Campo con ValorOz igual al mismo registro\n");
        exit(1);
      }
      if (in_almacen(temp->get_val())){
        Campo_Oz *temp2;
        temp2 = new Campo_Oz(variables[temp->get_val()]);
        n_campos[it->first] = temp2;
      }
      else{
        fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
        exit(1);
      }
    }
  }
  ValorOz_Reg *n_var;
  n_var = new ValorOz_Reg(n_key, n_etiqueta, n_campos);
  variables[n_key] = n_var;
}


void Almacen::unificar(string key, int n_val){
/*Unifica un ValorOz con un entero*/
/*Pre: key pertenece a variables, n_val*/
/*Pos: valor del ValorOz correspondiente a key = n_val*/
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
/*Unifica un ValorOz con un float*/
/*Pre: key pertenece a variables, n_val*/
/*Pos: valor del ValorOz correspondiente a key = n_val*/
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


void Almacen::unificar(string key, string n_etiqueta, map<string, Campo *>n_campos){
/*Unifica un ValorOz con un registro*/
/*Pre: key pertenece a variables, n_etiqueta, n_campos*/
/*Pos: valor del ValorOz correspondiente a key = {n_etiqueta, n_campos}*/
  if (!in_almacen(key)){
    fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
    exit(1);
  }
  Comparator comp;
  variables[key]->get_val(comp);
  if (is_empty(key)){
    if (comp.type == "char"){
      int i = 0;
      for (map<string, Campo *>::iterator it = n_campos.begin(); i < n_campos.size(); it++, i++) {
        if (it->second->type == "key"){
          Campo_Key *temp;
          temp = (Campo_Key *)it->second;
          if (temp->get_val() == key){
            fprintf(stderr, "Campo con ValorOz igual al mismo registro\n");
            exit(1);
          }
          if (in_almacen(temp->get_val())){
            Campo_Oz *temp2;
            temp2 = new Campo_Oz(variables[temp->get_val()]);
            n_campos[it->first] = temp2;
          }
          else{
            fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
            exit(1);
          }
        }
      }
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
  if (val1 == "_" || val2 == "_"){
    if (val1 == "_"){
      fprintf(stderr, "Llave inváldia para ValorOz\n");
      exit(1);
    }
    else{
      if (!is_empty(val1)){
        fprintf(stderr, "Asignación de vacio a valor no vacio\n");
        exit(1);
      }
    }
  }
  else {
    if(!in_almacen(val1) || !in_almacen(val2)){
      fprintf(stderr, "Referencia a ValorOz no definido en el Almacen\n");
      exit(1);
    }
    Comparator comp1, comp2;
    variables[val1]->get_val(comp1);
    variables[val2]->get_val(comp2);
    if (comp1.un_comp.c == '|' || comp2.un_comp.c == '|'){
      if (comp1.un_comp.c == '|' && comp2.un_comp.c == '|'){
        ValorOz_Reg *reg1, *reg2;
        reg1 = (ValorOz_Reg *)variables[val1];
        reg2 = (ValorOz_Reg *)variables[val2];
        if (reg1->get_etiqueta() != reg2->get_etiqueta()){
          fprintf(stderr, "Unificación de un registros con diferentes etiquetas\n");
          exit(1);
        }
        if (reg1->get_campos().size() != reg2->get_campos().size()){
          fprintf(stderr, "Unificación de un registros con diferentes cantidades de campos\n");
          exit(1);
        }
        list<string> temp1, temp2;
        map<string, Campo *>::iterator it;
        it =  reg1->get_campos().begin();
        while (it != reg1->get_campos().end()) {
          temp1.push_back(it->first);
          it++;
        }
        it =  reg2->get_campos().begin();
        while (it != reg2->get_campos().end()) {
          temp2.push_back(it->first);
          it++;
        }
        int i = 0;
        list<string>::iterator vt = temp1.begin();
        while (i < temp1.size()) {
          if (find(temp2.begin(), temp2.end(), *vt) == temp2.end()){
            fprintf(stderr, "Diferentes nombres de campos en Unificación de regs\n");
            exit(1);
          }
          vt++;
          i++;
        }//Verificacion campos hasta aqui
        i = 0;
        list<string>::iterator jt = temp1.begin();
        while (i < temp1.size()) {
          string type1, type2;
          type1 = reg1->get_campos()[*jt]->type;
          type2 = reg2->get_campos()[*jt]->type;
          // cout << type1 << ' ' << type2 << endl;
          if ((type1 == "int" && type2 == "float") || (type2 == "int" && type1 == "float")){
            fprintf(stderr, "Unificación de numeros diferentes\n");
            exit(1);
          }
          else if (type1 == "int" && type2 == "int"){
            Campo_Int *ent1, *ent2;
            ent1 = (Campo_Int *)(reg1->get_campos()[*jt]);
            ent2 = (Campo_Int *)(reg2->get_campos()[*jt]);
            if (ent1->val != ent2->val){
              fprintf(stderr, "Unificación de numeros diferentes\n");
              exit(1);
            }
          }
          else if (type1 == "float" && type2 == "float"){
            Campo_Float *float1, *float2;
            float1 = (Campo_Float *)(reg1->get_campos()[*jt]);
            float2 = (Campo_Float *)(reg2->get_campos()[*jt]);
            if (float1->val != float2->val){
              fprintf(stderr, "Unificación de numeros diferentes\n");
              exit(1);
            }
          }
          else if(type1 == "Oz"){
            Campo_Oz *COz1;
            COz1 = (Campo_Oz *)(reg1->get_campos()[*jt]);
            if (type2 == "int"){
              Campo_Int *v2;
              v2 = (Campo_Int *)(reg2->get_campos()[*jt]);
              unificar(COz1->val->get_key(), v2->val);
              ValorOz_Reg *cambio;
              cambio = (ValorOz_Reg *)variables[val2];
              cambio->set_campo(*jt, COz1);
            }
            else if (type2 == "float"){
              Campo_Float *v2;
              v2 = (Campo_Float *)(reg2->get_campos()[*jt]);
              unificar(COz1->val->get_key(), v2->val);
              ValorOz_Reg *cambio;
              cambio = (ValorOz_Reg *)variables[val2];
              cambio->set_campo(*jt, COz1);
            }
            else if (type2 == "Oz"){
              Campo_Oz *v2;
              v2 = (Campo_Oz *)(reg2->get_campos()[*jt]);
              unificar(COz1->val->get_key(), v2->val->get_key());
            }
          }
          else if(type2 == "Oz"){
            Campo_Oz *COz2;
            COz2 = (Campo_Oz *)(reg2->get_campos()[*jt]);
            if (type1 == "int"){
              Campo_Int *v2;
              v2 = (Campo_Int *)(reg1->get_campos()[*jt]);
              unificar(COz2->val->get_key(), v2->val);
              ValorOz_Reg *cambio;
              cambio = (ValorOz_Reg *)variables[val1];
              cambio->set_campo(*jt, COz2);
            }
            else if (type1 == "float"){
              Campo_Float *v2;
              v2 = (Campo_Float *)(reg1->get_campos()[*jt]);
              unificar(COz2->val->get_key(), v2->val);
              ValorOz_Reg *cambio;
              cambio = (ValorOz_Reg *)variables[val1];
              cambio->set_campo(*jt, COz2);
            }
            else if (type1 == "Oz"){
              Campo_Oz *v2;
              v2 = (Campo_Oz *)(reg1->get_campos()[*jt]);
              unificar(COz2->val->get_key(), v2->val->get_key());
            }
          }
          // // cout << type1 << ' ' << type2 << endl;
          jt++;i++;
        }
      }
      else{
        fprintf(stderr, "Unificación de un registro con un no registro\n");
        exit(1);
      }
    }
    else{
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
  }
}


void Operaciones::entrada(char *id1, char *id2 , char *v1, char *v2){
  /* Recibe una expresion y la transforma para poder guardarla en el almacen */
  /* Pre: Recibe una expresion que ha sido ingresado por pantalla */
  /* Pos: Transforma y evulua la expresion para poder guardarla en el almacen*/
  if(strcmp(id1,"Oz") == 0 && strcmp(id2,"Oz") == 0){
      storage.unificar(v1,v2);
  }
  else if(strcmp(id1,"r") == 0 || strcmp(id2,"r") == 0){
    char label[50];
    if (strcmp(id2,"r") == 0) {
      int i = 0, k = 0;
      list<char> format;

      map<string, Campo *> mp;
      storage.agregar_variable(v1);

      while (v2[i] != '[') {
        if (v2[i] == 'i') {
          format.push_back('i');
        }else if(v2[i] == 'f') {
          format.push_back('f');
        }else if(v2[i] == 'k') {
          format.push_back('k');
        }else{
          fprintf(stderr, "Errorr");
        }
        i++;
      }
      i++;

      while (v2[i] != '(') {
        label[k] = v2[i];
        k++;
        i++;
      }
      i++;

      int n = format.size();

      while (n--) {
        char name[50] = "", valor[50] = "";
        int j = 0, h = 0;

        while (v2[i] != ':') {
          name[j] = v2[i];
          j++;
          i++;
        }
        i++;

        while (v2[i] != ',' && v2[i] != ')') {
          valor[h] = v2[i];
          h++;
          i++;
        }
        i++;

        if(format.front() == 'i'){
          mp[name] = new Campo_Int(atoi(valor));
          format.pop_front();
        }else if(format.front() == 'f'){
          mp[name] = new Campo_Float(float(atof(valor)));
          format.pop_front();
        }else if(format.front() == 'k'){
          mp[name] = new Campo_Key(valor);
          format.pop_front();
        }
      }
      storage.unificar(v1,label,mp);

    }else if(strcmp(id1,"r") == 0){
      int i = 0, k = 0;
      list<char> format;

      map<string, Campo *> mp;
      storage.agregar_variable(v2);

      while (v1[i] != '[') {
        if (v1[i] == 'i') {
          format.push_back('i');
        }else if(v1[i] == 'f') {
          format.push_back('f');
        }else if(v1[i] == 'k') {
          format.push_back('k');
        }else{
          fprintf(stderr, "Errorr");
        }
        i++;
      }
      i++;

      while (v1[i] != '(') {
        label[k] = v1[i];
        k++;
        i++;
      }
      i++;

      int n = format.size();

      while (n--) {
        char name[50] = "", valor[50] = "";
        int j = 0, h = 0;

        while (v1[i] != ':') {
          name[j] = v1[i];
          j++;
          i++;
        }
        i++;

        while (v1[i] != ',' && v1[i] != ')') {
          valor[h] = v1[i];
          h++;
          i++;
        }
        i++;

        if(format.front() == 'i'){
          mp[name] = new Campo_Int(atoi(valor));
          format.pop_front();
        }else if(format.front() == 'f'){
          mp[name] = new Campo_Float(float(atof(valor)));
          format.pop_front();
        }else if(format.front() == 'k'){
          mp[name] = new Campo_Key(valor);
          format.pop_front();
        }
      }
      storage.unificar(v2,label,mp);
    }
  }
  else{

    if (strcmp(id1,"Oz") == 0) {
      if (strcmp(id2,"i") == 0) {
        if (!storage.in_almacen(v1)) {
          if (strcmp(v2,"_") == 0) {
            storage.agregar_variable(v1);
          }
          else{
            storage.agregar_variable(v1,atoi(v2));
          }
        }else{

          storage.unificar(v1,atoi(v2));
        }
      }
      else if(strcmp(id2,"f") == 0){
        if (!storage.in_almacen(v1)) {
          storage.agregar_variable(v1,atoi(v2));
        }else{
          storage.agregar_variable(v1,float(atof(v2)));
        }

      }
      else if(strcmp(id2,"v") == 0){
        storage.agregar_variable(v1);
      }

    }
    else if(strcmp(id2,"Oz") == 0){
      if (strcmp(id1,"i") == 0) {
        if (!storage.in_almacen(v2)) {
          storage.agregar_variable(v2,atoi(v1));
        }else{
          storage.unificar(v2,atoi(v1));
        }
      }
      else if(strcmp(id1,"f") == 0){
        if (!storage.in_almacen(v2)) {
          storage.agregar_variable(v2,float(atoi(v1)));
        }else{
          storage.agregar_variable(v2,float(atof(v1)));
        }
      }
      else if(strcmp(id1,"v") == 0){
        storage.agregar_variable(v2);
      }
    }
  }

}

void Operaciones::imprimir(){
  storage.print_almacen();
}
