#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include"PDB.h"

void lpdbWritebase(FILE* fpt,PDB* pdb){
  int countALA=0;//1
  int countGLY=0;//2
  int countARG=0;//3
  int countASN=0;//4
  int countASP=0;//5
  int countCYS=0;//6
  int countGLN=0;//7
  int countGLU=0;//8
  int countHIS=0;//9
  int countILE=0;//10
  int countLEU=0;//11
  int countLYS=0;//12
  int countMET=0;//13
  int countPHE=0;//14
  int countPRO=0;//15
  int countSER=0;//16
  int countTHR=0;//17
  int countTRP=0;//18
  int countTYR=0;//19
  int countVAL=0;//20
  int countOTH=0;//それ以外
  for(pdb->currentCA=pdb->topCA;pdb->currentCA !=NULL;pdb->currentCA=pdb->currentCA->nextCA){
    if(strcmp(pdb->currentCA->atom->resName,"ALA")==0){//動かなかったら ->resNameを.resNameに
      countALA++;
    }else if(strcmp(pdb->currentCA->atom->resName,"GLY")==0){//動かなかったら ->resNameを.resNameに
      countGLY++;
    }else if(strcmp(pdb->currentCA->atom->resName,"ARG")==0){//動かなかったら ->resNameを.resNameに
      countARG++;
    }else if(strcmp(pdb->currentCA->atom->resName,"ASN")==0){//動かなかったら ->resNameを.resNameに
      countASN++;
    }else if(strcmp(pdb->currentCA->atom->resName,"ASP")==0){//動かなかったら ->resNameを.resNameに
      countASP++;
    }else if(strcmp(pdb->currentCA->atom->resName,"CYS")==0){//動かなかったら ->resNameを.resNameに
      countCYS++;
    }else if(strcmp(pdb->currentCA->atom->resName,"GLN")==0){//動かなかったら ->resNameを.resNameに
      countGLN++;
    }else if(strcmp(pdb->currentCA->atom->resName,"GLU")==0){//動かなかったら ->resNameを.resNameに
      countGLU++;
    }else if(strcmp(pdb->currentCA->atom->resName,"HIS")==0){//動かなかったら ->resNameを.resNameに
      countHIS++;
    }else if(strcmp(pdb->currentCA->atom->resName,"ILE")==0){//動かなかったら ->resNameを.resNameに
      countILE++;
    }else if(strcmp(pdb->currentCA->atom->resName,"LEU")==0){//動かなかったら ->resNameを.resNameに
      countLEU++;
    }else if(strcmp(pdb->currentCA->atom->resName,"LYS")==0){//動かなかったら ->resNameを.resNameに
      countLYS++;
    }else if(strcmp(pdb->currentCA->atom->resName,"MET")==0){//動かなかったら ->resNameを.resNameに
      countMET++;
    }else if(strcmp(pdb->currentCA->atom->resName,"PHE")==0){//動かなかったら ->resNameを.resNameに
      countPHE++;
    }else if(strcmp(pdb->currentCA->atom->resName,"PRO")==0){//動かなかったら ->resNameを.resNameに
      countPRO++;
    }else if(strcmp(pdb->currentCA->atom->resName,"SER")==0){//動かなかったら ->resNameを.resNameに
      countSER++;
    }else if(strcmp(pdb->currentCA->atom->resName,"THR")==0){//動かなかったら ->resNameを.resNameに
      countTHR++;
    }else if(strcmp(pdb->currentCA->atom->resName,"TRP")==0){//動かなかったら ->resNameを.resNameに
      countTRP++;
    }else if(strcmp(pdb->currentCA->atom->resName,"TYR")==0){//動かなかったら ->resNameを.resNameに
      countTYR++;
    }else if(strcmp(pdb->currentCA->atom->resName,"VAL")==0){//動かなかったら ->resNameを.resNameに
      countVAL++;
    }else if(strcmp(pdb->currentCA->atom->resName,"OTH")==0){//動かなかったら ->resNameを.resNameに
      countOTH++;
    }
  }
  fprintf(fpt,"ALA:\t%d\n",countALA);//1
  fprintf(fpt,"ARG:\t%d\n",countARG);//2
  fprintf(fpt,"ASN:\t%d\n",countASN);//3
  fprintf(fpt,"ASP:\t%d\n",countASP);//4
  fprintf(fpt,"CYS:\t%d\n",countCYS);//5
  fprintf(fpt,"GLN:\t%d\n",countGLN);//6
  fprintf(fpt,"GLU:\t%d\n",countGLU);//7
  fprintf(fpt,"GLY:\t%d\n",countGLY);//8
  fprintf(fpt,"HIS:\t%d\n",countHIS);//9
  fprintf(fpt,"ILE:\t%d\n",countILE);//10
  fprintf(fpt,"LEU:\t%d\n",countLEU);//11
  fprintf(fpt,"LYS:\t%d\n",countLYS);//12
  fprintf(fpt,"MET:\t%d\n",countMET);//13
  fprintf(fpt,"PHE:\t%d\n",countPHE);//14
  fprintf(fpt,"PRO:\t%d\n",countPRO);//15
  fprintf(fpt,"SER:\t%d\n",countSER);//16
  fprintf(fpt,"THR:\t%d\n",countTHR);//17
  fprintf(fpt,"TRP:\t%d\n",countTRP);//18
  fprintf(fpt,"TYR:\t%d\n",countTYR);//19
  fprintf(fpt,"VAL:\t%d\n",countVAL);//20
  fprintf(fpt,"OTH:\t%d\n",countOTH);//それ以外
}
