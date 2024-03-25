#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Code for file organization for hypothesis test code in C++ (load ROOT 6 before running the hypothesis testing code)
# Run this code with ROOT 6 by going inside the file .bashrc and reloading using source ~/.profile
# This code prepares the hypothesis files to be tested in the other codes


# This code I created lets me plot "Correlation Plots" from the same ROOT file. 
# In this case the output file came from the analysis performed in MadAnalysis5.
# For a specific spin just change the input string to the desired case! CHANCHE THE SPECIFIC YLABEL TO ADJUST TO THE SPECIFIC CASE!

import uproot3
import ROOT
import mplhep as hep
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.tri as tri
import math

from matplotlib import rc
from matplotlib.ticker import AutoMinorLocator

from ROOT import Math
from ROOT import TLorentzVector

#----------------------------------------------#
#--------------   Formatting    ---------------#
#----------------------------------------------#

def set_style(font,size):
    rc('text', usetex=True)
    rc('font',**{'family':'serif','serif':[font]})
    plt.rcParams['mathtext.fontset'] = 'cm'
    plt.rcParams['font.size'] = size
    return True
#----------------------------------------------#
#------------ Read Data from ROOT -------------#
#----------------------------------------------#

def extract_data(input_ROOT,ttree,varA,varB,varC):
	
    file_data=uproot3.open(input_ROOT)
    CL_data=file_data[ttree].array(varA)
    k_data=file_data[ttree].array(varB)
    ktil_data=file_data[ttree].array(varC)
    
    return CL_data, k_data, ktil_data 

#----------------------------------------------#
#------------ Plot DATA from ROOT -------------#
#----------------------------------------------#

def Running_CL(input_directory, varA, varB, varC, ttree, mass_list):
    hep.style.use('ATLAS')
    for i, mass in enumerate(mass_list):
    # Construct the file name
        direc = input_directory + "Expb2_Gunion_KD_" + str(mass) + ".0_s0_9bins_A.rootmode12_table.CL.root"
        CL,k,ktil = extract_data(direc, ttree, varA, varB, varC)
        # Plot the data on the current axis
        sc = plt.scatter(k, ktil, c=CL, cmap='terrain', s=50, alpha=0.7,linewidths=1.5)
        cbar = plt.colorbar()
        cbar.set_label("CL")
        contour_levels = [0.68,0.90,0.95]
        contours = plt.tricontour(k, ktil, CL, levels=contour_levels, colors='black', linestyles='dashed', linewidths=1.0)
        plt.clabel(contours, inline=True, fontsize=5, fmt='%1.2f')

        plt.xlabel("$g_{u_{33}}^{S}$")
        plt.ylabel("$g_{u_{33}}^{P}$")
        hep.atlas.label(dictionary_Mass[mass],loc=2,data=True,lumi=3000,com=14,lumi_format="{0:.0f}")
        #hep.atlas.text(" $b_2$",loc=1)
        #hep.atlas.text(" $\\tilde{b_{2}}^{(0,1,0)}$",loc=1)
        hep.atlas.text(" $\\tilde{b_{2}}^{(0,\\frac{1}{\sqrt{2}},\\frac{1}{\sqrt{2}})}$",loc=1)

        plt.text(0.21, 1.03, "MadGraph5_aMC@NLO", transform=plt.gca().transAxes, ha="center", va="center")
    
        plt.savefig("Expb2_Gunion_KD_3000fb" + str(mass) + "GeV" + ".png",dpi=300)
        plt.show()
    return True

def Running_Limits(input_directory, varA, varB, varC, ttree, mass_list):
    k_68_low = 999.0
    k_68_high = -999.0
    kt_68_low = 999.0
    kt_68_high = -999.0

    k_95_low = 999.0
    k_95_high = -999.0
    kt_95_low = 999.0
    kt_95_high = -999.0

    # Open the text file for writing (it will be overwritten if it exists)
    with open("limits.txt", "w") as file:
        for mass in mass_list:
            # Reset the limits for each mass
            k_68_low = 999.0
            k_68_high = -999.0
            kt_68_low = 999.0
            kt_68_high = -999.0

            k_95_low = 999.0
            k_95_high = -999.0
            kt_95_low = 999.0
            kt_95_high = -999.0

            # Construct the file name
            direc = input_directory + "Expb2_Gunion_" + str(mass) + ".0_s0_9bins_A.rootmode02_table.CL.root"
            CL, k, ktil = extract_data(direc, ttree, varA, varB, varC)

            for j, cl_value in enumerate(CL):
                intCL = int(cl_value * 1000)

                if 675 <= intCL <= 685:
                    print("                                  --- CL=68% ---")
                    if k[j] > 0:
                        k_68_low = min(k_68_low, k[j])
                        k_68_high = max(k_68_high, k[j])
                    else:
                        k_68_low = min(k_68_low, k[j])
                        k_68_high = max(k_68_high, k[j])

                    kt_68_low = min(kt_68_low, ktil[j])
                    kt_68_high = max(kt_68_high, ktil[j])

                if 945 <= intCL <= 955:
                    print("                                  --- CL=95% ---")
                    if k[j] > 0:
                        k_95_low = min(k_95_low, k[j])
                        k_95_high = max(k_95_high, k[j])
                    else:
                        k_95_low = min(k_95_low, k[j])
                        k_95_high = max(k_95_high, k[j])

                    kt_95_low = min(kt_95_low, ktil[j])
                    kt_95_high = max(kt_95_high, ktil[j])

            # Append the results for the current mass to the text file
            file.write("Mass {}:\n".format(mass))
            file.write("CL 68%: k-> [{:.4f}, {:.4f}] ktil->[{:.4f}, {:.4f}]\n".format(
                k_68_low, k_68_high, kt_68_low, kt_68_high))
            file.write("CL 95%: k-> [{:.4f}, {:.4f}] ktil->[{:.4f}, {:.4f}]\n".format(
                k_95_low, k_95_high, kt_95_low, kt_95_high))
            file.write("\n")  # Add a newline to separate results for different masses
    return True


input_1="/Users/ruimiguelsilva/Desktop/CL_M12_3000fb/Stats/"

dictionary_Mass={
0 :r"$m_{Y_{0}}$= 0.01 GeV",
1 :r"$m_{Y_{0}}$= 1 GeV",
10 :r"$m_{Y_{0}}$= 10 GeV",
100 :r"$m_{Y_{0}}$= 100 GeV",
125 :r"$m_{Y_{0}}$= 125 GeV"
}

Running_CL(input_1,"CL_Exp","k","ktil","CL;1",[0,1,10,100,125])
#Running_Limits(input_1,"CL_Exp","k","ktil","CL;1",[0,1,10,100,125])

