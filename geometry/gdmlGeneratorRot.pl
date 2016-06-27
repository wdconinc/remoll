: # feed this into perl *-*-perl-*-*
    eval 'exec perl -S $0 "$@"'
    if $running_under_some_shell;

use Cwd;
use Cwd 'abs_path';
use File::Find ();
use File::Basename;
use Math::Trig;
use Getopt::Std;

### Declare variables explicitly so "my" not needed
use strict 'vars';
use vars qw($opt_D @numDetPerRing @quartzRad @quartzZ @quartzThickness @quartzHeight @quartzWidth @quartzTiltAngle @lgTiltAngle @refOpeningAngle @refLength @lgLength @zRing @detWidth @pmtWindowSize @wallThick @wtOverlap @range $x $y $z $i $j $k);

###  Get the option flags.
getopts('D:');

if ($#ARGV > -1){
    print STDERR "Unknown arguments specified: @ARGV\nExiting.\n";
    exit;
}

@range = (0,6); #range of rings to draw
@numDetPerRing = (28, 28, 28, 28, 84, 28, 84); # number of detectors per ring
@quartzTiltAngle = (-30, 10, 20, 20, 0, 20, -10); # angle of tilt of quartz with respect to xy-plane
@quartzThickness =  (15, 15, 15, 15, 15, 15, 15); # thickness of quartz piece along z-axis
@quartzHeight =  (50, 100, 60, 40, 120, 100, 120); # height of quartz piece
@wtOverlap = (1.1,1.1,1.1,1.1,1.1,1.1,1.1); # weight factor to avoid overlap.
@quartzRad = (656, 731, 811, 860, 940, 1050, 940); # radial position of quartz ring
for $i($range[0]..$range[1]){
$quartzWidth[$i]= pi*(($quartzRad[$i]+$quartzHeight[$i]/2)*($quartzRad[$i]+$quartzHeight[$i]/2)-($quartzRad[$i]-$quartzHeight[$i]/2)*($quartzRad[$i]-$quartzHeight[$i]/2))/($wtOverlap[$i]*$numDetPerRing[$i]*$quartzHeight[$i]); # calculate azimuthal width of quartz piece
}  
@quartzZ = (0, 400, 800, 1200, 1600, 1900, 2250); # position of the quartz ring along z-axis. Positive implies downstream. 
@lgTiltAngle = (60, 25, 36, 25, 0, -15, -20); # light guide tilt angle with respect to quartz piece. 
@lgLength = (485, 385, 325, 285, 165, 65, 165); # length of light guide
@refOpeningAngle = (19, 19, 19, 19, 19, 19, 19); # opening angle of reflector
@refLength = (35, 35, 35, 35, 35, 35, 35); # length of reflector
@pmtWindowSize= (76.2,76.2,76.2,76.2,76.2,76.2,76.2); # length of one side of square pmt window
@wallThick = (1,1,1,1,1,1,1); #thickness of wall of reflector and light guide

# Start definitions #

open(def, ">", "definitionsNew.xml") or die "cannot open > definitionsNew.xml: $!";
print def "<define>\n\n";

print  def "<matrix name=\"pmtSize\" coldim=\"1\" values=\"$pmtWindowSize[0]
                                                  $pmtWindowSize[1]
                                                  $pmtWindowSize[2]
                                                  $pmtWindowSize[3]
                                                  $pmtWindowSize[4]
                                                  $pmtWindowSize[5]
                                                  $pmtWindowSize[6]\"/>\n\n";

print  def "<matrix name=\"quartzTiltAngle\" coldim=\"1\" values=\"$quartzTiltAngle[0]
                                                  $quartzTiltAngle[1]
                                                  $quartzTiltAngle[2]
                                                  $quartzTiltAngle[3]
                                                  $quartzTiltAngle[4]
                                                  $quartzTiltAngle[5]
                                                  $quartzTiltAngle[6]\"/>\n\n";

print  def "<matrix name=\"lgTiltAngle\" coldim=\"1\" values=\"$lgTiltAngle[0]
                                              $lgTiltAngle[1]
                                              $lgTiltAngle[2]
                                              $lgTiltAngle[3]
                                              $lgTiltAngle[4]
                                              $lgTiltAngle[5]
                                              $lgTiltAngle[6]\"/>\n\n";

