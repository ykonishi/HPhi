#!/bin/sh -e

mkdir -p lobcg_kondogc_chain/
cd lobcg_kondogc_chain

cat > stan.in <<EOF
L = 4
model = "KondoGC"
method = "CG"
lattice = "chain"
t = 1.0
J = 4.0
exct = 3
EOF

${MPIRUN} ../../src/HPhi -s stan.in

# Check value

cat > reference.dat <<EOF
 0
  -12.6776213781764113 
  0.1072445462409942 
  0.0000000000000000 

 1
  -10.5371064976052171 
  0.5540651534011468 
  0.0822952996955437 

 2
  -10.5371064976049116 
  0.9181777883286992 
  -0.0977988871353539 
EOF
paste output/zvo_energy.dat reference.dat > paste.dat
diff=`awk 'BEGIN{diff=0.0} $1=="Energy"{diff+=sqrt(($2-$3)**2)} END{printf "%8.6f", diff}' paste.dat`
test "${diff}" = "0.000000"

exit $?