//------------------------------------------------------------------------------
// Copyright (c) 2020 Hsienchi Kuo (Allen Institute)
// All rights reserved.
//------------------------------------------------------------------------------

/*******************************************************************************
*
*  [FragTraceControlPanel] is the user interface of Neuron Assembler. 
*  It collects user's parameters and initiates [FragTraceManager]'s segment generating process. 
*  It also receives user's editing commands through buttons and communicates between [terafly::CViewer], [terafly::CViewer]'s view3DWidget, and [FragmentEditor].
*
********************************************************************************/

#ifndef _FRAGTRACECONTROLPANEL_H_
#define _FRAGTRACECONTROLPANEL_H_

#include "v3d_compile_full.h"
#include "v3d_interface.h"
#include "INeuronAssembler.h"
#include "IPMain4NeuronAssembler.h"

#include "FragTracer_Define.h"
#include "ui_fragmentedTraceUI.h"
#include "FragTraceManager.h"
#include "FragmentEditor.h"

class FragTraceControlPanel : public QDialog, public IPMain4NeuronAssembler
{
	Q_OBJECT
	Q_INTERFACES(IPMain4NeuronAssembler)

	friend class FragmentedAutoTracePlugin;
	friend class FragTraceTester;

public:
	FragTraceControlPanel(QWidget* parent, V3DPluginCallback2* callback);
	~FragTraceControlPanel();
	map<string, float> paramsFromUI;

	// ======= Saving path for results / intermediate results ======= //
	QString saveSWCFullName;
	// ============================================================== //


	/* ======= Result and Scaling Functions ======= */ 
	NeuronTree tracedTree;
	map<int, string> scalingRatioMap;
	/* ============================================ */


	/* ======= Terafly Communicating Methods ======= */
	virtual void getNAVersionNum();

	virtual void updateCViewerPortal();

	virtual bool markerMonitorStatus() { return this->uiPtr->groupBox_15->isChecked(); }
	virtual void sendSelectedMarkers2NA(const QList<ImageMarker>& selectedMarkerList, const QList<ImageMarker>& selectedLocalMarkerList);

	virtual void eraserSegProcess(V_NeuronSWC_list& displayingSegs, const map<int, vector<NeuronSWC>>& seg2includedNodeMap);
	virtual void connectSegProcess(V_NeuronSWC_list& displayingSegs, const map<int, vector<NeuronSWC>>& seg2includedNodeMap);
	virtual void exitNAeditingMode();

	virtual bool changeAssociatedSegsClicked();
	virtual void signalNA2retypeConnectedSegs(V_NeuronSWC_list& displayingSegs, const int retypedSeg, const int type);
	virtual void signalNA2retypeConnectedSegs(V_NeuronSWC_list& displayingSegs, const set<int>& retypedSegs, const int type);
	/* ============================================= */


	/* ================== User Interface Buttons =================== */
public slots:
	// ------- Configuration ------- //
	void imgFmtChecked(bool checked);
	void nestedChecks(bool checked);
	void markerMonitorOption(bool checked);
	void multiSomaTraceChecked(bool checked);
	void saveSettingsClicked();
	// ---------------------------- //

	// ------- Post Editing ------- //
	void eraseButtonClicked();
	void connectButtonClicked();
	void showHideButtonClicked(bool clicked);
	void sequentialTypeChangingToggled(bool toggle);
	// ---------------------------- //

	// - Capture Active 3D Viewer - //
	void captureImgName(QString newImgNameQ);
	// ---------------------------- //
	/* ======= END of [User Interface Configuration Buttons] ======= */


// ***************************************************************************** //
	void traceButtonClicked(); // ==> THIS IS WHERE THE TRACING PROCESS STARTS
// ***************************************************************************** //


// -------------- Receive and send tree between FragTraceManager -------------- //
	void catchTracedTree(NeuronTree tracedTree) { this->tracedTree = tracedTree; }
	void sendExistingNeuronTree(NeuronTree& existingTree_in_Manager) { existingTree_in_Manager = thisCallback->getSWCTeraFly(); }
// ---------------------------------------------------------------------------- //


private:
	/* ============== Member Class Pointers ============== */
	V3DPluginCallback2* thisCallback; // DO NOT DELETE! -> created and sent from v3d_plugin_loader.
	INeuronAssembler* CViewerPortal;  // DO NOT DELETE! -> This is the base class interface of CViewer!
	Ui::FragmentedTraceUI* uiPtr;
	FragTraceManager* traceManagerPtr;
	FragmentEditor* fragEditorPtr;
	/* =================================================== */


	/* =============== Additional Widget =============== */
	QStandardItemModel* somaListViewer;
	/* ================================================= */


	/* ============== Marker Detection ============== */
	v3dhandle currHandle;
	int surType;
	QList<ImageMarker> updatedMarkerList;
	QList<ImageMarker> selectedMarkerList;
	QList<ImageMarker> selectedLocalMarkerList;
	map<int, ImageMarker> somaMap;
	map<int, ImageMarker> localSomaMap;
	map<int, ImageMarker> localAxonMarkerMap;
	map<int, string> somaDisplayNameMap;
	void updateMarkerMonitor();
	/* ============================================== */


	/* =============== Parameter Collecting Functions =============== */
	void pa_imgEnhancement();
	void pa_maskGeneration();
	void pa_objFilter();
	void pa_objBasedMST();
	void pa_axonContinuous();
	/* =========== END of [Parameter Collecting Functions] ========== */


	/* ======= Tracing Volume Preparation ======= */
	// Partial volume tracing is achieved by talking to tf::PluginInterface through V3d_PluginLoader with v3d_interface's virtual [getPartialVolumeCoords],
	// so that it can be directly accessed through [thisCalback] from [teraflyTracePrep].
	bool volumeAdjusted;
	int* volumeAdjustedCoords; // local coordinates of [displaying image boudaries], eg, 1 ~ 256, etc
	int* globalCoords;         // global coordinates of [displaying image boundaries] in whole brain scale, currently not used.
	int* displayingDims;

	void teraflyTracePrep(workMode mode); // Image preparation; NOTE: FragTraceManager is created here!
	void sendImgParams();
	/* ========================================== */


	/* ========= Post Editing ========= */
	int totalVsegNum, distInterval, currentDist;
	vector<ptrdiff_t> type16Locs;
	vector<V_NeuronSWC> tracedType16Vsegs;
	boost::container::flat_set<ptrdiff_t> updatedHiddenSegLocs, permanentDelSegLocs, incrementHiddenLocs;
	boost::container::flat_map<int, boost::container::flat_set<ptrdiff_t>>::iterator type16showingPtr;
	boost::container::flat_map<int, boost::container::flat_set<ptrdiff_t>> dist2VsegLocMap;
	//boost::container::flat_map<int, boost::container::flat_set<segUnit>> dist2segUnitMap;
	
	void getType16Locs();
	void updateDisplayingVsegProfile();
	void moveType16showPtr(bool increment);
	/* ================================ */


private slots:	
void refreshSomaCoords();


private:
	//bool initThread();

	void fillUpParamsForm(); // This is for future parameter learning project.
};


#endif