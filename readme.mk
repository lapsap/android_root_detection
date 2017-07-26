# Android Ndk root detection

### intro
Using android ndk(c++) to determine if the phone is rooted.
The jni function is a boolean function named isRooted(). 

### Methods used to determine
1. busybox
  * try to execute busybox(need root to install busybox)
2. which su
  * execute 'which su', if we get a path, that means it may be rooted
3. package manager
  * find packages that are usually installed after rooting the phone
4. path
  * find comman path of root files 
5. build-tag
  * check build tag
