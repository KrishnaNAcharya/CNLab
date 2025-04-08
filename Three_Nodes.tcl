#7. Simulate a three nodes point-to-point network with duplex links between them. Set the queue size, vary the bandwidth, and find the number of packets dropped.

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

# Create 3 nodes and connect them
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns queue-limit $n0 $n1 50
$ns queue-limit $n1 $n2 50

# Setup UDP connection
set udp [new Agent/UDP]
set null [new Agent/Null]
$ns attach-agent $n0 $udp
$ns attach-agent $n2 $null
$ns connect $udp $null

# Setup CBR traffic
set cbr [new Application/Traffic/CBR]
$cbr set packetSize_ 500
$cbr set interval_ 0.005
$cbr attach-agent $udp

# Schedule events
$ns at 0.5 "$cbr start"
$ns at 4.5 "$cbr stop"
$ns at 5.0 "finish"

$ns run