print  def "<matrix name=\"lgLength\" coldim=\"1\" values=\"$lgLength[0]
                                           $lgLength[1]
                                           $lgLength[2]
                                           $lgLength[3]
                                           $lgLength[4]
                                           $lgLength[5]
                                           $lgLength[6]\"/>\n\n";

print  def "<matrix name=\"refOpeningAngle\" coldim=\"1\" values=\"$refOpeningAngle[0]
                                                  $refOpeningAngle[1]
                                                  $refOpeningAngle[2]
                                                  $refOpeningAngle[3]
                                                  $refOpeningAngle[4]
                                                  $refOpeningAngle[5]
                                                  $refOpeningAngle[6]\"/>\n\n";

print  def "<matrix name=\"refLength\" coldim=\"1\" values=\"$refLength[0]
                                            $refLength[1]
                                            $refLength[2]
                                            $refLength[3]
                                            $refLength[4]
                                            $refLength[5]
                                            $refLength[6]\"/>\n\n";

print  def "<matrix name=\"refLgWallThick\" coldim=\"1\" values=\"$wallThick[0]
                                                  $wallThick[1]
                                                  $wallThick[2]
                                                  $wallThick[3]
                                                  $wallThick[4]
                                                  $wallThick[5]
                                                  $wallThick[6]\"/>\n\n";


print def "<position name=\"center\"/>\n";
print def "<rotation name=\"identity\"/>\n\n";


print def "<matrix coldim=\"2\" name=\"absLengthQuartz\" values=\"1.54986e-06 263160
						1.77127e-06 250000 
						2.06648e-06 227270 
						2.47978e-06 200000 
						3.09973e-06 131580 
						4.13297e-6 16130 
						4.95956e-6 740 
						5.51063e-6 125
						5.90424e-6 10\"/>\n";
print def "<matrix coldim=\"2\" name=\"rIndexQuartz\" values=\"1.54986e-06 1.45338
						1.77127e-06 1.45536 
						2.06648e-06 1.4581 
						2.47978e-06 1.46239
						3.09973e-06 1.47018 
						4.13297e-6  1.48786
						4.95956e-6  1.50751
						5.51063e-6 1.52422 
						5.90424e-6 1.53842\"/> \n";
print def "<matrix coldim=\"2\" name=\"absLengthAir\" values=\"1.54986e-06 1e+06 
						1.77127e-06 1e+06
						2.06648e-06 1e+06
						2.47978e-06 1e+06 
						3.09973e-06 1e+06 
						4.13297e-6 1e+06 
						4.95956e-6 1e+06 
						5.51063e-6 1e+06 
						5.90424e-6 1e+06\"/> \n";
print def "<matrix coldim=\"2\" name=\"fastComponentAir\" values=\"1.54986e-06 0.1 
						1.77127e-06 0.1 
						2.06648e-06 0.1 
						2.47978e-06 0.1 
						3.09973e-06 0.1 
						4.13297e-06 0.1
						4.95956e-06 0.1 
						5.51063e-6 0.1 
						5.90424e-6 0.1\"/> \n";
print def "<matrix coldim=\"2\" name=\"rIndexAir\" values=\"1.54986e-06 1.000292 
						1.77127e-06 1
                                                2.06648e-06 1.000292 
						2.47978e-06 1.000292 
						3.09973e-06 1.000292
						4.13297e-06 1.000292
						4.95956e-06 1.000292 
						5.51063e-6 1.000292 
						5.90424e-6 1.000292\"/> \n";
print def "<matrix coldim=\"2\" name=\"slowComponentAir\" values=\"1.54986e-06 0.1 
						1.77127e-06 0.1 
						2.06648e-06 0.1
						2.47978e-06 0.1 
						3.09973e-06 0.1 
						4.13297e-06 0.1 
						4.95956e-06 0.1
						5.51063e-6 0.1 
						5.90424e-6 0.1\"/> \n";



