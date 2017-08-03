# Android Ndk root detection & Anti-Debugging

### intro
Using android ndk(c++) to determine if the phone is rooted.
The jni function is a boolean function named isRooted(). 

### Methods used to determine
## Root Detection
1. which su
  * execute 'which su', if we get a path, that means it may be rooted
2. package manager
  * find packages that are usually installed after rooting the phone
3. path
  * find comman path of root files 
4. build-tag
  * check build tag

## Anti-Debugging
1. Check if is in debugging mode
2. Check /proc/self/status and see if TracerPid != 0
3. Check Packages
