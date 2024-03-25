# The Scan Analysis
Code necessary to compute exclusion limits on CP sensitive variables.
This code is a series of scripts designed to interpret the outputs from the reconstruction code for *ATLAS/CMS* decay of the top quark particles. 

It is divided into parts:
1. [The Scan Analysis](#the-scan-analysis)

## Exclusion Limits

Contains the relevant code to perform exclusion limits. This step allows the generation of all the relevant statistical information extractable from a given likelihood that work with numbers of events.

##### List of Outputs:                                                                                                                
- Analysis tables containing the limits information for each analysis type (0,1);                                                                 
- Fits from the pseudoexperiments for the null hypothesis for each analysis type (0,1);                                                           
- Fits from the pseudoexperiments for the alternative hypothesis for each analysis type (0,1);                                                   
- TestStat: additional statistical information saved in ```.root``` format for each analysis type (0,1);                                                             
- Histograms used in analysis null hypothesis: *scalar alternative _H hypothesis: pseudoscalar _A*.
