You must run the program as administrator


Goal: Write a program capable of accomplishing certain objectives.

Objectives: 
*Blocking a specified ip
*Blocking a specified group of ip's
*Defence against unwanted and harmful connections


ChangeLog:
Java with netsh warp : 
  *blocking/unblocking ethernet connection - deprecated
-release 5/11/2015
  C++ with Windows Firewall API : unblocking/blocking connection to chosen ip(habrahabr.ru aka 178.248.233.33)
-release 12/11/2015
  *massive bug fixes
  +sniffer
  +blocking and unblocking inputed ip
  +test gui
-release 19/11/2015
  *fixed bugged unblocking of ip range
  -commented sniffer - raw socket is inconvenient to work with
  +active tcp connections review
  +when user tries to unblock a certain ip from a blocked range it is properly unblocked and other ips from range stay  untouched
  TODO put the code in order (it's really nasty)
  TODO add similar option as the last one but for ip ranges (partly unblock ip range) - almost done