## Forming the matrix defining quartz dimensions ##
for $j($range[0]..$range[1]){ 
print  def "<matrix name=\"quartzDim_$j\" coldim=\"3\" values=\"";
for $i(1..$numDetPerRing[$j]){
if($i!=0) {print def "                                              ";} 
print def "$quartzHeight[$j] $quartzWidth[$j] $quartzThickness[$j]";
if($i==$numDetPerRing[$j]){ print def "\"/>\n\n";  }
else { print def "\n";}
}
}
##------------------------------------------------##

## Forming the matrix defining quartz positions ##
for $j($range[0]..$range[1]){ 
print  def "<matrix name=\"quartzPos_$j\" coldim=\"3\" values=\"";
for $i(1..$numDetPerRing[$j]){
$x = $quartzRad[$j];
$y = $i*2*pi/$numDetPerRing[$j];
$z = $quartzZ[$j];
if($i!=0) {print def "                        ";} 
print def "$x $y $z";
if($i==$numDetPerRing[$j]){ print def "\"/>\n\n";  }
else { print def "\n";}
}
} 
##----------------------------------------------##

## Forming the matrix defining quartz rotations ##
for $j($range[0]..$range[1]){ 
print  def "<matrix name=\"quartzRot_$j\" coldim=\"3\" values=\"";
for $i(1..$numDetPerRing[$j]){
if($i!=0) {print def "                       ";} 
print def "quartzPos_$j\[$i,2\] quartzTiltAngle\[$j+1\]*pi/180  0";
if($i==$numDetPerRing[$j]){ print def "\"/>\n\n";  }
else { print def "\n";}
}
}  
##--------------------------------------------------## 
print def "</define>";
close(def) or warn "close failed: $!";

# end definitions #



# start materials #


open(def, ">", "materialsNew.xml") or die "cannot open > materialsNew.xml: $!";
print def "<materials>\n\n";

print def "<material Z=\"82\" name=\"Lead\" state=\"solid\">
      <MEE unit=\"eV\" value=\"823\"/>
      <D unit=\"g/cm3\" value=\"11.35\"/>
      <atom unit=\"g/mole\" value=\"207.19\"/>
</material>
    
<element Z=\"1\" name=\"Hydrogen\">
    <atom unit=\"g/mole\" value=\"1.01\"/>
</element>

<element Z=\"6\" name=\"Carbon\">
    <atom unit=\"g/mole\" value=\"12.011\"/>
</element>

<material name=\"Tyvek\" state=\"solid\">
    <MEE unit=\"eV\" value=\"56.5182975271737\"/>
    <D unit=\"g/cm3\" value=\"0.96\"/>
    <fraction n=\"0.14396693036847\" ref=\"Hydrogen\"/>
    <fraction n=\"0.85603306963153\" ref=\"Carbon\"/>
</material>

<element Z=\"14\" name=\"Silicon\">
    <atom unit=\"g/mole\" value=\"28.09\"/>
</element>

<element Z=\"8\" name=\"Oxygen\">
    <atom unit=\"g/mole\" value=\"16\"/>
</element>

<material name=\"Quartz\" state=\"solid\">
    <property name=\"ABSLENGTH\" ref=\"absLengthQuartz\"/>
    <property name=\"RINDEX\" ref=\"rIndexQuartz\"/>
    <MEE unit=\"eV\" value=\"125.663004061076\"/>
    <D unit=\"g/cm3\" value=\"2.2\"/>
    <fraction n=\"0.467465468463971\" ref=\"Silicon\"/>
    <fraction n=\"0.532534531536029\" ref=\"Oxygen\"/>
</material>

<element Z=\"7\" name=\"Nitrogen\">
    <atom unit=\"g/mole\" value=\"14.01\"/>
</element>

<material name=\"Air\" state=\"gas\">
    <property name=\"ABSLENGTH\" ref=\"absLengthAir\"/>
    <property name=\"FASTCOMPONENT\" ref=\"fastComponentAir\"/>
    <property name=\"RINDEX\" ref=\"rIndexAir\"/>
    <property name=\"SLOWCOMPONENT\" ref=\"slowComponentAir\"/>
    <MEE unit=\"eV\" value=\"85.7030667332999\"/>
    <D unit=\"g/cm3\" value=\"0.00129\"/>
    <fraction n=\"0.7\" ref=\"Nitrogen\"/>
    <fraction n=\"0.3\" ref=\"Oxygen\"/>
</material>

