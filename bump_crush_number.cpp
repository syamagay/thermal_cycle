int bump_crush_number(const char* module="QU-12",Int_t _Measure_NUM=35){
  TCut enable_cut = "enable==1";
  TCut noisy_cut = "noisy==1";
  TCut dead_cut = "dead==1";

  TCut mask_cut=enable_cut&&noisy_cut&&dead_cut;
  TCut hit0 = "sumocp==0";
  
  //  const Int_t measure_num=cycle_max/5+1;  
  const Int_t measure_num=_Measure_NUM;
  Int_t bump_crush_pixels[measure_num];
  Int_t cycle[measure_num];
  Int_t cycle2[measure_num-1];
  Int_t pixels_diff[measure_num-1];
  for(Int_t i=0;i<measure_num;i++){
    bump_crush_pixels[i]=0;
    cycle[i]=0;
    if(i>0){
      if(cycle[i-1]==85){
	cycle[i]=cycle[i-1]+15;
      }
      else if(cycle[i-1]>99){
	cycle[i]=cycle[i-1]+20;
      }
      else{
	cycle[i]=i*5;
      }
      cycle2[i-1]=0;
      pixels_diff[i-1]=0;
      cycle2[i-1]=cycle[i];
    }
    std::cout << cycle[i] << std::endl;
    TFile*datafile=new TFile(Form("%s/%dc/data.root",module,cycle[i]));
    TTree*maps=(TTree*)datafile->Get("maps");
    bump_crush_pixels[i]=maps->GetEntries(hit0&&mask_cut);
    
    if(i>0){
      pixels_diff[i-1]=bump_crush_pixels[i]-bump_crush_pixels[i-1];
    }
    delete maps;
    datafile->Close();
  }  
  TCanvas*bump_crush_canvas=new TCanvas("bump_crush_canvas","");
  TGraph*graph=new TGraph(measure_num,cycle,bump_crush_pixels);
  graph->Draw();
  graph->SetTitle("bump_crush_pixels# ;cycle_num;pixel#");

  TCanvas*bump_crush_diff_canvas=new TCanvas("bump_crush_diff_canvas","");
  TGraph*graph2=new TGraph(measure_num-1,cycle2,pixels_diff);
  graph2->Draw();
  graph2->SetTitle("bump_crush_diff_pixels# ;cycle_num;pixel#");

  bump_crush_canvas->Print(Form("%s/bump_crush_pixels.pdf(",module));
  bump_crush_diff_canvas->Print(Form("%s/bump_crush_pixels.pdf)",module));
  return 0;
}
