#ifndef VALOROZ_H
#define VALOROZ_H
#include <list>

using namespace std;

class ValorOz{
  private:
    int val; //Un registro con campos no puede tener valor
    list<ValorOz *> campos;
    ValorOz *father;  /*Una variable solo puede tener un padre*/
    list<ValorOz *> sons;  /*Una variable solo puede tener multiples hijos+
                                en caso de ser una etiqueta*/
  public:
    ValorOz(){
      val = -1;   /*Asignar un valor inicial que equivalga a vacio,
                    que nunca ocurra*/
      father = NULL;

    }
    int get_val();
    ValorOz* get_father();
    list<ValorOz *> get_sons();

    void set_father(ValorOz *n_father);
    void add_sons(ValorOz *n_son);
    void add_sons(list<ValorOz *> n_sons);
    void elim_sons();

    void operator =(char v);
    void operator =(int num);
    void operator =(ValorOz &val2);

    /*Pendiendtes*/
    /*Obtener cadena valor, obtener etiqueta, obtener lista de campos*/
};


class Almacen{
  private:
    list<ValorOz *> variables;
  public:
    Almacen();/*crear almacen*/
    void imprimir_almacen();
    int consultar_variable(string variable);
    bool consultar__ligadura_variable(string variable);
    void agregar_variable(string variable);
    list<ValorOz *> obtener_lista_variables();
    int unificar_variables(string val1, string val2);
};

#endif