<material Z=\"13\" name=\"Aluminium\" state=\"solid\">
    <MEE unit=\"eV\" value=\"166\"/>
    <D unit=\"g/cm3\" value=\"2.7\"/>
    <atom unit=\"g/mole\" value=\"26.98\"/>
</material>

<material Z=\"19\" name=\"Photocathode\" state=\"solid\">
      <MEE unit=\"eV\" value=\"190\"/>
      <D unit=\"g/cm3\" value=\"5\"/>
      <atom unit=\"g/mole\" value=\"39.0983\"/>
</material>";
 

print def "\n</materials>";
close(def) or warn "close failed: $!";


# end materials #



# start solids #
open(def, ">", "solidsNew.xml") or die "cannot open > solidsNew.xml: $!";
print def "<solids>\n\n";
print def "<box name=\"logicDetSol\" x=\"4000\" y=\"4000\" z=\"4000\" lunit=\"mm\"/>\n\n";
for $j($range[0]..$range[1]){
for $i(1..$numDetPerRing[$j]){
print def "<box name=\"quartzRec_$j\_$i\" x=\"quartzDim_$j\[$i,3\]\" y=\"quartzDim_$j\[$i,2\]\" z=\"quartzDim_$j\[$i,1\]\" lunit= \"mm\" />\n";


if ($lgTiltAngle[$j]>0){
print def "<arb8 name=\"quartzCut_$j\_$i\" v1x=\"quartzDim_$j\[$i,3\]/2\" v1y=\"quartzDim_$j\[$i,2\]/2 \" v4x=\"-quartzDim_$j\[$i,3\]/2\" v4y=\"quartzDim_$j\[$i,2\]/2 \" v3x=\"-quartzDim_$j\[$i,3\]/2 \" v3y=\"-quartzDim_$j\[$i,2\]/2 \" v2x=\"quartzDim_$j\[$i,3\]/2\" v2y=\"-quartzDim_$j\[$i,2\]/2\" v5x=\"quartzDim_$j\[$i,3\]/2\" v5y=\"quartzDim_$j\[$i,2\]/2\" v8x=\"quartzDim_$j\[$i,3\]/2 \" v8y=\"quartzDim_$j\[$i,2\]/2\" v7x=\"quartzDim_$j\[$i,3\]/2 \" v7y=\"-quartzDim_$j\[$i,2\]/2 \" v6x=\"quartzDim_$j\[$i,3\]/2 \" v6y=\"-quartzDim_$j\[$i,2\]/2 \" dz=\"quartzDim_$j\[$i,3\]*tan(lgTiltAngle[$j+1]*pi/180)/2\" lunit= \"mm\"/>\n";
}elsif ($lgTiltAngle[$j]<0){
print def "<arb8 name=\"quartzCut_$j\_$i\" v1x=\"quartzDim_$j\[$i,3\]/2\" v1y=\"quartzDim_$j\[$i,2\]/2 \" v4x=\"-quartzDim_$j\[$i,3\]/2\" v4y=\"quartzDim_$j\[$i,2\]/2 \" v3x=\"-quartzDim_$j\[$i,3\]/2 \" v3y=\"-quartzDim_$j\[$i,2\]/2 \" v2x=\"quartzDim_$j\[$i,3\]/2\" v2y=\"-quartzDim_$j\[$i,2\]/2\" v5x=\"-quartzDim_$j\[$i,3\]/2\" v5y=\"quartzDim_$j\[$i,2\]/2\" v8x=\"-quartzDim_$j\[$i,3\]/2 \" v8y=\"quartzDim_$j\[$i,2\]/2\" v7x=\"-quartzDim_$j\[$i,3\]/2 \" v7y=\"-quartzDim_$j\[$i,2\]/2 \" v6x=\"-quartzDim_$j\[$i,3\]/2 \" v6y=\"-quartzDim_$j\[$i,2\]/2 \" dz=\"quartzDim_$j\[$i,3\]*tan(-lgTiltAngle[$j+1]*pi/180)/2\" lunit= \"mm\"/>\n";
}else{
}


print def "<trd name=\"refOuterSol_$j\_$i\" x1=\"quartzDim_$j\[$i,3\]/(cos(lgTiltAngle[$j+1]*pi/180))\" y1=\"quartzDim_$j\[$i,2\]\" x2=\"2*refLength[$j+1]*tan(refOpeningAngle[$j+1]*pi/180)+quartzDim_$j\[$i,3\]/(cos(lgTiltAngle[$j+1]*pi/180))\" y2=\"2*refLength[$j+1]*tan(refOpeningAngle[$j+1]*pi/180)+quartzDim_$j\[$i,2\]\" z=\"refLength[$j+1]\" lunit=\"mm\" />\n";

print def "<trd name=\"refInnerSol_$j\_$i\" x1=\"quartzDim_$j\[$i,3\]/(cos(lgTiltAngle[$j+1]*pi/180))-refLgWallThick[$j+1]\" y1=\"quartzDim_$j\[$i,2\]-refLgWallThick[$j+1]\" x2=\"2*refLength[$j+1]*tan(refOpeningAngle[$j+1]*pi/180)+quartzDim_$j\[$i,3\]/(cos(lgTiltAngle[$j+1]*pi/180))-refLgWallThick[$j+1]\" y2=\"2*refLength[$j+1]*tan(refOpeningAngle[$j+1]*pi/180)+quartzDim_$j\[$i,2\]-refLgWallThick[$j+1]\" z=\"refLength[$j+1]\" lunit=\"mm\" />\n";

print def "<subtraction name=\"refSol_$j\_$i\">
         <first ref=\"refOuterSol_$j\_$i\"/>
         <second ref=\"refInnerSol_$j\_$i\"/>
         <positionref ref=\"center\"/>
         <rotationref ref=\"identity\"/>
</subtraction>\n"; 

print def "<trd name=\"lgOuterSol_$j\_$i\" x1=\"2*refLength[$j+1]*tan(refOpeningAngle[$j+1]*pi/180)+quartzDim_$j\[$i,3\]/(cos(lgTiltAngle[$j+1]*pi/180))\" y1=\"2*refLength[$j+1]*tan(refOpeningAngle[$j+1]*pi/180)+quartzDim_$j\[$i,2\]\" x2=\"pmtSize[$j+1]\" y2=\"pmtSize[$j+1]\" z=\"lgLength[$j+1]\"/>\n";

print def "<trd name=\"lgInnerSol_$j\_$i\" x1=\"2*refLength[$j+1]*tan(refOpeningAngle[$j+1]*pi/180)+quartzDim_$j\[$i,3\]/(cos(lgTiltAngle[$j+1]*pi/180))-refLgWallThick[$j+1]\" y1=\"2*refLength[$j+1]*tan(refOpeningAngle[$j+1]*pi/180)+quartzDim_$j\[$i,2\]-refLgWallThick[$j+1]\" x2=\"pmtSize[$j+1]-refLgWallThick[$j+1]\" y2=\"pmtSize[$j+1]-refLgWallThick[$j+1]\" z=\"lgLength[$j+1]\"/>\n";

print def "<subtraction name=\"lgSol_$j\_$i\">
         <first ref=\"lgOuterSol_$j\_$i\"/>
         <second ref=\"lgInnerSol_$j\_$i\"/>
         <positionref ref=\"center\"/>
         <rotationref ref=\"identity\"/>
</subtraction>\n"; 

## Forming the logical container for a detector system ##
if ($lgTiltAngle[$j]!=0){
print def "<union name=\"quartzBol_$j\_$i\">
    <first ref=\"quartzRec_$j\_$i\"/>
    <second ref=\"quartzCut_$j\_$i\"/>
    <position name=\"quartzCutPos_$j\_$i\" unit=\"mm\" x=\"0\" y=\"0\" z=\"quartzDim_$j\[$i,1\]/2+quartzDim_$j\[$i,3\]*tan(abs(lgTiltAngle[$j+1]*pi/180))/2\"/>
    <rotation name=\"quartzCutRot_$j\_$i\" unit=\"rad\" x=\"0\" y=\"0\" z=\"0\"/> 
</union>\n"; 
print def "<union name=\"quartzDol_$j\_$i\">
    <first ref=\"quartzBol_$j\_$i\"/>
    <second ref=\"refOuterSol_$j\_$i\"/>
    <position name=\"quartzCutDolPos_$j\_$i\" unit=\"mm\" x=\"refLength[$j+1]*sin(-lgTiltAngle[$j+1]*pi/180)/2\" y=\"0\" z=\"quartzDim_$j\[$i,1\]/2+quartzDim_$j\[$i,3\]*tan(abs(lgTiltAngle[$j+1]*pi/180))/2+refLength[$j+1]*cos(lgTiltAngle[$j+1]*pi/180)/2\"/>
    <rotation name=\"quartzCutDolRot_$j\_$i\" unit=\"rad\" x=\"0\" y=\"-lgTiltAngle[$j+1]*pi/180\" z=\"0\"/> 
</union>\n"; 
} else {
print def "<union name=\"quartzDol_$j\_$i\">
    <first ref=\"quartzRec_$j\_$i\"/>
    <second ref=\"refOuterSol_$j\_$i\"/>
    <position name=\"quartzCutDolPos_$j\_$i\" unit=\"mm\" x=\"refLength[$j+1]*sin(-lgTiltAngle[$j+1]*pi/180)/2\" y=\"\" z=\"quartzDim_$j\[$i,1\]/2+quartzDim_$j\[$i,3\]*tan(abs(lgTiltAngle[$j+1]*pi/180))/2+refLength[$j+1]*cos(lgTiltAngle[$j+1]*pi/180)/2\"/>
    <rotation name=\"quartzCutDolRot_$j\_$i\" unit=\"rad\" x=\"0\" y=\"-lgTiltAngle[$j+1]*pi/180\" z=\"0\"/> 
</union>\n"; 
}

print def "<union name=\"quartzSol_$j\_$i\">
    <first ref=\"quartzDol_$j\_$i\"/>
    <second ref=\"lgOuterSol_$j\_$i\"/>
    <position name=\"quartzCutSolPos_$j\_$i\" unit=\"mm\" x=\"(2*refLength[$j+1]+1*lgLength[$j+1])*sin(-lgTiltAngle[$j+1]*pi/180)/2\" y=\"0\" z=\"quartzDim_$j\[$i,1\]/2+quartzDim_$j\[$i,3\]*tan(abs(lgTiltAngle[$j+1]*pi/180))/2+(2*refLength[$j+1]+1*lgLength[$j+1])*cos(lgTiltAngle[$j+1]*pi/180)/2\"/>
    <rotation name=\"quartzCutSolRot_$j\_$i\" unit=\"rad\" x=\"0\" y=\"-lgTiltAngle[$j+1]*pi/180\" z=\"0\"/> 
</union>\n"; 

## -------------------------------------------------- ##



} 
}
print def "\n</solids>";
close(def) or warn "close failed: $!";

