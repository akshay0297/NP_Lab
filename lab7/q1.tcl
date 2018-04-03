set ns [new Simulator]
$ns color 1 Red
$ns color 2 Cyan

set nf [open output.nam w]
$ns namtrace-all $nf

proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam output.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]
set n4 [$ns node]

$ns duplex-link $n0 $n4 2Mb 10ms DropTail
$ns duplex-link $n1 $n4 2Mb 10ms DropTail
$ns duplex-link $n2 $n4 1.7Mb 20ms DropTail
$ns duplex-link $n3 $n4 1.7Mb 20ms DropTail

$ns queue-limit $n4 $n3 10
$ns queue-limit $n4 $n2 10

$ns duplex-link-op $n0 $n4 orient right-down
$ns duplex-link-op $n1 $n4 orient right-up
$ns duplex-link-op $n2 $n4 orient left-up
$ns duplex-link-op $n3 $n4 orient left-down

#$ns duplex-link-op $n2 $n3 queuePos 0.5

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0

set null1 [new Agent/Null]
$ns attach-agent $n3 $null1
$ns connect $udp0 $null1 

$udp0 set fid_ 1

set udp1 [new Agent/UDP]
$ns attach-agent $n1 $udp1

set null2 [new Agent/Null]
$ns attach-agent $n2 $null2
$ns connect $udp1 $null2 

$udp1 set fid_ 2

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$cbr0 set type_ CBR
$cbr0 set packet_size_ 1000
$cbr0 set rate_ 1mb
$cbr0 set random_ false

set cbr1 [new Application/Traffic/CBR]
$cbr1 attach-agent $udp1
$cbr1 set type_ CBR
$cbr1 set packet_size_ 1000
$cbr1 set rate_ 1mb
$cbr1 set random_ false



$ns at 0.0 "$cbr0 start"
$ns at 0.5 "$cbr1 start"
$ns at 9.0 "$cbr1 stop"
$ns at 9.5 "$cbr0 stop"

$ns at 10.0 "finish"

puts "CBR packet size = [$cbr0 set packet_size_]"
puts "CBR interval = [$cbr0 set interval_]"

puts "CBR packet size = [$cbr1 set packet_size_]"
puts "CBR interval = [$cbr1 set interval_]"

$ns run
