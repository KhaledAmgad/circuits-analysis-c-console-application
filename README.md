# circuits-analysis-c-console-application

==>please dont forget (F (capital) in the end of the inputs)
==>R,Vs,L1,C1,Cs (all start in capital not small)
==>R1->R2->R3->R4
==>C1->C2->C3->C4
==>L1->L2->L3->L4
==> Vs Node 1(+)  Node 2(-)
==> Cs Node 1(+)  Node 2(-) 
Vs and Cs With no Numbers

*input File*
//////////////
w   (omiga)
Vs N1 N2 Magnitude phase  (voltage)
R1 N1 N2 Magnitude        (resistance)
C1 N1 N2 Magnitude of C   (capacitor)
L1 N1 N2 Magintude of H   (inductor)
Cs N1 N2 Magnitude phase  (current source) 
F
/////////////
*Output File*
//////////////////////
V(Node) Magnitude phase
I(Node To Node) Magnitude phase
//////////////////////



EXAMPLE
************************************
*input File*
//////////////
4
Vs 1 0 50 0
R1 1 3 4
R2 1 2 8
L1 2 0 3
C1 3 0 .0833333
F
///////////



*Output File*
//////////////////////
V(1) 50 -0                    Node Voltage from 1---> 0
V(2) 49.163 4.66686           Node Voltage from 2---> 0
V(3) 50.04 -2.29061           Node Voltage from 3---> 0                            
I(1 0) -0 -180                Current from Node 1 to Node 0
I(1 3) 0.5 90                 Current from Node 1 to Node 3
I(1 2) 0.515388 -75.9638      Current from Node 1 to Node 2
I(2 0) 0.541464 -77.7385      Current from Node 2 to Node 0
I(3 0) 0.555691 85.8002       Current from Node 3 to Node 0
////////////////////////////
********************************************




