#ifndef VALOROZ_H
#define VALOROZ_H
#include <list>
#include <map>

using namespace std;

union comparer{
/*Estructura especial para diferenciar entre
 ValorOz, ValorOz_Int y ValorOz_Float*/
public:
	float f;
	int i;
	char c;
};


class comparator{
public:
  comparer un_comp;
  string type;

	bool operator =(float flotante){
		un_comp.f = flotante;
		type = "float";
	}

  bool operator =(int entero){
		un_comp.i = entero;
    type = "int";
	}

	bool operator =(char x){
		un_comp.c = x;
		type = "char";
	}

	bool operator ==(const comparator &comp2){
		if (un_comp.f == comp2.un_comp.f){
				return (un_comp.i == comp2.un_comp.i);
		}
		else{
			return false;
		}
	}
};


class ValorOz{
  protected:
    string key;
    char val;
    ValorOz *father;
    list<ValorOz *> sons;
  public:
    char vacio = '_';
    ValorOz(string n_key);

    void set_father(ValorOz *n_father);
    void add_sons(ValorOz *n_son);
    void add_sons(list<ValorOz *> n_sons);
    void elim_sons();

    string get_key();
		ValorOz* get_father();
    void get_val(char &ans);
    virtual void get_val(comparator &ans);
    list<ValorOz *> get_sons();

    virtual bool empty();
    virtual void consultar_val();

    void set_val(char v);
};


class ValorOz_Int : public ValorOz{
  private:
    int val;
  public:
    int vacio = 0;
    ValorOz_Int(string n_key, int entero);

    void get_val(int &ans);
    void get_val(comparator &ans);

    bool empty();
    void consultar_val();

    void set_val(int num);
		void set_val(comparator &comp);
};


class ValorOz_Float : public ValorOz{
  private:
    float val;
  public:
    float vacio = 0;
    ValorOz_Float(string n_key, float flotante);

    float get_val(float &ans);
    void get_val(comparator &ans);

    bool empty();
    void consultar_val();

    void set_val(float num);
		void set_val(comparator &comp);
};


class Almacen{
  private:
    map<string, ValorOz *> variables;
  public:
    void agregar_variable(string n_key);
    void agregar_variable(string n_key, int entero);
    void agregar_variable(string n_key, float flotante);

    bool in_almacen(string key);
    bool is_empty(string key);
    bool equal_vals(string key1, string key2);
    void unificar(string key1, string key2);

    void print_almacen();
};
/*
/*!!!Almacen::consultar_valor con comaparator
*/
#endif
