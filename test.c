#include<riscv_vector.h>
#include<stdio.h>

#define N 15

float vsum(float *v, int n){
  vfloat32m1_t vs, vv, vtmp;
  float s=0.0;
  int i;
  int vlmax;
  

  vlmax=vsetvlmax_e32m1();

  printf("vlmax:%d\n", vlmax);
  
  vs=vfmv_v_f_f32m1(0.0, vlmax);
  
  vtmp=vfmv_v_f_f32m1(0.0, vlmax);

  for(i=0; i<n-vlmax; i+=vlmax){
    vv = vle32_v_f32m1(&v[i], vlmax);
    vtmp = vfadd_vv_f32m1(vtmp, vv, vlmax);
  }

  vs=vfredusum_vs_f32m1_f32m1(vs,vtmp, vs, vlmax);
  
  s = vfmv_f_s_f32m1_f32(vs);
  
  for(; i<n; i++){
    s+=v[i];
  }
  return s;
}


float vsum1(float *v, int n){
  vfloat32m1_t vs, vv;
  float s;
  int i;
  int vl, vlmax;
  
  vlmax=vsetvlmax_e32m1();
  vs=vfmv_v_f_f32m1(0.0, vlmax);

  for(i=0; n>0; i+=vl, n-=vl){
    vl=vsetvl_e32m1(n);
    printf("vl:%d\n", vl);    
    vv = vle32_v_f32m1(&v[i], vl);

    vs=vfredusum_vs_f32m1_f32m1(vs,vv, vs, vl);  
  }

  
  s = vfmv_f_s_f32m1_f32(vs);
  
  return s;
}


float vsum2(float *v, int n){
  vfloat32m2_t vv;
  vfloat32m1_t vs;
  float s;
  int i;
  int vl, vlmax;
  
  vlmax=vsetvlmax_e32m1();
  
  vs=vfmv_v_f_f32m1(0.0, vlmax);

  for(i=0; n>0; i+=vl, n-=vl){
    vl=vsetvl_e32m2(n);
    printf("vl:%d\n", vl);    
    vv = vle32_v_f32m2(&v[i], vl);

    vs=vfredusum_vs_f32m2_f32m1(vs,vv, vs, vl);  
  }

  
  s = vfmv_f_s_f32m1_f32(vs);
  
  return s;
}


int main()
{
  int i;
  float v[N], sum=0.0;
  
  printf("Hello RISC-V!\n");

  for(i=0; i<N; i++){
    v[i]=i;
  }
  
  sum = vsum(v, N);

  printf("%f\n", sum);
  

  return 0;
}
