#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TCanvas.h>
#include <TStyle.h>
#include <TCut.h>
int diff_of_cycles(const char* module="QU-12",Int_t cycle_max=60){
  Int_t target_cycle=70;
  TFile*diff_file=new TFile("diff_of_cycle.root","recreate");

  TCut mask_1=Form("maps_%dc.enable==1&&maps_%dc.dead==1&&maps_%dc.noisy==1",target_cycle,target_cycle,target_cycle);
  TCut mask_2=Form("maps_%dc.enable==1&&maps_%dc.dead==1&&maps_%dc.noisy==1",target_cycle-5,target_cycle-5,target_cycle-5);

  TCut revive=Form("maps_%dc.sumocp>0&&maps_%dc.sumocp==0",target_cycle,target_cycle-5);

  Int_t cycle = 0;
  TFile*file=new TFile(Form("%s/%dc/data.root",module,cycle));
  diff_file->cd();
  TTree*maps_0c=(TTree*)file->Get("new_maps");
  for(Int_t i=0;i<cycle_max+1;i=i+5){
    cycle=i;
    maps_0c->AddFriend(Form("maps_%dc = new_maps",cycle),Form("%s/%dc/data.root",module,cycle));
  }
  TCanvas*c1=new TCanvas("c1","");
  TH2D*map=new TH2D("map","revive_pixels;column;row",160,1,161,672,1,673);
  map->SetMaximum(2);
  maps_0c->Draw(Form("maps_%dc.ROW:maps_%dc.COLUMN>>map",target_cycle,target_cycle),revive&&mask_2,"colz");
  gStyle->SetOptStat(0);
  c1->Print(Form("%s/%dc/revive_pixels.pdf(",module,cycle));
  
  TCanvas*c2=new TCanvas("c2","");
  gStyle->SetOptStat("eMinoru");
  TH1D*dis=new TH1D("dis","hitnum_of_survive_pixels;hit_num;pixel# ",100,0,100);
  maps_0c->Draw(Form("maps_%dc.sumocp>>dis",target_cycle),mask_2&&revive);
  c2->Print(Form("%s/%dc/revive_pixels.pdf)",module,cycle));  
  diff_file->cd();
  maps_0c->Write();
  return 0;
}
