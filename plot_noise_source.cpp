int plot_noise_source(const char* module="QU-12",Int_t cycle=0){
  //  Int_t cycle=0;
  Int_t noise_threshold_right=160;
  Int_t noise_threshold_left=160;
  Int_t column_max=161;
  Int_t row_max=673;
  
  TFile*cycle_file=new TFile(Form("%s/%dc/data.root",module,cycle));
  TTree*maps=(TTree*)cycle_file->Get("maps");
  TH2D*Occupancy_map=(TH2D*)cycle_file->Get("Occupancy_map");
  TH2D*Dead_pixels_map=(TH2D*)cycle_file->Get("Dead_pixels_map");
  TH2D*Noisy_pixels_map=(TH2D*)cycle_file->Get("Noisy_pixels_map");
  TH2D*Low_noise_and_no_hits_pixels_map=(TH2D*)cycle_file->Get("Low_noise_and_no_hits_pixels_map");
  TH2D*Noise_map=(TH2D*)cycle_file->Get("Noise_map"); 
  //  TH1D*Hits_of_pixels=(TH1D*)cycle_file->Get("#' 'of' 'pixels");
  /*
  TCanvas*basic_information=new TCanvas("basic_information","");
  Occupancy_map->Draw("colz");
  basic_information->Print(Form("%dc/picture/basic_information.pdf[",cycle));
  basic_information->Print(Form("%dc/picture/basic_information.pdf",cycle)); 
  Dead_pixels_map->Draw("colz");
  basic_information->Print(Form("%dc/picture/basic_information.pdf",cycle));
  Noisy_pixels_map->Draw("colz");
  basic_information->Print(Form("%dc/picture/basic_information.pdf",cycle));
  Low_noise_and_no_hits_pixels_map->Draw("colz");
  basic_information->Print(Form("%dc/picture/basic_information.pdf",cycle));
  Noise_map->SetMaximum(1000);
  Noise_map->Draw("colz");
  basic_information->Print(Form("%dc/picture/basic_information.pdf",cycle));
  //  Hits_of_pixels->Draw();
  //basic_information->Print(Form("%dc/picture/basic_information.pdf",cycle));
  basic_information->Print(Form("%dc/picture/basic_information.pdf]",cycle));
  */

  TCut map_left="chip==1||chip==3";
  TCut map_right="chip==2||chip==4";

  TCut source_scan_no_hit="sum_ocp==0";
  
 
  TCanvas*noise_dis_left=new TCanvas("noise_dif_left","");
  TCanvas*noise_dis_right=new TCanvas("noise_dif_right","");
  TCanvas*bump_crush_canvas=new TCanvas("bump_crush_canvas","");
  TCanvas*noise_0_canvas=new TCanvas("noise_0_canvas","");
  TCanvas*test_map_canvas=new TCanvas("test_map_canvas","");
  
  TH1D*noise_distribution_left=new TH1D("noise_distribution_left","noise_distribution_left;pixels#;noise[e-]",100,0,500);
  TH1D*noise_distribution_right=new TH1D("noise_distribution_right","noise_distribution_right;pixels#;noise[e-]",100,0,500);
  
  noise_dis_left->cd();
  maps->Draw("noise>>noise_distribution_left",map_left);
  noise_dis_left->SetLogy();
  noise_dis_right->cd();
  maps->Draw("noise>>noise_distribution_right",map_right);
  noise_dis_right->SetLogy();

  TH1D*noise_diff_left=new TH1D("noise_diff_left","",100,-200,200);
  TH1D*noise_diff_right=new TH1D("noise_diff_right","",100,-200,200);
  TCanvas*noise_diff_left_canvas=new TCanvas("noise_diff_left_canvas","");
  TCanvas*noise_diff_right_canvas=new TCanvas("noise_diff_right_canvas","");
  noise_diff_left_canvas->cd();
  noise_diff_left_canvas->SetLogy();
  maps->Draw("noise_hv0-noise>>noise_diff_left",map_left);
  noise_diff_right_canvas->cd();
  noise_diff_right_canvas->SetLogy();
  maps->Draw("noise_hv0-noise>>noise_diff_right",map_right);
    
  Int_t totalpixels = maps->GetEntries();
  Int_t threshold=0;
  Int_t chip=0;
  Int_t row=0;
  Int_t column=0;
  Int_t enable = 0;
  Int_t dead=0;
  Int_t noisy=0;
  Float_t noise=0;
  Float_t noise_hv0=0;
  Int_t sumocp=0;
  maps->SetBranchAddress("chip",&chip);
  maps->SetBranchAddress("row",&row);
  maps->SetBranchAddress("column",&column);
  maps->SetBranchAddress("enable",&enable);
  maps->SetBranchAddress("dead",&dead);
  maps->SetBranchAddress("noisy",&noisy);
  maps->SetBranchAddress("noise",&noise);
  maps->SetBranchAddress("noise_hv0",&noise_hv0);
  maps->SetBranchAddress("sumocp",&sumocp);

  TH2D*bump_crush_map=new TH2D("bump_crush_map","bump_crush_map;Column;Row",column_max-1,0,column_max,row_max-1,0,row_max);
  TH2D*noise_0_map=new TH2D("noise_0_map","noise_0_map;Column;Row",column_max-1,0,column_max,row_max-1,0,row_max);
  TH2D*noise_diff_map=new TH2D("noise_diff_map","noise_diff_map;Column;Row",column_max-1,0,column_max,row_max-1,0,row_max);
  TH2D*map=new TH2D("map","map;Column;Row",column_max-1,0,column_max,row_max-1,0,row_max);
  bump_crush_map->SetMaximum(2);
  noise_0_map->SetMaximum(2); 
  noise_diff_map->SetMaximum(2); 
  map->SetMaximum(2);
  Int_t COLUMN=0;
  Int_t ROW=0;
  for(Int_t i=0;i<totalpixels;i++){
    maps->GetEntry(i);
    if(chip==1||chip==3){
      threshold = noise_threshold_left;
    }
    else if(chip==2||chip==4){
      threshold = noise_threshold_right;
    }
    COLUMN = column + 80*((chip-1)%2);
    ROW = row + 336*(chip>2);
    if(sumocp==0&&noise<threshold&&enable==1&&dead==1&&noisy==1){
      bump_crush_map->Fill(COLUMN,ROW);
    }    
    if(noise<10){
      noise_0_map->Fill(COLUMN,ROW);
    }
    if(chip==1){
    map->Fill(COLUMN,ROW);
    }
    if(noise_hv0-noise>-50&&noise_hv0-noise<50&&sumocp==0&&enable==1&&dead==1&&noisy==1){
      noise_diff_map->Fill(COLUMN,ROW);
    }
  }
  bump_crush_canvas->cd();
  bump_crush_map->Draw("colz");
  
  noise_0_canvas->cd();
  noise_0_map->Draw("colz");

  noise_diff_map->Draw("colz");
  
  test_map_canvas->cd();
  map->Draw("colz");
  /*
  noise_dis_left->Print(Form("%dc/picture/noise_distribution.pdf[",cycle));
  noise_dis_left->Print(Form("%dc/picture/noise_distribution.pdf",cycle));
  noise_dis_right->Print(Form("%dc/picture/noise_distribution.pdf",cycle));
  bump_crush_canvas->Print(Form("%dc/picture/noise_distribution.pdf",cycle));
  noise_dis_right->Print(Form("%dc/picture/noise_distribution.pdf]",cycle));
  */
  return 0;
}
