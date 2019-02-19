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
  TCanvas*occupancy_canvas=new TCanvas("occupancy_canvas","");
  Occupancy_map->SetMaximum(20);
  Occupancy_map->Draw("colz");

  TCut map_left="chip==1||chip==3";
  TCut map_right="chip==2||chip==4";
  TCut ss_hit0="sumocp==0";
  TCut enable_pixel="enable==1";
  TCut Noisy_pixel="noisy==1";
  TCut dead_pixel="dead==1";

  TCut mask = enable_pixel&&Noisy_pixel&&dead_pixel;
  
  TCut map_hit0_left = map_left&&ss_hit0;
  TCut map_hit0_right= map_right&&ss_hit0;

  TCut source_scan_no_hit="sum_ocp==0";
  
 
  TCanvas*noise_dis_left=new TCanvas("noise_dif_left","");
  TCanvas*noise_dis_right=new TCanvas("noise_dif_right","");
  TCanvas*bump_crush_canvas=new TCanvas("bump_crush_canvas","");
  TCanvas*noise_0_canvas=new TCanvas("noise_0_canvas","");
  //TCanvas*test_map_canvas=new TCanvas("test_map_canvas","");
  
  TH1D*noise_distribution_left=new TH1D("noise_distribution_left",Form("noise_distribution_left(%dcycle);pixels#;noise[e-]",cycle),100,0,500);
  TH1D*noise_hit0_left=new TH1D("noise_hit0_left","noise_hit0_left;pixels#;noise[e-]",100,0,500);
  TH1D*noise_distribution_right=new TH1D("noise_distribution_right",Form("noise_distribution_right(%dcycle);pixels#;noise[e-]",cycle),100,0,500);
  TH1D*noise_hit0_right=new TH1D("noise_hit0_right","noise_hit0_right;pixels#;noise[e-]",100,0,500);
  noise_hit0_left->SetFillColor(kRed);
  noise_hit0_right->SetFillColor(kRed);

  noise_dis_left->cd();
  maps->Draw("noise>>noise_distribution_left",map_left&&mask);
  maps->Draw("noise>>noise_hit0_left",map_hit0_left&&mask,"same");
  noise_dis_left->SetLogy();
  noise_dis_right->cd();
  maps->Draw("noise>>noise_distribution_right",map_right&&mask);
  maps->Draw("noise>>noise_hit0_right",map_hit0_right&&mask,"same");
  noise_dis_right->SetLogy();

  TH1D*noise_diff_left=new TH1D("noise_diff_left","",100,-200,200);
  TH1D*noise_diff_right=new TH1D("noise_diff_right","",100,-200,200);
  TH1D*noise_diff_hit0_left=new TH1D("noise_diff_hit0_left","",100,-200,200);
  TH1D*noise_diff_hit0_right=new TH1D("noise_diff_hit0_right","",100,-200,200);
  TCanvas*noise_diff_left_canvas=new TCanvas("noise_diff_left_canvas","");
  TCanvas*noise_diff_right_canvas=new TCanvas("noise_diff_right_canvas","");
  noise_diff_left_canvas->cd();
  noise_diff_left_canvas->SetLogy();
  noise_diff_hit0_left->SetFillColor(kRed);
  maps->Draw("noise_hv0-noise>>noise_diff_left",map_left&&mask);
  maps->Draw("noise_hv0-noise>>noise_diff_hit0_left",map_hit0_left&&mask,"same");
  noise_diff_right_canvas->cd();
  noise_diff_right_canvas->SetLogy();
  noise_diff_hit0_right->SetFillColor(kRed);
  maps->Draw("noise_hv0-noise>>noise_diff_right",map_right&&mask);
  maps->Draw("noise_hv0-noise>>noise_diff_hit0_right",map_hit0_right&&mask,"same");
    
  TCanvas*noise_hv0_left_canvas=new TCanvas("noise_hv0_left_canvas","");
  TCanvas*noise_hv0_right_canvas=new TCanvas("noise_hv0_right_canvas","");
  //TCanvas*test_map_canvas=new TCanvas("test_map_canvas","");
  TH1D*noise_hv0_left=new TH1D("noise_hv0_left",Form("noise_hv0_left(%dcycle);pixels#;noise[e-]",cycle),100,0,500);
  TH1D*noise_hv0_hit0_left=new TH1D("noise_hv0_hit0_left","noise_hv0_hit0_left;pixels#;noise[e-]",100,0,500);
  TH1D*noise_hv0_right=new TH1D("noise_hv0_right",Form("noise_distribution_right(%dcycle);pixels#;noise[e-]",cycle),100,0,500);
  TH1D*noise_hv0_hit0_right=new TH1D("noise_hv0_hit0_right","noise_hit0_right;pixels#;noise[e-]",100,0,500);
  noise_hv0_left_canvas->cd();
  noise_hv0_hit0_left->SetFillColor(kRed);
  maps->Draw("noise_hv0>>noise_hv0_left",map_left&&mask);
  maps->Draw("noise_hv0>>noise_hv0_hit0_left",map_hit0_left&&mask,"same");
  noise_hv0_left_canvas->SetLogy();
  noise_hv0_right_canvas->cd();
  noise_hv0_hit0_right->SetFillColor(kRed);
  maps->Draw("noise_hv0>>noise_hv0_right",map_right&&mask);
  maps->Draw("noise_hv0>>noise_hv0_hit0_right",map_hit0_right&&mask,"same");
  noise_hv0_right_canvas->SetLogy(); 

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

  TCanvas*enable_canvas=new TCanvas("enable_canvas","");

  TH2D*bump_crush_map=new TH2D("bump_crush_map","bump_crush_map;Column;Row",column_max-1,0,column_max,row_max-1,0,row_max);
  TH2D*noise_0_map=new TH2D("noise_0_map","noise_0_map;Column;Row",column_max-1,0,column_max,row_max-1,0,row_max);
  TH2D*noise_diff_map=new TH2D("noise_diff_map","noise_diff_map;Column;Row",column_max-1,0,column_max,row_max-1,0,row_max);
  TH2D*map=new TH2D("map","map;Column;Row",column_max-1,0,column_max,row_max-1,0,row_max);  
  TH2D*enable_map=new TH2D("enable_map","enablemap;Column;Row",column_max-1,0,column_max,row_max-1,0,row_max);
  bump_crush_map->SetMaximum(2);
  noise_0_map->SetMaximum(2); 
  noise_diff_map->SetMaximum(2); 
  map->SetMaximum(2);
  enable_map->SetMaximum(2);
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
    if(sumocp==0&&enable==1&&dead==1&&noisy==1){
      bump_crush_map->Fill(COLUMN,ROW);
    }    
    if(noise<10){
      noise_0_map->Fill(COLUMN,ROW);
    }
    if(chip==1){
    map->Fill(COLUMN,ROW);
    }
    if(noise_hv0-noise>-100&&noise_hv0-noise<100&&sumocp==0&&enable==1&&dead==1&&noisy==1){
      noise_diff_map->Fill(COLUMN,ROW);
    }
    if(enable==0){
      enable_map->Fill(COLUMN,ROW);
    }
  }
  bump_crush_canvas->cd();
  bump_crush_map->Draw("colz");
  bump_crush_map->SetStats(0);
  noise_0_canvas->cd();
  noise_0_map->Draw("colz");

  enable_canvas->cd();
  enable_map->Draw("colz");
  
  //  test_map_canvas->cd();
  // map->Draw("colz");

  TCanvas*noise_hv0_canvas=new TCanvas("noise_hv0_canvas","");
  noise_diff_map->Draw("colz");  

  TCanvas*sumocp_vs_noise_hv0_canvas=new TCanvas("sumocp_vs_noise_hv0_canvas","");
  TH2D*hist=new TH2D("hist","sumocp_vs_noisehv0;noise_hv0;sumocp",100,0,500,100,-100,100);
  maps->Draw("sumocp:noise_hv0>>hist","","colz");
  hist->SetName("sumocp_vs_noise_hv0");

  TCanvas*sumocp_vs_noise_diff_canvas=new TCanvas("sumocp_vs_diff_hv0_canvas","");
  TH2D*hist2=new TH2D("hist2","sumocp_vs_noisediff;noise_diff;sumocp",100,-100,100,100,-100,100);
  maps->Draw("sumocp:noise_hv0-noise>>hist2","","colz");
  hist2->SetName("sumocp_vs_noise_diff");
  
  noise_dis_left->Print(Form("%s/%dc/picture/noise_distribution.pdf[",module,cycle));
  noise_dis_left->Print(Form("%s/%dc/picture/noise_distribution.pdf",module,cycle));
  noise_dis_right->Print(Form("%s/%dc/picture/noise_distribution.pdf",module,cycle));
  noise_diff_left_canvas->Print(Form("%s/%dc/picture/noise_distribution.pdf",module,cycle));
  noise_diff_right_canvas->Print(Form("%s/%dc/picture/noise_distribution.pdf",module,cycle));
  noise_hv0_left_canvas->Print(Form("%s/%dc/picture/noise_distribution.pdf",module,cycle));
  noise_hv0_right_canvas->Print(Form("%s/%dc/picture/noise_distribution.pdf",module,cycle));
  bump_crush_canvas->Print(Form("%s/%dc/picture/noise_distribution.pdf",module,cycle));
  noise_dis_right->Print(Form("%s/%dc/picture/noise_distribution.pdf]",module,cycle));

  
  //  cycle_file->Close();

  TCanvas*newcanvas=new TCanvas("newcanvas","");
  return 0;
}
