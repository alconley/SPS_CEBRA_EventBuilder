/*SFPPlotter.h
 *Class for generating histogram files for SPS-CEBRA data
 *Intended use case is generating a TChain of multiple analyzed files and making
 *histograms of the larger data set.
 *
 *Created Jan 2020 by GWM
 */

#include "SFPPlotter.h"
#include <TSystem.h>

namespace EventBuilder {

	/*Generates storage and initializes pointers*/
	SFPPlotter::SFPPlotter() :
		event_address(new ProcessedEvent()), m_progressFraction(0.1)
	{
	}
	
	SFPPlotter::~SFPPlotter() 
	{
		delete event_address;
	}
	
	/*2D histogram fill wrapper*/
	void SFPPlotter::MyFill(THashTable* table, const std::string& name, int binsx, double minx, double maxx, double valuex,
							int binsy, double miny, double maxy, double valuey)
	{
		TH2F *histo = (TH2F*) table->FindObject(name.c_str());
		if(histo != nullptr) 
			histo->Fill(valuex, valuey);
		else
		{
			TH2F *h = new TH2F(name.c_str(), name.c_str(), binsx, minx, maxx, binsy, miny, maxy);
			h->Fill(valuex, valuey);
			table->Add(h);
		}
	}
	
	/*1D histogram fill wrapper*/
	void SFPPlotter::MyFill(THashTable* table, const std::string& name, int binsx, double minx, double maxx, double valuex)
	{
		TH1F *histo = (TH1F*) table->FindObject(name.c_str());
		if(histo != nullptr)
			histo->Fill(valuex);
		else 
		{
			TH1F *h = new TH1F(name.c_str(), name.c_str(), binsx, minx, maxx);
			h->Fill(valuex);
			table->Add(h);
		}
	}
	
