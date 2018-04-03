set ns [new Simulator]

$ns color 1 Red
$ns color 2 Blue

set nf [open square.nam w]
$ns namtrace-all $nf

proc finish {} {
	global ns nf
	$ns flush-trace
	close $nf
	exec nam square.nam &
	exit 0
}

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n3 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link $n2 $n0 1Mb 10ms DropTail

$ns duplex-link-op $n0 $n2 orient right
$ns duplex-link-op $n0 $n1 orient down
$ns duplex-link-op $n1 $n3 orient right
$ns duplex-link-op $n2 $n3 orient down

set tcp0 [new Agent/TCP]
$ns attach-agent $n0 $tcp0
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $sink1
$ns connect $tcp0 $sink1
$tcp0 set fid_ 1

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ftp0 set type_ FTP

set tcp2 [new Agent/TCP]
$ns attach-agent $n2 $tcp2
set sink3 [new Agent/TCPSink]
$ns attach-agent $n3 $sink3
$ns connect $tcp2 $sink3
$tcp2 set fid_ 2

set ftp2 [new Application/FTP]
$ftp2 attach-agent $tcp2
$ftp2 set type_ FTP

$ns at 0.1 "$ftp0 start"
$ns at 1.0 "$ftp2 start"
$ns at 4.0 "$ftp2 stop"
$ns at 4.5 "$ftp0 stop"

$ns rtmodel-at 2.8 down $n0 $n1
$ns rtmodel-at 3.0 up $n0 $n1

$ns at 4.6 "$ns detach-agent $n0 $tcp0 ; $ns detach-agent $n1 $sink1"
$ns at 4.7 "$ns detach-agent $n2 $tcp2 ; $ns detach-agent $n3 $sink3"

$ns at 5.0 "finish"
$ns run