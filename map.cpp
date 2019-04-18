#include <iostream>
#include <string.h>
#include <map>

using namespace std;
int main()  {

  map<string, string> asociativo;

  FILE * date = fopen("Entrada.txt","rb");

  char caracter, enty[100000], arr[100000];
  int p = 0, x = 0;
  if( date == NULL) {

    perror("Error");
    return 1;
  }

  while (feof(date) == 0) {
      caracter = fgetc(date);
      if(caracter != ' ' && caracter != '\n') {
          enty[p++] = caracter;
      }

  }
  int i = 0, k = 0;
  while(i < p-1){

      if ((enty[i] == '-' && enty[i+1] == '>') || enty[i] == ':' ) {
        arr[i] = '=';
        i++;
      }
      else{
        arr[i] = enty[i];
      }
      i++;
  }
  for (int j = 0; j < i; j++) {
    cout<<arr[j];
  }
cout<<endl;
  while (k < i) {

      string clave, valor;

      while (arr[k] != '=' && k < i) {
        clave +=arr[k];
        k++;
      }
      while (arr[k] >= 48 && arr[k]<= 57 && k < i ) { //asci 48 57
        valor+=arr[k];
        k++;
      }
      cout<<clave<<'-'<<valor<<endl;
      k++;
  }




























//  //asociativo[clave] = valor;

/*  //std::cout << valor.first  << '\n';
  map<string, string> ::iterator iter;
  for (iter = asociativo.begin(); iter != asociativo.end(); iter++) {
      std::cout << iter->first << '='<<iter->second << '\n';
  }
  /*map<string, string>::iterator iter;
  for ( iter = asociativo.begin(); iter != asociativo.end(); iter++) {
    c*/

  return 0;
}
