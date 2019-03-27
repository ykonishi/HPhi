#!/bin/sh -e

mkdir -p te_pulse_hubbard_square/
cd te_pulse_hubbard_square
cp -rf ../te_ac_hubbard_square/output .

cat > stan.in <<EOF
model = "Hubbard"
method = "Time-Evolution"
lattice = "square"
a0w = 3
a0l = 0
a1w = 0
a1l = 3
t = 1.0
U = 10.0
nelec = 8
2Sz = 0
lanczos_max = 40
initial_iv = 1
EigenvecIO = "in"
dt = 0.01
tshift = 0.2
freq = 10.0
PumpType = "Pulse Laser"
VecPotW = 0.5
VecPotL = 0.5
EOF

${MPIRUN} ../../src/HPhi -s stan.in

# Check value: Flct
cat > reference.dat <<EOF
0.0000000000000000 8.0000000000000036 64.0000000000000284 0.2592919779062002 0.2991789411194021 0.0000000000000000 0.0000000000000000 0
0.0100000000000000 7.9999999999999964 63.9999999999999716 0.2592922288544937 0.2991793131588122 0.0000000000000000 0.0000000000000000 1
0.0200000000000000 8.0000000000000018 64.0000000000000142 0.2592928289583783 0.2991802155854233 0.0000000000000000 0.0000000000000000 2
0.0300000000000000 7.9999999999999982 63.9999999999999858 0.2592930212802234 0.2991806052719527 0.0000000000000000 0.0000000000000000 3
0.0400000000000000 8.0000000000000036 64.0000000000000284 0.2592915304356335 0.2991787332831348 0.0000000000000000 0.0000000000000000 4
0.0500000000000000 8.0000000000000036 64.0000000000000284 0.2592869054537295 0.2991726235654121 0.0000000000000000 0.0000000000000000 5
0.0600000000000000 8.0000000000000018 64.0000000000000142 0.2592783243010548 0.2991611822928432 0.0000000000000000 0.0000000000000000 6
0.0700000000000000 7.9999999999999982 63.9999999999999858 0.2592669579927529 0.2991460662250287 0.0000000000000000 0.0000000000000000 7
0.0800000000000000 7.9999999999999982 63.9999999999999858 0.2592578817458462 0.2991342845357214 0.0000000000000000 0.0000000000000000 8
0.0900000000000000 7.9999999999999982 63.9999999999999858 0.2592623492693152 0.2991412722217016 0.0000000000000000 0.0000000000000000 9
0.1000000000000000 8.0000000000000036 64.0000000000000284 0.2593000386192626 0.2991938902588963 0.0000000000000000 0.0000000000000000 10
0.1100000000000000 7.9999999999999973 63.9999999999999787 0.2594006835740121 0.2993325487714577 0.0000000000000000 0.0000000000000000 11
0.1200000000000000 7.9999999999999982 63.9999999999999858 0.2596043889824345 0.2996115062730577 0.0000000000000000 0.0000000000000000 12
0.1300000000000000 7.9999999999999982 63.9999999999999858 0.2599599549039771 0.3000964536846789 0.0000000000000000 0.0000000000000000 13
0.1400000000000000 7.9999999999999973 63.9999999999999787 0.2605207396244225 0.3008587870760020 0.0000000000000000 0.0000000000000000 14
0.1500000000000000 7.9999999999999991 63.9999999999999929 0.2613379712429399 0.3019664868571283 0.0000000000000000 0.0000000000000000 15
0.1600000000000000 8.0000000000000000 64.0000000000000000 0.2624519245641393 0.3034721786116414 0.0000000000000000 0.0000000000000000 16
0.1700000000000000 8.0000000000000000 64.0000000000000000 0.2638819368707119 0.3053996520249261 0.0000000000000000 0.0000000000000000 17
0.1800000000000000 8.0000000000000000 64.0000000000000000 0.2656167479834676 0.3077307598206599 0.0000000000000000 0.0000000000000000 18
0.1900000000000000 8.0000000000000000 64.0000000000000000 0.2676070122079303 0.3103951097097639 0.0000000000000000 0.0000000000000000 19
0.2000000000000000 8.0000000000000018 64.0000000000000142 0.2697619319135276 0.3132651806187539 0.0000000000000000 0.0000000000000000 20
0.2100000000000000 8.0000000000000000 64.0000000000000000 0.2719516997836575 0.3161592865825505 0.0000000000000000 0.0000000000000000 21
0.2200000000000000 8.0000000000000036 64.0000000000000284 0.2740167381512362 0.3188540145815267 0.0000000000000000 0.0000000000000000 22
0.2300000000000000 8.0000000000000000 64.0000000000000000 0.2757835983854954 0.3211062870063000 0.0000000000000000 0.0000000000000000 23
0.2400000000000000 7.9999999999999982 63.9999999999999858 0.2770859729475950 0.3226831554127044 0.0000000000000000 0.0000000000000000 24
0.2500000000000000 8.0000000000000018 64.0000000000000142 0.2777878794146487 0.3233952303863094 0.0000000000000000 0.0000000000000000 25
0.2600000000000000 8.0000000000000000 64.0000000000000000 0.2778051179632188 0.3231279775264734 0.0000000000000000 0.0000000000000000 26
0.2700000000000000 7.9999999999999982 63.9999999999999858 0.2771209785852887 0.3218646958110790 0.0000000000000000 0.0000000000000000 27
0.2800000000000000 8.0000000000000036 64.0000000000000284 0.2757930659749401 0.3196962577474041 0.0000000000000000 0.0000000000000000 28
0.2900000000000000 8.0000000000000018 64.0000000000000142 0.2739498525604839 0.3168154256533352 0.0000000000000000 0.0000000000000000 29
0.3000000000000000 8.0000000000000018 64.0000000000000142 0.2717776694933994 0.3134969337768028 0.0000000000000000 0.0000000000000000 30
0.3100000000000000 8.0000000000000036 64.0000000000000284 0.2695006754667000 0.3100674364072523 0.0000000000000000 0.0000000000000000 31
0.3200000000000000 7.9999999999999982 63.9999999999999858 0.2673574111687673 0.3068710020053910 0.0000000000000000 0.0000000000000000 32
0.3300000000000000 8.0000000000000000 64.0000000000000000 0.2655776761376735 0.3042358154554851 0.0000000000000000 0.0000000000000000 33
0.3400000000000000 8.0000000000000000 64.0000000000000000 0.2643628054321712 0.3024464764601493 0.0000000000000000 0.0000000000000000 34
0.3500000000000000 8.0000000000000018 64.0000000000000142 0.2638713206826958 0.3017244202783423 0.0000000000000000 0.0000000000000000 35
0.3600000000000000 8.0000000000000018 64.0000000000000142 0.2642107466316556 0.3022171787886390 0.0000000000000000 0.0000000000000000 36
0.3700000000000000 8.0000000000000000 64.0000000000000000 0.2654353784303364 0.3039958343007569 0.0000000000000000 0.0000000000000000 37
0.3800000000000000 7.9999999999999982 63.9999999999999858 0.2675490762344191 0.3070591992859426 0.0000000000000000 0.0000000000000000 38
0.3900000000000000 7.9999999999999982 63.9999999999999858 0.2705117645645285 0.3113428980203080 0.0000000000000000 0.0000000000000000 39
EOF
sed -e "1d" output/Flct.dat > flct.dat
paste flct.dat reference.dat > paste1.dat
diff=`awk 'BEGIN{diff=0.0} {diff+=sqrt(($2-$10)*($2-$10))} END{printf "%8.6f", diff/NR}' paste1.dat`
echo "Diff N : " ${diff}
test "${diff}" = "0.000000"
diff=`awk 'BEGIN{diff=0.0} {diff+=sqrt(($3-$11)*($3-$11))} END{printf "%8.6f", diff/NR}' paste1.dat`
echo "Diff N^2 : " ${diff}
test "${diff}" = "0.000000"
diff=`awk 'BEGIN{diff=0.0} {diff+=sqrt(($4-$12)*($4-$12))} END{printf "%8.6f", diff/NR}' paste1.dat`
echo "Diff D : " ${diff}
test "${diff}" = "0.000000"
diff=`awk 'BEGIN{diff=0.0} {diff+=sqrt(($5-$13)*($5-$13))} END{printf "%8.6f", diff/NR}' paste1.dat`
echo "Diff D^2 : " ${diff}
test "${diff}" = "0.000000"
diff=`awk 'BEGIN{diff=0.0} {diff+=sqrt(($6-$14)*($6-$14))} END{printf "%8.6f", diff/NR}' paste1.dat`
echo "Diff Sz : " ${diff}
test "${diff}" = "0.000000"
diff=`awk 'BEGIN{diff=0.0} {diff+=sqrt(($7-$15)*($7-$15))} END{printf "%8.6f", diff/NR}' paste1.dat`
echo "Diff Sz^2 : " ${diff}
test "${diff}" = "0.000000"

exit $?
