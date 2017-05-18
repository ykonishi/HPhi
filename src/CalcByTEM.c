/* HPhi  -  Quantum Lattice Model Simulator */
/* Copyright (C) 2015 The University of Tokyo */

/* This program is free software: you can redistribute it and/or modify */
/* it under the terms of the GNU General Public License as published by */
/* the Free Software Foundation, either version 3 of the License, or */
/* (at your option) any later version. */

/* This program is distributed in the hope that it will be useful, */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the */
/* GNU General Public License for more details. */

/* You should have received a copy of the GNU General Public License */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
#include "FirstMultiply.h"
#include "Multiply.h"
#include "expec_energy_flct.h"
#include "expec_cisajs.h"
#include "expec_cisajscktaltdc.h"
#include "CalcByTEM.h"
#include "FileIO.h"
#include "wrapperMPI.h"
#include "HPhiTrans.h"

/** 
 * 
 * 
 * @param NumAve 
 * @param ExpecInterval 
 * @param X 
 * 
 * @author Takahiro Misawa (The University of Tokyo)
 * @author Kazuyoshi Yoshimi (The University of Tokyo)
 *
 * @return 
 */
int CalcByTEM(
	    const int NumAve,
	    const int ExpecInterval,
	    struct EDMainCalStruct *X
)
{
  long unsigned int u_long_i;
  dsfmt_t dsfmt;
  char sdt[D_FileNameMax];
  char sdt_phys[D_FileNameMax];
  char  sdt_norm[D_FileNameMax];
  int rand_i, rand_max;
  long int i_max=0;
  FILE *fp;
  double Time=X->Bind.Def.Param.Tinit, Ns;
  double dt = X->Bind.Def.Param.TimeSlice;
  struct TimeKeepStruct tstruct;
  tstruct.tstart=time(NULL);
  
  
  rand_max = NumAve;
  step_spin = ExpecInterval;
  X->Bind.Def.St=0;
  fprintf(stdoutMPI, cLogTEM_Start);

  for (rand_i = 0; rand_i<rand_max; rand_i++){
    //Time = 0.0;
    if(X->Bind.Def.iInputEigenVec==FALSE){
    //calc  v1
    //fprintf(stdoutMPI, "An Initial Vector is calculated.\n");
    //if(!CalcByLanczos(&X)==0){
    //  FinalizeMPI();
    //  return -1;
    //}
      fprintf(stderr, "Error: A file of Inputvector is not inputted.\n");
      return -1;
    }
    else{
      //input v1
      fprintf(stdoutMPI, "An Initial Vector is inputted.\n");
      //sprintf(sdt, cFileNameInputVec, X->Bind.Def.CDataFileHead, rand_i, myrank);
      sprintf(sdt, cFileNameInputVec, X->Bind.Def.CDataFileHead, X->Bind.Def.k_exct-1, myrank);
      fp = fopen(sdt, "rb");
      if(fp==NULL){
        fprintf(stderr, "Error: A file of Inputvector does not exist.\n");
        fclose(fp);
        exitMPI(-1);
      }
      fread(&i_max, sizeof(long int), 1, fp);
      if(i_max != X->Bind.Check.idim_max){
        fprintf(stderr, "Error: A file of Inputvector is incorrect.\n");
        fclose(fp);
        exitMPI(-1);
      }
      fread(v1, sizeof(complex double),X->Bind.Check.idim_max+1, fp);
    
      fclose(fp);
    }
  //for (rand_i = 0; rand_i<X->Bind.Check.idim_max+1; rand_i++){
  //  printf("%d, %d:%.2e  %.2e\n",myrank, X->Bind.Check.idim_max, creal(v1[rand_i]), cimag(v1[rand_i]));
  //}
  //printf("%d, %d:%.2e  %.2e\n",myrank, X->Bind.Check.idim_max, creal(v1[0]), cimag(v1[0]));
  //printf("%d, %d:%.2e  %.2e\n",myrank, X->Bind.Check.idim_max, creal(v1[X->Bind.Check.idim_max]), cimag(v1[X->Bind.Check.idim_max]));


  //for (rand_i = 0; rand_i<1; rand_i++){
  //for (rand_i = 0; rand_i<rand_max; rand_i++){
    sprintf(sdt_phys, cFileNameSSRand, rand_i);
    if(!childfopenMPI(sdt_phys, "w", &fp)==0){
      return -1;
    }
    fprintf(fp, cLogSSRand);
    fclose(fp);
    
    sprintf(sdt_norm, cFileNameNormRand, rand_i);
    if(!childfopenMPI(sdt_norm, "w", &fp)==0){
      return -1;
    }
    fprintf(fp, cLogNormRand);
    fclose(fp);
    
/*    TransferWithPeierls(&(X->Bind), Time);
    FirstMultiplyForTEM(&dsfmt, &(X->Bind));
    
    expec_energy(&(X->Bind)); //v0 = H*v1
    Ns = 1.0*X->Bind.Def.NsiteMPI;
    step_i = 0;
    X->Bind.Def.istep=step_i;
    X->Bind.Def.irand=rand_i;
    expec_cisajs(&(X->Bind),v1);
    expec_cisajscktaltdc(&(X->Bind), v1);
    if(!childfopenMPI(sdt_phys, "a", &fp)==0){
      return -1;
    }
    fprintf(fp, "%.16lf  %.16lf %.16lf %.16lf %.16lf %d\n", Time, X->Bind.Phys.energy, X->Bind.Phys.var, X->Bind.Phys.doublon, X->Bind.Phys.num ,step_i);
    fclose(fp);

    Time += dt;
    step_i = 1;
    X->Bind.Def.istep=step_i;
    X->Bind.Def.irand=rand_i;

    TransferWithPeierls(&(X->Bind), Time);
    MultiplyForTEM(&(X->Bind));
    expec_energy(&(X->Bind)); //v0 = H*v1
    
    if(!childfopenMPI(sdt_phys, "a", &fp)==0){
      return -1;
    }
    fprintf(fp, "%.16lf  %.16lf %.16lf %.16lf %.16lf %d\n", Time, X->Bind.Phys.energy, X->Bind.Phys.var, X->Bind.Phys.doublon, X->Bind.Phys.num ,step_i);
    fclose(fp);

    if(!childfopenMPI(sdt_norm, "a", &fp)==0){
      return -1;
    }
    fprintf(fp, "%.16lf %.16lf %.16lf %d\n", Time, global_norm, global_1st_norm, step_i);
    fclose(fp);
*/
    //for (step_i = 2; step_i<X->Bind.Def.Lanczos_max; step_i++){
    for (step_i = 0; step_i<X->Bind.Def.Lanczos_max; step_i++){
      X->Bind.Def.istep=step_i;

      if(step_i %(X->Bind.Def.Lanczos_max/10)==0){
	fprintf(stdoutMPI, cLogTPQStep, step_i, X->Bind.Def.Lanczos_max);
      }
      TransferWithPeierls(&(X->Bind), Time);
      //TransferForQuench(&(X->Bind), Time);
      X->Bind.Def.istep=step_i;
      TimeKeeperWithStep(&(X->Bind), cFileNameTPQStep, cTPQStep, "a", step_i);
      //FirstMultiplyForTEM(&(X->Bind));
      MultiplyForTEM(&(X->Bind));
      //TimeKeeperWithStep(&(X->Bind), cFileNameTimeKeep, cTPQStepEnd, "a", step_i);
      expec_energy_flct(&(X->Bind));
      //expec(&(X->Bind));
      Time += dt;
      if(!childfopenMPI(sdt_phys, "a", &fp)==0){
	return -1;
      }
      fprintf(fp, "%.16lf  %.16lf %.16lf %.16lf %.16lf %d\n", Time, X->Bind.Phys.energy, X->Bind.Phys.var, X->Bind.Phys.doublon, X->Bind.Phys.num ,step_i);
      fclose(fp);

      if(!childfopenMPI(sdt_norm, "a", &fp)==0){
	return -1;
      }
      fprintf(fp, "%.16lf %.16lf %.16lf %d\n", Time, global_norm, global_1st_norm, step_i);
      fclose(fp);

      if (step_i%step_spin == 0){
	expec_cisajs(&(X->Bind),v1);
	expec_cisajscktaltdc(&(X->Bind), v1);
      }
      if(X->Bind.Def.iOutputEigenVec==TRUE){
        if(step_i%X->Bind.Def.Param.OutputInterval == 0){
          sprintf(sdt, cFileNameOutputEigen, X->Bind.Def.CDataFileHead, step_i, myrank);
          //sprintf(sdt, cFileNameOutputEigen, X->Bind.Def.CDataFileHead, rand_i, myrank);
          //sprintf(sdt, cFileNameOutputEigen, X->Bind.Def.CDataFileHead, X->Bind.Def.k_exct-1, myrank);
          if(childfopenALL(sdt, "wb", &fp)!=0){
            fclose(fp);
            exitMPI(-1);
            }
          fwrite(&X->Bind.Check.idim_max, sizeof(long int), 1, fp);
          fwrite(v1, sizeof(complex double),X->Bind.Check.idim_max+1, fp);
          fclose(fp);
        }
      }
    }
    if(X->Bind.Def.iOutputEigenVec==TRUE){
      sprintf(sdt, cFileNameOutputEigen, X->Bind.Def.CDataFileHead, rand_i, myrank);
      //sprintf(sdt, cFileNameOutputEigen, X->Bind.Def.CDataFileHead, X->Bind.Def.k_exct-1, myrank);
      if(childfopenALL(sdt, "wb", &fp)!=0){
        fclose(fp);
        exitMPI(-1);
        }
      fwrite(&X->Bind.Check.idim_max, sizeof(long int), 1, fp);
      fwrite(v1, sizeof(complex double),X->Bind.Check.idim_max+1, fp);
      fclose(fp);
    }
  }
  fprintf(stdoutMPI, cLogTEM_End);
  tstruct.tend=time(NULL);
  fprintf(stdoutMPI, cLogTEM_End, (int)(tstruct.tend-tstruct.tstart));

  return 0;
}