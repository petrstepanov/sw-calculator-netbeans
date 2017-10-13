/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ImportSpectrumPresenter.h
 * Author: petrstepanov
 *
 * Created on October 11, 2017, 6:30 PM
 */

#ifndef IMPORTSPECTRUMPRESENTER_H
#define IMPORTSPECTRUMPRESENTER_H

#include "AbstractImportSpectrumPresenter.h"
//#include "ImportSpectrumView.h"
#include <TString.h>

class ImportSpectrumView;

class ImportSpectrumPresenter : AbstractImportSpectrumPresenter<ImportSpectrumView> {
    public:
        ImportSpectrumPresenter(ImportSpectrumView* view);
        
        void setModelFileName(char* fileName);        
        void setModelHist(TH1F* hist, Bool_t isTwoDetector);
};

#endif /* IMPORTSPECTRUMPRESENTER_H */

