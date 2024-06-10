#include "stdio.h"
#include "stdlib.h"
#include <string>
int compare(int coda, int run1, int run2)
{
	std::string test_path    = "~/japan_mrc/testing/coda" + to_string(coda) + "/isu_sample_" + to_string(run1) + ".root";
	// std::string test_path    = "~/japan_mrc/testing/coda3/isu_sample_" + to_string(run1) + ".root";
	std::string compare_path = "~/data/mock_data/japan_orig/rootfiles/isu_sample_" + to_string(run2) + ".root";
	printf("test_build = %s\n", test_path.c_str());
	printf("japan_orig = %s\n", compare_path.c_str());
	TFile* F = new TFile(test_path.c_str());
	TFile* f = new TFile(compare_path.c_str());

	TTree* T = (TTree*)F->Get("evt");
	TTree* t = (TTree*)f->Get("evt");
	T->AddFriend(t,"japan_orig");
	TCanvas* c = new TCanvas();
	c->Divide(2,2);
	c->cd(1);
	T->Draw("s7_r5c_tr2-japan_orig.s7_r5c_tr2");
	c->cd(2);
	T->Draw("s4_r3_open-japan_orig.s4_r3_open");
	c->cd(3);
	T->Draw("s7_r6_closed-japan_orig.s7_r6_closed");
	c->cd(4);
	T->Draw("target_energy-japan_orig.target_energy");
	gPad->WaitPrimitive();
	
	
	return 0;
}