# end solids #


# start detector #

open(def, ">", "detectorNew.gdml") or die "cannot open > detectorNew.gdml: $!";
print def "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n
<!DOCTYPE gdml [
	<!ENTITY definitions SYSTEM \"definitionsNew.xml\">
	<!ENTITY materials SYSTEM \"materialsNew.xml\"> 
	<!ENTITY solids SYSTEM \"solidsNew.xml\"> 
]> \n
<gdml xmlns:gdml=\"http://cern.ch/2001/Schemas/GDML\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"schema/gdml.xsd\">\n
&definitions;
&materials; 
&solids;\n
<structure>\n";

for $j($range[0]..$range[1]){
for $i(1..$numDetPerRing[$j]){
$k= 1000+$j*100+$i;

if ($lgTiltAngle[$j]!=0){
print def "<volume name=\"detVol_$j\_$i\">
         <materialref ref=\"Quartz\"/>
         <solidref ref=\"quartzBol_$j\_$i\"/> 
         <auxiliary auxtype=\"Color\" auxvalue=\"red\"/> 
 	 <auxiliary auxtype=\"SensDet\" auxvalue=\"planeDet\"/> 
	 <auxiliary auxtype=\"DetNo\" auxvalue=\"$k\"/>  
</volume>\n";
} else {
print def "<volume name=\"detVol_$j\_$i\">
         <materialref ref=\"Quartz\"/>
         <solidref ref=\"quartzRec_$j\_$i\"/>
         <auxiliary auxtype=\"Color\" auxvalue=\"red\"/> 
 	 <auxiliary auxtype=\"SensDet\" auxvalue=\"planeDet\"/> 
	 <auxiliary auxtype=\"DetNo\" auxvalue=\"$k\"/>  
</volume>\n";
}

print def "<volume name=\"refVol_$j\_$i\">
           <materialref ref=\"Aluminium\"/>
           <solidref ref=\"refSol_$j\_$i\"/>
           <auxiliary auxtype=\"Color\" auxvalue=\"green\"/>  
</volume>\n";

print def "<volume name=\"lgVol_$j\_$i\">
           <materialref ref=\"Aluminium\"/>
           <solidref ref=\"lgSol_$j\_$i\"/>           
</volume>\n";



print def "<volume name=\"quartzVol_$j\_$i\"> 
	<materialref ref=\"Air\"/>
	<solidref ref=\"quartzSol_$j\_$i\"/> 
        <physvol name=\"det_$j\_$i\">
			<volumeref ref=\"detVol_$j\_$i\"/>
			<position name=\"detPos_$j\_$i\" unit=\"mm\" x=\"0\" y=\"0\" z=\"0\"/>
			<rotation name=\"detRot_$j\_$i\" unit=\"rad\" x=\"0\" y=\"0\" z=\"0\"/>
         </physvol>
            <physvol name=\"ref_$j\_$i\">
			<volumeref ref=\"refVol_$j\_$i\"/>
			<position name=\"refPos_$j\_$i\" unit=\"mm\" x=\"refLength[$j+1]*sin(-lgTiltAngle[$j+1]*pi/180)/2\" y=\"0\" z=\"quartzDim_$j\[$i,1\]/2+quartzDim_$j\[$i,3\]*tan(abs(lgTiltAngle[$j+1]*pi/180))/2+refLength[$j+1]*cos(lgTiltAngle[$j+1]*pi/180)/2\"/>
			<rotation name=\"refRot_$j\_$i\" unit=\"rad\" x=\"0\" y=\"lgTiltAngle[$j+1]*pi/180\" z=\"0\"/>
         </physvol> 
          <physvol name=\"lg_$j\_$i\">
			<volumeref ref=\"lgVol_$j\_$i\"/>
			<position name=\"lgPos_$j\_$i\" unit=\"mm\" x=\"(2*refLength[$j+1]+1*lgLength[$j+1])*sin(-lgTiltAngle[$j+1]*pi/180)/2\" y=\"0\" z=\"quartzDim_$j\[$i,1\]/2+quartzDim_$j\[$i,3\]*tan(abs(lgTiltAngle[$j+1]*pi/180))/2+(2*refLength[$j+1]+1*lgLength[$j+1])*cos(lgTiltAngle[$j+1]*pi/180)/2\"/>
			<rotation name=\"lgRot_$j\_$i\" unit=\"rad\" x=\"0\" y=\"lgTiltAngle[$j+1]*pi/180\" z=\"0\"/>
         </physvol> 
</volume>\n";


} 
}



print def "<volume name=\"logicDetVol\"> 
	<materialref ref=\"Air\"/>
	<solidref ref=\"logicDetSol\"/>\n";
for $j($range[0]..$range[1]){
for $i(1..$numDetPerRing[$j]){
print def "<physvol name=\"quartzDet_$j\_$i\">
			<volumeref ref=\"quartzVol_$j\_$i\"/>
			<position name=\"quartzPos_$j\_$i\" unit=\"mm\" x=\"quartzPos_$j\[$i,3\]\" y=\"quartzPos_$j\[$i,1\]*sin(quartzPos_$j\[$i,2\])\" z=\"quartzPos_$j\[$i,1\]*cos(quartzPos_$j\[$i,2\])\"/>
			<rotation name=\"quartzRot_$j\_$i\" unit=\"rad\" x=\"quartzRot_$j\[$i,1\]\" y=\"quartzRot_$j\[$i,2\]\" z=\"quartzRot_$j\[$i,3\]\"/>
</physvol> \n";
} 
}
print def "</volume>";



print def "\n</structure>\n";


# end detector #

print def "<setup name=\"logicDet\" version=\"1.0\">
	<world ref=\"logicDetVol\"/>
</setup>\n
</gdml>";

close(def) or warn "close failed: $!";




