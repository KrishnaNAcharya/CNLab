set ns [new Simulator]

# Open trace files
set nf [open out.nam w]
$ns namtrace-all $nf

proc finish {} {
    global ns nf
    $ns flush-trace
    close $nf
    exec nam out.nam &
    exit 0
}

# Create 3 nodes
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

# Create links
$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 1Mb 10ms DropTail

# Define ping receive behavior
Agent/Ping instproc recv {from rtt} {
    $self instvar node_
    puts "node [$node_ id] received ping answer from $from with round-trip-time $rtt ms."
}

# Setup Ping agents
set p0 [new Agent/Ping]
set p1 [new Agent/Ping]
$ns attach-agent $n0 $p0
$ns attach-agent $n2 $p1
$ns connect $p0 $p1

# Schedule events
$ns at 0.2 "$p0 send"
$ns at 0.4 "$p1 send"
$ns at 0.6 "$p0 send"
$ns at 0.6 "$p1 send"
$ns at 1.0 "finish"
$ns run
