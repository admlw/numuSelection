void plot_nue_spectrum(){

    TFile* _file_nuecc = new TFile("/uboone/data/users/alister1/SBNFit_files/filtered_events_mc_nue_sbnfit_skimmed_fixed_smeared.root", "read");
    TTree* bnb_nc = (TTree*)_file_nuecc->Get("nc");
    TTree* bnb_numu = (TTree*)_file_nuecc->Get("nu_mu");
    TTree* bnb_cosmic = (TTree*)_file_nuecc->Get("cosmic");

    TFile* _file_nueintrinsic = new TFile("/uboone/data/users/alister1/SBNFit_files/filtered_events_mc_nueintrinsic_sbnfit_skimmed_fixed.root", "read");
    TTree* outfv = (TTree*)_file_nueintrinsic->Get("outfv");
    TTree* contaminated = (TTree*)_file_nueintrinsic->Get("contaminated");
    TTree* nuecc = (TTree*)_file_nueintrinsic->Get("nu_e_cc");
    TTree* nuecc0pinp = (TTree*)_file_nueintrinsic->Get("nu_e_cc0pinp");

    TFile* _file_cov = new TFile("/uboone/app/users/alister1/NumuNueFitter/covariance_matrices.root", "read");

    const int n_bins = 8;
    float miniboone_binning[n_bins+1] = {0.2, 0.550, 0.675, 0.800, 0.950, 1.100, 1.300, 1.500, 3.00};
    TH1D* h_bnb_nc = new TH1D("h_bnb_nc", ";Reconstructed Neutrino energy (GeV);Selected Events", n_bins, miniboone_binning);
    TH1D* h_bnb_numu = new TH1D("h_bnb_numu", ";Reconstructed Neutrino energy (GeV);", n_bins, miniboone_binning);
    TH1D* h_bnb_cosmic = new TH1D("h_bnb_cosmic", ";Reconstructed Neutrino energy (GeV);Selected Events", n_bins, miniboone_binning);
    TH1D* h_outfv = new TH1D("h_outfv", ";Reconstructed Neutrino energy (GeV);", n_bins, miniboone_binning);
    TH1D* h_contaminated = new TH1D("h_contaminated", ";Reconstructed Neutrino energy (GeV);", n_bins, miniboone_binning);
    TH1D* h_nuecc = new TH1D("h_nuecc", ";Reconstructed Neutrino energy (GeV);", n_bins, miniboone_binning);
    TH1D* h_nuecc0pinp = new TH1D("h_nuecc0pinp", ";Reconstructed Neutrino energy (GeV);", n_bins, miniboone_binning);

    bnb_nc->Draw("reco_energy >> h_bnb_nc");
    bnb_numu->Draw("reco_energy >> h_bnb_numu");
    bnb_cosmic->Draw("reco_energy >> h_bnb_cosmic");
    outfv->Draw("reco_energy >> h_outfv");
    contaminated->Draw("reco_energy >> h_contaminated");
    nuecc->Draw("reco_energy >> h_nuecc");
    nuecc0pinp->Draw("reco_energy >> h_nuecc0pinp");

    h_outfv->Sumw2();
    h_contaminated->Sumw2();
    h_nuecc->Sumw2();
    h_nuecc0pinp->Sumw2();

    h_outfv->Scale(13.0/4.0);
    h_contaminated->Scale(13.0/4.0);
    h_nuecc->Scale(13.0/4.0);
    h_nuecc0pinp->Scale(13.0/4.0);

    h_bnb_cosmic->SetFillColor(TColor::GetColor(8,64,129));
    h_bnb_cosmic->SetLineWidth(0);
    h_contaminated->SetFillColor(TColor::GetColor(8,104,172));
    h_contaminated->SetLineWidth(0);
    h_outfv->SetFillColor(TColor::GetColor(78,179,211));
    h_outfv->SetLineWidth(0);
    h_bnb_nc->SetFillColor(TColor::GetColor(113,1,98));
    h_bnb_nc->SetLineWidth(0);
    h_bnb_numu->SetFillColor(TColor::GetColor(165, 0, 38));
    h_bnb_numu->SetLineWidth(0);
    h_nuecc->SetFillColor(kYellow+3);
    h_nuecc->SetLineWidth(0);
    h_nuecc0pinp->SetFillColor(kYellow+1);
    h_nuecc0pinp->SetLineWidth(0);

    THStack* hs = new THStack("hs", ";Reconstructed Neutrino Energy (GeV);Selected Events");
    hs->Add(h_bnb_cosmic);
    hs->Add(h_contaminated);
    hs->Add(h_outfv);
    hs->Add(h_bnb_nc);
    hs->Add(h_bnb_numu);
    hs->Add(h_nuecc);
    hs->Add(h_nuecc0pinp);

    TH1D* h_tot = (TH1D*)h_bnb_cosmic->Clone("h_tot");
    h_tot->Add(h_contaminated);
    h_tot->Add(h_outfv);
    h_tot->Add(h_bnb_nc);
    h_tot->Add(h_bnb_numu);
    h_tot->Add(h_nuecc);
    h_tot->Add(h_nuecc0pinp);

    TCanvas *c1 = new TCanvas("c1", "c1", 600, 500);
    TPad *ptop = new TPad("ptop", "", 0.0005, 0.1, 0.995, 0.995);
    ptop->SetTopMargin(0.23);
    ptop->SetBottomMargin(0.11);
    ptop->Draw();
    ptop->cd();

    TLegend *leg_1 = new TLegend(0.1, 0.8, 0.5, 0.98);
    leg_1->AddEntry(h_bnb_cosmic, Form("Cosmic, %g entries", std::floor(10*h_bnb_cosmic->Integral())/10.));
    leg_1->AddEntry(h_contaminated, Form("Mixed, %g entries", std::floor(10*h_contaminated->Integral())/10.));
    leg_1->AddEntry(h_outfv, Form("OOFV, %g entries", std::floor(10*h_outfv->Integral())/10.));
    leg_1->AddEntry(h_bnb_nc, Form("NC, %g entries", std::floor(10*h_bnb_nc->Integral())/10.));
    leg_1->SetTextSize(0.035);

    TLegend *leg_2 = new TLegend(0.5, 0.8, 0.9, 0.98);
    leg_2->AddEntry(h_bnb_numu, Form("#nu_{#mu}, %g entries", std::floor(10*h_bnb_numu->Integral())/10.));
    leg_2->AddEntry(h_nuecc, Form("#nu_{e}CC-Other, %g entries", std::floor(10*h_nuecc->Integral())/10.));
    leg_2->AddEntry(h_nuecc0pinp, Form("#nu_{e}CC0#piNP, %g entries", std::floor(10*h_nuecc0pinp->Integral())/10.));
    leg_2->SetTextSize(0.035);

    hs->Draw("hist");
    hs->GetYaxis()->SetTitleOffset(1.4);
    hs->Draw("hist");
    leg_1->Draw("same");
    leg_2->Draw("same");

    c1->SaveAs("nue_stack.pdf");

    // plot errors
    TCanvas *c2 = new TCanvas("c2", "c2", 600, 400);
    h_tot->SetFillStyle(0);
    h_tot->SetLineColor(kBlack);
    h_tot->SetLineWidth(2);
    
    TH1D* h_tot_stat_syst = (TH1D*)h_tot->Clone("h_tot_stat_syst");
    TH2D* h_cov = (TH2D*)_file_cov->Get("h_const_FULL_matrix");
    for (int i_b = 1; i_b < h_tot->GetNbinsX()+1; i_b++){

        float stat_error = std::sqrt(h_tot->GetBinContent(i_b));
        float statplussyst_error =  std::sqrt(h_cov->GetBinContent(i_b, i_b)); 
        float syst_error = std::sqrt(std::pow(statplussyst_error, 2) - std::pow(stat_error,2));

        std::cout << "bin " << i_b << " has " << h_tot->GetBinContent(i_b) << " entries " << std::endl;
        std::cout << "bin " << i_b << " has stat error: " << stat_error << std::endl;
        std::cout << "bin " << i_b << " has stat frac error: " << std::sqrt(h_tot->GetBinContent(i_b))/h_tot_stat_syst->GetBinContent(i_b) << std::endl;
        std::cout << "bin " << i_b << " has stat+syst error: " << statplussyst_error << std::endl;
        std::cout << "bin " << i_b << " has stat+syst frac error: " << std::sqrt(h_cov->GetBinContent(i_b, i_b))/h_tot_stat_syst->GetBinContent(i_b) << std::endl;
        h_tot_stat_syst->SetBinError(i_b, std::sqrt(h_cov->GetBinContent(i_b,i_b)));
        std::cout << "bin " << i_b << " has syst error: " << syst_error << std::endl; 
        std::cout << "bin " << i_b << " has syst frac error: " << syst_error/h_tot->GetBinContent(i_b) << std::endl; 

    }
   
    h_tot_stat_syst->Draw("histE1");
    h_tot->Draw("histE1same");

    TLegend *leg = new TLegend(0.15, 0.83, 0.5, 0.88);
    leg->AddEntry(h_tot, "Stat.+Syst.", "lp");
    leg->Draw("same");

    c2->SaveAs("nue_statsyst.pdf");
}
