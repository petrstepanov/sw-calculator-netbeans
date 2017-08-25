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
#include "Variable.h"

class CompositeModelProvider : public AbstractModelProvider {
public:
    CompositeModelProvider();
    CompositeModelProvider(const CompositeModelProvider& orig);
    
    CompositeModelProvider(RooRealVar* x, RooRealVar* x0, Bool_t hasParabola = kTRUE, const Int_t numGauss = 1, const Int_t numLorentz = 1, const Int_t numLorentzSum = 1, Bool_t hasOrthogonal = kFALSE, Bool_t hasAtan = kFALSE, Double_t constBgFraction = 0, Bool_t isTwoDetector = kTRUE);
//    virtual ~CompositeModelProvider();

    std::list<Variable*> getIndirectParameters();

private:
    RooArgList* pdfList;
    RooArgList* coeffList;
    Bool_t isTwoDetector;
    
    Double_t* getDefaultGaussAs(Int_t numGauss);
    Double_t* getDefaultLorentzAs(Int_t numGauss);
    
    void deleteObject();
};

#endif /* COMPOSITEMODELPROVIDER_H */
