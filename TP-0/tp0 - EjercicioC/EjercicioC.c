#include<stdio.h>  
#include<stdlib.h> // libreria para usar drand48()  
#include<time.h>   // libreria para usar time()  
#include<math.h>
#include<string.h>

#define PI 3.141592

/* Funciones que representan las curvas ro1 y ro2. */
float ro1 (float theta){
  return theta/(4*PI); 
}

float ro2 (float theta){
  return (theta+PI)/(4*PI); 
}


void main(int argc, char *argv[])  
{  
  int cantidad, i, cantnumgenc0, cantnumgenc1;  
  int hora = time(NULL);  
  float r = 1; //radio del circulo.
  float radio, theta, compX, compY;
  cantnumgenc0 = 0;
  cantnumgenc1 = 0;
  FILE *archivodata;
  FILE *archivonames;

  /* Recogemos desde la entrada la cantidad de datos
     que se quiere generar */  
  cantidad = atoi(argv[1]);  // n (del enunciado del tp)

  /* Semilla de drand48() */
  srand48(hora);  

  /* creamos el archivo .names */
  archivonames = fopen("EjercicioC.names", "w");
  fprintf(archivonames, "0, 1.\n\n");
  for(i=0; i<2; i++)
    fprintf(archivonames, "x%d: continuous.\n", i);
  fclose(archivonames);

  /* genero los puntos en coordenadas polares dentro 
     de un circulo de radio uno centrado en (0,0).
     Luego chequeo si los puntos estan o no entre las
     curvas ro1 y ro2; y convierto los puntos polares
     en coordenadas cartesianas y los guardo en el 
     archivo .data */
  archivodata = fopen("EjercicioC.data", "w");

  while(cantnumgenc0 < cantidad/2){
    radio = r * sqrt(drand48());
    theta = -2*PI*drand48();
    if ((radio <= ro2(theta) && radio >= ro1(theta)) 
         || (radio <= ro2(theta+2*PI) && radio >= ro1(theta+2*PI)) 
         || (radio <= ro2(theta+4*PI) && radio >= ro1(theta+4*PI))) {
      compX = radio * cos(theta);
      compY = radio * sin(theta);    
      fprintf(archivodata, "%f, %f, ", compX, compY);
      fprintf(archivodata, "0\n");
      cantnumgenc0++;
    }
  }  

  while(cantnumgenc1 < cantidad/2){
    radio = r * sqrt(drand48());
    theta = -2*PI*drand48();
    if (!((radio <= ro2(theta) && radio >= ro1(theta)) 
           || (radio <= ro2(theta+2*PI) && radio >= ro1(theta+2*PI)) 
           || (radio <= ro2(theta+4*PI) && radio >= ro1(theta+4*PI)))) {
      compX = radio * cos(theta);
      compY = radio * sin(theta);    
      fprintf(archivodata, "%f, %f, ", compX, compY);
      fprintf(archivodata, "1\n");
      cantnumgenc1++;
    }
  }  

  fclose(archivodata);

}
