#ifndef VALOROZ_H
#define VALOROZ_H
#include <vector>
#include <list>
#include <string>
#include <map>

using namespace std;

class ValorOz{
  private:
    int val; //Un registro con campos no puede tener valor
    string etiqueta;
    map<string, ValorOz *> campos;
    ValorOz *father;  /*Una variable solo puede tener un padre*/
    list<ValorOz *> sons;  /*Una variable solo puede tener multiples hijos+
    en caso de ser una etiqueta*/
    //list<ValorOz *> campos;
  public:
    ValorOz(){
      val = -1;   /*Asignar un valor inicial que equivalga a vacio,
                    que nunca ocurra*/
      etiqueta = "";
      father = NULL;

    }
    void set_father(ValorOz *n_father);
    void add_sons(ValorOz *n_son);
    void add_sons(list<ValorOz *> n_sons);
    void elim_sons();
    void set_campo(string llave, ValorOz *n_ValorOz);
    void elim_campo(string llave);

    int get_val();
    string get_etiqueta();
    ValorOz* get_father();
    list<ValorOz *> get_sons();
    list<string> get_campos_llaves();
    ValorOz* get_campo_valor(string llave);

    void operator =(char v);
    void operator =(int num);
    void operator =(ValorOz &val2);
    void operator =(string n_etiqueta);

    /*Pendiendtes*/
    /*Obtener cadena valor, obtener etiqueta, obtener lista de campos*/
};
typedef pair<string, ValorOz *> cam;


class Almacen{
  private:
    list<ValorOz *> variables;
  public:
    Almacen();/*crear almacen*/
    void agregar_variable(string variable);
    int unificar_variables(string val1, string val2);
    int consultar_variable(string variable);
    void imprimir_almacen();
    bool consultar__ligadura_variable(string variable);
    list<ValorOz *> obtener_lista_variables();
};

#endif
