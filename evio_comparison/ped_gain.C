#include "stdio.h"
#include "stdlib.h"
#include "cstring"
#include "time.h"
/*
 * Gain and Pedestal Calculation
 * Block[i] = Gain x [ Block_raw[i] * bpe / samples - pedestal ] 
 *
 * If summing:
 * Block_tot = Gain x [SUM{Block_raw[i] * bpe / samples}] - 4*{Gain x pedestal}
 *
 * To Run: root -l -q 'ped_gain.C("prex","bcm_dg_dsc")'
 *
 */


enum leaf
{
	HW_SUM = 0,
	BLOCK0 = 1,BLOCK1 = 2,
	BLOCK2 = 3,BLOCK3 = 4,
	SAMPLES = 5,
	ERROR = 6,
	HW_SUM_R = 7,
	BLOCK0R = 8,  BLOCK1R = 9,
	BLOCK2R = 10, BLOCK3R = 11,
	SEQ = 12
};


void ped_gain(const char* fileAbbr, const char* branch)
{
	const char* abr[3] = {"prex", "fork", "japan"};
	const char* file;
	const char* fileList[3] = {"/cache/halla/parity/rootfiles/pass1/crex_respin2/prexPrompt_pass2_5408.000.root",
							   "/volatile/halla/moller12gev/mrconaway/rootfiles/CODA2/EVIO4/prexPrompt_pass1_evio_5408.000.root",
							   "/volatile/halla/moller12gev/mrconaway/rootfiles/JAPAN-MOLLER/EVIO4/prexPrompt_pass1_evio_5408.000.root"};
	if (!strcmp(fileAbbr, abr[0])) {
		file = fileList[0];	
		printf("Opening %s\n", file);
	}
	else if (!strcmp(fileAbbr, abr[1])) {
		file = fileList[1];	
		printf("Opening %s\n", file);
	}
	else if (!strcmp(fileAbbr, abr[2])) {
		file = fileList[2];	
		printf("Opening %s\n", file);
	}
	else {
		printf("No valid file was given...\nChoices:\n");
		for(int i = 0; i < 3; i++)
			printf("%s -> %s\n", abr[i], fileList[i]);
		printf("Exiting...\n");
		exit(EXIT_FAILURE);
	}
	if(branch) printf("Selecting Branch %s\n", branch);
	// Timer 
	clock_t start = clock();

	// Open the files that we want to calculate the pedestal and gain for
	// TFile* f = new TFile(filename);
	TFile* f = new TFile(file);

	// Data Containers
	double leaves[13];
	const size_t abbrLen = strlen(fileAbbr);
	const size_t braLen = strlen(branch);

	// Open TTree
	TTree* t = (TTree*)f->Get("evt");
	t->SetBranchAddress(branch, &leaves);
	size_t tSize = t->GetEntries();
	printf("Tree Size = %zu\n", tSize);
	
	// TGraph for plotting
	TGraph *g = new TGraph();
	g->SetMarkerStyle(kFullCircle);
	char* title = new char[abbrLen + braLen + 1 + 1];
	if(!memcpy(title, fileAbbr, abbrLen))          { printf("Issue in memcpy"); }
	if(!memcpy(title+abbrLen, "_", 1))             { printf("Issue in memcpy"); }
	if(!memcpy(title+abbrLen+1, branch, braLen+1)) { printf("Issue in memcpy"); }

	g->SetTitle(title);

	// Loop through events
	int bpe = 4;
	int points = 500;
	for (int i = 0; i < points; i++) {
		if (i % 10000 == 0) printf("%i events processed...\n", i);
		t->GetEntry(i);
		int samples   = leaves[SAMPLES];
		double block  = 0;
		double blockr = 0;
		for (int j = 0; j < bpe; j++) {
			block  += leaves[BLOCK0+j];	
			blockr += leaves[BLOCK0R+j] * bpe/samples;
		}
		g->SetPoint(i, blockr, block);

	}

	// Fot data
	TF1 *flin = new TF1("flin", "[0]*x+[1]");
	flin->SetParameters(0.1,100);
	g->Fit("flin");

	// Calculate the Gain and Pedestal
	double slope = flin->GetParameter(0);
	double inter = flin->GetParameter(1);
	double pedal = -1*inter/(4*slope);
	printf("Slope: %f\tIntercept: %f\n", slope, inter);
	printf("--------------------------------------------\n");
	printf("| Gain: %f\tPedal: %f |\n", slope, pedal);
	printf("--------------------------------------------\n");

	
	// Plotting
	TCanvas* cprex = new TCanvas(fileAbbr);
	cprex->cd();
	auto legend = new TLegend(0.1,0.7,0.6,0.9);
	legend->AddEntry(g, Form("Gain: %f", slope), "r");
	legend->AddEntry(g, Form("Pedal: %f",pedal), "r");
	legend->AddEntry(g, Form("Points: %d",points), "r");
	g->Draw();
	legend->Draw();




	// Timer
	clock_t duration = clock() - start;
	printf("Time Elapsed: %ldms\n", duration*1000/CLOCKS_PER_SEC);
	gPad->WaitPrimitive();
	printf("Press Enter to continue...\n");
	getchar();

	return 0;
}
