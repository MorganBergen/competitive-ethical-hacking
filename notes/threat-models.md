#  introduction

####  what is security?  
achieving some goal in the presence of an adversary  

many systems are connected to the internet, which has adversaries.  thus, design of many systems might need to address security, i.e. will the system work when there's an adversary?

####  high level plan for thinking about security

policy -  the goal you want to achieve e.g. only alice should read file `x`

common goals -  confidentiality, integrity, availability

threat model -  assumptions about what the attacker could do e.g. can guess passwords, cannot physically grab file server.  better to err on the side of assuming attacker can do something.

mechanism -  knobs that your system provides to help upload policy e.g. user accounts, passwords, file permissions, encryption, etc.

resulting goal -  no way for adversary within threat model to violate policy, note that goal has nothing to say about mechanism

####  why is security hard?  negative goal

need to guarantee policy, assuming the threat model  
difficult to think of all possible ways that attacker might break in  
realistic threat models are open ended (almost negative models)  
contrast -  easy to check whether a positive goal is upheld, e.g. alice can actually read file `x`  
weakest link matters  
iterative process -  design, update threat models as necessary, etc.  

what's the point of we can't achieve perfect security?  the boundary line of each system to see when it breaks.  each system will likely have some breaking point leading to compromise.  doesn't necessarily mean the system is not useful depends on context.  it's important to understand what a system can do, and what a system cannot.

in reality, must manage security risk vs. benefit.  
more secure systems means less risk or consequences of some compromises.  
insecure system may require manual auditing to check for attacks, etc.  
higher cost of attack means more adversaries will be deterred

better security often makes new functionality practical and safe.  suppose you want to run some application on your system.  large companies sometimes prohibit users from installing software that hasn't been approved on their desktops, partly due to security.  javascript in the browser is isolated, making it okay for the most part to run new code / applications without manual inspection / approval or virtual machines, or native client, or better os isolation mechanism.  similarly, vpns make it practical to mitigate risk of allowing employees to connect to a corporate network from anywhere on the internet.

what goes wrong #1 -  problems with the policy examples

[sarah palin's email policy](https://en.wikipedia.org/wiki/Sarah_Palin_email_hack)

##  case studies

buffer overflows

consider a web server.  often times the web server's code is responsible for security e.g. checking which urls can be accessed, checking ssl client certs, etc.  thus, bugs in the server's code can lead to security compromises.

threat model policy

assume that adversary can connect to web server, supply any inputs  
policy is a bit fuzzy -  only perform operations intended by programmer  
e.g. don't want adversary to steal data, bypass checks, install backdoors  

web server

```cpp
int read_req(void) {

    char buf[128];
    int i;

    gets(buf);
    i = atoi(buf);
    
    return i;
}
```

buffer overflow vulnerability is a simplified c program.  the code example highlights how improper handling of user input (`gets` function) can lead to overwriting memory, enabling adversaries to manipulate program behavior.

environment requires - mac, gcc compiler, gdb debugger


```c
#include <stdio.h>
#include <stdlib.h>

int read_req(void) {
    char buf[128];
    int i;
    gets(buf);  //  dangerous function
    i = atoi(buf);
    return i;
}

int main(void) {
    read_req();
    return 0;
}
```

```bash
❯ gcc -o readreq readreq.c
readreq.c:19:5: warning: 'gets' is deprecated: This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of gets(3), it is highly recommended that you use fgets(3) instead. [-Wdeprecated-declarations]
   19 |     gets(buf);  //  dangerous function
      |     ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/_stdio.h:257:1: note: 'gets' has been explicitly marked deprecated here
  257 | __deprecated_msg("This function is provided for compatibility reasons only.  Due to security concerns inherent in the design of gets(3), it is highly recommended that you use fgets(3) instead.")
      | ^
/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/sys/cdefs.h:218:48: note: expanded from macro '__deprecated_msg'
  218 |         #define __deprecated_msg(_msg) __attribute__((__deprecated__(_msg)))
      |                                                       ^
1 warning generated.
```