/*Lucas Guerra 
 * gcc bprop -o xbprop -lm
 * 12/12/2016
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 

#define TOTAL_INPUTS 4
#define INPUT_UNITS 2 /*Number of 'xi'--> i */
#define HIDDEN_UNITS 4 /* --> J */
#define OUTPUT_NUMBERS 1 
/* #define MAX_TIMES 100000000 */
#define CRATE 0.002

void feed_foward(int input_number); 
void back_propagation(int input_number, double zj[], double yk[], double v[], double v2[]); 
void update_weights (double delta_wjk[][OUTPUT_NUMBERS], double delta_vij[][HIDDEN_UNITS],
		     double delta_v0j[], double delta_w0k[]);
void applicate (int numb); 
double sigmoid (double x); 
double d_sigmoid(double x);
double randinit(); 

int MAX_TIMES = 100000; 
int xi[TOTAL_INPUTS][INPUT_UNITS]= { {1 ,1}, {-1,-1}, {-1, 1}, {1,-1} };
int outputs [TOTAL_INPUTS] = {-1, -1, 1, 1};
double vij[INPUT_UNITS][HIDDEN_UNITS]; 
double v0j[HIDDEN_UNITS] = {1, 1, 1, 1};
double wjk[HIDDEN_UNITS][OUTPUT_NUMBERS]; 
double w0k[OUTPUT_NUMBERS] = {1}; 

int main (int argc, char *argv[]){

  int i,j,k; 
  int count = 0;

  if (argc > 1 ) {
    MAX_TIMES = atoi(argv[1]); 
  }
  else;

  printf("MAX_TIMES ---> %d\n", MAX_TIMES);
  printf("CORRETION RATE ----> %lf\n", CRATE); 
      
  /* Initialize vij values between 0 - 0.5 */
  for (i = 0; i < INPUT_UNITS; i++) {
    for(j = 0; j < HIDDEN_UNITS; j++)
      vij[i][j] = randinit();     
  }
  /* Initialize wjk  */
  for (j = 0; j < HIDDEN_UNITS; j++) {
    for (k = 0; k < OUTPUT_NUMBERS; k++)
      wjk[j][k] = randinit();
  }

  /* Training */
  for (count = 0; count < MAX_TIMES; count++) { 
    for (i = 0; i < TOTAL_INPUTS; i++){
      feed_foward(i);
    }
  }
  for (i = 0; i < TOTAL_INPUTS; i++)
    applicate(i); 
  return 0;
  
}

double d_sigmoid (double x) {

  double result = 0.0;
  result = 0.5 * (1 + sigmoid(x)) * (1 - sigmoid(x));
  return result;
  
}

double sigmoid (double x) {

  double result = 0.0;
  result = (2 / (1 + exp (-x))) - 1;
  return result; 

}

/* Create numbers between 0 and 0.5 */
double randinit () {
  return (((double) rand() / RAND_MAX) * 0.5);
}

void feed_foward(int input_number) {

  double z_inj[HIDDEN_UNITS];
  double y_ink[OUTPUT_NUMBERS];
  double zj[HIDDEN_UNITS]; 
  double yk[OUTPUT_NUMBERS];
  int i, j, k; 
  double sum = 0.0;

  for (j = 0; j < HIDDEN_UNITS; j++){
    z_inj[j] = randinit();
  }
  for (k = 0; k < OUTPUT_NUMBERS; k++){
    yk[k] = randinit();     
  }
  /*Calculate z_inj 
   *And zj
  */
  for (j = 0; j < HIDDEN_UNITS; j++) {
    sum = 0.0; 
    for (i = 0; i < INPUT_UNITS; i++) {
      sum += (xi[input_number][i] * vij[i][j]);
    }
    z_inj[j] += sum + v0j[j]; 
    zj[j] = sigmoid(z_inj[j]);
    
  }
 
  sum = 0;
  /* Calculate y_ink and yk[k] */
  for (k = 0; k < OUTPUT_NUMBERS; k++) {
    for(j = 0; j < HIDDEN_UNITS; j++) {
      sum = sum + (zj[j] * wjk[j][k]);       
    }
    y_ink[k] = w0k[k] + sum;
    yk[k] = sigmoid(y_ink[k]); 
  }

  /*Initiate b_propagation */
  back_propagation(input_number, zj, yk, z_inj, y_ink);
}

