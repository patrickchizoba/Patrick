/*  Calculo de Fourir


Autor: Patrick
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TAM 8
#define PI acos(-1)

int reverse_bits(unsigned int i, int n)
{
    int reverse = 0;
    for(; n > 1; n >>= 1){
          reverse = (reverse << 1) | (i & 1);
          i >>= 1;
    }
    return reverse;
}

void fft(int n, float x[], float y[])
{
    int i, j, k, n1, n2, rb = 0;
    float c, s, tetha, angle, t1, t2;
   
    /* Aqui ocorre a reversão dos bits */
    for(i = 1; i < n - 1; i++){
          rb = reverse_bits(i, n);
          if(i < rb){
              t1 = x[i];
              x[i] = x[rb];
              x[rb] = t1;
              t1 = y[i];
              y[i] = y[rb];
              y[rb] = t1;
          }
    }
    
    /* Aqui começa o cálculo da FFT */
    n1 = 0;
    n2 = 1;
   
    for(i = 0; i < log2(n); i++){
          n1 = n2;
          n2 += n2;
          tetha = PI/n2;
          angle = 0.0;
          for(j = 0; j < n1; j++){
                c = cos(angle);
                s = sin(angle);
                angle += tetha;
                for(k = 0; k < n; k += n2 ){
                      t1 = c*x[k+n1] - s*y[k+n1];
                      t2 = s*x[k+n1] + c*y[k+n1];
                      x[k+n1] = x[k] - t1;
                      y[k+n1] = y[k] - t2;
                      x[k] += t1;
                      y[k] += t2;
                }
          }
    }
}
                 

int main()
{
    int i;
   
    float x[TAM], y[TAM];
   
    for(i = 0; i < TAM; i++){
          printf("Digite x[%d]: ", i);
          scanf("%f", &x[i]);
          printf("Digite y[%d]: ", i);
          scanf("%f", &y[i]);
    }
    
    fft(TAM, x, y);
    printf("\n");
    
    for(i = 0; i < TAM; i++)
        printf("x[%d] = %f y[%d] = %f\n", i, x[i], i, y[i]);
   
    printf("\n");
    system("PAUSE");
    return 0;
}
