# Exclusion Limits
Code necessary to compute exclusion limits on CP sensitive variables.
This code is a series of scripts designed to interpret the outputs from the reconstruction code for *ATLAS/CMS* decay of the top quark particles. 

It is divided into 2 parts:
1. [The Scan Analysis](#the-scan-analysis)
3. [The Pipeline Results](#the-pipeline-results)

## The Scan Analysis

Contains the relevant codes to perform exclusion plots. Its outputs are moved to the directory ```Pipeline_Results```. This step allows the generation of all the relevant statistical information extractable from a given likelihood that work with numbers of events.

##### List of Outputs:                                                                                                                
- Analysis tables containing the limits information for each analysis type (0,1);                                                                 
- Fits from the pseudoexperiments for the null hypothesis for each analysis type (0,1);                                                           
- Fits from the pseudoexperiments for the alternative hypothesis for each analysis type (0,1);                                                   
- TestStat: additional statistical information saved in ```.root``` format for each analysis type (0,1);                                                
- $\kappa\tilde{\kappa}$ plots for each analysis type (0,1);                                                                                       
- $|\kappa|\alpha$ plots for each analysis type (0,1);                                                                                             
- Histograms used in analysis null hypothesis: *scalar alternative _H hypothesis: pseudoscalar _A*.

## The Pipeline Results

The output of the runs is stored in the folder **Pipeline_Results** for the considered case: Normalized distributions or Number of events for a bin in a given observable $X$. 
Used for setting the final results and plotting professionally all the data extracted in the 2) part of the code.
