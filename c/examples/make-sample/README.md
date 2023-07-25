# Hello Make
## Download Makefile
Before downloading Makefile, set a variable `TARGET_NAME`.
```sh
TARGET_NAME='your target name'
```
To download `Makefile for a binary project`, run:
```sh
curl -fsSL 'https://raw.githubusercontent.com/hansung080/study/master/c/examples/make-sample/bin.mk' | sed "s/make-sample/${TARGET_NAME:-change-me}/g" > "Makefile"
```
Or, to download `Makefile for a library project`, run:
```sh
curl -fsSL 'https://raw.githubusercontent.com/hansung080/study/master/c/examples/make-sample/lib.mk' | sed "s/make-sample/${TARGET_NAME:-change-me}/g" > "Makefile"
```