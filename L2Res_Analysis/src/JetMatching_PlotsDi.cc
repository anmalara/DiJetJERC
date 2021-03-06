#include "../include/parameters.h"
#include "../include/useful_functions.h"
#include "../include/CorrectionObject.h"

#include <iostream>
#include <fstream>
#include <string> 

#include <TStyle.h>
#include <TF1.h>
#include <TH1.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TGraph.h>
#include <TGraphErrors.h>
#include <TMultiGraph.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TLine.h>
#include <TCanvas.h>
#include <TMatrixDSym.h>
#include <TPaveStats.h>
#include <TFitResult.h>
#include <TLegend.h>
#include <TLatex.h>
#include <TVirtualFitter.h>
#include <TMath.h>
#include <TFile.h>
#include <TProfile.h>
#include <TString.h>

using namespace std;

void CorrectionObject::JetMatching_PlotsDi(){
  cout << "--------------- StartingJetMatching_PlotsDi () ---------------" << endl << endl;
  CorrectionObject::make_path(CorrectionObject::_outpath+"plots/matching/");
  TStyle* m_gStyle = new TStyle();
  m_gStyle->SetOptFit(000);

  int n_trigger = n_triggerDi;
  vector<int> triggerVal(triggerValDi, triggerValDi + sizeof(triggerValDi) / sizeof(triggerValDi[0]));
  
  // fill the histos for pt average in bins of eta
  TH1D* trg_data0[n_trigger];
  TH1D* trg_data1[n_trigger];
  
  int countPt = 0;
  TString namehist = "trg_";

  TString dirNames[n_trigger];
  for(int i = 0; i<n_trigger; i++){
    dirNames[i] = TString("HLT_DiPFJetAve") + to_string(triggerVal[i]); 
  }

  TString var1 = "matchJetId_0";
  TString var2 = "matchJetId_1";  
    
  for(int i=0; i<n_trigger; i++){
    TString dirName = dirNames[i];
  
    TH1D* hist;
    
    cout << "looking for "<<dirName << endl;
    
    trg_data0[i] =(TH1D*) CorrectionObject::_DATAFile->Get(dirName+"/"+var1)->Clone();
    trg_data1[i] =(TH1D*) CorrectionObject::_DATAFile->Get(dirName+"/"+var2)->Clone();
    // trg_data[i]->Rebin(6);
    // trg_data[i]->SaveAs(CorrectionObject::_outpath+"plots/trg/"+dirName+".root");
    }

  cout << "Draw plots to "<<CorrectionObject::_outpath+"plots/matching" << endl;

  for(int i=0; i<n_trigger; i++){
      TCanvas* c1 = new TCanvas("c1");
      trg_data0[i]->Draw();
      c1->Print(CorrectionObject::_outpath+"plots/matching/"+dirNames[i]+"_jetid_0.eps","eps");
      
      TCanvas* c2 = new TCanvas("c2");
      trg_data1[i]->Draw();
      c2->Print(CorrectionObject::_outpath+"plots/matching/"+dirNames[i]+"_jetid_1.eps","eps");
  }

  
}
