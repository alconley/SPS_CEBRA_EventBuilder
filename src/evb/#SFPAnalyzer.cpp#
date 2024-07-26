/*SFPAnalyzer.cpp
 *Class designed to analyze coincidence events. Currently only implemented for focal plane
 *data. Additional changes for SABRE would include this file and the sructure ProcessedEvent
 *in DataStructs.h. Based on code written by S. Balak, K. Macon, and E. Good.
 *
 *Gordon M. Oct. 2019
 *
 *Refurbished and updated Jan 2020 by GWM. Now uses both focal plane and SABRE data
 *
 * Position calibrations swapped as of Aug. 2021 due to detector fixes -- GWM
 */
#include "EventBuilder.h"
#include "SFPAnalyzer.h"

// Testing the main branch push here!!
namespace EventBuilder {

    /*Constructor takes in kinematic parameters for generating focal plane weights*/
    SFPAnalyzer::SFPAnalyzer(int zt, int at, int zp, int ap, int ze, int ae, double ep,
                                double angle, double b)
    {
        zfp = Delta_Z(zt, at, zp, ap, ze, ae, ep, angle, b);
        event_address = new CoincEvent();
        rootObj = new THashTable();
        GetWeights();

        EVB_INFO("Calculated z shift of focal plane:",zfp);

    }
   
    SFPAnalyzer::~SFPAnalyzer()
    {
        rootObj->Clear();
        delete rootObj;
        delete event_address;
    }
   
    void SFPAnalyzer::Reset()
    {
        pevent = blank; //set output back to blank
    }
   
    /*Use functions from FP_kinematics to calculate weights for xavg
     *While this seems kind of funny, it is mathematically equivalent to making a line
     *from the two focal plane points and finding the intersection with
     *the kinematic focal plane
     */
    void SFPAnalyzer::GetWeights()
    {
        w1 = (Wire_Dist()/2.0-zfp)/Wire_Dist();
        w2 = 1.0-w1;
        EVB_INFO("Calculated X-Avg weights of w1={0} and w2={1}",w1,w2);
    }
   
    /*2D histogram fill wrapper for use with THashTable (faster)*/
    void SFPAnalyzer::MyFill(const std::string& name, int binsx, double minx, double maxx, double valuex,
                                int binsy, double miny, double maxy, double valuey)
    {
        TH2F *histo = (TH2F*) rootObj->FindObject(name.c_str());
        if(histo != nullptr)
            histo->Fill(valuex, valuey);
        else 
        {
            TH2F *h = new TH2F(name.c_str(), name.c_str(), binsx, minx, maxx, binsy, miny, maxy);
            h->Fill(valuex, valuey);
            rootObj->Add(h);
        }
    }
   
    /*1D histogram fill wrapper for use with THashTable (faster)*/
    void SFPAnalyzer::MyFill(const std::string& name, int binsx, double minx, double maxx, double valuex)
    {
        TH1F *histo = (TH1F*) rootObj->FindObject(name.c_str());
        if(histo != nullptr)
            histo->Fill(valuex);
        else 
        {
            TH1F *h = new TH1F(name.c_str(), name.c_str(), binsx, minx, maxx);
            h->Fill(valuex);
            rootObj->Add(h);
        }
    }
   
