BEGIN {
recv=0
}
{
event=$1
pkt_size=$5
if(event=="r" && pkt_size>40){
recv++
}
}
END{
printf("recv=%d",recv)
}

