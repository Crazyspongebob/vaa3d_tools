//------------------------------------------------------------------------------
// Copyright (c) 2018 Hsienchi Kuo (Allen Institute, Neuronanatomy)
// All rights reserved.
//------------------------------------------------------------------------------

/*******************************************************************************
*
*  This library manages image libraries including ImgAnalyzer and ImgProcessor along with some image operation functions.
*
*  In ImgManager class, regardless of slice or cube, every image is represented by a registeredImg struct. 
*  A registeredImg struct carries information of the image, eg., dimensions, root path, name(imgAlias), and a map<string, myImg1DPtr> which stores all myImg1DPtrs with slice numbers as the key.
*  myImg1DPtr is a custom defined data type of boost::shared_array that stores 1D image data in order to avoid complications of memory management among different libraries.  
*  myImg1DPtr is used as oppose to Vaa3D's conventional use unsigned char[] data1d.
*
*  ImgManager class provides imgEntry method to initiate a registeredImg and stores it in ImgManager::imgDatabase.
*  ImgManager::imgDatabase is a map<string, registeredImg> that uses image name(imgAlias) as the key to access registeredImg.
*
********************************************************************************/

#ifndef IMGMANAGER_H
#define IMGMANAGER_H

#include <string>
#include <deque>

#include <boost/filesystem.hpp>

#include <qstring.h>
#include <qstringlist.h>

#include "my_surf_objs.h"
#include "basic_4dimage.h"
#include "v3d_interface.h"

#include "integratedDataStructures.h"

using namespace integratedDataStructures;

class ImgManager
{
public: 
	/********* Constructors and Basic Data Members *********/
	ImgManager() = default;
	ImgManager(QString inputPath);

	QString inputCaseRootPath;
	QString inputSWCRootPath;
	QString outputRootPath;
	
	QStringList caseList;
	string inputSingleCaseFullPath;
	string outputSingleCaseFullPath;
	multimap<string, string> inputMultiCasesFullPaths;       // Single or multiple, all cases and slices are stored in this multimap indexed with its case/slice name.
	multimap<string, string> outputMultiCasesSliceFullPaths;

	enum imgFormat { multicaseCubes, slices, singleCase};
	/*******************************************************/



	/***************** I/O and Image Property Profile *****************/
	map<string, registeredImg> imgDatabase;  // --> All images are managed and stored in the form of 'regesteredImg' in this library.
	void imgEntry(string caseID, imgFormat format);

	static inline bool saveimage_wrapper(const char* filename, unsigned char* pdata,  V3DLONG sz[], int datatype);
	
	static void imgsBlend(const vector<unsigned char*>& inputImgPtrs, unsigned char outputImgPtr[], int imgDims[]);
	/******************************************************************/


	// ~~~~~~~~~~~~~~~~~ The following is not frequently used. Most of them were developed for IVSCC project. May be deprecated in the future. ~~~~~~~~~~~~~~~~~ //
	/***************** Image - SWC Functionalities *****************/
	static inline vector<int> retreiveSWCcropDnParam_imgBased(const registeredImg& originalImg, const QList<NeuronSWC>& refNodeList, float xDnFactor, float yDnFactor, float zDnFactor, int boundaryMargin = 10, bool zShift = false);
	
	static NeuronTree imgSignal2SWC(const registeredImg& sourceImg, int type = 2);
	/***************************************************************/


	/********* Methods for Generating Binary Masks from SWC Files *********/
	void swc2Mask_2D(string swcFileName, long int dims[2], unsigned char*& mask1D); // Generate a 2D mask based on the corresponding "SWC slice."
	bool getMarkersBetween(vector<MyMarker>& allmarkers, MyMarker m1, MyMarker m2);

	void detectedNodes2mask_2D(QList<NeuronSWC>* nodeListPtr, long int dims[2], unsigned char*& mask1D);
	/**********************************************************************/


	/********* Assemble All SWC Masks Together as An "SWC Mip Mask." *********/
	void MaskMIPfrom2Dseries(string path);                       
	/*************************************************************************/


	/********* Dessemble Image/Stack Into Tiles. This Is For Caffe's Memory Leak Issue *********/
	static void imgSliceDessemble(string imgName, int tileSize);
	/*******************************************************************************************/
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ //
};

inline bool ImgManager::saveimage_wrapper(const char* filename, unsigned char pdata[], V3DLONG sz[], int datatype)
{
	if (!pdata)
	{
		cerr << "input array not valid" << endl;
		return false;
	}

	if (!filename || !sz)
	{
		v3d_msg("some of the parameters for simple_saveimage_wrapper() are not valid.", 0);
		return false;
	}

	ImagePixelType dt;
	if (datatype == 1) dt = V3D_UINT8;
	else if (datatype == 2) dt = V3D_UINT16;
	else if (datatype == 4) dt = V3D_FLOAT32;
	else
	{
		v3d_msg(QString("the specified save data type in simple_saveimage_wrapper() is not valid, dt=[%1].").arg(datatype), 0);
		return false;
	}

	Image4DSimple* outimg = new Image4DSimple;
	if (outimg) outimg->setData(pdata, sz[0], sz[1], sz[2], sz[3], dt);
	else
	{
		v3d_msg("Fail to new Image4DSimple for outimg.");
		return false;
	}
	outimg->saveImage(filename);
	
	return true;
}

inline vector<int> ImgManager::retreiveSWCcropDnParam_imgBased(const registeredImg& inputImg, const QList<NeuronSWC>& refNodeList, float xDnFactor, float yDnFactor, float zDnFactor, int boundaryMargin, bool zShift)
{
	int xlb = 10000, xhb = 0, ylb = 10000, yhb = 0, zlb = 10000, zhb = 0;
	for (QList<NeuronSWC>::const_iterator nodeIt = refNodeList.begin(); nodeIt != refNodeList.end(); ++nodeIt)
	{
		int thisNodeX = int(round(nodeIt->x / xDnFactor));
		int thisNodeY = int(round(nodeIt->y / yDnFactor));
		int thisNodeZ = int(round(nodeIt->z / zDnFactor));
		if (thisNodeX < xlb) xlb = thisNodeX;
		if (thisNodeX > xhb) xhb = thisNodeX;
		if (thisNodeY < ylb) ylb = thisNodeY;
		if (thisNodeY > yhb) yhb = thisNodeY;
		if (thisNodeZ < zlb) zlb = thisNodeZ;
		if (thisNodeZ > zhb) zhb = thisNodeZ;
	}
	xlb -= 10; xhb += 10; ylb -= 10; yhb += 10;
	if (xlb <= 0) xlb = 1;
	if (xhb >= inputImg.dims[0]) xhb = inputImg.dims[0];
	if (ylb <= 0) ylb = 1;
	if (yhb >= inputImg.dims[1]) yhb = inputImg.dims[1];
	if (zShift)
	{
		if (zlb <= 0) zlb = 1;
		if (zhb >= inputImg.dims[2]) zhb = inputImg.dims[1];
	}

	vector<int> offSets(3);
	offSets.at(0) = xlb;
	offSets.at(1) = ylb;
	zShift ? offSets.at(2) : 0;

	return offSets;
}

#endif