void back_propagation( int input_number,double zj[], double yk[], double z_inj[], double y_ink[]) {

  double delta_wjk[HIDDEN_UNITS][OUTPUT_NUMBERS];
  double delta_w0k[OUTPUT_NUMBERS]; 
  double delta_vij[INPUT_UNITS][HIDDEN_UNITS]; 
  double delta_v0j[HIDDEN_UNITS]; 
  double target = outputs[input_number];
  double sigmak[OUTPUT_NUMBERS];
  double sigma_inj[HIDDEN_UNITS];
  double sigmaj[HIDDEN_UNITS]; 
  int j, k, i;

  /*Calculate error for wjk */
  for (k = 0; k < OUTPUT_NUMBERS; k++) {
    sigmak[k] = (target - yk[k]) * d_sigmoid(y_ink[k]); 
  }

  for (j = 0; j < HIDDEN_UNITS; j++ ) {
    for (k = 0; k < OUTPUT_NUMBERS; k++) {
      delta_wjk[j][k] = CRATE * sigmak[k] * zj[j];
    }
  }

  for (k = 0; k < OUTPUT_NUMBERS; k++) {
    delta_w0k[k] = CRATE * sigmak[k];     
  }

  /* calculate sigma in j*/
  for (j = 0; j < HIDDEN_UNITS  ; j++) {
    for (k = 0; k < OUTPUT_NUMBERS; k++) {
      sigma_inj[j] = sigmak[k] * wjk[j][k];
    }
  }

  /*Calculate error for sigmaj */
  for (j = 0; j < HIDDEN_UNITS; j++) {
    sigmaj[j] = sigma_inj[j] * d_sigmoid(z_inj[j]);
  }
  
  for (i = 0; i < INPUT_UNITS; i++) {
    for (j = 0; j < HIDDEN_UNITS; j++) {
      delta_vij[i][j] = CRATE * sigmaj[j] * xi[input_number][i];
    }
  }

  for (j = 0; j < HIDDEN_UNITS; j++) {
    delta_v0j[j] = CRATE * sigmaj[j];
  }
  update_weights(delta_wjk, delta_vij, delta_v0j, delta_w0k); 
}


void update_weights (double delta_wjk[][OUTPUT_NUMBERS], double delta_vij[][HIDDEN_UNITS],
		     double delta_v0j[],
		     double delta_w0k[]) {

  int i,j,k;
  /*  Update wjk */
  for (j = 0; j < HIDDEN_UNITS; j++) {
    for (k = 0 ; k < OUTPUT_NUMBERS; k++) {
      wjk[j][k] = wjk[j][k] + delta_wjk[j][k];
    }
  }
  /*Update vij */
  for (i = 0; i < INPUT_UNITS; i++) {
    for (j = 0; j < HIDDEN_UNITS; j++) {
      vij[i][j] = vij[i][j] + delta_vij[i][j];
    }
  }
  
  for (k = 0; k < OUTPUT_NUMBERS; k++) {
    w0k[k] = w0k[k] + delta_w0k[k];     
  }
  
  for (j = 0; j < HIDDEN_UNITS; j++) {
    v0j[j] = v0j[j] + delta_v0j[j]; 			      
  }

} 

void applicate (int numb) {

  double z_j[HIDDEN_UNITS];
  double z_inj[HIDDEN_UNITS];
  double y_ink[OUTPUT_NUMBERS];
  double y_k[OUTPUT_NUMBERS]; 
  int j,i,k;
  double sum ;

  for (j = 0; j < HIDDEN_UNITS; j++)
    z_inj[j] = randinit();
  
  
  for (j = 0; j < HIDDEN_UNITS; j++) {
    sum = 0; 
    for (i = 0; i < INPUT_UNITS; i++){
      sum = sum + (xi[numb][i] * vij[i][j]);
    }
    z_inj[j] += v0j[j] + sum; 
    z_j[j] = sigmoid(z_inj[j]);
  }

  for (k = 0; k < OUTPUT_NUMBERS; k++) {
    sum = 0; 
    for (j = 0; j < HIDDEN_UNITS; j++) {
      sum = z_j[j]* wjk[j][k];
    }
    y_ink[k] = sum + w0k[k]; 
    y_k[k] = sigmoid(y_ink[k]);
  }

  printf("Input ---> "); 
  for (i = 0; i < INPUT_UNITS; i++) {
    printf("%d ",xi[numb][i]); 
  }
  printf("   Output ---->");
  double val = 0; 
  for (k = 0; k < OUTPUT_NUMBERS; k++) {
    printf("%lf ",y_k[k]);
  }
  printf("   Expected ----> %d\n", outputs[numb]);
  printf("\n"); 

}
