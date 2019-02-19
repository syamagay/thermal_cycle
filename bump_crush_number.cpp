int bump_crush_number(const char* module="QU-12",Int_t cycle_max=35){
  TCut enable_cut = "enable==1";
  TCut noisy_cut = "noisy==1";
  TCut dead_cut = "dead==1";

  TCut mask_cut=enable_cut&&noisy_cut&&dead_cut;
  TCut hit0 = "sumocp==0";
  
  const Int_t measure_num=cycle_max/5+1;  
  Int_t bump_crush_pixels[measure_num];
  Int_t cycle[measure_num];
  for(Int_t i=0;i<measure_num;i++){
    bump_crush_pixels[i]=0;
    cycle[i]=0;
    cycle[i]=i*5;
    TFile*datafile=new TFile(Form("%s/%dc/data.root",module,cycle[i]));
    TTree*maps=(TTree*)datafile->Get("maps");
    bump_crush_pixels[i]=maps->GetEntries(hit0&&mask_cut);
    
    delete maps;
    datafile->Close();
  }  
  TGraph*graph=new TGraph(measure_num,cycle,bump_crush_pixels);
  graph->Draw();
  graph->SetTitle("bump_crush_pixels# ;cycle_num;pixel#");
  return 0;
}