    void SFPAnalyzer::AnalyzeEvent(CoincEvent& event)
    {
        Reset();
        if(!event.focalPlane.anodeF.empty())
        {
            pevent.anodeFront = event.focalPlane.anodeF[0].Long;
            pevent.anodeFrontTime = event.focalPlane.anodeF[0].Time;
        }
        if(!event.focalPlane.anodeB.empty())
        {
            pevent.anodeBack = event.focalPlane.anodeB[0].Long;
            pevent.anodeBackTime = event.focalPlane.anodeB[0].Time;
        }
        if(!event.focalPlane.scintL.empty())
        {
            pevent.scintLeft = event.focalPlane.scintL[0].Long;
            pevent.scintLeftShort = event.focalPlane.scintL[0].Short;
            pevent.scintLeftTime = event.focalPlane.scintL[0].Time;
        }
        if(!event.focalPlane.scintR.empty())
        {
            pevent.scintRight = event.focalPlane.scintR[0].Long;
            pevent.scintRightShort = event.focalPlane.scintR[0].Short;
            pevent.scintRightTime = event.focalPlane.scintR[0].Time;
        }
        if(!event.focalPlane.cathode.empty())
        {
            pevent.cathode = event.focalPlane.cathode[0].Long;
            pevent.cathodeTime = event.focalPlane.cathode[0].Time;
        }
        if(!event.focalPlane.monitor.empty())
        {
            pevent.monitorE = event.focalPlane.monitor[0].Long;
            pevent.monitorShort = event.focalPlane.monitor[0].Short;
            pevent.monitorTime = event.focalPlane.monitor[0].Time;
        }
   
        /*Delay lines and all that*/
        if(!event.focalPlane.delayFR.empty())
        {
            pevent.delayFrontRightE = event.focalPlane.delayFR[0].Long;
            pevent.delayFrontRightTime = event.focalPlane.delayFR[0].Time;
            pevent.delayFrontRightShort = event.focalPlane.delayFR[0].Short;
        }
        if(!event.focalPlane.delayFL.empty())
        {
            pevent.delayFrontLeftE = event.focalPlane.delayFL[0].Long;
            pevent.delayFrontLeftTime = event.focalPlane.delayFL[0].Time;
            pevent.delayFrontLeftShort = event.focalPlane.delayFL[0].Short;
        }
        if(!event.focalPlane.delayBR.empty())
        {
            pevent.delayBackRightE = event.focalPlane.delayBR[0].Long;
            pevent.delayBackRightTime = event.focalPlane.delayBR[0].Time;
            pevent.delayBackRightShort = event.focalPlane.delayBR[0].Short;
        }
        if(!event.focalPlane.delayBL.empty())
        {
            pevent.delayBackLeftE = event.focalPlane.delayBL[0].Long;
            pevent.delayBackLeftTime = event.focalPlane.delayBL[0].Time;
            pevent.delayBackLeftShort = event.focalPlane.delayBL[0].Short;
        }  
        if(!event.focalPlane.delayFL.empty() && !event.focalPlane.delayFR.empty())
        {
            pevent.fp1_tdiff = (event.focalPlane.delayFL[0].Time-event.focalPlane.delayFR[0].Time)*0.5;
            pevent.fp1_tsum = (event.focalPlane.delayFL[0].Time+event.focalPlane.delayFR[0].Time);
            pevent.fp1_tcheck = (pevent.fp1_tsum)/2.0-pevent.anodeFrontTime;
            pevent.delayFrontMaxTime = std::max(event.focalPlane.delayFL[0].Time, event.focalPlane.delayFR[0].Time);
            pevent.x1 = pevent.fp1_tdiff*1.0/2.10; //position from time, based on total delay
            MyFill("x1",1200,-300,300,pevent.x1);
            MyFill("x1 vs anodeBack",600,-300,300,pevent.x1,512,0,4096,pevent.anodeBack);
        }
        if(!event.focalPlane.delayBL.empty() && !event.focalPlane.delayBR.empty())
        {
            pevent.fp2_tdiff = (event.focalPlane.delayBL[0].Time-event.focalPlane.delayBR[0].Time)*0.5;
            pevent.fp2_tsum = (event.focalPlane.delayBL[0].Time+event.focalPlane.delayBR[0].Time);
            pevent.fp2_tcheck = (pevent.fp2_tsum)/2.0-pevent.anodeBackTime;
            pevent.delayBackMaxTime = std::max(event.focalPlane.delayBL[0].Time, event.focalPlane.delayBR[0].Time);
            pevent.x2 = pevent.fp2_tdiff*1.0/1.98; //position from time, based on total delay
            MyFill("x2",1200,-300,300,pevent.x2);
            MyFill("x2 vs anodeBack",600,-300,300,pevent.x2,512,0,4096,pevent.anodeBack);
        }
        /*SABRE data*/
    /*  for(int j=0; j<5; j++)
        {
            if(!event.sabreArray[j].rings.empty())
            {
                pevent.sabreRingE[j] = event.sabreArray[j].rings[0].Long;
                pevent.sabreRingChannel[j] = event.sabreArray[j].rings[0].Ch;
                pevent.sabreRingTime[j] = event.sabreArray[j].rings[0].Time;
            }
            if(!event.sabreArray[j].wedges.empty())
            {
                pevent.sabreWedgeE[j] = event.sabreArray[j].wedges[0].Long;
                pevent.sabreWedgeChannel[j] = event.sabreArray[j].wedges[0].Ch;
                pevent.sabreWedgeTime[j] = event.sabreArray[j].wedges[0].Time;
            }
            //Aaaand passes on all of the rest. 4/24/20 GWM
            pevent.sabreArray[j] = event.sabreArray[j];
        }
        */
   
        for(int j=0; j<7; j++) {
           
            if(!event.cebraArray[j].cebr.empty())
            {
                // for(unsigned int l=0; l<=event.cebraArray[j].cebr.size(); l++){
                //    if(j==0){
                //         MyFill("CebraE0",4096,0,4096,event.cebraArray[j].cebr[l].Long);}
                //     else if(j==1){
                //         MyFill("CebraE1",4096,0,4096,event.cebraArray[j].cebr[l].Long);}    
                //     else if(j==2){
                //         MyFill("CebraE2",4096,0,4096,event.cebraArray[j].cebr[l].Long);}
                //     else if(j==3){
                //         MyFill("CebraE3",4096,0,4096,event.cebraArray[j].cebr[l].Long);}
                //     else if(j==4){
                //         MyFill("CebraE4",4096,0,4096,event.cebraArray[j].cebr[l].Long);}
                   
                //    }

                if(j==0){
                    pevent.cebraE0 = pevent.cebraE[j] = event.cebraArray[j].cebr[0].Long;
                    pevent.cebraChannel0 = event.cebraArray[j].cebr[0].Ch;
                    pevent.cebraTime0 = event.cebraArray[j].cebr[0].Time;
                }

                else if(j==1){
                    pevent.cebraE1 = pevent.cebraE[j] = event.cebraArray[j].cebr[0].Long;
                    pevent.cebraChannel1 = event.cebraArray[j].cebr[0].Ch;
                    pevent.cebraTime1 = event.cebraArray[j].cebr[0].Time;
                }

                else if(j==2){
                    pevent.cebraE2 = pevent.cebraE[j] = event.cebraArray[j].cebr[0].Long;
                    pevent.cebraChannel2 = event.cebraArray[j].cebr[0].Ch;
                    pevent.cebraTime2 = event.cebraArray[j].cebr[0].Time;
                }

                else if(j==3){
                    pevent.cebraE3 = pevent.cebraE[j] = event.cebraArray[j].cebr[0].Long;
                    pevent.cebraChannel3 = event.cebraArray[j].cebr[0].Ch;
                    pevent.cebraTime3 = event.cebraArray[j].cebr[0].Time;
                }

                else if(j==4){
                    pevent.cebraE4 = pevent.cebraE[j] = event.cebraArray[j].cebr[0].Long;
                    pevent.cebraChannel4 = event.cebraArray[j].cebr[0].Ch;
                    pevent.cebraTime4 = event.cebraArray[j].cebr[0].Time;
                }

                else if(j==5){
                    pevent.cebraE5 = pevent.cebraE[j] = event.cebraArray[j].cebr[0].Long;
                    pevent.cebraChannel5 = event.cebraArray[j].cebr[0].Ch;
                    pevent.cebraTime5 = event.cebraArray[j].cebr[0].Time;
                }

                else if(j==6){
                    pevent.cebraE6 = pevent.cebraE[j] = event.cebraArray[j].cebr[0].Long;
                    pevent.cebraChannel6 = event.cebraArray[j].cebr[0].Ch;
                    pevent.cebraTime6 = event.cebraArray[j].cebr[0].Time;
                }
     
            pevent.cebraE[j] = event.cebraArray[j].cebr[0].Long;
            pevent.cebraChannel[j] = event.cebraArray[j].cebr[0].Ch;
            pevent.cebraTime[j] = event.cebraArray[j].cebr[0].Time;

            j=j++;
     
    //   MyFill("CeBrAE vs CeBrA_channel",4096,0,4096,pevent.cebraE[j],200,0,200,pevent.cebraChannel[j]);
    //   if(j==0){
    //         MyFill("CeBrA.E.0 vs CeBrA_channel",4096,0,4096,pevent.cebraE[j],200,0,200,pevent.cebraChannel[j]);}
    //         else if(j==1){
    //         MyFill("CeBrA.E.1 vs CeBrA_channel",4096,0,4096,pevent.cebraE[j],200,0,200,pevent.cebraChannel[j]);}
    //         else if(j==2){
    //         MyFill("CeBrA.E.2 vs CeBrA_channel",4096,0,4096,pevent.cebraE[j],200,0,200,pevent.cebraChannel[j]);}
    //         else if(j==3){
    //         MyFill("CeBrA.E.3 vs CeBrA_channel",4096,0,4096,pevent.cebraE[j],200,0,200,pevent.cebraChannel[j]);}
    //         else if(j==4){
    //         MyFill("CeBrA.E.4 vs CeBrA_channel",4096,0,4096,pevent.cebraE[j],200,0,200,pevent.cebraChannel[j]);}
    }

    // if(pevent.cebraE[0]!=-1 && pevent.cebraE[1]!=-1){
    //         MyFill("cebraE0_vs_cebraE1_noCuts",4096,0,4096,pevent.cebraE[0],4096,0,4096,pevent.cebraE[1]);
    //         MyFill("cebraTime0-cebraTime1_noCuts",3000,-1500,1500,pevent.cebraTime[0]-pevent.cebraTime[1]);
    //         }
    // if(pevent.cebraE[0]!=-1 && pevent.cebraE[2]!=-1){
    //         MyFill("cebraE0_vs_cebraE2_noCuts",4096,0,4096,pevent.cebraE[0],4096,0,4096,pevent.cebraE[2]);
    //         MyFill("cebraTime0-cebraTime2_noCuts",3000,-1500,1500,pevent.cebraTime[0]-pevent.cebraTime[2]);
    //         }
    // if(pevent.cebraE[0]!=-1 && pevent.cebraE[3]!=-1){
    //         MyFill("cebraE0_vs_cebraE3_noCuts",4096,0,4096,pevent.cebraE[0],4096,0,4096,pevent.cebraE[3]);
    //         MyFill("cebraTime0-cebraTime3_noCuts",3000,-1500,1500,pevent.cebraTime[0]-pevent.cebraTime[3]);
    //         }
    // if(pevent.cebraE[0]!=-1 && pevent.cebraE[4]!=-1){
    //         MyFill("cebraE0_vs_cebraE4_noCuts",4096,0,4096,pevent.cebraE[0],4096,0,4096,pevent.cebraE[4]);
    //         MyFill("cebraTime0-cebraTime4_noCuts",3000,-1500,1500,pevent.cebraTime[0]-pevent.cebraTime[4]);
    //         }
    /*Aaaand passes on all of the rest. 4/24/20 GWM*/ // adjusted Mark
    pevent.cebraArray[j] = event.cebraArray[j];
  }

  
        if(pevent.cebraE[0]!=-1){ 
            MyFill("CebraE0",4096,0,4096,pevent.cebraE[0]);}
        if(pevent.cebraE[1]!=-1){ 
            MyFill("CebraE1",4096,0,4096,pevent.cebraE[1]);}
        if(pevent.cebraE[2]!=-1){ 
            MyFill("CebraE2",4096,0,4096,pevent.cebraE[2]);}
        if(pevent.cebraE[3]!=-1){ 
            MyFill("CebraE3",4096,0,4096,pevent.cebraE[3]);}
        if(pevent.cebraE[4]!=-1){ 
            MyFill("CebraE4",4096,0,4096,pevent.cebraE[4]);}
        if(pevent.cebraE[5]!=-1){ 
            MyFill("CebraE5",4096,0,4096,pevent.cebraE[5]);}
        if(pevent.cebraE[6]!=-1){ 
            MyFill("CebraE6",4096,0,4096,pevent.cebraE[6]);}


         

  

        /*Make some histograms and xavg*/
        MyFill("anodeBack vs scintLeft",512,0,4096,pevent.scintLeft,512,0,4096,pevent.anodeBack);
        if(pevent.x1 != -1e6 && pevent.x2 != -1e6)
        {
            pevent.xavg = pevent.x1*w1+pevent.x2*w2;
            MyFill("xavg",1200,-300,300,pevent.xavg);
            if((pevent.x2-pevent.x1) > 0)
                pevent.theta = std::atan((pevent.x2-pevent.x1)/36.0);
            else if((pevent.x2-pevent.x1) < 0)
                pevent.theta = TMath::Pi() + std::atan((pevent.x2-pevent.x1)/36.0);
            else 
				pevent.theta = TMath::Pi()/2.0;
			MyFill("xavg vs theta",600,-300,300,pevent.xavg,314,0,3.14,pevent.theta);
			MyFill("x1 vs x2",600,-300,300,pevent.x1,600,-300,300,pevent.x2);

        }
        if(pevent.anodeFrontTime != -1 && pevent.scintRightTime != -1)
            pevent.fp1_y = pevent.anodeFrontTime-pevent.scintRightTime;
        if(pevent.anodeBackTime != -1 && pevent.scintRightTime != -1)
            pevent.fp2_y = pevent.anodeBackTime-pevent.scintRightTime;
    }
   
    ProcessedEvent SFPAnalyzer::GetProcessedEvent(CoincEvent& event)
    {
        AnalyzeEvent(event);
        return pevent;
    }

}
