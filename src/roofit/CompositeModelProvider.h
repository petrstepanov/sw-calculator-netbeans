/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CompositeModelProvider.h
 * Author: petrstepanov
 *
 * Created on August 15, 2017, 9:59 PM
 */

#ifndef COMPOSITEMODELPROVIDER_H
#define COMPOSITEMODELPROVIDER_H

#include "AbstractModelProvider.h"
#include <RooRealVar.h>
#include <RooHistPdf.h>
#include "../util/Variable.h"

class CompositeModelProvider : public AbstractModelProvider {
public:
    CompositeModelProvider();
    CompositeModelProvider(const CompositeModelProvider& orig);
    
    CompositeModelProvider(RooRealVar* x, RooRealVar* x0);
//    virtual ~CompositeModelProvider();

    std::list<Variable*> getIndirectParameters();
    
    static std::map<Int_t, TString> getConvolutionTypes(void);
    
    void initTwoDetector(Bool_t hasParabola = kTRUE, const Int_t numGauss = 1, const Int_t numLorentz = 1, const Int_t numLorentzSum = 1, /*Bool_t hasOrthogonal = kFALSE,*/ Int_t convType = 0, Double_t convFWHM = 1.7, Bool_t isConvFixed = kFALSE);
    void initSingleDetector(Bool_t hasParabola = kTRUE, const Int_t numGauss = 1, const Int_t numLorentz = 1, const Int_t numLorentzSum = 1, /*Bool_t hasOrthogonal = kFALSE,*/ Int_t convType = 0, Double_t convFWHM = 1.7, Bool_t isConvFixed = kFALSE, Double_t bgFraction = 0.1);
    
    void initSourcePdf(TH1F* sourceHist, RooAbsReal* sourceContrib);
    
private:
    RooArgList* pdfsToBeConvoluted;
//    RooArgList* coeffList;
    RooRealVar* observable;
    RooHistPdf* sourcePdf = nullptr;
    RooAbsReal* sourceContribution = nullptr;
    Bool_t isTwoDetector;
    
    static std::map<Int_t, TString> createConvolutionType(){
        std::map<Int_t, TString> m = {{1, TString("None")}, {2, TString("FFT3")}};
        return m;
    }; 

    static std::map<Int_t, TString> convolutionType;
    
    void initModel(Bool_t hasParabola, const Int_t, const Int_t numLorentz, const Int_t numLorentzSum, RooRealVar* fwhm);
    void initBackground(Double_t backgroundFraction);
    
    Double_t* getDefaultGaussAs(Int_t numGauss);
    Double_t* getDefaultLorentzAs(Int_t numGauss);
    Double_t* getDefaultDampLorentzAs(Int_t numGauss);

    void deleteObject();

    RooAbsPdf* getConvolutedPdf(RooAbsPdf* pdf, RooRealVar* fwhm);
};

#endif /* COMPOSITEMODELPROVIDER_H */

