#Simulate the different types of Internet traffic such as FTP a TELNET over a network and analyze the throughput

set ns [new Simulator]

# Open trace files
set nf [open out.nam w]
set tf [open out.tr w]
$ns namtrace-all $nf
$ns trace-all $tf

proc finish {} {
    global ns nf tf
    $ns flush-trace
    close $nf; close $tf
    exec nam out.nam &
    exit 0
}

# Create 4 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

# Create links
$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns queue-limit $n0 $n2 50
$ns queue-limit $n1 $n2 50
$ns queue-limit $n2 $n3 50

# Setup TCP connection for FTP
set tcp0 [new Agent/TCP]
set sink0 [new Agent/TCPSink]
$ns attach-agent $n0 $tcp0
$ns attach-agent $n3 $sink0
$ns connect $tcp0 $sink0
$tcp0 set packetSize_ 1000

# Setup FTP traffic
set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

# Setup TCP connection for Telnet
set tcp1 [new Agent/TCP]
set sink1 [new Agent/TCPSink]
$ns attach-agent $n1 $tcp1
$ns attach-agent $n3 $sink1
$ns connect $tcp1 $sink1

# Setup Telnet traffic
set telnet0 [new Application/Telnet]
$telnet0 set interval_ 0.005
$telnet0 attach-agent $tcp1

# Schedule events
$ns at 0.5 "$telnet0 start"
$ns at 4.5 "$telnet0 stop"
$ns at 0.75 "$ftp0 start"
$ns at 4.75 "$ftp0 stop"
$ns at 5.0 "finish"
$ns run
