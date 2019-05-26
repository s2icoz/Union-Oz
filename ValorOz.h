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


class Comparator{
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

	bool operator ==(const Comparator &comp2){
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
    virtual void get_val(Comparator &ans);
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
    void get_val(Comparator &ans);

    bool empty();
    void consultar_val();

    void set_val(int num);
		void set_val(Comparator &comp);
};


class ValorOz_Float : public ValorOz{
  private:
    float val;
  public:
    float vacio = 0;
    ValorOz_Float(string n_key, float flotante);

    float get_val(float &ans);
    void get_val(Comparator &ans);

    bool empty();
    void consultar_val();

    void set_val(float num);
		void set_val(Comparator &comp);
};


class Campo{
	public:
		string name;
		string val;
		string type;
		Campo(string n_name);
		virtual string get_val();
		virtual void cons_val();
};
class Campo_Int: public Campo{
	public:
		int val;
		Campo_Int(string n_name, int n_entero);
		void cons_val();
};
class Campo_Float: public Campo{
	public:
		float val;
		Campo_Float(string n_name, float n_flotante);
		void cons_val();
};
class Campo_Key: public Campo{
	public:
		string val;
		Campo_Key(string n_name, string key);
		string get_val();
		void cons_val();
};
class Campo_Oz: public Campo{
	public:
		ValorOz *val;
		Campo_Oz(string n_name, ValorOz *n_Oz);
		void cons_val();
};

class ValorOz_Reg : public ValorOz{
	private:
		char val = '|';
		string etiqueta;
		list<Campo *> campos;
	public:
		ValorOz_Reg(string n_key, string n_etiqueta, list<Campo *> n_campos);
		string get_etiqueta();
		list<Campo *> get_campos();
		void consultar_val();
};


class Almacen{
  private:
    map<string, ValorOz *> variables;
  public:
    void agregar_variable(string n_key);
    void agregar_variable(string n_key, int entero);
    void agregar_variable(string n_key, float flotante);
		void agregar_variable(string n_key, string n_etiqueta, list<Campo *>n_campos);

    bool in_almacen(string key);
    bool is_empty(string key);
    bool equal_vals(string key1, string key2);

		void unificar(string key, int n_val);
		void unificar(string key, float n_val);
		void unificar(string key, string n_etiqueta, list<Campo *>n_campos);
		void unificar(string key1, string key2);

    void print_almacen();
};
/*
/*!!!Almacen::consultar_valor con comaparator
*/
#endif