	/*Makes histograms where only rejection is unset data*/
	void SFPPlotter::MakeUncutHistograms(const ProcessedEvent& ev, THashTable* table)
	{



		// if(ev.x1 != -1e6 && ev.x2 == -1e6){

		// MyFill(table,"RelDelayFrontLeftTime_nox2_rel_to_frontanode_NoCut",8000,-4000,4000,ev.delayFrontLeftTime-ev.anodeFrontTime);
		// MyFill(table,"RelDelayFrontRightTime_nox2_rel_to_frontanode_NoCut",8000,-4000,4000,ev.delayFrontRightTime-ev.anodeFrontTime);
		// MyFill(table,"RelDelayBackLeftTime_nox2_rel_to_frontanode_NoCut",8000,-4000,4000,ev.delayBackLeftTime-ev.anodeFrontTime);
		// MyFill(table,"RelDelayBackRightTime_nox2_rel_to_frontanode_NoCut",8000,-4000,4000,ev.delayBackRightTime-ev.anodeFrontTime);

		// MyFill(table,"RelDelayFrontLeftTime_nox2_rel_to_backanode_NoCut",8000,-4000,4000,ev.delayFrontLeftTime-ev.anodeBackTime);
		// MyFill(table,"RelDelayFrontRightTime_nox2_rel_to_backanode_NoCut",8000,-4000,4000,ev.delayFrontRightTime-ev.anodeBackTime);
		// MyFill(table,"RelDelayBackLeftTime_nox2_rel_to_backanode_NoCut",8000,-4000,4000,ev.delayBackLeftTime-ev.anodeBackTime);
		// MyFill(table,"RelDelayBackRightTime_nox2_rel_to_backanode_NoCut",8000,-4000,4000,ev.delayBackRightTime-ev.anodeBackTime);

		// }

		// if(ev.x2 != -1e6 && ev.x1 == -1e6){

		// MyFill(table,"RelDelayFrontLeftTime_nox1_rel_to_frontanode_NoCut",8000,-4000,4000,ev.delayFrontLeftTime-ev.anodeFrontTime);
		// MyFill(table,"RelDelayFrontRightTime_nox1_rel_to_frontanode_NoCut",8000,-4000,4000,ev.delayFrontRightTime-ev.anodeFrontTime);
		// MyFill(table,"RelDelayBackLeftTime_nox1_rel_to_frontanode_NoCut",8000,-4000,4000,ev.delayBackLeftTime-ev.anodeFrontTime);
		// MyFill(table,"RelDelayBackRightTime_nox1_rel_to_frontanode_NoCut",8000,-4000,4000,ev.delayBackRightTime-ev.anodeFrontTime);

		// MyFill(table,"RelDelayFrontLeftTime_nox1_rel_to_backanode_NoCut",8000,-4000,4000,ev.delayFrontLeftTime-ev.anodeBackTime);
		// MyFill(table,"RelDelayFrontRightTime_nox1_rel_to_backanode_NoCut",8000,-4000,4000,ev.delayFrontRightTime-ev.anodeBackTime);
		// MyFill(table,"RelDelayBackLeftTime_nox1_rel_to_backanode_NoCut",8000,-4000,4000,ev.delayBackLeftTime-ev.anodeBackTime);
		// MyFill(table,"RelDelayBackRightTime_nox1_rel_to_backanode_NoCut",8000,-4000,4000,ev.delayBackRightTime-ev.anodeBackTime);


		// }


		if(ev.x1 != -1e6 && ev.x2 != -1e6){
		MyFill(table,"x1NoCuts_bothplanes",600,-300,300,ev.x1);
		MyFill(table,"x2NoCuts_bothplanes",600,-300,300,ev.x2);
		MyFill(table,"xavgNoCuts_bothplanes",600,-300,300,ev.xavg);
		MyFill(table,"xavgNoCuts_theta_bothplanes",600,-300,300,ev.xavg,100,0,TMath::Pi()/2.,ev.theta);
		}
		
		MyFill(table,"x1_delayBackRightE_NoCuts",600,-300,300,ev.x1,512,0,4096,ev.delayBackRightE);
		MyFill(table,"x2_delayBackRightE_NoCuts",600,-300,300,ev.x2,512,0,4096,ev.delayBackRightE);
		MyFill(table,"x1_delayBackLeftE_NoCuts",600,-300,300,ev.x1,512,0,4096,ev.delayBackLeftE);
		MyFill(table,"x2_delayBackLeftE_NoCuts",600,-300,300,ev.x2,512,0,4096,ev.delayBackLeftE);
		MyFill(table,"xavg_delayBackRightE_NoCuts",600,-300,300,ev.xavg,512,0,4096,ev.delayBackRightE);
		MyFill(table,"xavg_delayBackLeftE_NoCuts",600,-300,300,ev.xavg,512,0,4096,ev.delayBackLeftE);
		MyFill(table,"x1_x2_NoCuts",600,-300,300,ev.x1,600,-300,300,ev.x2);
	
		Double_t delayBackAvgE = (ev.delayBackRightE+ev.delayBackLeftE)/2.0;
		MyFill(table,"x1_delayBackAvgE_NoCuts",600,-300,300,ev.x1,512,0,4096,delayBackAvgE);
		MyFill(table,"x2_delayBackAvgE_NoCuts",600,-300,300,ev.x2,512,0,4096,delayBackAvgE);
		MyFill(table,"xavg_delayBackAvgE_NoCuts",600,-300,300,ev.xavg,512,0,4096,delayBackAvgE);
		Double_t delayFrontAvgE = (ev.delayFrontRightE+ev.delayFrontLeftE)/2.0;
		MyFill(table,"x1_delayFrontAvgE_NoCuts",600,-300,300,ev.x1,512,0,4096,delayFrontAvgE);
		MyFill(table,"x2_delayFrontAvgE_NoCuts",600,-300,300,ev.x2,512,0,4096,delayFrontAvgE);
		MyFill(table,"xavg_delayFrontAvgE_NoCuts",600,-300,300,ev.xavg,512,0,4096,delayFrontAvgE);
	
		MyFill(table,"scintLeft_anodeBack_NoCuts",512,0,4096,ev.scintLeft,512,0,4096,ev.anodeBack);
		MyFill(table,"scintLeft_anodeFront_NoCuts",512,0,4096,ev.scintLeft,512,0,4096,ev.anodeFront);
		MyFill(table,"scintLeft_cathode_NoCuts",512,0,4096,ev.scintLeft,512,0,4096,ev.cathode);

		MyFill(table,"scintRight_anodeBack_NoCuts",512,0,4096,ev.scintRight,512,0,4096,ev.anodeBack);
		MyFill(table,"scintRight_anodeFront_NoCuts",512,0,4096,ev.scintRight,512,0,4096,ev.anodeFront);
		MyFill(table,"scintRight_cathode_NoCuts",512,0,4096,ev.scintRight,512,0,4096,ev.cathode);
	
		MyFill(table,"x1_scintLeft_NoCuts",600,-300,300,ev.x1,512,0,4096,ev.scintLeft);
		MyFill(table,"x2_scintLeft_NoCuts",600,-300,300,ev.x2,512,0,4096,ev.scintLeft);
		MyFill(table,"xavg_scintLeft_NoCuts",600,-300,300,ev.xavg,512,0,4096,ev.scintLeft);
		MyFill(table,"xavg_scintRight_NoCuts",600,-300,300,ev.xavg,512,0,4096,ev.scintRight);
	
		MyFill(table,"x1_anodeBack_NoCuts",600,-300,300,ev.x1,512,0,4096,ev.anodeBack);
		MyFill(table,"x2_anodeBack_NoCuts",600,-300,300,ev.x2,512,0,4096,ev.anodeBack);
		MyFill(table,"xavg_anodeBack_NoCuts",600,-300,300,ev.xavg,512,0,4096,ev.anodeBack);
	
		MyFill(table,"x1_anodeFront_NoCuts",600,-300,300,ev.x1,512,0,4096,ev.anodeFront);
		MyFill(table,"x2_anodeFront_NoCuts",600,-300,300,ev.x2,512,0,4096,ev.anodeFront);
		MyFill(table,"xavg_anodeFront_NoCuts",600,-300,300,ev.xavg,512,0,4096,ev.anodeFront);
	
		MyFill(table,"x1_cathode_NoCuts",600,-300,300,ev.x1,512,0,4096,ev.cathode);
		MyFill(table,"x2_cathode_NoCuts",600,-300,300,ev.x2,512,0,4096,ev.cathode);
		MyFill(table,"xavg_cathode_NoCuts",600,-300,300,ev.xavg,512,0,4096,ev.cathode);

		MyFill(table,"x1_delayFrontRightE_noCuts",600,-300,300,ev.x1,512,0,4096,ev.delayFrontRightE);
		MyFill(table,"x2_delayFrontRightE_noCuts",600,-300,300,ev.x2,512,0,4096,ev.delayFrontRightE);
		MyFill(table,"x1_delayFrontLeftE_noCuts",600,-300,300,ev.x1,512,0,4096,ev.delayFrontLeftE);
		MyFill(table,"x2_delayFrontLeftE_noCuts",600,-300,300,ev.x2,512,0,4096,ev.delayFrontLeftE);
		MyFill(table,"xavg_delayFrontRightE_noCuts",600,-300,300,ev.xavg,512,0,4096,ev.delayFrontRightE);
		MyFill(table,"xavg_delayFrontLeftE_noCuts",600,-300,300,ev.xavg,512,0,4096,ev.delayFrontLeftE);
	
		

		/****Timing relative to back anode****/
		if(ev.anodeBackTime != -1 && ev.scintLeftTime != -1)
		{
			Double_t anodeRelFT = ev.anodeFrontTime - ev.anodeBackTime;
			Double_t delayRelFT = ev.delayFrontMaxTime - ev.anodeBackTime;
			Double_t delayRelBT = ev.delayBackMaxTime - ev.anodeBackTime;
			Double_t anodeRelBT = ev.anodeBackTime - ev.scintLeftTime;
			Double_t delayRelFT_toScint = ev.delayFrontMaxTime - ev.scintLeftTime;
			Double_t delayRelBT_toScint = ev.delayBackMaxTime - ev.scintLeftTime;
			Double_t delayFL_toScint = ev.delayFrontLeftTime - ev.scintLeftTime;
			Double_t delayFR_toScint = ev.delayFrontRightTime - ev.scintLeftTime;
			Double_t delayBL_toScint = ev.delayBackLeftTime - ev.scintLeftTime;
			Double_t delayBR_toScint = ev.delayBackRightTime - ev.scintLeftTime;
			MyFill(table,"anodeRelFrontTime_NoCuts",1000,-3000,3500, anodeRelFT);
			MyFill(table,"delayRelFrontTime_NoCuts",1000,-3000,-3500,delayRelFT);
			MyFill(table,"delayRelBackTime_NoCuts",1000,-3000,-3500,delayRelBT);
			MyFill(table,"delayFL_RelScint_NoCuts",3000,-3000,3000,delayFL_toScint);
			MyFill(table,"delayFR_RelScint_NoCuts",3000,-3000,3000,delayFR_toScint);
			MyFill(table,"delayBL_RelScint_NoCuts",3000,-3000,3000,delayBL_toScint);
			MyFill(table,"delayBR_RelScint_NoCuts",3000,-3000,3000,delayBR_toScint);

			
			
			for(int i=0; i<5; i++) {

				//Cebra Relative Time to Left Scint Plots
				Double_t cebraRelT_toScint = ev.cebraTime[i] - ev.scintLeftTime;
				MyFill(table,fmt::format("cebra_RelTime_toScint_{}_noCuts",i),12000,-6000,6000,cebraRelT_toScint);
				// MyFill(table,"cebra_RelTime_toScint_noCuts",8000,-4000,4000,cebraRelT_toScint);
			}

			MyFill(table,"anodeBackRelTime_toScint",1000,-3000,3500,anodeRelBT);
			MyFill(table,"delayRelBackTime_toScint",1000,-3000,3500,delayRelBT_toScint);
			MyFill(table,"delayRelFrontTime_toScint",1000,-3000,3500,delayRelFT_toScint);
		} else {
		MyFill(table,"noscinttime_counter_NoCuts",2,0,1,1); 
		}


		//plots with no cuts and no scint stuff
		for(int i=0; i<5; i++) {
			if(ev.cebraE[i] != -1){

				MyFill(table,fmt::format("cebra_E_{}_noCuts",i),1024,0,4096,ev.cebraE[i]);
				MyFill(table,fmt::format("cebra_E_{}_cebraTime_noCuts",i),7200, 0, 7200, ev.cebraTime[i] / 1e9, 1024,0,4096,ev.cebraE[i]);

				//Cebra ADC Channel shift (to make all the detectors line up with each other) with the corresponding plots
				//good for run 82 - 123
				// double cebra_E_ADCShift[5] = {	1.15672328675213*ev.cebraE[0]	-16.6919499054403,
				// 								1.3021940822188	*ev.cebraE[1]	-17.935158566721,
				// 								1.14400591545883*ev.cebraE[2]	-2.44528388259982,
				// 								1.13872748785169*ev.cebraE[3]	-5.59919193459234,
				// 								1.0				*ev.cebraE[4]	-0};

				//run 162 -183
				// double cebra_E_ADCShift[5] = {1.14759314191149	*ev.cebraE[0]-33.6481331086578,
				// 						1.13138046963966	*ev.cebraE[1]-38.3795474557953,
				// 						1.10901267613132	*ev.cebraE[2]-4.52471201077913,
				// 						1.10283776422464	*ev.cebraE[3]-14.7328089971076,
				// 						1	*ev.cebraE[4]+0};


				//run 184 -    (49Ti)
				// double cebra_E_ADCShift[5] = {1.13839222519026	*ev.cebraE[0]-19.0471201323429,
				// 							1.12273313860131	*ev.cebraE[1]-25.5137729880996,
				// 							1.08900756001104	*ev.cebraE[2]+3.6871117152541,
				// 							1.08140038495971	*ev.cebraE[3]-0.744386649146463,
				// 							1					*ev.cebraE[4]+0};

				// MyFill(table,fmt::format("cebra_E_{}_ADCShift_noCuts",i),1024,0,4096,cebra_E_ADCShift[i]);
				//MyFill(table,"cebra_E_ADCShift_noCuts",1024,0,4096,cebra_E_ADCShift[i]);

				
				// if(ev.x1 != -1e6 && ev.x2 != -1e6){
				// MyFill(table,fmt::format("x1_cebraE_{}_noCuts",i),600,-300,300,ev.x1,1024,0,1024,ev.cebraE[i]);
				// MyFill(table,"x1_cebraE_noCuts",600,-300,300,ev.x1,1024,0,1024,ev.cebraE[i]);
				// }
				
			}
		}	

		if(ev.x1 != -1e6 && ev.x2 == -1e6)
			MyFill(table,"x1NoCuts_only1plane",600,-300,300,ev.x1);
		else if(ev.x2 != -1e6 && ev.x1 == -1e6)
			MyFill(table,"x2NoCuts_only1plane",600,-300,300,ev.x2);
		else if(ev.x1 == -1e6 && ev.x2 == -1e6)
			MyFill(table,"nopos_counter",2,0,1,1);
	}
	
