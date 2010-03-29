v 20081231 1
C 40000 40000 0 0 0 title-B.sym
C 41200 48200 1 0 0 connector3-1.sym
{
T 43000 49100 5 10 0 0 0 0 1
device=CONNECTOR_3
T 41200 49300 5 10 1 1 0 0 1
refdes=CONN1
T 41200 48200 5 10 0 0 0 0 1
footprint=JUMPER3
}
C 51500 44900 1 0 1 connector3-1.sym
{
T 49700 45800 5 10 0 0 0 6 1
device=CONNECTOR_3
T 51500 46000 5 10 1 1 0 6 1
refdes=CONN2
T 51500 44900 5 10 0 0 0 0 1
footprint=JUMPER3
}
C 46000 43600 1 0 0 max232-1.sym
{
T 46300 46650 5 10 0 0 0 0 1
device=MAX232
T 48300 46500 5 10 1 1 0 6 1
refdes=U1
T 46300 46850 5 10 0 0 0 0 1
footprint=DIP16
}
C 45100 46200 1 270 0 capacitor-2.sym
{
T 45800 46000 5 10 0 0 270 0 1
device=POLARIZED_CAPACITOR
T 45600 46000 5 10 1 1 270 0 1
refdes=C2
T 46000 46000 5 10 0 0 270 0 1
symversion=0.1
T 45100 46200 5 10 0 0 0 0 1
footprint=JUMPER2
}
C 45100 45100 1 270 0 capacitor-2.sym
{
T 45800 44900 5 10 0 0 270 0 1
device=POLARIZED_CAPACITOR
T 45600 44900 5 10 1 1 270 0 1
refdes=C3
T 46000 44900 5 10 0 0 270 0 1
symversion=0.1
T 45100 45100 5 10 0 0 0 0 1
footprint=JUMPER2
}
C 44100 46600 1 270 0 capacitor-2.sym
{
T 44800 46400 5 10 0 0 270 0 1
device=POLARIZED_CAPACITOR
T 44600 46400 5 10 1 1 270 0 1
refdes=C1
T 45000 46400 5 10 0 0 270 0 1
symversion=0.1
T 44100 46600 5 10 0 0 0 0 1
footprint=JUMPER2
}
C 45400 43800 1 270 0 capacitor-2.sym
{
T 46100 43600 5 10 0 0 270 0 1
device=POLARIZED_CAPACITOR
T 45900 43600 5 10 1 1 270 0 1
refdes=C4
T 46300 43600 5 10 0 0 270 0 1
symversion=0.1
T 45400 43800 5 10 0 0 0 0 1
footprint=JUMPER2
}
N 45300 46200 46000 46200 4
N 46000 46200 46000 46000 4
N 45300 45300 46000 45300 4
N 46000 45300 46000 45400 4
N 45300 45100 46000 45100 4
N 46000 44800 45800 44800 4
N 45800 44800 45800 44200 4
N 45800 44200 45300 44200 4
N 44300 45700 46000 45700 4
N 44300 46600 45000 46600 4
{
T 44300 46600 5 10 1 1 0 0 1
netname=GND
}
N 46000 44500 45600 44500 4
N 45600 44500 45600 43800 4
N 45600 42900 46900 42900 4
{
T 45600 42900 5 10 1 1 0 0 1
netname=GND
}
N 42900 49000 43500 49000 4
{
T 43100 49000 5 10 1 1 0 0 1
netname=GND
}
N 42900 48700 43500 48700 4
{
T 43100 48700 5 10 1 1 0 0 1
netname=Rx-TTL
}
N 42900 48400 43500 48400 4
{
T 43100 48400 5 10 1 1 0 0 1
netname=Tx-TTL
}
N 48600 44800 48900 44800 4
{
T 48600 44800 5 10 1 1 0 0 1
netname=Rx-TTL
}
N 48600 44500 48900 44500 4
{
T 48600 44500 5 10 1 1 0 0 1
netname=Tx-TTL
}
N 49100 45700 49800 45700 4
{
T 49100 45700 5 10 1 1 0 0 1
netname=GND
}
N 49200 45100 49800 45100 4
{
T 49200 45100 5 10 1 1 0 0 1
netname=Tx-232
}
N 48900 45400 49800 45400 4
{
T 49200 45400 5 10 1 1 0 0 1
netname=Rx-232
}
N 48900 45400 48900 45100 4
N 48900 45100 48600 45100 4
N 48600 45400 48800 45400 4
N 48800 45400 48800 45300 4
N 48800 45300 49200 45300 4
N 49200 45300 49200 45100 4
C 50200 46200 1 90 0 connector2-1.sym
{
T 49200 46400 5 10 0 0 90 0 1
device=CONNECTOR_2
T 49400 46200 5 10 1 1 90 0 1
refdes=CONN3
T 50200 46200 5 10 0 0 0 0 1
footprint=JUMPER2
}
N 50000 47900 50900 47900 4
{
T 50000 47900 5 10 1 1 0 0 1
netname=GND
}
N 49700 47900 48900 47900 4
{
T 49700 47900 5 10 1 1 0 0 1
netname=Vcc
}
T 54000 40100 9 10 1 0 0 0 1
the
T 50000 40100 9 10 1 0 0 0 1
1
T 51500 40100 9 10 1 0 0 0 1
1
T 54000 40400 9 10 1 0 0 0 1
mar 2010
T 50000 40400 9 10 1 0 0 0 1
max232-board
T 50100 41000 9 10 1 0 0 0 1
rs232 to ttl converter board
