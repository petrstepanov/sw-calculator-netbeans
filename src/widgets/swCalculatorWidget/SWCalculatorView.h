/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SWCalculatorFrame.h
 * Author: petrstepanov
 *
 * Created on August 1, 2017, 5:02 PM
 */

#ifndef SWCALCULATORVIEW_H
#define SWCALCULATORVIEW_H

#include <TGFrame.h>
#include <TString.h>
#include <TGLabel.h>
#include <TGTab.h>
#include <TGTextEdit.h>
#include <TGNumberEntry.h>
#include <TGComboBox.h>
#include <TGButton.h>
#include <TGButtonGroup.h>
#include <TCanvas.h>
#include <TImage.h>
#include <TH1I.h>
#include <TH1F.h>
#include <RooCurve.h>
#include <RooFitResult.h>
#include <RooPlot.h>
#include "../../model/Model.h"
#include <TGDoubleSlider.h>
#include <TGTextEntry.h>
#include <TGDoubleSlider.h>
#include <TGTextBuffer.h>
#include "../AbstractView.h"
#include "SWCalculatorPresenter.h"
#include "../rooRealVarWidget/RooRealVarView.h"
#include "../../util/HistProcessor.h"

class SWCalculatorPresenter;

class SWCalculatorView : public AbstractView<SWCalculatorPresenter> {
  protected:
    void initUI();

  public:
    SWCalculatorView(const TGWindow *w = 0);
    virtual ~SWCalculatorView();

    // Override base class virtual functions
    SWCalculatorPresenter* instantinatePresenter();
    void connectSignals();

    // View elements
    TGTab* tabsWidget;
    TGCompositeFrame *tabFit;

    // Fit range
    TGNumberEntry* numFitMin;
    TGNumberEntry* numFitMax;
    TGDoubleHSlider* numFitSlider;

    // S and W widths
    TGLabel* lblRescale1;
    TGLabel* lblRescale2;
    TGLabel* lblRescale3;
    TGNumberEntry* numSWidth;
    TGNumberEntry* numWWidth;
    TGNumberEntry* numWShift;

    // Model components
    TGCheckButton* hasParabola;
    TGNumberEntry* numGauss;
    TGNumberEntry* numExponent;
    TGNumberEntry* numDampExponent;

    TGTextButton* addHistogramButton;
    TGLabel* histComponentLabel;
    TGTextButton* removeHistogramButton;

    // Convolution radios
    TGButtonGroup* convTypeButtonGroup;

    // Fit
    TGTextButton* btnEditParameters;
    TGTextButton* btnFitSpectrum;

    TGTextEdit* txtFitResult;
    TGTextButton* btnClearResult;
    TGTextButton* btnSaveResult;

    // Plot and display params
     TGTextButton* btnSaveData;
    TGTextButton* btnSaveImage;
    TCanvas* canvasPlot;
    TGDoubleHSlider* zoomSlider;
    TGNumberEntry* displayMin;
    TGNumberEntry* displayMax;
//    TGTextBuffer* tbMin;
//    TGTextBuffer* tbMax;

//    TGNumberEntry* numDisplayMin;
//    TGNumberEntry* numDisplayMax;
//    TGCheckButton* hasOrtho;
//    TGTextButton*  btnApplyZoom;
//    TGTextButton*  btnResetZoom;
    RooPlot* fitFrame;
    RooPlot* chiFrame;
    TPad* padData;
    TPad* padChi2;

    // Calls from Presenter
    void setTabEnabled(Int_t, Bool_t);
    void setToolbarEnabled(Bool_t isEnabled);

    void setFitRange(Double_t min, Double_t max);
    void setFitRangeLimits(Double_t min, Double_t max);
    void reflectTwoDetector(Bool_t isTwoDetector);
    void setComponentHistogram(TH1F* hist);

    void setConvolutionType(ConvolutionType t);

    void displayFitParameters(RooFitResult* fitResult);
    void displayVariable(RooRealVar* variable);
    void displayVariables(RooArgList* variables);
    void displayChi2(Chi2Struct chi2Struct);
    void displaySW(RooRealVar* s, RooRealVar* w);
    void updateCanvas();
    void setDisplayLimits(Float_t min, Float_t max);
    TCanvas* getCanvas();
    void clearFitResults();
    void scrollOutputDown();

    // Calls to Presenter
    void initRooPlots(RooPlot* fitFrame, RooPlot* chiFrame);

    // Local view functions for widgt interactions
    void displayFilename(TString* fileName);
    void onDisplayMinChange(char*);
    void onDisplayMaxChange(char*);
    void onSliderChange();
    void updateCanvasLimits(Double_t min, Double_t max);

    ClassDef(SWCalculatorView,0);
};

#endif /* SWCALCULATORVIEW_H */
