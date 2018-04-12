set val(chan) Channel/WirelessChannel ;# channel type
set val(prop) Propagation/TwoRayGround ;# radio-propagation model
set val(netif) Phy/WirelessPhy ;# network interface type
set val(mac) Mac/802_11 ;# MAC type
set val(ifq) Queue/DropTail/PriQueue ;# interface queue type
set val(ll) LL ;# link layer type
set val(ant) Antenna/OmniAntenna ;# antenna model
set val(ifqlen) 50 ;# max packet in ifq
set val(nn) 10 ;# number of mobilenodes
set val(rp) DSDV ;# routing protocol
# ======================================================================
# Main Program
# ======================================================================
#
# Initialize Global Variables
#
set ns_ [new Simulator]
set tracefd [open l9q1.tr w]
$ns_ trace-all $tracefd
set namtrace [open out9.nam w]
$ns_ namtrace-all-wireless $namtrace 100 100
# set up topography object
set topo [new Topography]
$topo load_flatgrid 100 100
#
# Create God
#
create-god $val(nn)
#
# Create the specified number of mobilenodes [$val(nn)] and "attach" them
# to the channel.
# Here two nodes are created : node(0) and node(1)
# configure node
$ns_ node-config -adhocRouting $val(rp) \
-llType $val(ll) \
-macType $val(mac) \
-ifqType $val(ifq) \
-ifqLen $val(ifqlen) \
-antType $val(ant) \
-propType $val(prop) \
-phyType $val(netif) \
-channelType $val(chan) \
-topoInstance $topo \
-agentTrace ON \
-routerTrace ON \
-macTrace OFF \
-movementTrace OFF
for {set i 0} {$i < $val(nn) } {incr i} {
set node_($i) [$ns_ node]
$node_($i) random-motion 0 ;# disable random motion
}
#
# Provide initial (X,Y, for now Z=0) co-ordinates for mobilenodes
#
$node_(4) set X_ 5.0
$node_(4) set Y_ 2.0
$node_(4) set Z_ 0.0
$node_(5) set X_ 10.0
$node_(5) set Y_ 2.0
$node_(5) set Z_ 0.0
$node_(6) set X_ 15.0
$node_(6) set Y_ 2.0
$node_(6) set Z_ 0.0
$node_(7) set X_ 20.0
$node_(7) set Y_ 2.0
$node_(7) set Z_ 0.0
$node_(1) set X_ 7.0
$node_(1) set Y_ 4.0
$node_(1) set Z_ 0.0
$node_(2) set X_ 12.0
$node_(2) set Y_ 4.0
$node_(2) set Z_ 0.0
$node_(3) set X_ 17.0
$node_(3) set Y_ 4.0
$node_(3) set Z_ 0.0
$node_(0) set X_ 12.0
$node_(0) set Y_ 7.0
$node_(0) set Z_ 0.0
$ns_ at 5.0 "$node_(4) setdest 8.0 4.0 5.0"
$ns_ at 5.0 "$node_(5) setdest 26.0 4.0 6.0"
$ns_ at 5.0 "$node_(6) setdest 46.0 4.0 7.0"
$ns_ at 5.0 "$node_(7) setdest 65.0 4.0 8.0"
$ns_ at 5.0 "$node_(1) setdest 17.0 25.0 9.0"
$ns_ at 5.0 "$node_(2) setdest 37.0 25.0 10.0"
$ns_ at 5.0 "$node_(3) setdest 56.0 25.0 11.0"
$ns_ at 5.0 "$node_(0) setdest 37.0 50.0 12.0"
$ns_ at 5.0 "$node_(8) setdest 82.0 12.0 15.0"
$ns_ at 5.0 "$node_(9) setdest 99.0 12.0 16.0"
# Setup traffic flow between nodes
# TCP connections between node_(4) and node_(1)
set tcp [new Agent/TCP]
$tcp set class_ 2
set sink [new Agent/TCPSink]
$ns_ attach-agent $node_(0) $tcp
$ns_ attach-agent $node_(2) $sink
$ns_ connect $tcp $sink

set ftp [new Application/FTP]
$ftp attach-agent $tcp
$ns_ at 10.0 "$ftp start"

#Setup a UDP connection
set udp [new Agent/UDP]
$ns_ attach-agent $node_(0) $udp
set null [new Agent/Null]
$ns_ attach-agent $node_(1) $null
$ns_ connect $udp $null
#$udp set fid_ 2

#Setup a CBR over UDP connection
set cbr [new Application/Traffic/CBR]
$cbr attach-agent $udp
$cbr set type_ CBR
$cbr set packet_size_ 1000
$cbr set rate_ 1mb
$cbr set random_ false


$ns_ at 6.0 "$cbr start"
$ns_ at 30.0 "$cbr stop"
#
# Tell nodes when the simulation ends
#

for {set i 0} {$i < $val(nn) } {incr i} {
$ns_ at 150.0 "$node_($i) reset";
}
$ns_ at 150.0 "stop"
$ns_ at 150.01 "puts \"NS EXITING...\" ; $ns_ halt"
proc stop {} {
global ns_ tracefd
$ns_ flush-trace
close $tracefd
exec nam out.nam &
}
puts "Starting Simulation..."
$ns_ run
