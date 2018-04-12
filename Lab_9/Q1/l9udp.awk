BEGIN {
sent=0;
received=0;
}
{
  if($1=="s" && $7=="cbr" && $3== "_0_")
   {
    sent++;
   }
  else if($1=="r" && $7=="cbr" && $3== "_1_")
   {
     received++;
   }
 
}
END{
 printf " Packet Sent:%d",sent;
 printf "\n Packet Received:%d",received;
 printf "\n Packet Delivery Ratio:%.2f\n",(received/sent)*100;

}

