#ifndef VALOROZ_H
#define VALOROZ_H
#include <vector>

class ValorOz{
  private:
    int val; //Un registro con campos no puede tener valor
    std::vector<ValorOz *> campos;
    ValorOz *father;  /*Una variable solo puede tener un padre*/
    std::vector<ValorOz *> sons;  /*Una variable solo puede tener multiples hijos+
                                en caso de ser una etiqueta*/
  public:
    ValorOz(){
      val = -1;   /*Asignar un valor inicial que equivalga a vacio,
                    que nunca ocurra*/
      father = NULL;

    }
    int get_val();
    ValorOz* get_father();
    std::vector<ValorOz *> get_sons();

    void set_father(ValorOz *n_father);
    void add_sons(ValorOz *n_son);
    void add_sons(std::vector<ValorOz *> n_sons);
    void elim_sons();

    void operator =(char v);
    void operator =(int num);
    void operator =(ValorOz &val2);
};

#endif
