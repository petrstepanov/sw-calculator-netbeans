/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AbstractImportSpectrumPresenter.h"
#include "AbstractImportSpectrumView.h"
#include <TGFileDialog.h>
#include "../../model/Model.h"
#include "../../util/UiHelper.h"
#include "../../util/FileUtils.h"

AbstractImportSpectrumPresenter::AbstractImportSpectrumPresenter(AbstractImportSpectrumView* view) : 
    AbstractPresenter<Model, AbstractImportSpectrumView>(view) {
	model = instantinateModel();
}

void AbstractImportSpectrumPresenter::onOpenFileClicked(){
    // Get FileInfo from open file dialog
    UiHelper* uiHelper = UiHelper::getInstance();
    TGFileInfo* fileInfo = uiHelper->getFileFromDialog();
    if (!fileInfo->fFilename){
        return;
    }
    TString* fileNamePath = new TString(fileInfo->fFilename);
    // Update Model with new file name (virtual function)
    this->setModelFileName(fileNamePath);
    // Update View to reflect 
    view->loadFile(fileNamePath);
}

void AbstractImportSpectrumPresenter::onImportSpectrumClicked(){
    // Import Histogram
    Int_t energyColumn = view->getEnergyColumnNumber();
    Int_t countsColumn = view->getCountsColumnNumber();
    TString* fileName = view->getFileName();
    FileUtils* fileUtils = FileUtils::getInstance();
    TH1F* hist = fileUtils->importTH1(fileName->Data(), energyColumn, countsColumn);
    if (!hist){
        return;
    }
    
    // Update Model
    setModelHist(hist);
    
    // Update View
    view->drawHistogram(hist);
}
