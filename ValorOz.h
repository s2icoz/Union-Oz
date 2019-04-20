#ifndef VALOROZ_H
#define VALOROZ_H
#include <vector>

class ValorOz{
  private:
    int val;
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
    void operator =(char v);
    void operator =(int num);
    void operator =(ValorOz val2);
};

#endif
