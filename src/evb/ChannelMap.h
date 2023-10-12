/*
	ChannelMap.h
	Class which acts as the go between for global compass channels (board#*16 + channel) and
	physical detector information. Used in the event builder to assign compass data to real values
	in a simple way. Takes in a definition file and parses it into an unordered_map container.

	Written by G.W. McCann Oct. 2020
*/
#ifndef CHANNELMAP_H
#define CHANNELMAP_H

namespace EventBuilder {
	//Detector part/type identifiers for use in the code
	enum DetType
	{
		CEBRA,
		//Sabre,
		FocalPlane,
		NoneType
	};
	
	enum DetAttribute 
	{
		ScintLeft,
		ScintRight,
		AnodeFront,
		AnodeBack,
		DelayFR,
		DelayFL,
		DelayBR,
		DelayBL,
		Cathode,
		Monitor,
		CEBRA0,
		CEBRA1,
		CEBRA2,
		CEBRA3,
		CEBRA4,
		CEBRA5,
		CEBRA6,

		ScintLeftCopy,
		/*
		SabreRing0,
		SabreRing1,
		SabreRing2,
		SabreRing3,
		SabreRing4,
		SabreWedge0,
		SabreWedge1,
		SabreWedge2,
		SabreWedge3,
		SabreWedge4,
		*/
		NoneAttr
	};
	
	struct Channel 
	{
		DetType type;
		DetAttribute attribute; //What kind of detector we're looking at
		int local_channel; //Which specific piece of detector we're looking at
	};
	
	class ChannelMap 
	{
		
	public:
		typedef std::unordered_map<int, Channel> Containter;
		typedef std::unordered_map<int, Channel>::iterator Iterator;
	
		ChannelMap();
		ChannelMap(const std::string& filename);
		~ChannelMap();
		bool FillMap(const std::string& filename);
		inline const Containter* GetCMap() { return &m_cmap; };
		inline Iterator FindChannel(int key) { return m_cmap.find(key); };
		inline Iterator End() { return m_cmap.end(); };
		inline bool IsValid() { return m_validFlag; };
	
	private:
		Containter m_cmap;
		bool m_validFlag;
	};
}

#endif
