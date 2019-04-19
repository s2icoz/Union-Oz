#include <iostream>
#include "ValorOz.h"

int ValorOz::get_val(){
  if (father != NULL){
    /*Retornará el val del ancestro mayor (sin antecesor)*/
    return father->get_val();
  }
  else{
    /*Si él es el padre sin antecesor entonces retorna su val*/
    return val;
  }
}


void ValorOz::operator =(char v){
  if (val == -1){
    if (v != '_'){
      fprintf(stderr, "Asignación desconocida\n");
    }
  }
  else{
    fprintf(stderr, "Asignación a un valor no vacío\n");
  }
}


void ValorOz::operator =(int num){
  if (sons.size() == 0 && val == -1){
    val = num;
    /*Su padre y antecesores "tendrán" el mismo val porque a la hora de hacer
    /*get_val se busca hasta el nivel más profundo de hijos*/
  }
  else{
    fprintf(stderr, "Asignación de una constante a un valor con referencia\n");
    /*referencia => que apunta a alguien,
    /*referenciado => que alguien apunta a él.*/
  }
}


void ValorOz::operator =(ValorOz val2){
  /*Siempre se debe cumplir esta condicion, igualdad de campos*/
  if (sons.size() == val2.sons.size()){
    if (sons.size() == 1){
      /*Recursividad para agregar ultimo nivel, ejemplo
      /*x = y
      /*z = y
      /*No queremos tener dos variables apuntanto a la misma variable, por esto
      /*llevamos la Recursividad de "y" al máximo y se la agregamos a "z" para que
      /*quede asi:
      /*z->x->y*/
    }
  }
  else{
    fprintf(stderr, "Cantidad de campos distinta en asignación\n");
  }
}
