/*
 *Goal is to provide a fast coinc window for rejecting si.
 *And a way to orgainize focal plane data within slow cw.
 *
 */
#ifndef FASTSORT_H
#define FASTSORT_H

#include "DataStructs.h"
#include <TH2.h>

namespace EventBuilder {

	class FastSort 
	{
	  
	public:
	//	FastSort(float si_windowSize, float ion_windowSize);
		FastSort(float cebr_windowSize, float ion_windowSize);
		~FastSort();
		std::vector<CoincEvent> GetFastEvents(CoincEvent& event);
	
	private:
		void ResetCEBRA();
		void ResetFocalPlane();
		void ProcessCEBRA(unsigned int scint_index);
		void ProcessFocalPlane(unsigned int scint_index, unsigned int ionch_index);
	
	//	float si_coincWindow, ion_coincWindow;
		float cebr_coincWindow, ion_coincWindow;
		CoincEvent *event_address, slowEvent;
		CoincEvent fastEvent, blank;
		CeBrADetector cebrblank;
		FPDetector fpblank;
	
	};

}
#endif