	/*Makes histograms with cuts & gates implemented*/
	void SFPPlotter::MakeCutHistograms(const ProcessedEvent& ev, THashTable* table) 
	{
		if(!cutter.IsInside(&ev)) 
			return;
	

		if(ev.x1 != -1e6 && ev.x2 != -1e6){
		MyFill(table,"x1_bothplanes_Cut",600,-300,300,ev.x1);
		MyFill(table,"x2_bothplanes_Cut",600,-300,300,ev.x2);

		MyFill(table,"RelDelayFrontLeftTime_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayFrontLeftTime-ev.anodeFrontTime);
		MyFill(table,"RelDelayFrontRightTime_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayFrontRightTime-ev.anodeFrontTime);
		// MyFill(table,"RelDelayBackLeftTime_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayBackLeftTime-ev.anodeFrontTime);
		// MyFill(table,"RelDelayBackRightTime_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayBackRightTime-ev.anodeFrontTime);

		// MyFill(table,"RelDelayFrontLeftTime_rel_to_backanode_Cut",8000,-4000,4000,ev.delayFrontLeftTime-ev.anodeBackTime);
		// MyFill(table,"RelDelayFrontRightTime_rel_to_backanode_Cut",8000,-4000,4000,ev.delayFrontRightTime-ev.anodeBackTime);
		MyFill(table,"RelDelayBackLeftTime_rel_to_backanode_Cut",8000,-4000,4000,ev.delayBackLeftTime-ev.anodeBackTime);
		MyFill(table,"RelDelayBackRightTime_rel_to_backanode_Cut",8000,-4000,4000,ev.delayBackRightTime-ev.anodeBackTime);



		}

		MyFill(table,"xavg_bothplanes_Cut",600,-300,300,ev.xavg);
		MyFill(table,"x1_x2_Cut",600,-300,300,ev.x1, 600,-300,300,ev.x2);
		MyFill(table,"xavg_theta_Cut_bothplanes",600,-300,300,ev.xavg,100,0,TMath::Pi()/2.,ev.theta);

		if(ev.x1 != -1e6 && ev.x2 == -1e6){
		MyFill(table, "x1_only1plane_Cut", 600, -300, 300, ev.x1);

		MyFill(table,"RelDelayFrontLeftTime_nox2_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayFrontLeftTime-ev.anodeFrontTime);
		MyFill(table,"RelDelayFrontRightTime_nox2_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayFrontRightTime-ev.anodeFrontTime);
		MyFill(table,"RelDelayBackLeftTime_nox2_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayBackLeftTime-ev.anodeFrontTime);
		MyFill(table,"RelDelayBackRightTime_nox2_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayBackRightTime-ev.anodeFrontTime);

		MyFill(table,"RelDelayFrontLeftTime_nox2_rel_to_backanode_Cut",8000,-4000,4000,ev.delayFrontLeftTime-ev.anodeBackTime);
		MyFill(table,"RelDelayFrontRightTime_nox2_rel_to_backanode_Cut",8000,-4000,4000,ev.delayFrontRightTime-ev.anodeBackTime);
		MyFill(table,"RelDelayBackLeftTime_nox2_rel_to_backanode_Cut",8000,-4000,4000,ev.delayBackLeftTime-ev.anodeBackTime);
		MyFill(table,"RelDelayBackRightTime_nox2_rel_to_backanode_Cut",8000,-4000,4000,ev.delayBackRightTime-ev.anodeBackTime);

		}

		if(ev.x2 != -1e6 && ev.x1 == -1e6){
		MyFill(table, "x2_only1plane_Cut", 600, -300, 300, ev.x2);

		MyFill(table,"RelDelayFrontLeftTime_nox1_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayFrontLeftTime-ev.anodeFrontTime);
		MyFill(table,"RelDelayFrontRightTime_nox1_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayFrontRightTime-ev.anodeFrontTime);
		MyFill(table,"RelDelayBackLeftTime_nox1_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayBackLeftTime-ev.anodeFrontTime);
		MyFill(table,"RelDelayBackRightTime_nox1_rel_to_frontanode_Cut",8000,-4000,4000,ev.delayBackRightTime-ev.anodeFrontTime);

		MyFill(table,"RelDelayFrontLeftTime_nox1_rel_to_backanode_Cut",8000,-4000,4000,ev.delayFrontLeftTime-ev.anodeBackTime);
		MyFill(table,"RelDelayFrontRightTime_nox1_rel_to_backanode_Cut",8000,-4000,4000,ev.delayFrontRightTime-ev.anodeBackTime);
		MyFill(table,"RelDelayBackLeftTime_nox1_rel_to_backanode_Cut",8000,-4000,4000,ev.delayBackLeftTime-ev.anodeBackTime);
		MyFill(table,"RelDelayBackRightTime_nox1_rel_to_backanode_Cut",8000,-4000,4000,ev.delayBackRightTime-ev.anodeBackTime);

		}
		
		MyFill(table,"x1_delayBackRightE_Cut",600,-300,300,ev.x1,512,0,4096,ev.delayBackRightE);
		MyFill(table,"x2_delayBackRightE_Cut",600,-300,300,ev.x2,512,0,4096,ev.delayBackRightE);
		MyFill(table,"x1_delayBackLeftE_Cut",600,-300,300,ev.x1,512,0,4096,ev.delayBackLeftE);
		MyFill(table,"x2_delayBackLeftE_Cut",600,-300,300,ev.x2,512,0,4096,ev.delayBackLeftE);
		MyFill(table,"xavg_delayBackRightE_Cut",600,-300,300,ev.xavg,512,0,4096,ev.delayBackRightE);
		MyFill(table,"xavg_delayBackLeftE_Cut",600,-300,300,ev.xavg,512,0,4096,ev.delayBackLeftE);

		MyFill(table,"x1_delayFrontRightE_Cut",600,-300,300,ev.x1,512,0,4096,ev.delayFrontRightE);
		MyFill(table,"x2_delayFrontRightE_Cut",600,-300,300,ev.x2,512,0,4096,ev.delayFrontRightE);
		MyFill(table,"x1_delayFrontLeftE_Cut",600,-300,300,ev.x1,512,0,4096,ev.delayFrontLeftE);
		MyFill(table,"x2_delayFrontLeftE_Cut",600,-300,300,ev.x2,512,0,4096,ev.delayFrontLeftE);
		MyFill(table,"xavg_delayFrontRightE_Cut",600,-300,300,ev.xavg,512,0,4096,ev.delayFrontRightE);
		MyFill(table,"xavg_delayFrontLeftE_Cut",600,-300,300,ev.xavg,512,0,4096,ev.delayFrontLeftE);
	
		Double_t delayBackAvgE = (ev.delayBackRightE+ev.delayBackLeftE)/2.0;
		MyFill(table,"x1_delayBackAvgE_Cut",600,-300,300,ev.x1,512,0,4096,delayBackAvgE);
		MyFill(table,"x2_delayBackAvgE_Cut",600,-300,300,ev.x2,512,0,4096,delayBackAvgE);
		MyFill(table,"xavg_delayBackAvgE_Cut",600,-300,300,ev.xavg,512,0,4096,delayBackAvgE);
		Double_t delayFrontAvgE = (ev.delayFrontRightE+ev.delayFrontLeftE)/2.0;
		MyFill(table,"x1_delayFrontAvgE_Cut",600,-300,300,ev.x1,512,0,4096,delayFrontAvgE);
		MyFill(table,"x2_delayFrontAvgE_Cut",600,-300,300,ev.x2,512,0,4096,delayFrontAvgE);
		MyFill(table,"xavg_delayFrontAvgE_Cut",600,-300,300,ev.xavg,512,0,4096,delayFrontAvgE);
	
		MyFill(table,"scintLeft_anodeBack_Cut",512,0,4096,ev.scintLeft,512,0,4096,ev.anodeBack);
		MyFill(table,"scintLeft_anodeFront_Cut",512,0,4096,ev.scintLeft,512,0,4096,ev.anodeFront);
		MyFill(table,"scintLeft_cathode_Cut",512,0,4096,ev.scintLeft,512,0,4096,ev.cathode);

		MyFill(table,"scintRight_anodeBack_Cut",512,0,4096,ev.scintRight,512,0,4096,ev.anodeBack);
		MyFill(table,"scintRight_anodeFront_Cut",512,0,4096,ev.scintRight,512,0,4096,ev.anodeFront);
		MyFill(table,"scintRight_cathode_Cut",512,0,4096,ev.scintRight,512,0,4096,ev.cathode);
	
		MyFill(table,"x1_scintLeft_Cut",600,-300,300,ev.x1,512,0,4096,ev.scintLeft);
		MyFill(table,"x2_scintLeft_Cut",600,-300,300,ev.x2,512,0,4096,ev.scintLeft);
		MyFill(table,"xavg_scintLeft_Cut",600,-300,300,ev.xavg,512,0,4096,ev.scintLeft);
		MyFill(table,"xavg_scintRight_Cut",600,-300,300,ev.xavg,512,0,4096,ev.scintRight);
	
		MyFill(table,"x1_anodeBack_Cut",600,-300,300,ev.x1,512,0,4096,ev.anodeBack);
		MyFill(table,"x2_anodeBack_Cut",600,-300,300,ev.x2,512,0,4096,ev.anodeBack);
		MyFill(table,"xavg_anodeBack_Cut",600,-300,300,ev.xavg,512,0,4096,ev.anodeBack);
		
		MyFill(table,"x1_anodeFront_Cut",600,-300,300,ev.x1,512,0,4096,ev.anodeFront);
		MyFill(table,"x2_anodeFront_Cut",600,-300,300,ev.x2,512,0,4096,ev.anodeFront);
		MyFill(table,"xavg_anodeFront_Cut",600,-300,300,ev.xavg,512,0,4096,ev.anodeFront);
		
		MyFill(table,"x1_cathode_Cut",600,-300,300,ev.x1,512,0,4096,ev.cathode);
		MyFill(table,"x2_cathode_Cut",600,-300,300,ev.x2,512,0,4096,ev.cathode);
		MyFill(table,"xavg_cathode_Cut",600,-300,300,ev.xavg,512,0,4096,ev.cathode);

		double cebra_E_ADCShift[5] = {	1.0			*ev.cebraE[0]+ 0.0,
											1.10926476470248* ev.cebraE[1] +	1.08683520943367,
											1.10769015886069* ev.cebraE[2] +	7.96018591651148,
											0.976988483900976*ev.cebraE[3] +	6.09760569824573,
											0.947475209624302*ev.cebraE[4] +	8.03998545288471
											};

											


	
		/****Timing relative to back anode****/
		if(ev.anodeBackTime != -1 && ev.scintLeftTime != -1) 
		{
			Double_t anodeRelFT = ev.anodeFrontTime - ev.anodeBackTime;
			Double_t anodeRelBT = ev.anodeBackTime - ev.anodeBackTime;
			Double_t anodeRelFT_toScint = ev.anodeFrontTime-ev.scintLeftTime;
			Double_t delayFR_toScint = ev.delayFrontRightTime - ev.scintLeftTime;
			Double_t delayFL_toScint = ev.delayFrontLeftTime - ev.scintLeftTime;
			Double_t delayBL_toScint = ev.delayBackLeftTime - ev.scintLeftTime;
			Double_t delayBR_toScint = ev.delayBackRightTime - ev.scintLeftTime;
			MyFill(table,"anodeRelBackTime_Cut",1000,-3000,3500, anodeRelBT);
			MyFill(table,"anodeRelFrontTime_Cut",1000,-3000,3500, anodeRelFT);
			MyFill(table,"anodeRelTime_toScint_Cut",1000,-3000,3500,anodeRelFT_toScint);
			MyFill(table,"delayFL_RelScint_Cuts",3000,-3000,3000,delayFL_toScint);
			MyFill(table,"delayFR_RelScint_Cuts",3000,-3000,3000,delayFR_toScint);
			MyFill(table,"delayBL_RelScint_Cuts",3000,-3000,3000,delayBL_toScint);
			MyFill(table,"delayBR_RelScint_Cuts",3000,-3000,3000,delayBR_toScint);
			MyFill(table, "xavg_timeDifferenceScints", 600, -300, 300, ev.xavg, 12800, -3200,3200, ev.scintRightTime - ev.scintLeftTime);

	
			for(int i=0; i<5; i++) {

				//CeBrA Relative Time to Left Scint Cut Plots
				Double_t cebraRelT_toScint = ev.cebraTime[i] - ev.scintLeftTime;
				//CeBrA relative time to right Scint
				Double_t cebraRelT_toRightScint = ev.cebraTime[i] - ev.scintRightTime;

				MyFill(table,fmt::format("cebra_RelTime_toScint_{}_Cut",i),6400,-3200,3200,cebraRelT_toScint);
				MyFill(table,fmt::format("cebra_RelTime_toScint_{}_theta_Cut",i),6400,-3200,3200,cebraRelT_toScint,100,0,TMath::Pi()/2.,ev.theta);

				//adjust accordingly using the "cebra_RelTime_toScint_I" plots

				double cebra_RelTime_toScint_Shift[5] = {	1162,  
															1160,
															1159,
															1159,
															1129};

// time shifts for 8.3 kG setting 52Cr(d,pg)
/*
				double cebra_RelTime_toScint_Shift[5] = {	1155.542,  
															1153.885,
															1153.527,
															1152.917,
															1123.127};

*/

				//CeBrA time cut ... make sure the shifts are good
				// double cebra_RelTime_Width = 6.0;
				double cebra_RelTime_Width = 2.4;

				double cebraRelT_toScint_Shifted = cebraRelT_toScint + cebra_RelTime_toScint_Shift[i];
				MyFill(table, fmt::format("xavg_vs_timeDiff_cebra{}_scintRight", i), 600, -300, 300, ev.xavg, 6400, -3200, 3200, cebraRelT_toRightScint);
				MyFill(table, fmt::format("xavg_vs_timeDiff_cebra{}_scintLeft", i), 600, -300, 300, ev.xavg, 6400, -3200, 3200, cebraRelT_toScint);

				if(cebraRelT_toScint_Shifted > -cebra_RelTime_Width && cebraRelT_toScint_Shifted < cebra_RelTime_Width){
					
					MyFill(table,"xavg_TimeCutShift_Cut",600,-300,300,ev.xavg);
					MyFill(table,fmt::format("cebra_E_{}_TimeCutShift_Cut",i),512,0,4096,ev.cebraE[i]);
					MyFill(table,fmt::format("xavg_cebraE_{}_TimeCutShift_Cut",i),600,-300,300,ev.xavg,512,0,4096,ev.cebraE[i]);
					MyFill(table,fmt::format("x1_cebraE_{}_TimeCutShift_Cut",i),600,-300,300,ev.x1,512,0,4096,ev.cebraE[i]);
					MyFill(table,fmt::format("cebra_RelTime_toScint_{}_TimeCutShift_Cut",i),400,-100,100,cebraRelT_toScint_Shifted);

					//All the detectors summed using the ADC Shift values
					MyFill(table,"AA_xavg_cebraE_Sum_TimeCutShift_Cut",600,-300,300,ev.xavg,512,0,4096,cebra_E_ADCShift[i]);
					MyFill(table,"AA_x1_cebraE_Sum_TimeCutShift_Cut",600,-300,300,ev.x1,512,0,4096,cebra_E_ADCShift[i]);

					//Energy Calibrated to the GS band 
					// double cebra_E_EnergyCalibrated = 1.77817107*cebra_E_ADCShift[i]+4.74455886;   // run 286 -   61Ni @8.7kG


					//Shifting x1 so run_82_123 x1_bothplanes_cut lines up with run_162_183
					// double x1_shifted = 1.00248436*ev.x1 + 2.46724718; 

					//run 184-232 energy calibrated
					//double x1_shifted = -21.1595478758973*ev.x1+	2112.63002693692;

					//run 245-283 energy calibrated
					//double xavg_shifted = -17.1003806*ev.xavg +		6700.1328827;

					//run 291-351 energy calibrated
					double x1_shifted = -20.6867155520197*ev.x1+	2377.1950716545;


					// MyFill(table,"AA_xavg_cebraE_Sum_EnergyCalibrated_TimeCutShift_Cut",600,-300,300,ev.xavg,2048, 0, 8192,cebra_E_EnergyCalibrated);
					// MyFill(table,"AA_x1_cebraE_Sum_EnergyCalibrated_TimeCutShift_Cut",600,-300,300,ev.x1,2048, 0, 8192,cebra_E_EnergyCalibrated);

					// //Use x1 calibration for 49Ti @ 8.8kG setting, x1 was better here, xavg is better for 49Ti @7.9kG and the 61Ni stuff
					// MyFill(table,"AA_ENERGYCAL_x1_cebraE_TimeCutShift_Cut",512,0,8192,x1_shifted,2048, 0, 8192,cebra_E_EnergyCalibrated);
					// MyFill(table,"x1_ENERGYCAL_TimeCutShift_Cut",512,0,8192,x1_shifted);

					//MyFill(table,"AA_ENERGYCAL_xavg_cebraE_TimeCutShift_Cut",4096, 0, 16384,xavg_shifted,2048,0,8192,cebra_E_EnergyCalibrated);
					//MyFill(table, "xavg_ENERGYCAL_TimeCutShift_Cut", 4096, 0, 16384,xavg_shifted);


					// Conditional statement that plots certain decay bands of interest
					
					// if ( (cebra_E_EnergyCalibrated <= (xavg_shifted-2675) + 40)  && (cebra_E_EnergyCalibrated >= (xavg_shifted-2675) - 40) ){
					// 	MyFill(table, "AA_testbandplot", 4096, 0, 16384, xavg_shifted, 2048, 0, 8192,cebra_E_EnergyCalibrated );
					// 	MyFill(table, "AA_xavg_with_gamma_condition", 4096, 0, 16384, xavg_shifted);
					// }

					// if ( (cebra_E_EnergyCalibrated <= (x1_shifted) + 60)  && (cebra_E_EnergyCalibrated >= (x1_shifted) - 60) ){
					// 	MyFill(table, "AA_GS_band", 4096, 0, 16384, x1_shifted, 2048, 0, 8192,cebra_E_EnergyCalibrated );
					// 	MyFill(table, "AA_x1_with_gamma_condition_GS", 256, 0, 8192, x1_shifted);
					// }

					// if ( (cebra_E_EnergyCalibrated <= (x1_shifted - 1172) + 60)  && (cebra_E_EnergyCalibrated >= (x1_shifted - 1172) - 60) ){
					// 	MyFill(table, "AA_first_band", 4096, 0, 16384, x1_shifted, 2048, 0, 8192,cebra_E_EnergyCalibrated );
					// 	MyFill(table, "AA_x1_with_gamma_condition_first", 256, 0, 8192, x1_shifted);
					// }

					// if ( (cebra_E_EnergyCalibrated <= (x1_shifted - 2336) + 60)  && (cebra_E_EnergyCalibrated >= (x1_shifted - 2336) - 60) ){
					// 	MyFill(table, "AA_second_band", 4096, 0, 16384, x1_shifted, 2048, 0, 8192,cebra_E_EnergyCalibrated );
					// 	MyFill(table, "AA_x1_with_gamma_condition_second", 256, 0, 8192, x1_shifted);
					// }
				


					MyFill(table, "AA_cebraE_Sum_ADCShift_TimeCutShift_Cut", 1024, 0, 4096, cebra_E_ADCShift[i]);
					// MyFill(table, "AA_cebraE_Sum_EnergyCal_TimeCutShift_Cut", 2048, 0, 8192, cebra_E_EnergyCalibrated);



					//Zony plots (small CeBr3 detectors, small zebras, like a small horses or a pony)
					if(i != 4){
							// MyFill(table,"cebraE_zony_cebraE4_TimeCut_Cut",512,0,4096,cebra_E_ADCShift[i],512,0,4096,cebra_E_ADCShift[4]);
							MyFill(table,"xavg_cebraE_zony_TimeCutShift_Cut",600,-300,300,ev.xavg,512,0,4096,cebra_E_ADCShift[i]);
							MyFill(table,"x1_cebraE_zony_TimeCutShift_Cut",600,-300,300,ev.x1,512,0,4096,cebra_E_ADCShift[i]);
							// MyFill(table,"AA_xavg_cebraE_zony_EnergyCalibrated_TimeCutShift_Cut",600,-300,300,ev.xavg,2048, 0, 8192,cebra_E_EnergyCalibrated);
							// MyFill(table,"AA_x1_cebraE_zony_EnergyCalibrated_TimeCutShift_Cut",600,-300,300,ev.x1,2048, 0, 8192,cebra_E_EnergyCalibrated);
							
							// MyFill(table, "AA_zony_Sum_EnergyCal_TimeCutShift_Cut", 2048, 0, 8192, cebra_E_EnergyCalibrated);

							//MyFill(table,"AA_ENERGYCAL_ZONY_x1_cebraE_TimeCutShift_Cut",2048,0,8192,x1_shifted,2048, 0, 8192,cebra_E_EnergyCalibrated);
							//MyFill(table,"AA_ENERGYCAL_ZONY_xavg_cebraE_TimeCutShift_Cut",2048,0,8192,xavg_shifted,2048, 0, 8192,cebra_E_EnergyCalibrated);

					}	

				}
			
			}
			
		}

		
			//run 184-232 energy calibrated
			// double x1_shifted = -21.1595478758973*ev.x1+	2112.63002693692;
			// MyFill(table,"x1_ENERGYCAL_Cut",2048,0,8192,x1_shifted);

			//run 245-285 energy calibrated
			//double xavg_shifted = -17.1003806*ev.xavg +		6700.1328827;
			//MyFill(table,"xavg_ENERGYCAL_Cut",2048,0,8192,xavg_shifted);



			//	plots that do not contain scint stuff
			for(int i=0; i<5; i++) {
       			if(ev.cebraE[i] != -1 && ev.x1 != -1e6 && ev.x2 != -1e6){
	
					MyFill(table,fmt::format("cebra_E_{}_Cut",i),1024,0,4096,ev.cebraE[i]);
					MyFill(table,fmt::format("cebra_E_{}_ADCShift_Cut",i),1024,0,4096,cebra_E_ADCShift[i]);
					MyFill(table,"cebra_E_ADCShift_Cut",1024,0,4096,cebra_E_ADCShift[i]);
					// MyFill(table,fmt::format("xavg_cebraE_{}_Cut",i),600,-300,300,ev.xavg,1024,0,4096,ev.cebraE[i]);
					// MyFill(table,"xavg_cebraE_Cut",600,-300,300,ev.xavg,1024,0,4096,ev.cebraE[i]);
					// MyFill(table,fmt::format("x1_cebraE_{}_Cut",i),600,-300,300,ev.x1,1024,0,4096,ev.cebraE[i]);
					// MyFill(table,"x1_cebraE_Cut",600,-300,300,ev.x1,1024,0,4096,ev.cebraE[i]);

					//CeBrA vs xavg without the time cut
					MyFill(table,"AA_xavg_cebraE_Sum_Cut",600,-300,300,ev.xavg,512,0,4096,cebra_E_ADCShift[i]);

				}
			}


		//plots for CeBrA that are relative to Detector 0
		// for(int i=1; i<5; i++) {
		// 	if(ev.cebraE[0]!=-1 && ev.cebraE[i]!=-1){
		// 		MyFill(table,fmt::format("cebraTime0_cebraTime{}_Cut",i),5000,-15000,15000,ev.cebraTime[0]-ev.cebraTime[i]);
		// 	}
		// }

		
	}
	
	/*Runs a list of files given from a RunCollector class*/
	void SFPPlotter::Run(const std::vector<std::string>& files, const std::string& output)
	{
		TFile *outfile = TFile::Open(output.c_str(), "RECREATE");
		TChain* chain = new TChain("SPSTree");
		for(unsigned int i=0; i<files.size(); i++)
			chain->Add(files[i].c_str()); 
		chain->SetBranchAddress("event", &event_address);
		THashTable* table = new THashTable();
	
		long blentries = chain->GetEntries();
		long count=0, flush_val=blentries*m_progressFraction, flush_count=0;
	
	
		for(long i=0; i<chain->GetEntries(); i++) 
		{
			count++;
			if(count == flush_val)
			{
				flush_count++;
				count=0;
				m_progressCallback(flush_count*flush_val, blentries);
			}
			chain->GetEntry(i);
			MakeUncutHistograms(*event_address, table);
			if(cutter.IsValid()) MakeCutHistograms(*event_address, table);
		}
		outfile->cd();
		table->Write();
		if(cutter.IsValid()) 
		{
			auto clist = cutter.GetCuts();
			for(unsigned int i=0; i<clist.size(); i++) 
			  clist[i]->Write();
		}
		delete table;
		outfile->Close();
		delete outfile;
	}

}
