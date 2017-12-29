#!/usr/bin/python

# Reference Implementation

f = open("/etc/passwd")

users = {}
for l in f:
    fields  = l.split(":");
    users[fields[0]] = l;
    print l,
    
print "-"*50    
print users["sshd"],
print "-"*50    

    
