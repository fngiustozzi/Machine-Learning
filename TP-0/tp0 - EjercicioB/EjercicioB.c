#include<stdio.h>  
#include<stdlib.h> // libreria para usar drand48()  
#include<time.h>   // libreria para usar time()  
#include<math.h>
#include<string.h>

#define PI 3.141592

/* Funcion para saber cuanto vale la normal en un valor dado */
float pnormal(float mu, float ds, float x) {
  float res = (1/(sqrt(2* PI)*ds))*(exp((-0.5)*pow(((x-mu)/ds),2)));
  return res;
}

void main(int argc, char *argv[])  
{  
  int cantidad, cantinputs, i, j, flag;  
  //int cantintentos = 0;
  int hora = time(NULL);  
  int cantnumgenc0 = 0;
  int cantnumgenc1 = 0;
  float *punto;
  float c; 
  float mu0 = -1; //media de la clase 0
  float mu1 = 1;  //media de la clase 1
  float num1,num2;

  /* Recogemos desde la entrada la cantidad de datos
     que se quiere generar y la cantidad de inputs de 
      cada dato y ademas el C */  
  cantidad = atoi(argv[1]);    // n (del enunciado del tp)
  cantinputs = atoi(argv[2]);  // d (del enunciado del tp)
  c = atof(argv[3]);           // C (del enunciado del tp)

  /* desvio estandar */
  float ds;
  ds = c; // desviacion estandar

  // Semilla de drand48() 
  srand48(hora);  

  /* Los archivos según C4.5 (el .data y el .names)*/
  FILE *archivodata;
  FILE *archivonames;

  archivodata = fopen("EjercicioB.data", "w");

  archivonames = fopen("EjercicioB.names", "w");

  /* creamos el archivo ?.names */
  fprintf(archivonames, "0, 1.\n\n");
  for(i=0; i<cantinputs; i++)
    fprintf(archivonames, "x%d: continuous.\n", i);
  fclose(archivonames);

  /* Generamos ciclos que se repiten la cantidad 
  de veces indicada. En cada vuelta del ciclo se 
  genera y se escriben los resultados en el 
  archivo .data si es que satisface la condicion
  indicada */ 
  
  punto = (float *)malloc(cantinputs * sizeof(float));

  while (cantnumgenc1 < cantidad/2) {
    //cantintentos++;
    flag = 0;
    while (flag != 1){    
      num1 = (drand48()*((mu1+5*ds)-(mu1-5*ds)))+(mu1-5*ds);
      num2 = drand48()*(pnormal(mu1,ds,mu1));          
      if (num2 <= pnormal(mu1,ds,num1)){
          punto[0] = num1;        
          flag = 1;      
      }
    }
    
    i=1;
    while(i<cantinputs){
      num1 = (drand48()*((5*ds+5*ds)))-5*ds;
      num2 = drand48()*(pnormal(0,ds,0));          
      if (num2 <= pnormal(0,ds,num1)){
        punto[i] = num1;        
        i++;      
      }
    }
    cantnumgenc1++; 
    for (j=0;j<cantinputs;j++)
      fprintf(archivodata, "%f, ", punto[j]);
    fprintf(archivodata, "1\n");
  }

  while (cantnumgenc0 < cantidad/2) {
    //cantintentos++;
    flag = 0;
    while (flag != 1){    
      num1 = (drand48()*((mu0+5*ds)-(mu0-5*ds)))+(mu0-5*ds);
      num2 = drand48()*(pnormal(mu0,ds,mu0));          
      if (num2 <= pnormal(mu0,ds,num1)){
          punto[0] = num1;        
          flag = 1;      
      }
    }
    
  i=1;
  while(i<cantinputs){
    num1 = (drand48()*((5*ds)+(5*ds)))-5*ds;
    num2 = drand48()*(pnormal(0,ds,0));          
    if (num2 <= pnormal(0,ds,num1)){
        punto[i] = num1;        
        i++;      
    }
  }
  cantnumgenc0++; 
  for (j=0;j<cantinputs;j++)
    fprintf(archivodata, "%f, ", punto[j]);
  fprintf(archivodata, "0\n");
  }

  fclose(archivodata);

}
