#!/usr/bin/expect

##-------------------------------------------------------------------
## Recommended to use it with permission 700 (chmod 700 scriptname)
##-------------------------------------------------------------------

set username "user"
set pw [open "/p" r]
set password [read $pw]

spawn ssh [lindex $argv 0]

expect {
"*(yes/no)*" {
send "yes\n"
exp_continue
}		
"*?assword:*" {
send "$password\r"
interact
exit
}
-re "FATAL*|no hostkey alg" {
	spawn telnet [lindex $argv 0]
		expect {
			"?sername:" {
			send "$username\n"
			exp_continue
			}
			"?ogin:*" {
			send "$username\n"
			exp_continue
			}
			"*?assword:*" {
			send "$password\n"
			interact 
			exit
			exp_continue
				}
				}
				}	
}
