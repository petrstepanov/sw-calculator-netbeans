/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Constants.h
 * Author: petrstepanov
 *
 * Created on August 19, 2017, 11:30 PM
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <TROOT.h>

class Constants {
  public:
    static constexpr Double_t chbar = 0.19732697 * 1E4; // c*hbar, eV*Å
    static constexpr Double_t mc2 = 0.511E6; // electron mc^2, eV
    static constexpr Double_t Ry = 13.605; // Rydberg constant, eV
    static constexpr Double_t a_B = 0.529177; // Bohr radius, Å
    
    static const Int_t windowWidth = 1000;
    static const Int_t windowHeight = 800;
    static const Int_t leftPanelWidth = 420;
    
    static const Double_t* padMargin; // left, right, bottom, top
    
    static const char* applicationName;
};

#endif /* CONSTANTS_H */

