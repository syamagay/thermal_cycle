#include <TFile.h>
#include <TH2D.h>
int histgram_compar(const char* module="QU-12",int cycle_1=50,int cycle_2=55){
  //  TFile*compaire_file=new (Form("%s/compaire.root",module),"recreate");

  Int_t column_1chip=80;
  Int_t row_1chip=336;
  
  Int_t column=column_1chip*2;
  Int_t row=row_1chip*2;
  
  TFile*file1=new TFile(Form("%s/%dc/data.root",module,cycle_1));
  TFile*file2=new TFile(Form("%s/%dc/data.root",module,cycle_2));
  
  TH2D*Occupancy_1=(TH2D*)file1->Get("Occupancy_map");
  TH2D*Occupancy_2=(TH2D*)file2->Get("Occupancy_map");
  
  TH2D*Occupancy_diff=new TH2D("Occupancy_diff",Form("Occupancy_%d-%d;column;row",cycle_1,cycle_2),column,1,column+1,row,1,row+1);
  Occupancy_diff->Add(Occupancy_1,Occupancy_2,1,-1);
  Occupancy_diff->Draw("colz");
  
  
  return 0;
}
