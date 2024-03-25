#!/bin/bash

#rm -fR Figs/*.root
rm -fR Figs/*.pdf

root -q -b ttH_GenRecExp.C
#open Figs/*.pdf

# Case 0-5 [Spin0-]
cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_minus_0gev_case0
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_minus_1gev_case1
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_minus_10gev_case2
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_minus_100gev_case3
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_minus_125gev_case4
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_minus_1000gev_case5

# Case 6-11 [Spin0+]
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_plus_0gev_case6
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_plus_1gev_case7
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_plus_10gev_case8
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_plus_100gev_case9
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_plus_125gev_case10
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin0_plus_1000gev_case11

# Case 12-16 [Spin1-]
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin1_minus_0gev_case12
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin1_minus_1gev_case13
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin1_minus_10gev_case14
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin1_minus_100gev_case15
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin1_minus_1000gev_case16

# Case 17-21 [Spin1+]
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin1_plus_0gev_case17
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin1_plus_1gev_case18
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin1_plus_10gev_case19
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin1_plus_100gev_case20
#cp -R Figs/ ~/Desktop/GenRecExp_Spin1Plus0Gev/dm_simp_spin1_plus_1000gev_case21